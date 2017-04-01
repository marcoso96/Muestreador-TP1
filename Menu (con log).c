/*El programa anda! Si quieren pruebenlo, lo unico, cuando pide la funcion, elijan el logaritmo que es la unica que puse hasta ahora!*/
#include <stdio.h>
#include <math.h>

#define Msj_ENTRADA "Bienvenido!\n"                                                         /*A esto se refieren con no "hardcodear"?*/
#define Msj_INICIO "Si se desea muestrar una funcion oprima 1, de lo contrario oprima 0:\n"
#define Msj_PARAMETROS "Elija el tiempo inicial de muestro, el tiempo final, y el paso temporal:\n"
#define Msj_MENU "ELija la funcion que se desea muestrar:\n-1 Seno\n-2 Logaritmo\n"
#define Msj_CIERRE "Fin del programa\n"

void menu(int caso,int tiempoi, int tiempof,int espacio);  /*funcion que cree con el switch que seria el menu y las funciones, etc. Habria que poner las funciones ahi*/

int main (void)
{    
    int n,a,ti,tf,s; /*se podria considerar un cambio en el nombre de las variables en caso de que no se entiendan*/

    printf ("%s", Msj_ENTRADA);
    
    do
    {
        printf ("%s", Msj_INICIO); /*se pregunta si se quiere muestrar una fucion, si tipean 0 el programa termina*/
        scanf("%d",&n);

        if(n==0)
        {
            printf ("%s", Msj_CIERRE);
        }

        else
        {    
            printf ("%s", Msj_PARAMETROS);          /*Aca se va pidiendo los parametro tipo tiempo inicial, etc*/
            scanf("%d",&ti);                        /*Hay alguna forma de mejorar esto de los scanf?*/
            scanf("%d",&tf);                        
            scanf("%d",&n);
            s= (tf-ti)/n;                           /*Aca se guarda el valor del espacio temporal, en mi caso esta variable la uso en el for, para las funciones*/
            
            if(tf<ti)                               /*Esto es para evitar un bucle!*/
            { 
                printf("ERROR, el tiempo final es menor al inicial\n"); /*Aca creo que se podria usar lo del return exit_failure que usann en clase, pero no me deja compilar si lo pongo*/
            }            
            else
            {    
                printf ("%s", Msj_MENU);    /*Aca se imprime el menu, y se pide la opcion que el usuario quiere*/
                scanf("%d",&a);
    
                menu(a,ti,tf,s);            /*uso de la funcion menu que cree*/

            }
        }   
    }

    while (n!=0);           /*Mientras que el usuario siga oprimiendo 1 en vez de 0, el programa no termina, lo deja graficar cuantas veces quiera y diferetes funciones con diferentes parametros*/
    return 0;
}
/*Termino el main*/
                       
void menu(int caso,int tiempoi, int tiempof,int espacio)
{
    switch(caso)                                
                {
                    case 1:                                 /*Vayan agregando sus funciones aca!*/
            
                            break;
                        
                    case 2:
                        
                            for (tiempoi ; tiempoi<=tiempof ; tiempoi+=espacio)    
                            {
                                printf("log(%d):%f\n", tiempoi, log10(tiempoi));
                            }
                            break;

                        
                }
    return;
}
