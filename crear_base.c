#include <stdio.h>
#include <stdlib.h>
#include "crearbase_macros.h"
#include "crearbase_constantes.h"
#include <time.h>
#include <string.h>

typedef enum {ST_OK, ST_ERROR_FILE, ST_ERROR_WRITE, ST_ERROR_NULL_PTR, ST_ERROR_NO_MEMORIA ,ST_ERROR} t_status;
	
typedef struct libro {
	
	long id;
	char titulo[MAX_STR] ;
	char autor[MAX_STR] ;
	char genero[MAX_STR];
	/*struct tm *fecha;*/														
	double puntaje;
	size_t reviews;
	
} book_t;

char * strdup(const char *s);
t_status split(char *linea, char delim, char **csvfields, size_t *l);
void handle_error(t_status st);
t_status del_str_array(char **s_array, size_t l);
t_status del_book_array(book_t **book, size_t *n);

int main(int argc, char *argv[]){
	
	book_t *book;
	book_t *aux;
	size_t used_size, alloc_size, n, i;
	char **csvfields=(char **)malloc(sizeof(char *));
	char *endptr=(char*)malloc(sizeof(char));
	char *line=malloc(sizeof(char)*MAX_STR);            /*Defino las variables*/
	FILE *fi, *fo;
	t_status st;
	
	if(argc!=3){ 
		
		fprintf (stderr, "%s:%s",MSJ_ERROR,MSJ_ERROR_NOMEM);
		return EXIT_FAILURE;
	}
		
	fo= fopen(argv[ARG_POS_2], "w+");                       /*Abro los archivos que necesito*/
	fi= fopen(argv[ARG_POS_1], "r+");
	
	if((book=malloc(sizeof(book_t)))==NULL){                /*Verifico que el espacio que necesito este disponible*/
		
		st=ST_ERROR_NO_MEMORIA;
		handle_error(st);
		 
		fclose(fi);
		fclose(fo);
		free(*csvfields);
		free(csvfields);
		return EXIT_FAILURE;
	}
	
	used_size=0;                           
	alloc_size = INIT_CHOP;
	
	while(fgets(line,MAX_STR,fi)!=NULL){      /*NULL si hay error o fin de archivo*/ 
		
		if((endptr=strchr(line, '\n'))!=NULL) *endptr='\0';  
		
		for(i=0; i<FIELD_NUM; i++){
	
		
			if((*(csvfields+i)=(char *)malloc(sizeof(char)*MAX_STR))==NULL){
					
					st=ST_ERROR_NO_MEMORIA;
					handle_error(st);
					free(endptr);
					fclose(fi);
					fclose(fo);
					free(*csvfields);
					free(csvfields);
					return EXIT_FAILURE;
			}
		
		}
		
		if ((st=split(line,',',csvfields,&n))!=ST_OK){            
				
			handle_error(st);
			
			del_book_array(&book,&used_size);
			free(endptr);
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
			}
		
		if(used_size==alloc_size){                                                                          
			
			if((aux=(book_t *)realloc(book, (alloc_size + CHOP_SIZE)*sizeof(book_t)))==NULL){   
					
				st=ST_ERROR_NO_MEMORIA;
				
				handle_error(st);
				
				del_book_array(&book,&used_size);
				
				del_str_array(csvfields,n);
				free(endptr);
				fclose(fi);
				fclose(fo);
			
			return EXIT_FAILURE;
				
			}
			
			alloc_size=CHOP_SIZE;  
			book=aux;
			}
		
		if(*endptr!='\0'){   /*Si endptr no apunta a una casilla con el caracter de una terminacion de un string, habia algo mal*/
			
			st=ST_ERROR_WRITE;
			handle_error(st);
			
			del_book_array(&book,&used_size);
			del_str_array(csvfields,n);
			free(endptr);
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
			}
		
		book[used_size].id = strtol(*(csvfields+ID_FIELD_POS),&endptr,0);
		
		strcpy(*book[used_size].titulo,*(csvfields+TITULO_FIELD_POS));
		strcpy(*book[used_size].autor,*(csvfields+AUTOR_FIELD_POS));
		strcpy(*book[used_size].genero,*(csvfields+GENERO_FIELD_POS));
		
		/*strptime(csvfields[FECHA_FIELD_POS], "%d/%m/%Y", book[used_size].fecha);*/	
		
		book[used_size].puntaje = strtod(*(csvfields+PUNTAJE_FIELD_POS),&endptr);
	
		book[used_size].reviews = strtol(*(csvfields+REVIEWS_FIELD_POS),&endptr,0);
		
		del_str_array(csvfields,n);
		
		used_size++;
		
		if(fwrite(book, sizeof(book_t),1,fo)!=used_size){         
			
			st=ST_ERROR_WRITE;
			handle_error(st);
			
			free(endptr);
			del_book_array(&book,&used_size);
			fclose(fi);
			fclose(fo);
			
			return EXIT_FAILURE;
			}
	}
	fclose(fi);
	fclose(fo);
	free(aux);
	free(book);
	for(i=0;i<used_size;i++) free(*(csvfields+i));
	free(csvfields);
	return EXIT_SUCCESS;
}	
t_status del_book_array(book_t **book, size_t *n){       /*No se que utilidad tiene devolver el estado con esta funcion ni con del_str_array, no se usan en el main los estados que devuelve*/
	
	if (book==NULL) return ST_ERROR_NULL_PTR;
	
	free (*book);
	
	*book=NULL;
	*n=0;
	
	return ST_OK;   /*no faltaria un else aca?*/
}

		
t_status del_str_array(char **s_array, size_t l){
	
	size_t i;
	
	for(i=0;i<l;i++){
		
		free (s_array[i]);
		s_array[i]=NULL;
	}
	
	free(s_array);
	
	return ST_OK;
}

