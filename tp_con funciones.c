#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//#include "muestras.h"
//#include "muestras.c"


typedef  enum { SALIR=0, INGRESAR} t_bool;
typedef  enum { Fun_Senoidal= 1, Fun_Log, Fun_Loglineal, Fun_Exp, Fun_escalon, Fun_mrua, Fun_phiper} t_funciones;
typedef  enum { dato_amp=0, dato_fase=1, dato_frec=2 } t_parametros;
typedef   enum  { mrua_x, mrua_v, mrua_a} t_mrua;


void generador_muestras (float v[], float t[], int cant_muestras, int fun,float t_inicial, float t_final, int precision) ;
float funcion_exponencial (float dato);
float funcion_escalon (float dato);
float funcion_senoidal (float dato, float AMP, float FASE, float FREC);

void  cargar_datos_senoidal (float AMP, float FASE, float FREC);
float cargar_seno (t_parametros datos);
float cargar_mrua (t_mrua dato ) ;

float  funcion_mrua(float dato,float  x,float v,float a) ;


#define MAX_MUESTRAS  100
#define pi 3.1416

#define CALCULO_T(tinf,tsup,i)   (tinf+i*(tsup-tinf)/( MAX_MUESTRAS -1))
#define MSJ_DOMINIO      "Ingresar en que intervalo de 't' desea trabajar: "
#define MSJ_T_FINAL      "Tiempo final: "
#define MSJ_T_INICIAL    "Tiempo inicial: "
#define MSJ_CANT_MUESTRAS "Cantidad de muestras: "
#define MSJ_PRECISION "Ingrese la precision a utilizar: "
#define MSJ_MENU         "Seleccione lo que desea hacer:  "
#define MSJ_MENU_2         "Seleccione la funcion que desea muestrear:  "
#define MSJ_MUESTREAR    "1 Muestrear una funcion predefinida"
#define MSJ_SALIR        "0 Salir "
#define MSJ_SENOIDAL        "1. Senoidal: "
#define MSJ_LOGARITMICA     "2. logaritmica: "
#define MSJ_LOGLINEAL       "3. loglineal: "
#define MSJ_EXPONENCIAL     "4. exponencial: "
#define MSJ_ESCALON_HEAVISIDE   "5. escalon o Heaviside: "
#define MSJ_MRUA        "6. mrua: "
#define MSJ_PARABOLOIDE_HIPERBOLICO     "7. parabolico hiperbolico: "
#define MSJ_VOLVER      "0. volver al menu principal: "
#define MSJ_ERROR         0
#define MSJ_VALIDO        1
#define MSJ_AMPLITUD   "Amplitud:  "

#define FUNCION_SENOIDAL    "v (t)= amplitud * Sen(2 * pi * frecuencia * tiempo + fase)"
#define FUNCION_MRUA        " x(t)= x+ v*t + 0.5*a*t^2 "

#define MSJ_FASE      "Fase en radianes (Considerando un rango de 0 a 2*pi, (pi=3.1416): "
#define MSJ_FRECUENCIA  "Frecuencia: "

#define FUNCION_A_MUESTREAR  "Funcion a muestrear: "

#define MSJ_MRUA_POS "\nIngrese la posicion inicial: "
#define MSJ_MRUA_VEL "\nIngrese la velocidad inicial: "
#define MSJ_MRUA_ACEL "\nIngrese la aceleracion: "






// #define FUNCION_EXP


