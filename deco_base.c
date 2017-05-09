#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int tm_mday;
	int tm_mon;
	int tm_year;
	} date_t;
	
typedef struct libro {
	
	long id;
	char titulo[MAX_STR];
	char autor[MAX_STR];
	char genero[MAX_STR];
	date_t fecha;														
	double puntaje;
	size_t reviews;
	
} book_t;


int main(int argc, char *argv[]){
	FILE *bin;
	FILE *deco;
	long *id;
	char titulo[MAX_STR];
	char autor[MAX_STR];
	char genero[MAX_STR];
	date_t *fecha;														
	double *puntaje;
	size_t *reviews;
	
	
	if(argc!=NUM_ARG){
		procesar_error();
		
		}
	
	if((bin=fopen(argv[ARG_ENTRADA],"r+b"))==NULL){
		procesar_error;
	}
	
	if((deco=fopen(argv[ARG_ENTRADA],"w+t"))==NULL){
		procesar_error();
	}
	
	for(i=0; i<NRO_STRUCT; i++){
		
		fread(id, sizeof(long),1, bin);
		fread(titulo[], sizeof(char)*MAX_STR,1, bin);
		fread(titulo[], sizeof(char)*MAX_STR,1, bin);
		fread(autor[], sizeof(char)*MAX_STR,1, bin);
		fread(genero[], sizeof(char)*MAX_STR,1, bin);
		/* algo con fseek que ponga al puntero en el siguiente. despues 
		 * seguir strcopiando al csv en orden con comas*/
		}
	
