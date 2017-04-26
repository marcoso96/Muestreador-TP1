

/*PENDIENTE: son dos cosas, una es la variable CANT_ELEMENTOS no esta definida, y no se muy bien como usarla asi que eso lo deje. Y lo ultimo seria formatos! Cuando hacemos el scanf de dato que es un tipo t_algo no nos deja poner 
																																							%d %S %i o lo que sea....*/

/*HIce cambbios en ST_PARAM y en la funcion funciones, definitivamente maniana lo vuelvo a chequear antes de que se entregue. Pueden fijarse si tiene logica*/



#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constantes.h"
#include "config.h"

#ifdef LENGUAJE_ES
#include "macros_reent3.h"
#endif

typedef enum {F_SENOIDAL=INDICE_SEN, F_LOG=INDICE_LOG, F_LOGLINEAL=INDICE_LOGLIN,
	F_EXPONENCIAL=INDICE_EXP, F_ESCALON=INDICE_ESC, F_MRUA=INDICE_MRUA,
	F_PAR_HIP=INDICE_PARAB, F_VOLVER=INDICE_VOLVER} t_funciones;
typedef enum {ST_SALIR, ST_PARAM, ST_INICIO, ST_FUNCION} t_state;
typedef enum {OK, ERR_DATO, ERR_OPC_FUN, ERR_OPC_PPAL, OK_VOLVER} t_status; 
typedef enum {OPC_SALIR, OPC_FUNCION} t_menu_ppal;

