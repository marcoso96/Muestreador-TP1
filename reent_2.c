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
typedef enum {SALIR, PARAM, ERR_OPC_PPAL, INICIO, ERR_OPC_FUN, ERR_DAT, FUNC} t_stat; /*Cambie el orden de param y salir porque asi es como se pide cuando hace el printf (param=0)*/
typedef enum {TIEMPOI, TIEMPOF, CANT_MUESTRAS, PRECISION} t_parametros;
typedef enum {FALSE, TRUE} t_bool; /*Me parece que no es necesario definir que false sea 0 y true 1, creo que eso se hace solo con cada enumeracion que hagas*/


float leer_float();
void limpiar_buffer(void);

void f_log(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_loglin(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_escalon(float tiempoi,float tiempof, int prec,int cant_muestras);
void f_senoidal(float tiempoi, float tiempof, float fase, float amp, float frec, int prec, int cant_muestras);
void f_par_hip(float tiempoi,float tiempof,float a,float b,int prec,int cant_muestras);
void f_mrua(float tiempoi,float tiempof,float pos,float vel,float acel,int prec,int cant_muestras);
void f_exp(float tiempoi,float tiempof, int prec,int cant_muestras);	

int leer_func(void);
t_funciones menu_funcion(void);

int leer_stat(void);
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
                	
/*Esto deberia ser una funcion*/cant_muestras=(int)men_par(param, camb);
                	
								precision=(int)men_par(param,camb);
								
								if(tiempoi>tiempof||precision<0||
								cant_muestras%((int)cant_muestras!=1)||
								cant_muestras<=0){ /*tenia el signo puesto al revez*/
									
									stat=ERR_DAT;
									param=TIEMPOI;
								}
								
								else{/* AGREGUE UN ELSE, me parece que faltaba, si no, definia stat dos veces y te dejaba pasar directo a FUNC*/
								
								stat=FUNC; 
								
								}

								break;
					
					case FUNC:
								tfunc=menu_funcion();
								
								if(tfunc==F_VOLVER) {
									
									stat=INICIO;
									
									break;
								}
								
								else{ /*Aca le agregue un else */
 									/*iguale la funcion a stat porque si no nunca se entera el programa del cambio*/
									stat=funciones(tiempoi, tiempof, cant_muestras, tfunc, precision);  														     
									param=TIEMPOI;  /*Esto lo pongo meramente para que el "lector" se guie con las enumeraciones. Significaria: una vez que se termino de ejecutar 														funciones, param=TIEMPOI y entonces el puntero camb, vuelve a apuntar al comienzo*/
									}
																		
								break;
					
					case ERR_OPC_PPAL:
								
								fprintf(stderr,"\n%s\n",MSJ_MENU_ERR_OPC);
								stat=INICIO;
								
								break;
								
					case ERR_OPC_FUN:
								
								fprintf(stderr,"\n%s\n",MSJ_MENU_ERR_OPC);
								stat=FUNC;			
					
								break;
								
					case ERR_DAT:
								
								fprintf(stderr,"\n%s\n", MSJ_MENU_ERRD);
								stat=PARAM;
								
								break;					
								
					case SALIR: 
								
								fprintf(stderr, "\n%s\n", MSJ_SALIDA);
								return EXIT_SUCCESS;
								
								break;
			}
	}
	return 0;
}

t_stat menu_inicio(void){

	t_stat stat;
	
	fprintf(stderr,"\n%s\n\n%s\t%s\n%s\t%s\n\n\n", MSJ_MENU, MSJ_MENU_OPC1, MSJ_MUESTREAR, MSJ_MENU_OPC0, MSJ_SALIR );
	
	stat=leer_stat();
	
	return stat;

}

int leer_stat(){   /* Aca supuestamente la funcion devulve un t_stat, pero dato es un int, no estoy segura de si esto esta mal o bien*/
	
	int dato;
	t_bool j;
	
	do{
		
		j=scanf("%d", &dato); 

		if(j==FALSE) {
			
			fprintf(stderr, "\n%s\n", MSJ_MENU_ERRD);
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
						
						fprintf(stderr, "\n%s\n",MSJ_T_INICIAL);
						*camb=TIEMPOF;
						return leer_float();
						break;
			
			case TIEMPOF:
						
						fprintf(stderr, "\n%s\n",MSJ_T_FINAL);
						*camb=CANT_MUESTRAS;
						return leer_float();
						break;
			
			case CANT_MUESTRAS:
						
						fprintf(stderr, "\n%s\n",MSJ_CANT_MUESTRAS);	
						*camb=PRECISION;
						return leer_float();
						break;
			
			case PRECISION:			
						
						fprintf(stderr, "\n%s\n",MSJ_PRECISION);
						*camb=PRECISION;
						return leer_float();
						break;
		}
return 0;
}

float leer_float(){
	
	float dato;
	t_bool j;
	do{
		
		limpiar_buffer();
		
		j=scanf("%f", &dato);
		
		if((j==FALSE)){ 

			fprintf(stderr, "\n%s\n", MSJ_MENU_ERRD);
			/*camb--; Esto deberia ocurrir, porque en men_par lo primero que se hace es cambiar la direccion del elemto al que apunta en enum, al siguiente, y si hay un error, deberiamos volver a la posicion anterior con esta misma sentencia, pero se me complica con las funciones ya que esta funcion se usa en otras funciones x.x. PEEROO no es tan relevante*/
			}
		else {j=TRUE;}
	}
	
	while(j==FALSE);
	
	return dato; 
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

int leer_func(){ /* aca cambie t_funciones por int, porque dato es un int*/
	
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
		
	fprintf(stderr,"%s\n\n%s\n\n%s",MSJ_FUNCION, MSJ_PARAB, TABLA_XY);
	
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


void limpiar_buffer(void){
	
	while(getchar()!='\n');
	
	return;
}	
	
