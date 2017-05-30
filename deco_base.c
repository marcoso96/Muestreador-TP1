#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cb_constantes.h"
#include "cb_macros.h"

typedef struct libro {

	long id;
	char titulo[MAX_TITLE];
	char autor[MAX_AUTOR];
	char genero[MAX_GENERO];
	struct tm fecha;
	double puntaje;
	size_t reviews;

} book_t;


int main(int argc, char *argv[]){

	FILE *bin=fopen(argv[ARG_FILE], "r+b");
	book_t *line=(book_t *)malloc(sizeof(book_t));
	char str_fecha[FECHA_CHAR_NUM];
	int date;
	
	
	while(!feof(bin)){
	
		fread(line, sizeof(book_t), 1, bin);

		fprintf(stderr, "%ld\n", line->id);
		fprintf(stderr, "%s\n", line->titulo);
		fprintf(stderr, "%s\n", line->autor);
		fprintf(stderr, "%s\n", line->genero);
	
		date=mktime(&line->fecha);
		if(date==-1){
			fprintf(stderr, "%s\n", MSJ_ERROR_FECHA);
		}
		
		strftime(str_fecha, sizeof(str_fecha), "%Y/%m/%d", &line->fecha);
		fprintf(stderr, "%s\n", str_fecha);
		fprintf(stderr, "%.*f\n", PREC_PUNTAJE, line->puntaje);
		fprintf(stderr, "%ld\n\n", line->reviews);
	}
	 
	free(line);
	return 0;
}
