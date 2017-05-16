#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **errorfile, FILE **arrangefile);
int count_lines (FILE *arrangefile);
void close_all_files (FILE *database,FILE *log,FILE *arrangefile);

int main(int argc, char *argv[]){


	FILE *database;
	FILE *log;
	FILE *arrangefile;
	FILE *temporal;
	
	temporal=tmpfile();

	int aux_cant_lineas;
	int cant_lineas;
	
	t_status st;

	book_t *line_arrangefile=(book_t*)malloc(sizeof(book_t));
	book_t *line_database=(book_t*)malloc(sizeof(book_t));
	book_t *standby_line=(book_t*)malloc(sizeof(book_t));
	
	if ((st=validar_argumentos(argc, argv, &database, &log, &arrangefile))!=ST_OK){ 
	
		fprintf(log, "%s:%s\n", MSJ_ERROR, MSJ_ERROR_ARG);
		
		close_all_files(database,log,arrangefile);
		 
		return EXIT_FAILURE;
	}
	
	else{

		cant_lineas=count_lines(arrangefile);		
								
/*BAJA (Asumiendo que los archivos que se reciben tienen registros en orden de menor a mayor y que arrangfile es un archivo con estructuras)*/										
		if(*argv[ARGV_OP]=='B'){
					
				aux_cant_lineas=1;  /*Se supone que el archivo arrangefile no es nulo, asi que por lo menos tiene una linea que dar de baja*/

				fread(line_arrangefile, sizeof(book_t), 1, arrangefile);

				while(!feof(database)){

					fread(line_database, sizeof(book_t), 1, database);

	
					if(line_database->id==line_arrangefile->id){ /*si se ecuentra el mismo id, no escribimos en el temporal esa linea */
		
						if(aux_cant_lineas==cant_lineas){ /*caso en el que se llego al ultimo registro par borrar. Se copia todo lo que queda de database en temporal, y finalmente se llega al endoffile*/
			
							while(!feof(database)){

								fread(line_database, sizeof(book_t), 1, database);   /*Leo la siguiente linea de database ya que la anterior no nos interesa*/
								fwrite(line_database, sizeof(book_t),1,temporal);			
							}	
						}
						else{

							aux_cant_lineas++;
							fread(line_arrangefile, sizeof(book_t), 1, arrangefile);  /*se lee la siguiente linea del arrangefile*/
						}
					}

					else{
			
							fwrite(line_database, sizeof(book_t),1,temporal);
					}
				}

				if (aux_cant_lineas++!=cant_lineas){

					fprintf(log, "%s\n", MSJ_ERROR_BAJA);   /*se llego al EOF antes de que se dieran 
																los registros. esto puede pasar porque los registros no estaban en orden o hay un registro que se queria dar de baja y en realidad no existia en database.*/
				}	
		
		}

/*ALTA*/
		else if(*argv[ARGV_OP]=='A'){
		
			fread(line_arrangefile, sizeof(book_t), 1, arrangefile);
			fread(line_database, sizeof(book_t), 1, database);

			aux_cant_lineas =1;
	
			while(!feof(database)){

				if((line_arrangefile->id) > (line_database->id)){
	
					standby_line=line_database;         /*Guardo la linea anterior de database */
					fread(line_database, sizeof(book_t), 1, database);  /*Leo la siguiente linea de database*/
				
					if((line_arrangefile->id) <= (line_database->id)){   /*Comparo nuevamente, si resulta que el ahora id de arrangefile no supera al de database, entonces es momento de poner el registro da arrangefile en temporal*/
				
						fwrite(line_arrangefile, sizeof(book_t),1,temporal);

						if((line_arrangefile->id) == (line_database->id)) fprintf(log, "%s,%s\n", MSJ_ERROR, MSJ_ERROR_ALTA);

						if(aux_cant_lineas==cant_lineas){
								
							fwrite(standby_line, sizeof(book_t),1,temporal); /*EScribo la linea que guarde y dps guardo el resto*/

							while(!feof(database)){

								fread(line_database, sizeof(book_t), 1, database);   /*Leo la siguiente linea de database ya que la anterior no nos interesa*/
								fwrite(line_database, sizeof(book_t),1,temporal);			
							}
						}
						else{ 

							fread(line_arrangefile, sizeof(book_t), 1, arrangefile); /*ya que todavia quedan registro por agregar, leemos la siguiente linea de arrangefile*/							
							aux_cant_lineas++;
						}
					}
					else{

						fwrite(standby_line, sizeof(book_t),1,temporal);	 /*si resulto que todavia no supera el id, escribimos el registro de*/					
					}

				}
				else{
						fwrite(line_arrangefile, sizeof(book_t),1,temporal);
						
						if((line_arrangefile->id) == (line_database->id)) fprintf(log, "%s,%s\n", MSJ_ERROR, MSJ_ERROR_ALTA);

						if(aux_cant_lineas==cant_lineas){
							
							while(!feof(database)){

								fwrite(line_database, sizeof(book_t),1,temporal);
								fread(line_database, sizeof(book_t), 1, database);			
							}
						}
						else{ 

							fread(line_arrangefile, sizeof(book_t), 1, arrangefile);
							aux_cant_lineas++;
						}
						
				}
			}
		}
/*MODIFICACIONES*/
		else if(*argv[ARGV_OP]=='M'){

				aux_cant_lineas=1;  /*Se supone que el archivo arrangefile no es nulo, asi que por lo menos tiene una linea que dar de baja*/

				fread(line_arrangefile, sizeof(book_t), 1, arrangefile);

				while(!feof(database)){

					fread(line_database, sizeof(book_t), 1, database);

					if(line_database->id==line_arrangefile->id){ /*si se ecuentra el mismo id, escribimos en el temporal la linea de arrangefile que contiene las modificaciones */
						
						fwrite(line_arrangefile, sizeof(book_t),1,temporal); /*SOLO SE AGREGA ESTO A DIFERENCIA DE BAJA*/

						if(aux_cant_lineas==cant_lineas){ /*caso en el que se llego al ultimo registro para modificiar. Se copia todo lo que queda de database en temporal, y finalmente se llega al endoffile*/
			
							while(!feof(database)){

								fread(line_database, sizeof(book_t), 1, database);   /*Leo la siguiente linea de database ya que la anterior no nos interesa*/
								fwrite(line_database, sizeof(book_t),1,temporal);			
							}	
						}
						else{

							aux_cant_lineas++;
							fread(line_arrangefile, sizeof(book_t), 1, arrangefile);  /*se lee la siguiente linea del arrangefile*/
						}
					}

					else{
			
							fwrite(line_database, sizeof(book_t),1,temporal);
					}
				}

				if (aux_cant_lineas++!=cant_lineas){

					fprintf(log, "%s\n", MSJ_ERROR_MODIFICACIONES);   /*se llego al EOF antes de que se modificaran todos
																los registros. esto puede pasar porque hay registros que se quieren modificar y no existen.*/
				}	
		
		
		}
		else{
			free(line_arrangefile);
			free(line_database);
			free(standby_line);
			fprintf(log, "%s", MSJ_ERROR_PREFIJO);
			close_all_files(database,log,arrangefile);
		}
	}

	    fclose(database);
		fopen(argv[DATABASE_ARGV_POS], "w");
		fwrite(temporal, sizeof(book_t), count_lines(temporal), database);
		close_all_files(database,log,arrangefile);

	return EXIT_FAILURE;

}
	

t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **log, FILE **arrangefile){

	if (argc!=ARG_FUNC || 
	(*database=fopen(argv[DATABASE_ARGV_POS],"r+"))==NULL ||
	(*log=fopen(argv[LOG_ARGV_POS],"w"))==NULL ||
	(*arrangefile=fopen(argv[ARRANGEFILE_ARGV_POS],"r+"))==NULL){
	
		return ST_ERROR;
	}
	else return ST_OK;
	
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