int main (void)
{ //double suma=0;
  //double muestras[MAX_MUESTRAS];
 // double coef[GRADO+1];
  t_bool opcion ;
  float t_inicial, t_final, base;
  size_t i;
  int j=0;
  t_funciones opciones;
  int repetir=1;
  int cant_muestras, precision;
  float v[MAX_MUESTRAS] , t[MAX_MUESTRAS] ;
  float AMP, FASE, FREC;



/************************* MENU ***************************************/
do{
repetir=1;
fprintf(stderr,"%s\n\n%s\n%s\n\n\n", MSJ_MENU, MSJ_MUESTREAR, MSJ_SALIR );

scanf("%d", &opcion) ;

if( opcion!=SALIR && opcion!=INGRESAR)
    {
      fprintf(stderr,"error: ingreso mal la opcion\n");
      return EXIT_FAILURE;
    } ;

if ( opcion==SALIR)
                return EXIT_FAILURE ;


                /*ENTRADA*/
do{
    while(getchar()!='\n');
    fprintf(stderr,"%s",MSJ_T_INICIAL);
    j=scanf("%f",&t_inicial);
    if( j==0 ){
            fprintf(stderr,"error: ingreso mal el dato\n");
                 }
    else  j =1;
}
while( j==0);

/*al salir del ciclo se obtendra un valor de tiempo mayor o igual a cero ya que el tiempo*/
/*se introduce el valor minimo de tiempo con el que se trabajara*/
do{
    while(getchar()!='\n');
    fprintf(stderr,"%s",MSJ_T_FINAL);
    j=scanf("%f",&t_final);
    if( j==0 || t_final<=t_inicial ){
            fprintf(stderr,"error: ingreso mal el dato\n\n");
            j=0;
                 }
    else  j =1;
}
while( j==0);

do{
    while(getchar()!='\n');
    fprintf(stderr,"%s",MSJ_CANT_MUESTRAS);
    j=scanf("%d",&cant_muestras);
    if( j==0 && cant_muestras<=0){
            fprintf(stderr,"error: ingreso mal el dato\n");
                 }
    else  j =1;
}
while( j==0);
do{
    while(getchar()!='\n');
    fprintf(stderr,"%s",MSJ_PRECISION);
    j=scanf("%d",&precision);
    if( j==0 || precision<0 ){
            fprintf(stderr,"error: ingreso mal el dato\n");
                 }
    else  j =1;
}
while( j==0);

/*---MENU DE FUNCIONES---*/
fprintf(stderr,"%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n\n", MSJ_MENU_2, MSJ_SENOIDAL,MSJ_LOGARITMICA, MSJ_LOGLINEAL,MSJ_EXPONENCIAL,
        MSJ_ESCALON_HEAVISIDE,MSJ_MRUA,MSJ_PARABOLOIDE_HIPERBOLICO, MSJ_VOLVER);

scanf("%i", &opciones) ;


switch (opciones) {

    case SALIR: {
            repetir=0;
            break;
                }
    case Fun_Senoidal: {

                        generador_muestras (v, t, cant_muestras,Fun_Senoidal, t_inicial, t_final, precision);

                        break;
                        }

    case Fun_Log:   {
                        printf("\t T\t\tValor\n\n");
                        generador_muestras (v, t, cant_muestras,Fun_Log, t_inicial, t_final, precision);

                        break;
                    }
    case Fun_Loglineal: {    printf("\t T\t\tValor\n\n");
                            generador_muestras (v, t, cant_muestras,Fun_Loglineal, t_inicial, t_final, precision);



                            break;
                        }


    case Fun_Exp: {
                    printf("\t T\t\tValor\n\n");
                    generador_muestras (v, t, cant_muestras,Fun_Exp, t_inicial, t_final, precision);

                    break;
                    }
    case Fun_escalon: {
                        printf("\t T\t\tValor\n\n");
                        generador_muestras (v, t, cant_muestras,Fun_escalon, t_inicial, t_final, precision);

                        break;
                        }
    case Fun_mrua: {

                      generador_muestras (v, t, cant_muestras,Fun_mrua, t_inicial, t_final, precision);

                     break;

                   }

    case Fun_phiper: {
                    printf("fun 7\n\n") ;
                    break;
                    }

    default:
        fprintf(stderr,"error: ingreso mal la opcion\n");

}

}while(repetir==0);


return EXIT_SUCCESS;
}


/**************/

//#include "muestras.h"


void generador_muestras (float v[], float t[], int cant_muestras, int fun,float t_inicial, float t_final, int precision)

{ int i;
  float dato, aux=0;

 float AMP, FASE, FREC ;
 float vel, acel, posicion ;



for(i=0; i<cant_muestras; i++)
{
    t[i]=t_inicial +(i+1)*(float)((t_final- t_inicial)/(float)cant_muestras) ;

    dato= t[i] ;

    switch (fun)
                {
                    case Fun_Senoidal: {  if ( aux==0)
                                              {  //printf( "usted esta a punto de cargar datos seno \n");
                                                 fprintf(stderr,"%s\n\n%s\n\n\n\n",FUNCION_A_MUESTREAR,FUNCION_SENOIDAL);
                                                // printf("2pi: %f\n", 2*pi) ;

                                                 AMP= cargar_seno(dato_amp) ;
                                                 FASE= cargar_seno(dato_fase);
                                                 FREC=cargar_seno (dato_frec);

                                                aux=1 ;

                                                printf("\t T\t\tValor\n\n");

                                              } ;


                                        v[i]= funcion_senoidal(dato, AMP, FASE, FREC) ;
                                        printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);
                                        break;
                                        }


                    case Fun_Log:   {
                                        v[i]= log(dato) ;
                                        printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);

                                        break;
                                    }

                    case Fun_Loglineal: {
                                            v[i]= dato*log(dato) ;
                                            printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);

                                            break;
                                        }


                    case Fun_Exp: {
                                    v[i]= funcion_exponencial(dato);
                                    printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);
                                    break;

                                    }


                    case Fun_escalon: {
                                        v[i]= funcion_escalon(dato);
                                        printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);
                                        break;
                                        }

                    case Fun_mrua: {   if ( aux==0)
                                              {  //printf( "usted esta a punto de cargar datos seno \n");
                                                 fprintf(stderr,"%s\n\n%s\n\n\n\n",FUNCION_A_MUESTREAR,FUNCION_MRUA);


                                                 posicion= cargar_mrua(mrua_x) ;
                                                 vel= cargar_mrua(mrua_v);
                                                 acel=cargar_mrua(mrua_a);

                                                aux=1 ;

                                                printf("\t T\t\tValor\n\n");

                                              } ;

                                        v[i]= funcion_mrua(dato, posicion, vel, acel) ;
                                        printf("\t%.*f%20.*f\n",  precision, t[i], precision, v[i]);
                                        break;


                                    }
                    case Fun_phiper: {
                                        printf("fun 7\n\n") ;
                                        break;
                                    }
}


}
}


