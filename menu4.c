#include <stdio.h>
#include <math.h>
           /*IMPORTANTE, no se como se hace lo de la precision todavia*/
           /*A esto se refieren con no "hardcodear"?*/
           /*Si, supongo que si ponemos todos los define, en un mismo archivo .h, se puede hacer mucho mas prolijo. O por funcion, ya que por los menos
           las que piden mas parametros necesitan muchos*/
#define Msj_ENTRADA "Bienvenido!\n"
#define Msj_INICIO "\nIngrese lo que se desea hacer:\n1. Muestrar una funcion predefinida\n0. Salir\n"
#define Msj_PARAMETROS "\nIngrese el tiempo inicial de muestro, el tiempo final, y la cantidad de muestras:\n"
#define Msj_MENU "\nSeleccione la funcion que se desea muestrar:\n-1 Seno\n-2 Logaritmo\n-3 Loglineal\n-4 Exponencial\n-5 Heaviside\n-6 Mrua\n-7 Paraboloide Hiperbolico\n-8 Volver al inicio\n\n"
#define Msj_CIERRE "Fin del programa\n"
#define pi 3.14159
#define MSJ_SEN_FRQ "\nIngrese la frecuencia\n"
#define MSJ_SEN_FAS "\nIngrese la fase\n"
#define MSJ_SEN_AMP "\nIngrese la amplitud\n"
#define MSJ_MRUA_POS "\nIngese la posicion inicial\n"
#define MSJ_MRUA_VEL "\nIngrese la velocidad inicial\n"
#define MSJ_MRUA_ACEL "\nIngrese la aceleracion\n"

void opcsen(int i_s);
void senoid(float tiempoi, float tiempof, float espacio);
void menu(int caso,float tiempoi,float tiempof,float espacio, float precision);  /*funcion que cree con el switch que seria el menu y las funciones, etc. Habria que poner las funciones ahi*/
void opciones(int caso2);                                                         /*Otra funcion mas*/
void mrua(float tiempoi, float tiempof, float espacio);
void opt_mrua(int indic);

int main (void)
{
    int inicio,opcmenu;
    float Prm[4];        /* vector que sirve para guardar los parametros basicos*/
    float esp;          /* variable espacio que se deja por cada muestra*/
    int i;
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
            for (i=1; i<=4 ; i++)                /*ESte ciclo for es para ir rellenando el vector con parametros*/
            {
                opciones(i);                    /*Es una funcion que cree para no tener tantos printf y scanf*/
                scanf ("%f", &Prm[i]);
            }                                        /* Prm[0]=tiempoinicial, Prm[1]= tiempofinal, Prm[2]=cantidaddemuestras, Prm[3]=precision*/

            esp = (Prm[2]-Prm[1])/Prm[3];              /*HUbiera estado bueno cambiar el nombre de los prm[] pero me da error :( */

            if(Prm[2]<Prm[1])                               /*Esto es para evitar un bucle!*/
            {
                printf("ERROR, el tiempo final es menor al inicial\n"); /*Aca creo que se podria usar lo del return exit_failure que usann en clase, pero no me deja compilar si lo pongo */
            }
            else
            {
                printf ("%s", Msj_MENU);    /*Aca se imprime el menu, y se pide la opcion que el usuario quiere*/
                scanf("%d",&opcmenu);

                menu(opcmenu,Prm[1],Prm[2],esp,Prm[4]);            /*uso de la funcion menu que cree*/

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
                    case 1:
                            senoid(tiempoi, tiempof, espacio);

                            break;

                    case 2:

                            for (tiempoi ; tiempoi<tiempof ; tiempoi+=espacio)
                            {

                                printf("%.4f:%f\n", tiempoi, log10(tiempoi));
                            }
                            break;

                     case 3:
                             for (tiempoi ; tiempoi<tiempof ; tiempoi+=espacio)
                            {
                                aux= tiempoi*log10(tiempoi);
                                printf("%.4f:(%f)*log(%f)\n", tiempoi, tiempoi, aux);
                            }
                            break;
                    case 6:
                            mrua(tiempoi, tiempof, espacio);

                            break;
                }
    return;
}
void opciones(int caso2)
{
switch (caso2)
        {
            case 1: printf("Ingrese el tiempo inicial: "); break;
            case 2: printf("Ingrese el tiempo final: "); break;
            case 3: printf("Ingrese la cantidad de muestras: "); break;
            case 4: printf("Ingrese la precision a utilizar: "); break;
        }
return;
}

void senoid(float tiempoi, float tiempof, float espacio)
{

   float fase=0;
   float amp;
   float frq;/*prsn=Parametros seno*/
   int i_s;
   float t;
   float arg;

    printf("%s",MSJ_SEN_FRQ);
    scanf("%f",&frq);

    printf("%s",MSJ_SEN_AMP);
    scanf("%f",&amp);

    printf("%s",MSJ_SEN_FAS);
    scanf("%f",&fase);

    for(t=tiempoi ; t<tiempof ; t+=espacio){

        arg=sin((2*pi*(frq)*t)+fase);
        printf("%.4f:%f\n",t ,amp*arg);
   }

   return;
}

void mrua(float tiempoi, float tiempof, float espacio){

    float x_in, v_in, acel;
    int i;
    float tm;
    float pos;
    float mrua;

    printf("%s",MSJ_MRUA_POS);
    scanf("%f",&x_in);

    printf("%s",MSJ_MRUA_VEL);
    scanf("%f",&v_in);

    printf("%s",MSJ_MRUA_ACEL);
    scanf("%f",&acel);

    for(tm=tiempoi; tm<tiempof; tm+=espacio){

        mrua=((x_in)+(v_in)*tm+(acel)*0.5*(pow(tm,2)));

        printf("%f:%f\n",tm, mrua);
    }
    return;
}

