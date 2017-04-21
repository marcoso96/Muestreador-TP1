/*PROGRAMA MUESTREADOR*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "config.h"
#ifdef Lenguaje_ES
#include "macros_reentrega.h"
#endif

typedef enum {F_SENOIDAL=IND_SEN, F_LOG=IND_LOG, F_LOGLINEAL=IND_LOGLIN,
	F_EXPONENCIAL=IND_EXP, F_ESCALON=IND_ESC, F_MRUA=IND_MRUA,
	F_PAR_HIP=IND_PARAB, F_VOLVER=IND_VOLVER} t_funciones;
typedef enum {SALIR, PARAM, ERR_OPC_PPAL, INICIO, ERR_OPC_FUN, ERR_DAT, FUNC} t_stat;
typedef enum {TIEMPOI, TIEMPOF, CANT_MUESTRAS, PRECISION} t_parametros;
typedef enum {FALSE, TRUE} t_bool;
typedef enum {OK, ERR_DAT, ERR_OPC_FUN, ERR_OPC_PPAL} ; /* no deberia tener el nombre del enum? */
typedef enum {CANT_CERO, CANT_UNO, CANT_DOS} t_cantidad; /*agregue cant para no hardcodear en la linea 76, 77 ,78*/

void f_log(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_loglin(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_senoidal(float tiempoi, float tiempof, float fase, float amp, float frec, int prec, int cant_muestras);
void f_par_hip(float tiempoi,float tiempof,float a,float b,int prec,int cant_muestras);
void f_mrua(float tiempoi,float tiempof,float pos,float vel,float acel,int prec,int cant_muestras);
void f_exp(float tiempoi,float tiempof, int prec,int cant_muestras);

float leer_float(void);
int   leer_int (void);

int leer_func(void);
int leer_stat(void);

void limpiar_buffer(void);

t_funciones menu_funcion(void);
t_stat menu_inicio(void);
t_stat funciones (float tiempoi, float tiempof, int cant_muestras, t_funciones func, int prec);

float men_par(t_parametros param, t_parametros *camb);


int main (void) {
	
	t_status status;
	t_stat stat=INICIO;
	t_funciones tfunc;
	t_parametros param=TIEMPOI;
	t_parametros *camb=&param;
	float tiempoi;
	float tiempof;
	int precision;
	int cant_muestras;

	while(1){

			switch (stat){

					case INICIO:

								status=menu_inicio();
								
								break;

					case ST_PARAM:

								tiempoi=leer_double();

								tiempof=leer_double();

                                				cant_muestras=leer_int();

								precision=leer_int();

								if(tiempoi>tiempof||precision< CANT_CERO||
								cant_muestras%((int)cant_muestras!= CANT_UNO)||
								cant_muestras<= CANT_CERO){

									status=ERR_DAT;
									param=TIEMPOI;
								}

								else{

								stat=FUNC;

								}

								break;

					case ST_FUNC:
								tfunc=menu_funcion();

								if(tfunc==F_VOLVER) {

									stat=ST_INICIO;
									status=OK;
									break;
								}

								else{

									stat=funciones(tiempoi, tiempof, cant_muestras, tfunc, precision);
									param=TIEMPOI;
									}

								break;
					case ST_ERR:
								switch(status)
										case OK:
												break;
										case ERR_DAT:
										case ERR_OPC_FUN:
										case ERR_OPC_PPAL:
					case ST_SALIR:

								fprintf(stderr, "\n%s\n", MSJ_SALIDA);
								return EXIT_SUCCESS;

								break;
			}
	}
	return EXIT_SUCESS;
}

t_stat menu_inicio(void){


	fprintf(stderr,"\n%s\n\n%s\t%s\n%s\t%s\n\n\n", MSJ_MENU, MSJ_MENU_OPC1, MSJ_MUESTREAR, MSJ_MENU_OPC0, MSJ_SALIR );

	return leer_stat() ;

}

int leer_stat(void){

	int dato;
	t_bool j;

	do{

		if(!scanf("%d", &dato)) {
			
			j=FALSE; 
			fprintf(stderr, "\n%s:%s\n", MSJ_MENU_ERR, MSJ_MENU_ERRD);
			limpiar_buffer();
			}
		else j=TRUE;
	}
	while(j==FALSE);

	return dato;
}

float men_par(t_parametros param, t_parametros *camb){

	switch (param){

			case TIEMPOI:

						fprintf(stderr, "\n%s:\n",MSJ_T_INICIAL);
						*camb=TIEMPOF;
						return leer_float();
						break;

			case TIEMPOF:

						fprintf(stderr, "\n%s:\n",MSJ_T_FINAL);
						*camb=CANT_MUESTRAS;
						return leer_float();
						break;

			case CANT_MUESTRAS:

						fprintf(stderr, "\n%s:\n",MSJ_CANT_MUESTRAS);
						*camb=PRECISION;
						return (float)leer_int();
						break;

			case PRECISION:

						fprintf(stderr, "\n%s:\n",MSJ_PRECISION);
						*camb=PRECISION;
						return (float)leer_int();
						break;
		}
return EXIT_SUCESS;
}

int leer_int (void) {

	int dato;
	t_bool j;
	do{

		limpiar_buffer();

		if(scanf("%d", &dato)){
			
			j=FALSE;
			fprintf(stderr, "\n%s:%s\n", MSJ_MENU_ERR, MSJ_MENU_ERRD);
			}
		else j=TRUE;
	}

	while(j==FALSE);

	return dato;
}

float leer_float (void) {

	float dato;
	t_bool j;
	do{

		limpiar_buffer();

		if(!scanf("%f", &dato)){

			fprintf(stderr, "\n%s:%s\n", MSJ_MENU_ERR, MSJ_MENU_ERRD);
			j=FALSE;
			}
		else  j=TRUE;
		     
	}

	while(j==FALSE);

	return dato;
}
t_funciones menu_funcion(void){

	fprintf(stderr,"%s\n\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n%d\\%s:\n\n", MSJ_MENU_2,
		IND_SEN, MSJ_SENOIDAL,
		IND_LOG,MSJ_LOGARITMICA,
		IND_LOGLIN, MSJ_LOGLINEAL,
		IND_EXP, MSJ_EXPONENCIAL,
        IND_ESC, MSJ_ESCALON,
        IND_MRUA, MSJ_MRUA,
        IND_PARAB, MSJ_PARAB,
        IND_VOLVER, MSJ_VOLVER);

	return leer_func();
}

int leer_func(void){

	int dato;
	t_bool j;

	do{

		limpiar_buffer();


		if( !scanf("%d", &dato) || dato<FALSE) {

			fprintf(stderr, "\n%s:%s\n", MSJ_MENU_ERR, MSJ_MENU_ERRD);
			j=FALSE;
		        }

		else j=TRUE;
	}
	while(j==FALSE);

	return dato;
}

t_stat funciones (float tiempoi, float tiempof, int cant_muestras, t_funciones func, int prec){

	float amp, fase, frec;
	float vel, acel, pos;
	float a, b;

    switch (func){

				case F_SENOIDAL:

								f_senoidal(tiempoi, tiempof, fase, amp, frec, prec, cant_muestras);

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

								f_mrua(tiempoi, tiempof, pos, vel, acel, prec, cant_muestras);

								break;

				case F_PAR_HIP:

								f_par_hip(tiempoi, tiempof, a, b, prec, cant_muestras);

								break;

				case F_VOLVER:
								return SALIR;


				default:
								return ERR_OPC_FUN;

				}


	return INICIO;

}

void f_par_hip(float tiempoi,float tiempof,float a,float b,int prec,int cant_muestras){

	float parh;
	float t;

	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_A);
	a=leer_float();

	fprintf(stderr,"%s\n\n%s:\n\n",MSJ_FUNCION, MSJ_CONS_B);
	b=leer_float();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_PARAB, MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			parh=((t/a)*(t/a))-((t/b)*(t/b));

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, parh);
	}

}