t_status f_logaritmica(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_loglineal(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_escalon(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_senoidal(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_paraboloide_hiperbolico(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_mrua(double tiempoi,double tiempof, int prec,int cant_muestras);
t_status f_exponencial(double tiempoi,double tiempof, int prec,int cant_muestras);

t_status leer_double (double *dato);
t_status leer_int (int *dato);

void limpiar_buffer(void);

void menu_funcion(void);
void menu_inicio(void);
t_status funciones (float tiempoi, float tiempof, int cant_muestras, int prec);
void procesar_error(t_status stat_ejecucion);

int main (void) {

	t_status stat_ejecucion;
	t_state stat_programa = ST_INICIO;
	
	int aux_opcion;
	double tiempoi;
	double tiempof;
	int precision;
	int cant_muestras;

	while(1){

		switch (stat_programa){

				case ST_INICIO:

					menu_inicio();
					
					if((scanf("%i",&aux_opcion))!=CANT_ELEMENTO) stat_ejecucion=ERR_DATO;
					
					limpiar_buffer();
					
					switch(aux_opcion){

							case OPC_FUNCION:

									stat_ejecucion=OK;
									stat_programa=ST_PARAM;
									break;

							case OPC_SALIR:
									
									stat_ejecucion=OK;
									stat_programa=ST_SALIR;
									break;

							default:
									stat_ejecucion=ERR_OPC_PPAL;									
									break;									
					}				
					
					if(stat_ejecucion!=OK){
					
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					break;
							
				case ST_PARAM:
					
					fprintf(stderr, "\n%s\n", MSJ_INGRESO_PARAMETROS);

					fprintf(stderr, "\n%s\n", MSJ_T_INICIAL);
					
					stat_ejecucion=leer_double(&tiempoi);
					if(stat_ejecucion!=OK){
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					fprintf(stderr, "\n%s\n", MSJ_T_FINAL);
					stat_ejecucion=leer_double(&tiempof);
					if(stat_ejecucion!=OK){
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					fprintf(stderr, "\n%s\n", MSJ_CANT_MUESTRAS);
					stat_ejecucion=leer_int(&cant_muestras);
					if(stat_ejecucion!=OK){
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					fprintf(stderr, "\n%s\n", MSJ_PRECISION);
					stat_ejecucion=leer_int(&precision);					
					if(stat_ejecucion!=OK){
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					if(tiempoi>tiempof||precision< MIN_PREC||
					   cant_muestras<=MIN_CANTIDAD_MUESTRAS) {

						stat_ejecucion=ERR_DATO;
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					stat_programa=ST_FUNCION;
					
					break;

				case ST_FUNCION:

					menu_funcion();

					stat_ejecucion=funciones(tiempoi, tiempof, cant_muestras, precision);
					
					if(stat_ejecucion!=OK&&stat_ejecucion!=OK_VOLVER){
						procesar_error(stat_ejecucion);
						return EXIT_FAILURE;
					}
					
					if(stat_ejecucion==OK_VOLVER) stat_programa=ST_INICIO;
					
					else stat_programa=ST_INICIO;
					
					break;

				case ST_SALIR:

					fprintf(stderr, "\n%s\n", MSJ_SALIDA);
					return EXIT_SUCCESS;

					break;
		}
	}
}

void procesar_error(t_status stat_ejecucion){

			switch(stat_ejecucion){

					case OK_VOLVER:
							
							break;
								
					case OK:
					
							break;

					case ERR_DATO:

						fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_DATO);
						
						break;

					case ERR_OPC_FUN:

						fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_OPC);
						
						break;

					case ERR_OPC_PPAL:

						fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_OPC);
						
						break;
			}	
}


void menu_inicio(void){

	fprintf(stderr,"\n%s\n\n%d\t%s\n%d\t%s\n\n\n", MSJ_MENU, INDICE_OPC_MUESTREAR, MSJ_MUESTREAR, INDICE_OPC_SALIR, MSJ_SALIR );

    return;

}

t_status leer_int (int *dato) {   
		
	if(scanf("%d", dato)!=CANT_ELEMENTO){
		 
		limpiar_buffer();
		return ERR_DATO;
	
	}
	else {
		limpiar_buffer();
		return OK;
	}
}
		
t_status leer_double (double *dato){

	if(scanf("%lf", dato)!=CANT_ELEMENTO){
		 
		limpiar_buffer();
		return ERR_DATO;
	}
	
	else {
		limpiar_buffer();
		return OK;
	}
}

void menu_funcion(void){

	fprintf(stderr,"%s\n\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n\n", MSJ_MENU_2,
		INDICE_SEN, MSJ_SENOIDAL,
		INDICE_LOG,MSJ_LOGARITMICA,
		INDICE_LOGLIN, MSJ_LOGLINEAL,
		INDICE_EXP, MSJ_EXPONENCIAL,
        INDICE_ESC, MSJ_ESCALON,
        INDICE_MRUA, MSJ_MRUA,
        INDICE_PARAB, MSJ_PARAB,
        INDICE_VOLVER, MSJ_VOLVER);
}

t_status funciones (float tiempoi, float tiempof, int cant_muestras, int prec){
	
	int aux_fun;
	
	if((scanf("%d", &aux_fun))!=CANT_ELEMENTO){
				
		return ERR_OPC_FUN;
	
	}

	switch (aux_fun){

		case F_SENOIDAL:																					

						return f_senoidal(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_LOG:

						return f_logaritmica(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_LOGLINEAL:

						return f_loglineal(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_EXPONENCIAL:

						return f_exponencial(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_ESCALON:

						return f_escalon(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_MRUA:

						return f_mrua(tiempoi, tiempof, prec, cant_muestras);
						break;

		case F_PAR_HIP:

						return f_paraboloide_hiperbolico(tiempoi, tiempof, prec, cant_muestras);
						
						break;

		case F_VOLVER:
						return OK_VOLVER;
						break;
		default:	
						return ERR_OPC_FUN;
						break;
	}
}
t_status f_paraboloide_hiperbolico(double tiempoi,double tiempof, int prec,int cant_muestras){

	double parh;
	double t;
	double a,b;
	t_status stat_ejecucion;
	
	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_A);
	stat_ejecucion=leer_double(&a);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_B);
	stat_ejecucion=leer_double(&b);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_PARAB, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){

			parh=((t/a)*(t/a))-((t/b)*(t/b));

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, parh);
	}
	return OK;
}



t_status f_escalon(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;

	fprintf(stderr,"%s\n\n%s\n\n\n%s",MSJ_FUNCION, MSJ_ESCALON, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){


		fprintf(stderr, "\n%.*f\t|%d", prec, t,(t>0)?1:0);
	}
	
	return OK;

}


t_status f_mrua(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;
	double posicion_final;
	double pos, vel, acel;
	t_status stat_ejecucion;
	
	fprintf(stderr,"%s\n" ,MSJ_MRUA_POS);
	stat_ejecucion=leer_double(&pos);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n" ,MSJ_MRUA_VEL);
	stat_ejecucion=leer_double(&vel);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n" ,MSJ_MRUA_ACEL);
	stat_ejecucion=leer_double(&acel);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_MRUA, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){

			posicion_final=pos+vel*t+0.5*acel*t*t;

			fprintf(stderr,"\n%.*f\t|%.*f", prec, t, prec, posicion_final);
		}
	return OK;

}

t_status f_exponencial(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_EXPONENCIAL,ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, exp(t));
	}
	return OK;

}


t_status f_loglineal(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;

	fprintf(stderr,"%s\n\n%s\n\n%s",  MSJ_FUNCION, MSJ_LOGLINEAL,ENCABEZADO_XY);

	for(t=tiempoi;  t<tiempof;   t+=((tiempof-tiempoi)/cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, t*log(t));
	}
	return OK;

}

t_status f_logaritmica(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_LOGARITMICA,ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, log(t));
	}
	return OK;

}


t_status f_senoidal(double tiempoi,double tiempof, int prec,int cant_muestras){

	double t;
	double sen;
    double fase;
	double amp;
    double frec;
	t_status stat_ejecucion;
	
	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_AMP);
	stat_ejecucion=leer_double(&amp);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FASE);
	stat_ejecucion=leer_double(&fase);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FREC);
	stat_ejecucion=leer_double(&frec);
	if(stat_ejecucion!=OK) return ERR_DATO;
	
	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_SENOIDAL,ENCABEZADO_XY);  

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){

		sen=amp*sin(t*2*pi*frec+fase);
		fprintf(stderr, "\n%*.f\t|%*.f", prec, t, prec, sen);

	}
	return OK;
}

void limpiar_buffer(void){

	while(getchar()!='\n');
}
