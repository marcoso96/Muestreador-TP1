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
typedef enum {ERR_DAT, PARAM, ERR_OPC_PPAL, INICIO, ERR_OPC_FUN, SALIR, FUNC} t_stat;
typedef enum {TIEMPOI, TIEMPOF, CANT_MUESTRAS, PRECISION} t_parametros;
typedef enum {FALSE=0, TRUE=1} t_bool;


float leer_float(void);
void limpiar_buffer(void);

void f_log(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_loglin(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_senoidal(float tiempoi, float tiempof, float fase, float amp, float frec, int prec, int cant_muestras);
void f_par_hip(float tiempoi,float tiempof,float a,float b,int prec,int cant_muestras);
void f_mrua(float tiempoi,float tiempof,float pos,float vel,float acel,int prec,int cant_muestras);
void f_exp(float tiempoi,float tiempof, int prec,int cant_muestras);	

t_funciones leer_func(void);
t_funciones menu_funcion(void);

t_stat leer_stat(void);
t_stat menu_inicio(void);
t_stat funciones (float tiempoi, float tiempof, int cant_muestras, t_funciones func, int prec);

float men_par(t_parametros param, t_parametros *camb);

int main(void){
	
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
								
								stat=menu_inicio();
								
								break;
					
					case PARAM:
					
								tiempoi=men_par(param, camb);
								tiempof=men_par(param, camb);
								cant_muestras=(int)men_par(param, camb);
								precision=(int)men_par(param,camb);
								
								if(tiempoi<tiempof){
									
									stat=ERR_DAT;
									param=TIEMPOI;
								}
								
								stat=FUNC;
								
								break;
					
					case FUNC:
								tfunc=menu_funcion();
								
								if(tfunc==F_VOLVER) {
									
									stat=INICIO;
									break;
								}
								
								funciones(tiempoi, tiempof, cant_muestras, tfunc, precision);
								
								break;
					
					case ERR_OPC_PPAL:
								
								fprintf(stderr,"%s\n",MSJ_MENU_ERR_OPC);
								stat=INICIO;
								
								break;
								
					case ERR_OPC_FUN:
								
								fprintf(stderr,"%s\n",MSJ_MENU_ERR_OPC);
								stat=FUNC;			
					
								break;
								
					case ERR_DAT:
								
								fprintf(stderr,"%s\n", MSJ_MENU_ERRD);
								stat=PARAM;
								
								break;					
								
					case SALIR: 
								return EXIT_SUCCESS;
								
								break;
			}
	}
	return 0;
}

t_funciones menu_funcion(void){
		
	fprintf(stderr,"%s\n\n%d\\%s\n%d\\%s\n%d\\%s\n%d\\%s\n%d\\%s\n%d\\%s\n%d\\%s\n%d\\%s\n\n", MSJ_MENU_2, 
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
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_CONS_A);
	a=leer_float();
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_CONS_B);
	b=leer_float();
		
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_PARAB);
	
	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){
			
			parh=((t/a)*(t/a))-((t/b)*(t/b));
			
			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, parh);
	}		
	
	return;
}



void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras){
	
	float t;
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_ESCALON);
	
	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

		
		fprintf(stderr, "\n%.*f\t|%d", prec, t,(t>0)?1:0);
	}

return;
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

	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_MRUA);
	
	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){
			
			posicion_final=pos+vel*t+0.5*acel*t*t;
			
			fprintf(stderr,"\n%.*f\t|%.*f", prec, t, prec, posicion_final);
		}
	
	return;
}						
									
void f_exp(float tiempoi,float tiempof, int prec,int cant_muestras){
	
	float t;
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_EXPONENCIAL);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){
			
			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, exp(t));
	}
	
	return;
}


void f_loglin(float tiempoi,float tiempof, int prec,int cant_muestras){
	
	float t;
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_LOGLINEAL);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){
			
			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, t*log(t));
	}
	
	return;
}

void f_log(float tiempoi,float tiempof, int prec,int cant_muestras){
	
	float t;
	
	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_LOGARITMICA);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){
			
			fprintf(stderr, "\n%.*f\t|%.*f", prec, t, prec, log(t));
	}
	
	return;
}


void f_senoidal(float tiempoi, float tiempof, float fase, float amp, float frec, int prec, int cant_muestras){
	
	float t;
	float sen;
	
	fprintf(stderr,"%s\n" ,MSJ_LEER_AMP);
	amp=leer_float();
	
	fprintf(stderr,"%s\n" ,MSJ_LEER_FASE);
	fase=leer_float();
	
	fprintf(stderr,"%s\n" ,MSJ_LEER_FREC);
	frec=leer_float();

	fprintf(stderr,"%s\n\n%s\n\n\n\n",MSJ_FUNCION, MSJ_SENOIDAL);

	for(t=tiempoi; t<tiempof; t+=((tiempof-tiempoi)/(float)cant_muestras)){

		sen=amp*sin(t*2*pi*frec+fase);
		fprintf(stderr, "\n%*.f\t|%*.f", prec, t, prec, sen);
	
		}
	
	return;
	
}
		
t_stat menu_inicio(void){

	t_stat stat;
	
	fprintf(stderr,"%s\n\n%s\t%s\n%s\t%s\n\n\n", MSJ_MENU, MSJ_MENU_OPC1, MSJ_MUESTREAR, MSJ_MENU_OPC0, MSJ_SALIR );
	
	stat=leer_stat();
	
	return stat;

}
	
t_funciones leer_func(){
	
	int dato;
	t_bool j;
	
	do{
		
		limpiar_buffer();
		
		j=scanf("%d", &dato);
		
		if(j==FALSE||dato<FALSE) 
		
			fprintf(stderr, "\n%s\n", MSJ_MENU_ERRD);
		
		else j=TRUE;
	}
	while(j==FALSE);
	
	return dato;
}

t_stat leer_stat(){
	
	int dato;
	t_bool j;
	
	do{
		
		limpiar_buffer();
		
		j=scanf("%d", &dato);
		
		if(j==FALSE||dato<FALSE) fprintf(stderr, "\n%s\n", MSJ_MENU_ERRD);
		
		else j=TRUE;
	}
	while(j==FALSE);
	
	return dato;
}

float leer_float(){
	
	float dato;
	t_bool j;
	do{
		
		limpiar_buffer();
		
		j=scanf("%f", &dato);
		
		if((j==FALSE)||(dato<FALSE)) fprintf(stderr, "\n%s\n", MSJ_MENU_ERRD);
		
		else j=TRUE;
	}
	
	while(j==FALSE);
	
	return dato; 
}

void limpiar_buffer(void){
	
	while(getchar()!='\n');
	
	return;
}	
	
float men_par(t_parametros param, t_parametros *camb){
	
	switch (param){
			
			case TIEMPOI:
						
						*camb=TIEMPOF;
						return leer_float();
						break;
			
			case TIEMPOF:
			
						*camb=CANT_MUESTRAS;
						return leer_float();
						break;
			
			case CANT_MUESTRAS:
							
						*camb=PRECISION;
						return leer_float();
						break;
			
			case PRECISION:			
						
						*camb=PRECISION;
						return leer_float();
						break;
		}
return 0;
}

	
	
	
	
	
