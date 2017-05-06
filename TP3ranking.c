include <stdio.h>   /*Todavia esta muy flojo este*/
typedef enum {}

int main(int argc, char *argv[]){


	FILE *database;
	FILE *errorfile;
	FILE *arrangementfile;
	
	if (st=validar_argumentos(argc,argv,&database,&errorfile,&arrangemetfile)!=ST_OK){ 
	
		fprintf(sderr,"%s%S\n", MSJ_ERROR, MSJ_ERROR_PREFIJO);
		
		fclose(database);
		flcose(errorfile);
		flcose(arrangementsfile);
		 
		return EXTI_FAILURE;
	}
	
	else{
			
		lines=countlines();			
	
		switch(argv[OPERACION_ARGV_POS]){
		
			case A:
						
						fread(line,sizeof(struct libros),lines,arrangemetfile);
						fwrite(line,sizeof(book_t),lines,database);                            /*creo que esto no esta bien, me parece que hay que hacer otra vez lo de split*/
			
			case B:
		
			case M:
			
		}
		
	}
}

t_status validar_argumentos(int arg c, char *argv[], FILE **database, FILE **errorfile, FILE **arrangemetfile){

	if (argc!=8 || (*database=fopen(argv[DATABASE_ARGV_POS],"r+"))==NULL || *errorfile=fopen(argv[ERRORFILE_ARGV_POS],"r+" || arrangementfile=fopen(argv[ARRANGEMENTFILE_ARGV_POS],"r+"))==NULL){
	
		return ST_ERROR;
	}
	else return ST_OK;
	

	
}	

int countlines (void){
	
	lines=0;
	char aux;
			
	while((aux=fgetc(arrangementfile))!=EOF){
			
		if (ch=='\n') { lines++; }
		
	}
	return lines;
}
