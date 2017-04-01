/*El programa anda! Si quieren pruebenlo, lo unico, cuando pide la funcion, elijan el logaritmo o loglineal que son las unicas que puse hasta ahora!*/
#include <stdio.h>
#include <math.h>
   /*IMPORTANTE, no se como se hace lo de la precision todavia*/
   /*A esto se refieren con no "hardcodear"?*/
#define Msj_INICIO "\nIngerese lo que se desea hacer:\n1. Muestrar una funcion predefinida\n0. Salir\n"
#define Msj_PARAMETROS "\nIngrese el tiempo inicial de muestro, el tiempo final, y la cantidad de muestras:\n"
#define Msj_MENU "\nSeleccione la funcion que se desea muestrar:\n-1 Seno\n-2 Logaritmo\n-3 Loglineal\n-4 Exponencial\n-5 Heaviside\n-6 Mrua\n-7 Paraboloide Hiperbolico\n-8 Volver al inicio\n\n"
#define Msj_CIERRE "Fin del programa\n"

void menu(int caso,float tiempoi,float tiempof,float espacio, float precision);  /*funcion que cree con el switch que seria el menu y las funciones, etc. Habria que poner las funciones ahi*/
void opciones(int caso2);                                                         /*Otra funcion mas*/

int main (void)
{    
    int inicio,opcmenu;
    float Prm[4];        /* vector que sirve para guardar los parametros basicos*/
    float esp;          /* variable espacio que se deja por cada muestra*/
    
    printf ("%s", Msj_ENTRADA);
    
    do
    {
        printf ("%s", Msj_INICIO); /*se pregunta si se quiere muestrar una fucion, si tipean 0 el programa termina*/
        scanf("%d",&inicio);

        if(inicio==0)
        {
            printf ("%s", Msj_CIERRE);
        }

        else                        /*Aca empieza el menu*/
        {    
            int i=0;                
            for (i; i<4 ; i++)                /*ESte ciclo for es para ir rellenando el vector con parametros*/
            {    
                opciones(i);                    /*Es una funcion que cree para no tener tantos printf y scanf*/
                scanf ("%f", &Prm[i]);
            }                                        /* Prm[0]=tiempoinicial, Prm[1]= tiempofinal, Prm[2]=cantidaddemuestras, Prm[3]=precision*/

            esp = (Prm[1]-Prm[0])/Prm[2];              /*HUbiera estado bueno cambiar el nombre de los prm[] pero me da error :( */                                 

            if(Prm[1]<Prm[0])                               /*Esto es para evitar un bucle!*/
            { 
                printf("ERROR, el tiempo final es menor al inicial\n"); /*Aca creo que se podria usar lo del return exit_failure que usann en clase, pero no me deja compilar si lo pongo*/
            }            
            else
            {    
                printf ("%s", Msj_MENU);    /*Aca se imprime el menu, y se pide la opcion que el usuario quiere*/
                scanf("%d",&opcmenu);
    
                menu(opcmenu,Prm[0],Prm[1],esp, Prm[3]);            /*uso de la funcion menu que cree*/

            }
        }   
    }

    while (inicio!=0);           /*Mientras que el usuario siga oprimiendo 1 en vez de 0, el programa no termina, lo deja graficar cuantas veces quiera y diferetes funciones con diferentes parametros*/
    return 0;
}
/*Termino el programa*/
                  
void menu(int caso,float tiempoi, float tiempof,float espacio, float precision)
{
    float aux;                         /*Esta variable usenla como quieran, sirve como variable auxiliar*/
    switch(caso)                                
                {
                    case 1:                                 /*Vayan agregando sus funciones aca!*/
            
                            break;
                        
                    case 2:
                        
                            for (tiempoi ; tiempoi<tiempof ; tiempoi+=espacio)    
                            {
                                printf("log(%f):%f\n", tiempoi, log10(tiempoi));
                            }
                            break;
                    
                     case 3:
                             for (tiempoi ; tiempoi<tiempof ; tiempoi+=espacio)    
                            {   
                                aux= tiempoi*log10(tiempoi);
                                printf("(%f)*log(%f):%f\n", tiempoi, tiempoi, aux);
                            }
                            break;

                        
                }
    return;
}

void opciones(int caso2)
{
    switch (caso2)
            {
                case 0: printf("Ingrese el tiempo inicial: "); break;
                case 1: printf("Ingrese el tiempo final: "); break;
                case 2: printf("Ingrese la cantidad de muestras: "); break;
                case 3: printf("Ingrese la precision a utilizar: "); break;
            }
    return;
}