/************** funcion exponencial **********/

float funcion_exponencial (float dato)
{
    return (exp(dato)) ;
} ;


/*********** funcion partida ************/

float funcion_escalon (float dato)
{
    float positivo=1;
    float negativo=0;

    if (dato>=0)   return positivo ;

    else            return negativo;

}

/***********datos ***senoidal ***********/

float cargar_seno (t_parametros datos)

{float variable;
int j;

switch (datos)
   {
       case dato_amp : {  fprintf(stderr,"\n%s",MSJ_AMPLITUD);


                            do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_AMPLITUD);
                                j=scanf("%f",&variable);
                                if( j==0 ){
                                        fprintf(stderr,"error: ingreso mal el dato\n");
                                        }
                                else  j =1;
                                }
                        while( j==0);

                        return variable;
                        break;
                        }

     case dato_fase :  {
                         do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_FASE);
                                j=scanf("%f",&variable);

                                if( j==0 ){
                                            fprintf(stderr,"Error: ingreso mal la fase\n");
                                            }
                                else  j =1;
                            }
                        while( j==0 ||!(variable<=2*pi) ||   !(variable>=0) );


                        return variable;
                        break;
                        }

    case dato_frec : {
                        do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_FRECUENCIA);
                                j=scanf("%f",&variable);
                                if( j==0 ){
                                        fprintf(stderr,"Error: ingreso mal la frecuencia\n");
                                            }
                                else  j =1;
                            }
                        while( j==0);
                        return variable;
                        break;


                    }





       }
   }




/********************** senoidal *************/


float funcion_senoidal (float dato, float AMP, float FASE, float FREC)

{
//printf( "dato*2pi frec :  %f\n", dato*2*pi*FREC);
// printf( "seeeeeeeenoo   %f\n", AMP* sin( (dato*2*pi*FREC)+ FASE ));
return  AMP*sin( dato*2*pi*FREC+ FASE ) ;



}

/**************   cargar datos mrua ************/

float cargar_mrua (t_mrua dato )

{ float variable;
  int j;

    switch (dato)
    {
        case mrua_x : {
                         do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_MRUA_POS);
                                j=scanf("%f",&variable);
                                if( j==0 ){
                                        fprintf(stderr,"Error: ingreso mal la posicion\n\n");
                                            }
                                else  j =1;
                            }
                        while( j==0);
                        return variable;
                        break;
                    }

        case mrua_v : {
                        do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_MRUA_VEL);
                                j=scanf("%f",&variable);
                                if( j==0 ){
                                        fprintf(stderr,"Error: ingreso mal la velocidad\n\n");
                                            }
                                else  j =1;
                            }
                        while( j==0);
                        return variable;
                        break;
                    }

        case mrua_a:  {
                        do{
                                while(getchar()!='\n');
                                fprintf(stderr,"\n%s",MSJ_MRUA_ACEL);
                                j=scanf("%f",&variable);
                                if( j==0 ){
                                        fprintf(stderr,"Error: ingreso mal la aceleracion\n\n");
                                            }
                                else  j =1;
                            }
                        while( j==0);

                        return variable;
                        break;
                       }


        }

    }


/*************** funcion mrua **************/



float  funcion_mrua(float dato,float  x,float v,float a)
{

    return (x+(v*dato+(a)*0.5*(pow(dato,2)))) ;




}
/*
void mrua(double tiempoi, double tiempof, double espacio, int prec)
{

        float x_in, v_in, acel;
        float tm;
        float mrua;

        printf("%s",MSJ_MRUA_POS);
        scanf("%f",&x_in);

        printf("%s",MSJ_MRUA_VEL);
        scanf("%f",&v_in);

        printf("%s",MSJ_MRUA_ACEL);
        scanf("%f",&acel);

        for(tm=tiempoi; tm<tiempof; tm+=espacio){

        mrua=((x_in)+(v_in)*tm+(acel)*0.5*(pow(tm,2)));

        printf("%f:%.*f\n",tm, prec, mrua);
    }
    return;
}
*/
