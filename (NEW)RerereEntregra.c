#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constantes.h"
#include "config.h"
#ifdef LENGUAJE_ES
#include "macros_reent_3.h"
#endif

typedef enum {F_SENOIDAL=INDICE_SEN, F_LOG=INDICE_LOG, F_LOGLINEAL=INDICE_LOGLIN,
	F_EXPONENCIAL=INDICE_EXP, F_ESCALON=INDICE_ESC, F_MRUA=INDICE_MRUA,
	F_PAR_HIP=INDICE_PARAB, F_VOLVER=INDICE_VOLVER} t_funciones;
typedef enum {ST_SALIR, ST_PARAM, ST_INICIO, ST_ERROR, ST_FUNCION} t_stat;
typedef enum {FALSE, TRUE} t_bool;
typedef enum {OK, ERR_DATO, ERR_MAXCANT_INTENTOS, ERR_OPC_FUN, ERR_OPC_PPAL} t_err; /* no deberia tener el nombre del enum? */
typedef enum {OPC_SALIR, OPC_FUNCION} t_menu_ppal;

void f_logaritmica(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_loglineal(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_senoidal(float tiempoi, float tiempof, int prec, int cant_muestras);
void f_paraboloide_hiperbolico(float tiempoi,float tiempof,int prec,int cant_muestras);
void f_mrua(float tiempoi,float tiempof,int prec,int cant_muestras);
void f_exponencial(float tiempoi,float tiempof, int prec,int cant_muestras);

double leer_double (void);
int   leer_int (void);

int leer_funcion(void);
int leer_stat(void);

void limpiar_buffer(void);

void menu_funcion(void);
void menu_inicio(void);
t_stat funciones (float tiempoi, float tiempof, int cant_muestras, t_funciones funcion, int prec);

int main (void) {

	t_err stat_ejecucion;
	t_stat stat_programa = ST_INICIO;
	t_menu_ppal opcion;
	t_funciones funcion;

	float tiempoi;
	float tiempof;
	int precision;
	int cant_muestras;
	int cant_intentos=0;

	while(1){

			switch (stat_programa){

					case ST_INICIO:

								menu_inicio();
                                scanf("%d", &opcion);

                                switch(opcion){

                                            case OPC_FUNCION:

                                                        stat_ejecucion=OK;
                                                        stat_programa=ST_PARAM;
                                                        break;

                                            case OPC_SALIR:

                                                        stat_ejecucion=OK;
                                                        stat_programa=ST_SALIR;
                                                        break;

                                            default:
                                                        stat_programa=ST_ERROR;
                                                        stat_ejecucion=ERR_OPC_PPAL;
                                                        break;
                                            }

					case ST_PARAM:

                                fprintf(stderr, "\n%s\n", MSJ_INGRESO_PARAMETROS);

								fprintf(stderr, "\n%s\n", MSJ_T_INICIAL);
								tiempoi=leer_double();


								fprintf(stderr, "\n%s\n", MSJ_T_FINAL);
								tiempof=leer_double();


								fprintf(stderr, "\n%s\n", MSJ_CANT_MUESTRAS);
                                cant_muestras=leer_int();

                                fprintf(stderr, "\n%s\n", MSJ_PRECISION);
								precision=leer_int();

								if(tiempoi>tiempof||precision< MIN_PREC||
								   cant_muestras<=MIN_CANTIDAD_MUESTRAS) {
				
                                    stat_programa=ST_ERROR;
									stat_ejecucion=ERR_DATO;

									if( (cant_intentos++)==MAX_CANT_INTENTOS){
									
										stat_programa=ST_ERROR;
										stat_ejecucion=ERR_MAXCANT_INTENTOS;	
									}
								}

								else{

                                	stat_ejecucion=OK;   	/*el problema del error de opc de la funcion se resuelve si aca se cambia OK por error opc funciones pero no tendria sentid la logica!*/
									stat_programa=ST_FUNCION;
									cant_intentos=0; 	/*Se reinicializa la variable cant_intentos, una vez que el usuario ingresa bien los datos (en tanto no se supere la max cant de intentos)*/
								}

								break;

                    case ST_ERROR:

								switch(stat_ejecucion){

										case OK:
												break;

										case ERR_DATO:

										    fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_DATO);
										    stat_programa=ST_PARAM;
										    break;

										case ERR_MAXCANT_INTENTOS:

											fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_CANTMAX_INTENTOS);
										    stat_programa=ST_SALIR;
										    break;

										case ERR_OPC_FUN:

										    fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_OPC);
										    stat_programa=ST_FUNCION;
										    break;

										case ERR_OPC_PPAL:

										    fprintf(stderr,"\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_OPC);
										    stat_programa=ST_INICIO;
										    break;
								}

					case ST_FUNCION:

								menu_funcion();

								scanf("%i", &funcion);

								stat_programa=funciones(tiempoi, tiempof, cant_muestras, funcion, precision);

                                if(stat_programa==ST_ERROR) stat_ejecucion=ERR_OPC_FUN;

                                stat_ejecucion=OK;

                                break;

					case ST_SALIR:

								fprintf(stderr, "\n%s\n", MSJ_SALIDA);
								return EXIT_SUCCESS;

								break;
			}
	}
}

