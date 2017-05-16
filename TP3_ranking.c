#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TP3_constantes.h"
#include "TP3_macros.h"

typedef enum {ST_OK,ST_ERROR} t_status;

typedef struct date {
	
	int tm_mday;
	int tm_mon;
	int tm_year;
	
} date_t;
	
typedef struct book {
	
	long id;
	char titulo[MAX_TITLE];
	char autor[MAX_AUTOR];
	char genero[MAX_GENERO];
	/*date_t fecha;*/														
	double puntaje;
	size_t reviews;
	
} book_t;

t_status split(const char *s, char delim, char ***csvfields, size_t *l);
t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **errorfile, FILE **arrangefile);
t_status copy_file(FILE **temporal, FILE **database);
t_status del_str_array(char **s_array, size_t *l)
t_status make_date(char *str_fecha, t_book *fecha);
void close_all_files (FILE *database, FILE *errorfile, FILE *arrangefile);

int main(int argc, char *argv[]){


	FILE *database;
	FILE *errorfile;
	FILE *arrangefile;
	FILE *temporal;

	size_t used_size, alloc_size,;
	char **csvfields=NULL;
	char *endptr=NULL;
	char line[MAX_STR];
	
	book_t *line_arrangefile=(book_t*)malloc(sizeof(book_t));
	book_t *line_database=(book_t*)malloc(sizeof(book_t));
	book_t *standby_line=(book_t*)malloc(sizeof(book_t));

	book_t *book,*aux;
	t_status st;
	
	temporal=tmpfile();
	
	errorfile=fopen(argv[ARG_LOG],"w+");       /*el archivo que guarda los errores es errorfile, se abre cuando se validan los argumentos*/
	 
	if ((st=validar_argumentos(argc, argv, &database, &errorfile, &arrangefile))!=ST_OK){ 
	
		fprintf(errorfile, "%s:%s\n", MSJ_ERROR, MSJ_ERROR_PREFIJO);
		
		close_all_files(&database, &errorfile, &arrangefile);
		 
		return EXIT_FAILURE;
	}
	
	else{
		
		cant_lineas=count_lines(arrangefile);
																					
		switch(argv[ARGV_OP]){
				
				case 'B':
						aux_cant_lineas=1;  /*Se supone que el archivo arrangefile no es nulo, asi que por lo menos tiene una linea que dar de baja*/

						fread(line_arrangefile, sizeof(book_t), 1, arrangefile);

						while(!feof(database)){

							fread(line_database, sizeof(book_t), 1, database);

							if(line_database->id==line_arrangefile->id){ /*si se ecuentra el mismo id, no escribimos en el temporal esa linea */

								if(aux_cant_lineas==cant_lineas){ /*caso en el que se llego al ultimo registro par borrar. Se copia todo lo que queda de database en temporal, y finalmente se llega al endoffile*/

									while(!feof(database)){

										fread(line_database, sizeof(book_t), 1, database);   /*Leo la siguiente linea de database ya que la anterior no nos interesa*/
										fwrite(line_database, sizeof(book_t),1,tmpfile);			
									}	
								}
								else{

									aux_cant_lineas++;
									fread(line_arrangefile, sizeof(book_t), 1, arrangefile);  /*se lee la siguiente linea del arrangefile*/
								}
							}

							else{

									fwrite(line_database, sizeof(book_t),1,tmpfile);
							}
						}

						if (aux_cant_lineas++!=cant_lineas){

							fprintf(log, "%s\n", MSJ_ERROR_BAJA);   /*se llego al EOF antes de que se dieran 
																		los registros. esto puede pasar porque los registros no estaban en orden o hay un registro que se queria dar de baja y en realidad no existia en database.*/
						}	

				}

			case 'A':
					
					fread(line_arrangefile, sizeof(book_t), 1, arrangefile);
					fread(line_database, sizeof(book_t), 1, database);

					aux_cant_lineas=1;

					while(!feof(database)){

						if((line_arrangefile->id) > (line_database->id)){

							standby_line=line_database;         /*Guardo la linea anterior de database */
							fread(line_database, sizeof(book_t), 1, database);  /*Leo la siguiente linea de database*/

							if((line_arrangefile->id) <= (line_database->id)){   /*Comparo nuevamente, si resulta que el ahora id de arrangefile no supera al de database, entonces es momento de poner el registro da arrangefile en tmpfile*/

								fwrite(line_arrangefile, sizeof(book_t),1,t);

								if((line_arrangefile->id) == (line_database->id)) fprintf(log, "%s,%s\n", MSJ_ERROR, MSJ_ERROR_ALTA);

								if(aux_cant_lineas==cant_lineas){

									fwrite(standby_line, sizeof(book_t),1,temporal); /*EScribo la linea que guarde y dps guardo el resto*/

									while(!feof(database)){

										fread(line_database, sizeof(book_t), 1, database);   /*Leo la siguiente linea de database ya que la anterior no nos interesa*/
										fwrite(line_database, sizeof(book_t),1,temporal);
										continue;
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

/*MODIFICACIONES*/
		case 'M':

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
	}
    close_all_files(database,log,arrangefile);

    if(count_lines(log)!=0){
        remove(argv[DATABASE_ARGV_POS]);
        rename(temporal, argv[DATABASE_ARGV_POS]);
    }

	return EXIT_FAILURE;
}
		
return EXIT_SUCCESS;
}
	

t_status validar_argumentos(int argc, char *argv[], FILE **database, FILE **errorfile, FILE **arrangefile){

	if (argc!=8 || 
	(*database=fopen(argv[DATABASE_ARGV_POS],"r+"))==NULL ||  /*No deberia leer desde el segundo caracter en adelante del argumento*/
	(*errorfile=fopen(argv[ERRORFILE_ARGV_POS],"w+"))==NULL ||
	(*arrangefile=fopen(argv[ARRANGEFILE_ARGV_POS],"r+"))==NULL){
	
		return ST_ERROR;
	}
	else return ST_OK;
	

	
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

/*int countlines (FILE *arrangefile){ 
	
	int lines=0;
	int aux;
			
	while((aux=fgetc(arrangefile))!=EOF){
			
		if (=='\n') lines++; 
		
	}
	return lines;
}*/

void close_all_files (FILE *database, FILE *errorfile, FILE *arrangefile){
	
	fclose(database);
	fclose(errorfile);
	fclose(arrangefile);
	
	return 0;
	
}
		
t_status make_date(char *str_fecha, t_book *fecha){
		
	char **aux_fecha;
	char fec_delim[2];
	char *t_fecha;
	/*smax es el umero de caracteres del campo, supongo que deberian ser 10 de dd/mm/yyyy*/
	if(strptime(str_fecha, smax, "%d/%m/%Y", fecha)!=smax) return ERROR_FECHA;
	
	return ST_OK;
}
	
t_status del_book_array(book_t **book, size_t *n){       /*No se que utilidad tiene devolver el estado con esta funcion ni con del_str_array, no se usan en el main los estados que devuelve*/
	
	if (book==NULL) return ST_ERROR;
	
	free (*book);
	
	*book=NULL;
	*n=0;
	
	return ST_OK;   /*no faltaria un else aca?*/
}


t_status copy_file(FILE **temporal, FILE **database){
	
	char c;
	/*EN QUE PUEDE FALLAR? PREGUNTAR*/
	while((c=fgetc(database))!=EOF) fputc(c,temporal);
	
	return OK; 		
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
