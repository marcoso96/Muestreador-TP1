#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "crearbase_macros.h"
#include "crearbase_constantes.h"


typedef enum {ST_ERROR_ARG, ST_OK, ST_ERROR_LINE, ST_ERROR_FILE, ST_ERROR_WRITE, ST_ERROR_NULL_PTR, ST_ERROR_NO_MEMORIA  ,ST_ERROR} t_status;
	
typedef struct libro {
	
	long id;
	char titulo[MAX_TITLE] ;
	char autor[MAX_AUTOR] ;
	char genero[MAX_GENERO];
	/*struct tm *fecha;*/														
	double puntaje;
	size_t reviews;
	
} book_t;

char * strdup(const char *s);
t_status split(char *linea, char delim, char ***csvfields, size_t *nro_campos);
void handle_error(t_status st);
t_status del_str_array(char **s_array, size_t l);
t_status del_book_array(book_t **book, size_t *n);
/*	
int main(void){
	char ** csvfields;
	char line[MAX_LINE];
	size_t n, i;
	char *endp;


	fgets(line, MAX_LINE, stdin);
	if((endp=strchr(line, '\n'))!=NULL) *endp='\0';
	
	split(line, ',', &csvfields, &n);
	
	for(i=0; i< n; i++){
		fprintf(stderr, "|%s|\n", csvfields[i]);
	}
	
	for(i=0; i< n; i++){
		free(csvfields[i]);
	}
	free(csvfields);
	return EXIT_SUCCESS;
}*/
	
