#include <stdio.h>
#include <math.h>

#define Msj_ENTRADA "Bienvenido!\n"                                                                        /*A esto se refieren con no "hardcodear"?*/
#define Msj_INICIO "Si se desea muestrar una funcion oprima 1, de lo contrario oprima 0:\n"
#define Msj_PARAMETROS "Elija el tiempo inicial de muestro, el tiempo final, y el paso temporal:\n"
#define Msj_MENU "ELija la funcion que se desea muestrar:\n-1 Seno\n-2 Logaritmo\n"
#define Msj_CIERRE "Fin del programa\n"

void menu(int caso,int tiempoi, int tiempof,int espacio);  /*funcion que cree con el switch que seria el menu y las funciones, etc. Habria que poner las funciones ahi*/


int main (void)
{    
    int n,a,ti,tf,s;

    printf ("%s", Msj_ENTRADA);
    
    do
    {
        printf ("%s", Msj_INICIO);
        scanf("%d",&n);

        if(n==0)
        {
            printf ("%s", Msj_CIERRE);
        }

        else
        {    
            printf ("%s", Msj_PARAMETROS);
            scanf("%d",&ti);                        /*Hay alguna forma de mejorar esto de los scanf?*/
            scanf("%d",&tf);                        
            scanf("%d",&n);
            s= (tf-ti)/n;
            
            if(tf<ti)
            { 
                printf("ERROR, el tiempo final es menor al inicial\n"; /*Aca creo que se podria usar lo del return exit_failure que usann en clase, pero no me deja compilar si lo pongo*/
            }            
            else
            {    
                printf ("%s", Msj_MENU);    
                scanf("%d",&a);
    
                menu(a,ti,tf,s);

            }
        }
        
    }

    while (n!=0);
    return 0;
}

void menu(int caso,int tiempoi, int tiempof,int espacio)
{
    switch(caso)                                
                {
                    case 1:
                            
                            printf("Entraste a 1\n");
                            break;
                        
                    case 2:
                        
                            printf("Entraste a 2\n");
                            for (tiempoi ; tiempoi<=tiempof ; tiempoi+=espacio)    
                            {
                                log10(tiempoi);
                                printf("log(%d):%f\n", tiempoi, log10(tiempoi));
                            }
                            break;

                        
                }
    return;
}
