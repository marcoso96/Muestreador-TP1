#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 20
#define ARG_POS 1

typedef struct libro {

	long id;
	char titulo[MAX_STR];
	char autor[MAX_STR];
	char genero[MAX_STR];
	struct tm *fecha;
	double puntaje;
	size_t reviews;

} book_t;


int main(int argc, char *argv[]){

	FILE *bin=fopen(argv[ARG_POS], "r+b");
	book_t *line=(book_t *)malloc(sizeof(book_t));
	char *str_fecha=(char*)malloc(sizeof(char)*11);

	while (!feof(bin)){

		fread(line, sizeof(book_t), 1, bin);

		fprintf(stderr, "%ld", line->id);
		fprintf(stderr, "%s", line->titulo);
		fprintf(stderr, "%s", line->autor);
		fprintf(stderr, "%s", line->genero);
		strftime(str_fecha, 11, "%d/%m/%Y", line->fecha);
		fprintf(stderr, "%s", str_fecha);
		fprintf(stderr, "%lf", line->puntaje);
		fprintf(stderr, "%lud", line->reviews);
	}
	 
	free(line);
	free(str_fecha);
	return 0;
}