void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n\n%s",MSJ_FUNCION, MSJ_ESCALON, MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){


		fprintf(stderr, "\n%.*f\t|%d", prec, t,(t>0)?1:0);
	}

	
}


void f_mrua(float tiempoi,float tiempof,float pos,float vel,float acel,int prec,int cant_muestras){

	float t;
	float posicion_final;

	fprintf(stderr,"%s\n" ,MSJ_MRUA_POS);
	pos=leer_float();

	fprintf(stderr,"%s\n" ,MSJ_MRUA_VEL);
	vel=leer_float();

	fprintf(stderr,"%s\n" ,MSJ_MRUA_ACEL);
	acel=leer_float();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_MRUA, MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			posicion_final=pos+vel*t+0.5*acel*t*t;

			fprintf(stderr,"\n%.*f\t|%.*f", prec, t, prec, posicion_final);
		}

	
}

void f_exp(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_EXPONENCIAL,MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, exp(t));
	}

	
}


void f_loglin(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",  MSJ_FUNCION, MSJ_LOGLINEAL,MSJ_TABLA_XY);

	for(t=tiempoi;  t<tiempof;   t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, t*log(t));
	}

	
}

void f_log(float tiempoi,float tiempof, int prec,int cant_muestras){

	float t;

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_LOGARITMICA,MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, log(t));
	}

	
}


void f_senoidal(float tiempoi, float tiempof, float fase, float amp, float frec, int prec, int cant_muestras){

	float t;
	float sen;

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_AMP);
	amp=leer_float();

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FASE);
	fase=leer_float();

	fprintf(stderr,"\n%s:\n" ,MSJ_LEER_FREC);
	frec=leer_float();

	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_SENOIDAL,MSJ_TABLA_XY);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

		sen=amp*sin(t*2*pi*frec+fase);
		fprintf(stderr, "\n%*.f\t|%*.f", prec, t, prec, sen);

		}



}


void limpiar_buffer(void){

	while(getchar()!='\n');

	
}

