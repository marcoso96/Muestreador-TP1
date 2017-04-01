#include <stdio.h>
#include <math.h>

#define Msj_ENTRADA "Bienvenido!\n"                                               /*A esto se refieren con no "hardcodear"?*/
#define Msj_INICIO "Si se desea muestrar una funcion oprima 1, de lo contrario oprima 0:\n"
#define Msj_PARAMETROS "Elija el tiempo inicial de muestro, el tiempo final, y la cantidad de muestras:\n"
#define Msj_MENU "ELija la funcion que se desea muestrar:\n-1 Seno\n-2 Logaritmo\n" 
#define Msj_CIERRE "Fin del programa\n"


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
            else
            {    
                printf ("%s", Msj_MENU);    
                scanf("%d",&a);
    
                switch(a)                                /* Todo esto del switch me pareceria mejor definirlo arriba como una fucion*/
                {
                    case 1:
                            
                            printf("Entraste a 1\n");
                            break;
                        
                    case 2:
                        
                            printf("Entraste a 2\n");
                            for (ti ; ti<=tf ; ti+=s)    
                            {
                                log10(ti);
                                printf("log(%d):%f\n", ti, log10(ti));
                            }
                            break;

                    case 3:

                    case 4:

                    case 5:

                    case 6:

                    case 7:

                    case 8:
                            break; /* ESta opcion es para volver al principio sin imprimir ninguna funcion*/

                        
                }
            }
        }
        
    }

    while (n!=0);
    return 0;
}