t_status split(char *linea, char delim, char **strarray, size_t *l){
	
	char **cadenas;
	size_t n, i;
	char *campo=malloc(sizeof(char)*MAX_STR);
	char *lin_aux=malloc(sizeof(char)*strlen(linea)+1);
	char sdelim[2];
	
	if(linea==NULL||strarray==NULL||l==NULL) return ST_ERROR_NULL_PTR;
	
	for(n=1,i=0;*(linea+i);i++){
		
		if(*(linea+i)==delim) n++;
		}
	
	if((cadenas=(char **)malloc(n*sizeof(char*)))==NULL){
	
		return ST_ERROR_NO_MEMORIA;
	}
	
	if((lin_aux=strdup(linea))==NULL){ /*duplico la linea*/
		
		free(cadenas);
		return ST_ERROR_NO_MEMORIA;
	}
	
	sdelim[0]=',';
	sdelim[1]='\0';
	/*strtok divide el cvs en tokens*/
	
	for(i=0;(campo=strtok(lin_aux,sdelim))!=NULL; i++, lin_aux=NULL){
		
		if((*(cadenas+i)=(char*)malloc(sizeof(char)*(strlen(campo)+1)))==NULL){
			
			free(lin_aux);
			free(campo);
			del_str_array(cadenas, i);
			*l=0;
			return ST_ERROR_NO_MEMORIA;
			}
			*(cadenas+i)=strdup(campo);
		}
		
	free(lin_aux);/*duplicado liberado*/
	lin_aux=NULL;
	
	for(i=0; i<FIELD_NUM; i++){
		
		*(strarray+i)=*(cadenas+i);
	
	}	
	
	return ST_OK;
}

void handle_error(t_status st){
	
	switch(st){
		
		case ST_ERROR:
				
				fprintf(stderr, "%s", "Error");
				break;
				
		case ST_ERROR_NO_MEMORIA:	
				
				fprintf(stderr, "%s", "Error de memoria");
				break;
		case ST_ERROR_NULL_PTR:
				
				fprintf(stderr, "%s", "Error de puntero nulo");
				break;
		case ST_ERROR_WRITE:
				
				fprintf(stderr, "%s", "Error de escritura");
				break;
		case ST_ERROR_FILE:
				
				fprintf(stderr, "%s", "Error de archivo");
				break;
		default:
				break;
		
	}
}

char * strdup(const char *s){
	char *s_dup;
	s_dup=malloc((strlen(s)+1));
	strcpy(s_dup, s);
	return s_dup;
}

	