int main(int argc, char *argv[]){
	
	book_t *book=NULL;
	book_t *aux=NULL;
	size_t used_size, alloc_size, nro_campos;
	char **csvfields=NULL;
	char *endptr=NULL;
	char line[MAX_LINE];            
	FILE *fi=NULL, *fo=NULL;
	t_status st;
	
	if(argc!=CANT_ARGUMENTOS){ 
		fprintf (stderr, "%s:%s",MSJ_ERROR,MSJ_ERROR_ARG);
		return EXIT_FAILURE;
	}
		
	if((fo=fopen(argv[ARG_POS_2], "w+"))==NULL){
		
		st=ST_ERROR_FILE;
		handle_error(st);
		
		return EXIT_FAILURE;
		
	}
	
	if((fi= fopen(argv[ARG_POS_1], "r+"))==NULL){
		
		fprintf (stderr, "%s:%s",MSJ_ERROR,MSJ_ERROR_FILE);
		fclose(fo);
		
		return EXIT_FAILURE;
		
	}
	
	if((book=(book_t *)calloc(INIT_CHOP, sizeof(book_t)))==NULL){                /*Verifico que el espacio que necesito este disponible*/
		
		st=ST_ERROR_NO_MEMORIA;
		handle_error(st);
		
		fclose(fi);
		fclose(fo);
		
		return EXIT_FAILURE;
	}
	
	used_size=0;                           
	alloc_size = INIT_CHOP;
	
	while(fgets(line,MAX_LINE,fi)!=NULL||!feof(fi)){
		
		if((endptr=strchr(line, '\n'))!=NULL) *endptr='\0';

		
		if ((st=split(line,',', &csvfields,&nro_campos))!=ST_OK){            
				
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(csvfields, FIELD_NUM);
			
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}

		if (nro_campos != 6) continue; /*fuerza el proximo ciclo*/
		
		fprintf(stderr, "NRO_CAMPOS: %lu\n", nro_campos);
		
		if(used_size==alloc_size){                                                                          
			
			if((aux=(book_t *)realloc(book, (alloc_size + CHOP_SIZE)*sizeof(book_t)))==NULL){   
					
				st=ST_ERROR_NULL_PTR;
				
				handle_error(st);
				
				del_book_array(&book,&used_size);
				del_str_array(csvfields,FIELD_NUM);
		
				fclose(fi);
				fclose(fo);
			
				return EXIT_FAILURE;	
			}
			
			alloc_size+=CHOP_SIZE;  
			book=aux;
			del_book_array(&aux, &used_size);
		}
		
		/*pegado a struct book*/
		
		book[used_size].id = strtol(csvfields[ID_FIELD_POS],&endptr, 10);
		strcpy(book[used_size].titulo,csvfields[TITULO_FIELD_POS]);
		strcpy(book[used_size].autor,csvfields[AUTOR_FIELD_POS]);
		strcpy(book[used_size].genero,csvfields[GENERO_FIELD_POS]);
		
		/*memset(book[used_size].fecha, 0, sizeof(struct tm));
		strptime(csvfields[FECHA_FIELD_POS], "%d/%m/%Y", book[used_size].fecha);*/	
		book[used_size].puntaje = strtod(csvfields[PUNTAJE_FIELD_POS],&endptr);
		book[used_size].reviews = strtol(csvfields[REVIEWS_FIELD_POS],&endptr,10);
		
		del_str_array(csvfields,nro_campos);
		used_size++;

		if(fwrite(book, sizeof(book_t),1,fo)!=used_size){         
			
			st=ST_ERROR_WRITE;
			handle_error(st);

			del_book_array(&book,&used_size);
			del_str_array(csvfields, FIELD_NUM);	
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
	}
	
	fclose(fi);
	fclose(fo);
	
	del_book_array(&book,&used_size);		
	del_str_array(csvfields, FIELD_NUM);
	
	return EXIT_SUCCESS;
}


t_status del_book_array(book_t **book, size_t *n){       /*No se que utilidad tiene devolver el estado con esta funcion ni con del_str_array, no se usan en el main los estados que devuelve*/
	
	int i;
	
	if (book==NULL) return ST_ERROR_NULL_PTR;
	
	for(i=0; i<*n; i++){
		
		free (book[i]);
	}
	*book=NULL;
	*n=0;
	
	return ST_OK;   
}

t_status del_str_array(char **s_array, size_t l){
	
	size_t i;
	
	for(i=0;i<l;i++){
		
		free (*(s_array+i));
		*(s_array+i)=NULL;
	}
	
	free(s_array);
	
	return ST_OK;
}

t_status split(char linea[MAX_LINE], char delim, char ***strarray, size_t *nro_campos){
	
	size_t n, i;
	char *campo=NULL;
	char *lin_aux=NULL, *aux=NULL;
	char sdelim[2]={delim , '\0'};
		
	if(linea==NULL||strarray==NULL) return ST_ERROR_NULL_PTR;
	
	for(n=1,i=0;linea[i];i++){
		
		if(linea[i]==delim) n++;
	}
	
	lin_aux=strdup(linea);
	
	if((*strarray=(char **)malloc(n*sizeof(char*)))==NULL){
			
			return ST_ERROR_NO_MEMORIA;
	}
	
	for(i=0, aux=lin_aux; (campo=strtok(aux,sdelim))!=NULL; i++, aux=NULL){
		
		if(((*strarray)[i]=strdup(campo))==NULL){
			
			free(lin_aux);
			*nro_campos=0;
			return ST_ERROR_NO_MEMORIA;
		}
		
	}
	
	*nro_campos=n;
	free(lin_aux);
		
	return ST_OK;
}


char * strdup(const char *s){
	char *s_dup;
	
	s_dup=malloc(strlen(s)+1);
	
	strcpy(s_dup, s);
	return s_dup;
}

void handle_error(t_status st){
	
	switch(st){
		
		case ST_ERROR:
				
				fprintf(stderr, "%s", MSJ_ERROR);
				break;
		case ST_ERROR_ARG:		
				
				fprintf(stderr, "%s", MSJ_ERROR_ARG);
				break;
				
		case ST_ERROR_NO_MEMORIA:	
				
				fprintf(stderr, "%s", MSJ_ERROR_NOMEM);
				break;
		case ST_ERROR_NULL_PTR:
				
				fprintf(stderr, "%s", MSJ_ERROR_NULL_PTR);
				break;
		case ST_ERROR_WRITE:
				
				fprintf(stderr, "%s", MSJ_ERROR_WRITE);
				break;
		case ST_ERROR_FILE:
				
				fprintf(stderr, "%s", MSJ_ERROR_FILE);
				break;
		default:
				break;
		
	}
}

