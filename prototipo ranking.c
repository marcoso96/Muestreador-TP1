t_status leer_modificaciones(FILE *arrangefile, FILE *log, char ***campos, int *cant_modif, size_t *arr_size)

	char line[MAX_LINE];
	
	while(fgets(line,MAX_LINE,fi)!=NULL){
		
		if((endptr=strchr(line, '\n'))!=NULL) *endptr='\0';

		if ((st=split(line,DELIM_CSV,&campos[arr_size],cant_modif))!=ST_OK){
				
				fprintf(log, "%s:%d", MSJ_ERROR_READ, *arr_size);
				free(campos[arr_size]);
				continue; 
		}
		
		if (cant_modif!= FIELD_NUM){
			
			fprintf(log, "%s:%d", MSJ_ERROR_FIELD, *arr_size);
			free(campos[arr_size]);
			continue; /*fuerza el proximo ciclo*/
		}
		
		(*arr_size)++; /*tendra el contenido de celdas leidas correctamente */
	}
	
	return ST_OK;
	
}

void cargar_book(char ***campos, book_t **arrange_book, size_t arr_size){

	size_t i, fecha_campos;
	char *endptr=NULL;
	char **fechafields=NULL;
	
	/*para un unico book*/	
	arrange_book[used_size].id = strtol(*campos[ID_FIELD_POS],&endptr, 10);
	
	strcpy(*arrange_book[SINGLE_CONS].titulo,*campos[TITULO_FIELD_POS]);
	strcpy(*arrange_book[SINGLE_CONS].autor,*campos[AUTOR_FIELD_POS]);
	strcpy(*arrange_book[SINGLE_CONS].genero,*campos[GENERO_FIELD_POS]);
	
	/*manejo de fecha*/
	split(*campos[FECHA_FIELD_POS], DELIM_FECHA, &fechafields, &fecha_campos); /*malloc de fecha, cerrar*/
	*arrange_book[SINGLE_CONS].fecha.tm_year=((int)strtol(fechafields[YEAR_POS], &endptr, 10))-YEAR_ADJUST;
	*arrange_book[SINGLE_CONS].fecha.tm_mon=((int)strtol(fechafields[MONTH_POS],&endptr, 10))-MONTH_ADJUST;
	*arrange_book[SINGLE_CONS].fecha.tm_mday=(int)strtol(fechafields[DAY_POS], &endptr, 10);

	
	*arrange_book[SINGLE_CONS].puntaje = strtod(*campos[PUNTAJE_FIELD_POS],&endptr);
	*arrange_book[SINGLE_CONS].reviews = strtol(*campos[REVIEWS_FIELD_POS],&endptr,10);
	del_str_array(&fechafields, &fecha_campos); 

	for(i=1; i<=arr_size; i++){
		
		*arrange_book=(book_t *)realloc(*arrange_book,(i + CHOP_SIZE)*sizeof(book_t))
		arrange_book[i].id = strtol(*campos[ID_FIELD_POS],&endptr, 10);
		
		strcpy(*arrange_book[i].titulo,*campos[TITULO_FIELD_POS]);
		strcpy(*arrange_book[i].autor,*campos[AUTOR_FIELD_POS]);
		strcpy(*arrange_book[i].genero,*campos[GENERO_FIELD_POS]);
		
		/*manejo de fecha*/
		split(csvfields[FECHA_FIELD_POS], DELIM_FECHA, &fechafields, &fecha_campos);
		*arrange_book[i].fecha.tm_year=((int)strtol(fechafields[YEAR_POS], &endptr, 10))-YEAR_ADJUST;
		*arrange_book[i].fecha.tm_mon=((int)strtol(fechafields[MONTH_POS],&endptr, 10))-MONTH_ADJUST;
		*arrange_book[i].fecha.tm_mday=(int)strtol(fechafields[DAY_POS], &endptr, 10);
	
		
		*arrange_book[i].puntaje = strtod(csvfields[PUNTAJE_FIELD_POS],&endptr);
		*arrange_book[i].reviews = strtol(csvfields[REVIEWS_FIELD_POS],&endptr,10);
		
		del_str_array(&fechafields, &fecha_campos);
	
	}
	
	del_str_array(&(*campos), FIELD_NUM);
	
	return; 
}


