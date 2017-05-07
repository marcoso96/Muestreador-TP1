#include <stdio.h>   /*Todavia esta muy flojo este*/

typedef enum {}

int main(int argc, char *argv[]){


	FILE *database;
	FILE *errorfile;
	FILE *arrangefile;
	FILE *log;
	char *linea;
	FILE *temporal;
	
	log=fopen(argv[ARG_LOG],wt);
	 
	if (st=validar_argumentos(argc, argv, &database, &errorfile, &arrangemetfile)!=ST_OK){ 
	
		fprintf(log, "%s:%S\n", MSJ_ERROR, MSJ_ERROR_PREFIJO);
		
		fclose(database);
		fclose(errorfile);
		fclose(arrangefile);
		 
		return EXIT_FAILURE;
	}
	
	else{
			
		lines=countlines();			
	
		switch(argv[ARGV_OP]){
		
			case 'A':				
						fread(line,sizeof(struct libros),lines,arrangefile);
						fwrite(line,sizeof(book_t),lines,database);                            /*creo que esto no esta bien, me parece que hay que hacer otra vez lo de split*/
			
			case 'B':
						
						
						
			case 'M':
			
		}
		
	}
}

t_status validar_argumentos(int arg c, char *argv[], FILE **database, FILE **errorfile, FILE **arrangefile){

	if (argc!=8 || 
	(*database=fopen(argv[DATABASE_ARGV_POS],"r+"))==NULL ||
	(*errorfile=fopen(argv[ERRORFILE_ARGV_POS],"r+"))==NULL ||
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

int countlines (FILE *arrangefile){ /*cuanta cantidad de caracteres de una linea*/
	
	int lines=0;
	int aux;
			
	while((aux=fgetc(arrangefile))!=EOF){
			
		if (=='\n') lines++; 
		
	}
	return lines;
}
