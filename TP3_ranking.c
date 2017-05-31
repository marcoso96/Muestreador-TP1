#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "TP3_constantes.h"
#include "TP3_macros.h"

typedef enum {ST_OK,ST_ERROR} t_status;
	
typedef struct book {
	
	long id;
	char titulo[MAX_STR];
	char autor[MAX_STR];
	char genero[MAX_STR];
	struct tm *fecha;														
	double puntaje;
	size_t reviews;
	
} book_t;

typedef enum {ALTA, BAJA, MODIFICACION} t_operacion;

t_status realizar_baja(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size);
t_status realizar_modificacion(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size);
t_status realizar_alta(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size);
t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **errorfile, FILE **arrangefile, t_operacion * st_op);
int count_lines (FILE *arrangefile);
void close_all_files (FILE *database,FILE *log,FILE *arrangefile);

int main(int argc, char *argv[]){


	FILE *database;
	FILE *log;
	FILE *arrangefile;
	FILE *temporal;
	
	temporal=tmpfile();
	
	int cant_lineas;
	t_status st;
	t_operacion st_op;
	
	if ((st=validar_argumentos(argc, argv, &database, &log, &arrangefile, &st_op))!=ST_OK){ 
	
		fprintf(log, "%s:%s\n", MSJ_ERROR, MSJ_ERROR_ARG);
		
		close_all_files(database,log,arrangefile);
		
		return EXIT_FAILURE;
	}

	cant_lineas=count_lines(arrangefile);		
								

	switch (st_op){
		
		case BAJA:
						
				st=realizar_baja(temporal, database, log, arrangefile, cant_lineas);
		
				break; 
		
		case ALTA:
				
				st=realizar_alta(temporal, database, log, arrangefile, cant_lineas);
		
				
				break; 
		
		case MODIFICACION:

				st=realizar_modificacion(temporal, database, log, arrangefile, cant_lineas);
		
				break;
		
	}

	fopen(argv[DATABASE_ARGV_POS], "w");
	/*RENOMBRAR EL ARCHIVO TEMPORAL*/
	close_all_files(database,log,arrangefile);

	return EXIT_FAILURE;

}
	

t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **log, FILE **arrangefile, t_operacion *st_op){

	if (argc!=ARG_FUNC || 
	(*database=fopen(argv[DATABASE_ARGV_POS],"a+"))==NULL ||
	(*log=fopen(argv[LOG_ARGV_POS],"w"))==NULL ||
	(*arrangefile=fopen(argv[ARRANGEFILE_ARGV_POS],"r+"))==NULL){
	
		return ST_ERROR;
	}
	
	if((strcmp(argv[ARGV_OP],OP_ALTA))==0) *st_op=ALTA;
	
	else{ 
		
		if((strcmp(argv[ARGV_OP],OP_BAJA))==0) *st_op=BAJA;
		
		else{ 
			
			if((strcmp(argv[ARGV_OP],OP_MODIFICACION))==0) *st_op=MODIFICACION;
			
			else return ST_ERROR;
		}
	}
	
	return ST_OK;
	
}	

int count_lines (FILE *arrangefile){ 
	
	int lines=0;
	int aux;
			
	while((aux=fgetc(arrangefile))!=EOF){
			
		if (aux=='\n') lines++; 
		
	}
	return lines;
}

void close_all_files (FILE *database,FILE *log,FILE *arrangefile){
	
	fclose(database);
	fclose(log);
	fclose(arrangefile);
	
	return ;	
}


t_status realizar_baja(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	size_t arrange_count;
	
	fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	
	while(fread(&db_book, sizeof(book_t), SINGLE_CONST, database)!=SINGLE_CONST){
		
		if(db_book.id<arrange_book.id){
			
			fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			if((fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange))!=SINGLE_CONST){
				
				arrange_count++;
				continue;
			}
			else break;
		}	
	}
	
	while(fread(&db_book, sizeof(book_t), SINGLE_CONST, database)!=SINGLE_CONST){
		
		fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
	
	}
	
	if(arrange_count!=arr_size){
		
		fprintf(log, "%s", MSJ_ERROR_BAJA);
		
	}
	
	return ST_OK;
		
}
	
t_status realizar_modificacion(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	size_t arrange_count=SINGLE_CONST;
	
	fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	
	while(fread(&db_book, sizeof(book_t), SINGLE_CONST, database)!=SINGLE_CONST){
		
		if(db_book.id<arrange_book.id){
			
			fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			fwrite(&arrange_book, sizeof(book_t), SINGLE_CONST, temporal);
			if((fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange))!=SINGLE_CONST){
			
				arrange_count++;
				continue;
			}
			
			else break;
		}
	}
	
	while((fread(&db_book, sizeof(book_t), SINGLE_CONST, database))!=SINGLE_CONST){
		
		fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
	
	}
			
	if(arrange_count!=arr_size){
		
		fprintf(log, "%s", MSJ_ERROR_MODIFICACIONES);
	}

	return ST_OK;
}

t_status realizar_alta(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	size_t arrange_count=1;
	
	fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	
	while(fread(&db_book, sizeof(book_t), SINGLE_CONST, database)!=SINGLE_CONST){
		
		if(db_book.id<arrange_book.id){
			
			fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			fprintf(log, "%s:%ld\n", MSJ_ERROR_ALTA, db_book.id);
			fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			if((fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange))!=SINGLE_CONST){
			
				arrange_count++;
				continue;
			}
			
			else break;
		}
		
		if(db_book.id>arrange_book.id){
			
			fwrite(&arrange_book, sizeof(book_t), SINGLE_CONST, temporal);
			arrange_count++;	
			
			if((fread(&arrange_book, sizeof(book_t), SINGLE_CONST, arrange))!=SINGLE_CONST){
			
				arrange_count++;
				continue;
			}
			
			else break;
		}
				
	}
	
	while(fread(&db_book, sizeof(book_t), SINGLE_CONST, database)!=SINGLE_CONST){
		
		fwrite(&db_book, sizeof(book_t), SINGLE_CONST, temporal);
	
	}
			
	if(arrange_count!=arr_size){
		
		fprintf(log, "%s", MSJ_ERROR_ALTA);
	}
	
	return ST_OK;
}
