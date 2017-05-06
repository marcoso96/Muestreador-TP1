#include <stdio.h>
#include <stdlib.h>
#include macros.h
#include constantes.h

typedef enum {ST_OK,ST_ERROR} t_status;

typedef struct libro {
	
	long id;
	char[MAX_STR] titulo;
	char[MAX_STR] autor;
	char[MAX_STR] director;
	time_t fecha;														
	double puntaje;
	size_t reviews;
	
} book_t;


int main(int argc, char *argv[]){
	
	book_t *book,*aux;
	size_t used_size, alloc_size;
	char ** csvfields, *endptr, line[MAX_STR];            /*Defino las variables*/
	FILE *fi, *fo;
	t_status st;
	
	fo= fopen("archivo.bin", "w+");                       /*Abro los archivos que necesito*/
	fi= stdin;
	
	if((book =(book_t *)calloc(INIT_CHOP,sizeof(book_t)))==!NULL){                /*Verifico que el espacio que necesito este disponible*/
		
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
		strcopy(book[used_size].director,csvfields[DIRECTOR_FIELD_POS]);
		/*ver como hacer la fecha*/     
		
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
	
