#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cb_macros.h"
#include "cb_constantes.h"


typedef enum {ST_ERROR_ARG, ST_OK, ST_ERROR_LINE, ST_ERROR_FILE, ST_ERROR_WRITE, ST_ERROR_NULL_PTR, ST_ERROR_NO_MEMORIA  ,ST_ERROR} t_status;
	
typedef struct libro {
	
	long id;
	char titulo[MAX_TITLE] ;
	char autor[MAX_AUTOR] ;
	char genero[MAX_GENERO];
	struct tm fecha;														
	double puntaje;
	size_t reviews;
	
} book_t;

char * strdup(const char *s);
t_status split(char *linea, char delim, char ***csvfields, size_t *nro_campos);
void handle_error(t_status st);
t_status del_str_array(char ***s_array, size_t l);
t_status del_book_array(book_t **book, size_t *n);
	
int main(int argc, char *argv[]){
	
	book_t *book=NULL;
	size_t used_size, alloc_size, nro_campos, fecha_campos;
	char **csvfields=NULL;
	char **fechafields=NULL;
	
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
	
	while(fgets(line,MAX_LINE,fi)!=NULL){
		
		if((endptr=strchr(line, '\n'))!=NULL) *endptr='\0';

		
		if ((st=split(line,DELIM_CSV, &csvfields,&nro_campos))!=ST_OK){            
				
			handle_error(st);
			
			/*del_book_array(&book,&used_size);*/
			del_str_array(&csvfields, FIELD_NUM);	
			free(csvfields);
		
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}

		if (nro_campos != FIELD_NUM){
			
			del_str_array(&fechafields, fecha_campos); /*medio confuso estos dos nombres*/
			del_str_array(&csvfields, nro_campos);
			csvfields=NULL;
			continue; /*fuerza el proximo ciclo*/
		}
		
		if(used_size==alloc_size){                                                                          
			
			if((book=(book_t *)realloc(book, (alloc_size + CHOP_SIZE)*sizeof(book_t)))==NULL){   
					
				st=ST_ERROR_NULL_PTR;
				
				handle_error(st);
				
				free(book);
				del_str_array(&csvfields, FIELD_NUM);	
				csvfields=NULL;
		
				fclose(fi);
				fclose(fo);
			
				return EXIT_FAILURE;	
			}
			
			alloc_size+=CHOP_SIZE;  
		}
		
		book[used_size].id = strtol(csvfields[ID_FIELD_POS],&endptr, 10);
		strcpy(book[used_size].titulo,csvfields[TITULO_FIELD_POS]);
		strcpy(book[used_size].autor,csvfields[AUTOR_FIELD_POS]);
		strcpy(book[used_size].genero,csvfields[GENERO_FIELD_POS]);
		
		/*manejo de fecha*/
		split(csvfields[FECHA_FIELD_POS], DELIM_FECHA, &fechafields, &fecha_campos);
		book[used_size].fecha.tm_year=((int)strtol(fechafields[YEAR_POS], &endptr, 10))-YEAR_ADJUST;
		book[used_size].fecha.tm_mon=((int)strtol(fechafields[MONTH_POS],&endptr, 10))-MONTH_ADJUST;
		book[used_size].fecha.tm_mday=(int)strtol(fechafields[DAY_POS], &endptr, 10);
	
		
		book[used_size].puntaje = strtod(csvfields[PUNTAJE_FIELD_POS],&endptr);
		book[used_size].reviews = strtol(csvfields[REVIEWS_FIELD_POS],&endptr,10);
		
		del_str_array(&fechafields, fecha_campos);
		del_str_array(&csvfields,FIELD_NUM);
		used_size++;
		
	}
	
	if(fwrite(book, sizeof(book_t),used_size,fo)!=used_size){         
			
			st=ST_ERROR_WRITE;
			handle_error(st);
			
			free(book);
			del_str_array(&csvfields, FIELD_NUM);	
			free(csvfields);
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
		}
		
	fclose(fi);
	fclose(fo);
	
	free(book);
	book=NULL;

	return EXIT_SUCCESS;
}

t_status del_str_array(char ***s_array, size_t l){
	
	size_t i;
	
	for(i=0;i<l;i++){
		
		free ((*s_array)[i]);
		(*s_array)[i]=NULL;
	}
	
	free(*s_array);
	*s_array=NULL;
	
	return ST_OK;
}

t_status split(char linea[MAX_LINE], char delim, char ***strarray, size_t *nro_campos){
	
	size_t n, i;
	char *campo=NULL;
	char *lin_aux=NULL, *aux=NULL;
	char sdelim[2];
		
	if(linea==NULL||*linea=='\0'||strarray==NULL) return ST_ERROR_NULL_PTR;
	
	for(n=1,i=0;linea[i];i++){
		
		if(linea[i]==delim) n++;
	}
	
	lin_aux=strdup(linea);
	
	sdelim[0]=delim;
	sdelim[1]='\0';
	
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
	
	s_dup=(char*)malloc(strlen(s)+1);
	
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