t_status realizar_baja(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	size_t used_size=0;
	size_t arrange_count;
	
	fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	
	while(fread(db_book, sizeof(book_t), SINGLE_CONST, database)!=NULL){
		
		/*temp_book=(book_t *)realloc(temp_book, (used_size+INIT_CHOP)*sizeof(book_t));*/ 
		if(db_book.id<arrange_book.id){
			
			fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
			arrange_count++;
			continue;
		}
		
		if(db_book.id<arrange_book.id){
			
			fprintf(log, "%s: %d", MSJ_ERROR_BAJA, arrange_count);
			return ST_ERROR;
		}
			
		if(arrange_count=arr_size){
			
			fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			while(fread(db_book, sizeof(book_t), SINGLE_CONST, database)!=NULL){
				
				fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			}
		}
	}
}
	
t_status realizar_modificacion(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	size_t used_size=0;
	size_t arrange_count=1;
	
	fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	
	while(fread(db_book, sizeof(book_t), SINGLE_CONST, database)!=NULL){
		
		/*temp_book=(book_t *)realloc(temp_book, (used_size+INIT_CHOP)*sizeof(book_t));*/ 
		if(db_book.id<arrange_book.id){
			
			fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			fwrite(arrange_book, sizeof(book_t), SINGLE_CONST, temporal);
			fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
			arrange_count++;
			continue;
		}
		
		if(db_book.id<arrange_book.id){
			
			fprintf(log, "%s: %d\n", MSJ_ERROR_BAJA, arrange_count);
			return ST_ERROR;
		}
		
		if (arrange_count!=arr_size){

			fprintf(log, "%s\n", MSJ_ERROR_MODIFICACIONES);   
			return ST_ERROR;
		}
				
		if(arrange_count=arr_size){
			
			fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			while(fread(db_book, sizeof(book_t), SINGLE_CONST, database)!=NULL){
				
				fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			}
		}
	}
}	

t_status realizar_alta(FILE *temporal, FILE *database, FILE *log, FILE *arrange, size_t arr_size){
	
	book_t db_book;
	book_t arrange_book;
	book_t standby_book;
	size_t used_size=0;
	size_t arrange_count=1;
	
	fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
	fread(database,sizeof(book_t), SINGLE_CONST, db_book);
	
	while(!feof(database)){
		
		if(db_book.id<arrange_book.id){
			
			standby_book=db_book;
			
			fread(database,sizeof(book_t), SINGLE_CONST, db_book);
			
			if(db_book.id>arrange_book.id){
				
				fwrite(standby_line, sizeof(book_t), SINGLE_CONST, temporal);
				fwrite(arrange_file, sizeof(book_t), SINGLE_CONST, temporal);
				
				if(arrange_count<=arr_size){
					
					fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);		
					arrange_count++;
				}
				
				else {
					
					fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
					
					while(fread(database,sizeof(book_t), SINGLE_CONST, db_book)!=NULL){
						
						fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
					}
				}			
			}					
		
			
			fwrite(db_book, sizeof(book_t), SINGLE_CONST, temporal);
			
			continue;	
		}
		
		if(db_book.id==arrange_book.id){
			
			
			fprintf(log, "%s:%d", MSJ_ERROR_ALTA, arrange_book.id);
			
			fread(arrange_book, sizeof(book_t), SINGLE_CONST, arrange);
		
			continue;
		}
		
		else{
				
			fwrite(arrange_book, sizeof(book_t), SINGLE_CONST,temporal);
						
			if((arrange_book.id) == (db_book.id)) fprintf(log, "%s,%s\n", MSJ_ERROR, MSJ_ERROR_ALTA);

			if(arrange_count==arr_size){
							
					while(!feof(database)){

						fwrite(arrange_book, sizeof(book_t), SINGLE_CONST,temporal);
						fread(database,sizeof(book_t), SINGLE_CONST, db_book);			
					}
				}
				
			else{ 

					fread(database,sizeof(book_t), SINGLE_CONST, db_book);
					arrange_count++;
				}
				
		}
	}
		
		} 
	































	
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
		
		break;





