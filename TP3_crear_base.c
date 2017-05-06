/*ver como hacer la fecha
	
		if (strptime(csvfields[FECHA_FIELD_POS],"%D", &fecha_struct)==NULL){
			
				del_book_array(&book,&used_size);
				
				del_str_array(&csvfield,&n);
				
				fclose(fi);
				fclose(fo);
			
				return EXIT_FAILURE;
		}
		else{
		
			book[used_size].fecha=mktime(&fecha_struct);
		}
		
		*/
		
#include <stdio.h>
#include <stdlib.h>
#include macros.h
#include constantes.h
#include <time.h>

typedef enum {ST_OK,ST_ERROR} t_status;

typedef struct tm {
	int tm_mday;
	int tm_mon;
	int tm_year;
	} date_t;
	
typedef struct libro {
	
	long id;
	char[MAX_STR] titulo;
	char[MAX_STR] autor;
	char[MAX_STR] director;
	date_t fecha;														
	double puntaje;
	size_t reviews;
	
} book_t;

t_status split(const char *s, char delim, char ***csvfields, size_t *l);

int main(int argc, char *argv[]){
	
	book_t *book,*aux;
	size_t used_size, alloc_size;
	char **csvfields;
	char *endptr;
	char line[MAX_STR];            /*Defino las variables*/
	FILE *fi, *fo;
	t_status st;
	
	if(argc!=CANT_ARGUMENTOS){ 
		
		fprintf (stderr, "%s:%s",MSJ_ERROR,MSJ_ERROR_NOMEM);
		return EXIT_FAILURE;
	}
	
	fo= fopen(*argv[ARG_POS_2], "wb+");                       /*Abro los archivos que necesito*/
	fi= fopen(*argv[ARG_POS_1], "rt+");
	
	if((book =(book_t *)calloc(INIT_CHOP,sizeof(book_t)))=!NULL){                /*Verifico que el espacio que necesito este disponible*/
		
		fprintf (stderr, "%s%s",MSJ_ERROR,MSJ_ERROR_NOMEM);
		
		fclose(fi);
		fclose(fo);
		
		return EXIT_FAILURE;
	}
	
	used_size=0;                           
	alloc_size = INIT_CHOP;
	
	while(fgets(line, MAX_STR,fi)!=NULL){       
		
		if((endptr=strchr(line, '\n'))!=NULL) *endptr='\0';  
		
		if ((st=split(line,',',&csvfields,&n))!=ST_OK){            
				
			handle_error(st);
			
			del_book_array(&book,&used_size);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
		
		if(used_size==alloc_size){                                                                          
			
			if((aux=(libro_t*)realloc((libro, calloc_size + CHOP_SIZE)*sizeof(libro_t)))==NULL){   
					
				fprintf();
				
				del_book_array(&book,&used_size);
				
				del_str_array(&csvfield,&n);
				
				fclose(fi);
				fclose(fo);
			
			return EXIT_FAILURE;
				
			}
			
			alloc_size=CHOP_SIZE;  
			book=aux;
		}
		
		
		book[used_size].id = strtol(csv_fields[ID_FIELD_POS],&endptr,0);
		
		if(*endptr!='0'){   /*Si endptr no apunta a una casilla con el caracter de una terminacion de un string, habia algo mal*/
			
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(&csvfield,&n);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
		
		strcopy(book[used_size].titulo,csvfields[TITULO_FIELD_POS]);
		strcopy(book[used_size].autor,csvfields[AUTOR_FIELD_POS]);
		strcopy(book[used_size].genero,csvfields[GENERO_FIELD_POS]);
		
		if((make_date(csvfields[DATE_FIELD_POS], book[used_size].fecha))!=OK){
			
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(&csvfield,&n);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
		
		book[used_size].puntaje = strtol(csv_fields[PUNTAJE_FIELD_POS],&endptr,0);
		
		if(*endptr!='0'){   /*Si endptr no apunta a una casilla con el caracter de una terminacion de un string, habia algo mal*/
			
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(&csvfield,&n);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
		
		book[used_size].reviews = strtol(csv_fields[REVIEWS_FIELD_POS],&endptr,0);
		
		if(*endptr!='0'){   /*Si endptr no apunta a una casilla con el caracter de una terminacion de un string, habia algo mal*/
			
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(&csvfield,&n);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
 		}
		
		del_str_array(&csvfield,&n);
		
		used_size++;
		
		if(fwrite(book, sizeof(book_t), used_size,fo)!=used_size){         
			
			fprintf (stderr,"%s",MSJ_ERROR,MSJ_ERROR_);
			
			del_book_array(&book,&used_size);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
	}
	
t_status del_book_array(book_t **book, size_t *n){       /*No se que utilidad tiene devolver el estado con esta funcion ni con del_str_array, no se usan en el main los estados que devuelve*/
	
	if (book==NULL) return ST_ERROR;
	
	free (*book);
	
	*book=NULL;
	*n=0;
	
	return ST_OK;   /*no faltaria un else aca?*/
}

		
t_status del_str_array(char **s_array, size_t *l){
	
	size_t i;
	
	for(i=0;i<l;i++){
		
		free (s_array[i]);
		s_array[i]=NULL;
	}
	
	free(s_array);
	
	return ST_OK;
}

t_status split(const char *s, char delim, char ***strarray, size_t *l){
	
	char **cadenas;
	size_t n, i;
	char *campo;
	char *aux;
	char *linea;
	char sdelim[2];
	
	if(s==NULL||strarray==NULL||l==NULL) return ERROR_NULL_PTR;
	
	for(n=1,i=0;s[i];i++){
		
		if(s[i]==delim)n++;
	}
	
	if((cadenas==(char **)malloc(n*sizeof(char*)))==NULL){
	
		return ERROR_NO_MEMORIA;
	}
	
	if((linea=strdup(s))==NULL){
		free(cadenas);
		return ERROR_NO_MEM;
	}
	sdelim[0]=',';
	sdelim[1]='\0';
	/*strtok divide el cvs en tokens*/
	for(i=0, aux=linea; (campo=strtok(aux,sdelim))!=NULL; i++, aux=NULL){
		if((cadenas[i]=strdup(campo))==NULL){
			free(linea);
			del_str_array(cadenas, i);
			*del_str_array=NULL;
			*l=0;
			return ERROR_NO_MEMORIA;
			}
	}
	free(linea);/*duplicado liberado*/
	*linea=i;
	*str_array=cadenas;
	return OK;
}

t_status make_date(char *str_fecha, t_book *fecha){
		
	char **aux_fecha;
	char fec_delim[2];
	char *t_fecha;
	/*smax es el umero de caracteres del campo, supongo que deberian ser 10 de dd/mm/yyyy*/
	if(strftime(str_fecha, smax, "%d/%m/%Y", fecha)!=smax) return ERROR_FECHA;
	
	