void menu_inicio(void){

	fprintf(stderr,"\n%s\n\n%i\t%s\n%s\t%s\n\n\n", MSJ_MENU, INDICE_OPC_MUESTREAR, MSJ_MUESTREAR, INDICE_OPC_SALIR, MSJ_SALIR );

    return;

}

int leer_int (void) {    /* la volvi a dejar como estaba con mis modificaciones de ayer*/

	int dato;
	t_bool j;
	do{

		limpiar_buffer();

		if(!scanf("%d", &dato) ) {

			j=FALSE;

			fprintf(stderr, "\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_OPC);

			}
		else j=TRUE;
	}

	while(j==FALSE);

	return dato;
}

double leer_double (void) {

	double dato;
	t_bool j;

    if(i>=1) {limpiar_buffer();}

    if(!scanf("%f", &dato)){         

        fprintf(stderr, "\n%s:%s\n", MSJ_ERROR, MSJ_ERROR_DATO);

			}

    else  j=TRUE;

	while(j==0);

	return dato;    /* pedazo incompleto*/ /*supuse que es como leer_int */
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

    return;
}

t_stat funciones (float tiempoi, float tiempof, int cant_muestras, t_funciones funcion, int prec){
	
	t_bool opcfuncion_es_erroneo= FALSE; /*Es false, en tanto no entre en default(switch)*/

    switch (funcion){

				case F_SENOIDAL:

								f_senoidal(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_LOG:

								f_log(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_LOGLINEAL:

								f_loglin(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_EXPONENCIAL:

								f_exp(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_ESCALON:

								f_escalon(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_MRUA:

								f_mrua(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_PAR_HIP:

								f_par_hip(tiempoi, tiempof, prec, cant_muestras);
								break;

				case F_VOLVER:
								return ST_SALIR;


				default:		
								opcfuncion_es_erroneo=TRUE;
								return ST_ERROR;   

				}

	if(opcfuncion_es_erroneo=FALSE){

	return ST_INICIO;
	}

}

void f_paraboloide_hiperbolico(float tiempoi,float tiempof,int prec,int cant_muestras){

	float parh;
	float t;
	float a,b;

	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_A);
	a=leer_double();

	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_B);
	b=leer_double();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_PARAB, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			parh=((t/a)*(t/a))-((t/b)*(t/b));

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, parh);
	}

}



void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n\n%s",MSJ_FUNCION, MSJ_ESCALON, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){


		fprintf(stderr, "\n%.*f\t|%d", prec, t,(t>0)?1:0);
	}


}


void f_mrua(float tiempoi,float tiempof,int prec,int cant_muestras){

	float t;
	float posicion_final;
	float pos, vel, acel;

	fprintf(stderr,"%s\n" ,MSJ_MRUA_POS);
	pos=leer_double();

	fprintf(stderr,"%s\n" ,MSJ_MRUA_VEL);
	vel=leer_double();

	fprintf(stderr,"%s\n" ,MSJ_MRUA_ACEL);
	acel=leer_double();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_MRUA, ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			posicion_final=pos+vel*t+0.5*acel*t*t;

			fprintf(stderr,"\n%.*f\t|%.*f", prec, t, prec, posicion_final);
		}


}

void f_exponencial(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_EXPONENCIAL,ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, exp(t));
	}


}


void f_loglineal(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",  MSJ_FUNCION, MSJ_LOGLINEAL,ENCABEZADO_XY);

	for(t=tiempoi;  t<tiempof;   t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, t*log(t));
	}


}

void f_logaritmica(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_LOGARITMICA,ENCABEZADO_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, log(t));
	}


}


void f_senoidal(float tiempoi, float tiempof, int prec, int cant_muestras){

	float t;
	float sen;
    float fase;
    float amp;
    float frec;

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_AMP);
	amp=leer_double();

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FASE);
	fase=leer_double();

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FREC);
	frec=leer_double();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_SENOIDAL,ENCABEZADO_XY);  /*Supuse que en vez de tabla_xy iba encabezado_xy*/

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

		sen=amp*sin(t*2*pi*frec+fase);
		fprintf(stderr, "\n%*.f\t|%*.f", prec, t, prec, sen);

		}



}


void limpiar_buffer(void){

	while(getchar()!='\n');


}
