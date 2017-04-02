#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "muestras.h"
#include "muestras.c"


typedef  enum { SALIR=0, INGRESAR} t_bool;
typedef  enum { Fun_Senoidal= 1, Fun_Log, Fun_Loglineal, Fun_Exp, Fun_escalon, Fun_mrua, Fun_phiper} t_funciones;

#define MAX_MUESTRAS  100

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
    j=scanf("%d",&t_inicial);
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
    j=scanf("%d",&t_final);
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
    case Fun_Senoidal: { printf("fun 1\n\n") ;

                        break;
                        }
    case Fun_Log:   {printf("fun 2\n\n") ;

                    break;
                    }
    case Fun_Loglineal: {
                    printf("fun 3\n\n") ;
                    break;}


    case Fun_Exp: {
                    generador_muestras (v, t, cant_muestras,Fun_Exp, t_inicial, t_final)

                     ;
                    break;}
    case Fun_escalon: {
                    printf("fun 5\n\n") ;
                    break;}
    case Fun_mrua: {
                printf("fun 6\n\n") ;
                break;}
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

