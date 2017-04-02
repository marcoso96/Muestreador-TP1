#include "muestras.h"


void generador_muestras (float v[], float t[], int cant_muestras, int fun,float t_inicial, float t_final)

{ int i;
  float dato;


for(i=0; i<cant_muestras; i++)
{
    t[i]=t_inicial +(i+1)*((t_final- t_inicial)/cant_muestras) ;
    dato= t[i] ;

    switch (fun)
                {
                    case Fun_Senoidal: {

                                        break;
                                        }


                    case Fun_Log:   {
                                    printf("fun 2\n\n") ;

                                    break;
                                    }

                    case Fun_Loglineal: {

                                        break;}


                    case Fun_Exp: {
                                    v[i]= funcion_exponencial(dato);
                                    break;

                                    }


                    case Fun_escalon: {
                                        v[i]= funcion_escalon(dato);

                                        break;
                                        }

                    case Fun_mrua: {
                                        printf("fun 6\n\n") ;
                                        break;

                                    }
                    case Fun_phiper: {
                                        printf("fun 7\n\n") ;
                                        break;
                                    }
}



}


/************** funcion exponencial **********/

float funcion_exponencial (float dato)
{
    return (exp(dato)) ;
}


/*********** funcion partida ************/

float funcion_escalon (float dato)
{
    float positivo=1;
    float negativo=0;

    if (dato>=0)   return positivo

    else            return negativo;

}

