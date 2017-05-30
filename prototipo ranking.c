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


realizar_baja(FILE *temporal, FILE *database, FILE *log, book_t **arrange_book, size_t arr_size){
	
	book_t *temp_book;
	size_t used_size=0;
	
	while(!feof(database)){
		
		temp_book=(book_t *)realloc(temp_book, (used_size+INIT_CHOP)*sizeof(book_t));
		 
		fread(temp_book, sizeof(book_t), SINGLE_CONS, database);
		
		for(i=0; i<=arr_size; i++){
			
			if(temp_book[used_size].id==*arrange_book[]
		
		
	
}
	
	realizar_baja(database, log, campos, &arrange_book);





