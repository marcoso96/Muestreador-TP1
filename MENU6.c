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

#define MSJ_INI_TI "Ingrese el tiempo inicial: "
#define MSJ_INI_TF "Ingrese el tiempo final: "
#define MSJ_INI_MUE "Ingrese la cantidad de muestras: "
#define MSJ_INI_PRE "Ingrese la precision a utilizar: "

#define pi 3.14159

#define MSJ_SEN_FRQ "\nIngrese la frecuencia: "
#define MSJ_SEN_FAS "\nIngrese la fase: "
#define MSJ_SEN_AMP "\nIngrese la amplitud: "

#define MSJ_MRUA_POS "\nIngrese la posicion inicial: "
#define MSJ_MRUA_VEL "\nIngrese la velocidad inicial: "
#define MSJ_MRUA_ACEL "\nIngrese la aceleracion: "

#define MSJ_PAR_XO "\nIngrese el parametro Xo: "
#define MSJ_PAR_YO "\nIngrese el parametro Yo: "
#define MSJ_PAR_A "\nIngrese la constante A: "
#define MSJ_PAR_B "\nIngrese la constante B: "
#define MSJ_PAR_INTER "\nIngrese el intervalo entre muestras: "
#define MSJ_PAR_MUES "\nIngrese la cantidad de muestras: "
#define Msj_ER_Menu "\nIngrese un valor valido\n"

#define MSJ_PAR_ERPRE "\n ERROR: Ingrese una precision entera mayor a 0\n"
#define TABLA_XY "\nX|Y|f(x,y)\n"
#define DISP_PARAB "\nParaboloide Hiperbolico de la forma f(x,y)=(x/a)^2+(y/b)^2\n"

void menu(int caso,float tiempoi,float tiempof,float espacio, float precision);  /*funcion que cree con el switch que seria el menu y las funciones, etc. Habria que poner las funciones ahi*/
void opciones(int caso2);
void menu_par(double x_in, double y_in, double cons_a, double cons_b, double intev, double muest, int prec);    /*Menu solo para paraboloide*/
void opc_par(int caso3);
void mrua(float tiempoi, float tiempof, float espacio, float prec);
void senoid(float tiempoi, float tiempof, float espacio, float prec);

int main (void){

    int inicio;
	int opcmenu;
    float Prm[3]; /* vector que sirve para guardar los parametros basicos*/
	int prec;        /*para paraboloide*/
	double Parab[5];  /*guarda variables de paraboloide( x _inicial, Y_inicial, a, b, intervalo, muestras)*/
	float esp;          /* variable espacio que se deja por cada muestra*/
    int i, f_1=0, f_2=0;

	printf ("%s", Msj_ENTRADA);

    do{
        printf ("%s", Msj_INICIO); /*se pregunta si se quiere muestrar una fucion, si tipean 0 el programa termina*/
        scanf("%d",&inicio);

        if(inicio==0){

			printf ("%s", Msj_CIERRE);
        }
		else{

			do{
				if(f_1>0) printf("%s", Msj_ER_Menu);
				else printf("%s", Msj_MENU);

				scanf("%d", &opcmenu);
				f_1++;
			}
			while(opcmenu<0 && opcmenu>9);

			f_1=0;

			if (opcmenu==7){

				printf("%s", DISP_PARAB);

				for(i=0; i<=5; i++){

						opc_par(i);/*scanf si escanea un 7 de paraboloide, desarrolla menu parab*/ /*uso de la funcion menu que cree*/
						scanf("%f", &Parab[i]);
					}

				do{

					if(f_2>0) printf("\n%s", MSJ_PAR_ERPRE);
					else printf("\n%s", MSJ_INI_PRE);

					scanf("%d", prec);
					f_2++;						/*flag para marcar que ya paso una vez por el pedido normal*/

					}
				while (prec<0);

                f_2=0;

			menu_par(Parab[0],Parab[1],Parab[2],Parab[3],Parab[4],Parab[5],prec); /*xo, yo, a, b, intervalo, cant de muestras, precision*/

			}


			else {

				for (i=0; i<4 ; i++){                /*ESte ciclo for es para ir rellenando el vector con parametros*/

					opciones(i);                    /*Es una funcion que cree para no tener tantos printf y scanf*/
					scanf ("%f", &Prm[i]);
				}                                        /* Prm[0]=tiempoinicial, Prm[1]= tiempofinal, Prm[2]=cantidaddemuestras, Prm[3]=precision*/

				do{
					printf("%s", MSJ_INI_PRE);
					scanf("%f", &prec);/*consige el entero precision*/
				}
				while (prec<0);

				esp = (Prm[1]-Prm[0])/Prm[2];

				if(Prm[1]<Prm[0]){                               /*Esto es para evitar un BUCL*/

				printf("ERROR, el tiempo final es menor al inicial\n"); /*Aca creo que se podria usar lo del return exit_failure que usann en clase, pero no me deja compilar si lo pongo */
				}

              menu(opcmenu,Prm[0],Prm[1],esp,Prm[3]);						/*HUbiera estado bueno cambiar el nombre de los prm[] pero me da error :( */
			}
        }
    }

    while (inicio!=0);           /*Mientras que el usuario siga oprimiendo 1 en vez de 0, el programa no termina, lo deja graficar cuantas veces quiera y diferetes funciones con diferentes parametros*/
    return 0;
}
/*Termino el programa*/

void menu(int caso,float tiempoi,float tiempof,float espacio,float prec){

    float aux;                         /*Esta variable usenla como quieran, sirve como variable auxiliar*/
    switch(caso)
                {
                    case 1:
                            senoid(tiempoi, tiempof, espacio, prec);

                            break;

                    case 2:
                            for (tiempoi ; tiempoi<=tiempof ; tiempoi+=espacio)
                            {
                                printf("%f:%.*f\n", tiempoi, (int)prec, log10(tiempoi));
                            }
                            break;

                     case 3:
                             for (tiempoi ; tiempoi<tiempof ; tiempoi+=espacio)
                            {
                                aux= tiempoi*log10(tiempoi);
                                printf("%f:(%.*f)*log(%.*f)\n", tiempoi, (int)prec, tiempoi, prec, aux);
                            }
                            break;

                    case 6:
                            mrua(tiempoi, tiempof, espacio, prec);

                            break;
                }
    return;
}

void menu_par(double x_in, double y_in, double cons_a, double cons_b, double espacio, double muest, int prec){		/*funcion paraboloide*/

	double x;
	double y;

	printf("%s", TABLA_XY);

	for(x=x_in,y=y_in; x<=(x_in+(muest*espacio)); x+=espacio, y+=espacio){

		printf("%f|%f|%.*f\n", x, y, prec, (pow((x/cons_a),2))-(pow((y/cons_b),2)));

	}
	return;
}

void opciones(int caso2){
switch (caso2){

            case 0: printf("%s", MSJ_INI_TI); break;
            case 1: printf("%s", MSJ_INI_TF); break;
            case 2: printf("%s", MSJ_INI_MUE); break;
            case 3: printf("%s", MSJ_INI_PRE); break;
        }
return;
}

void opc_par(int caso3){

	switch (caso3)
        {
            case 0: printf("%s", MSJ_PAR_XO); break;
            case 1: printf("%s", MSJ_PAR_YO); break;			/* definir mensajes*/
			case 2: printf("%s", MSJ_PAR_A); break;
            case 3: printf("%s", MSJ_PAR_B); break;
			case 4: printf("%s", MSJ_PAR_INTER); break;
			case 5: printf("%s", MSJ_PAR_MUES); break;
			}
return;
}

void senoid(float tiempoi, float tiempof, float espacio, float prec){

	float fase=0;
	float amp;
	float frq;                                /*prsn=Parametros seno*/
	int i_s;
	float t;
	float arg;

	printf("%s",MSJ_SEN_FRQ);
    scanf("%f",&frq);

    printf("%s",MSJ_SEN_AMP);               /*declare variables por separado, los arrays me fallaban siempre*/
    scanf("%f",&amp);

    printf("%s",MSJ_SEN_FAS);
    scanf("%f",&fase);

    for(t=tiempoi ; t<tiempof ; t+=espacio){

        arg=sin((2*pi*(frq)*t)+fase);
        printf("%f:%0.*f\n", t, (int)prec, amp*arg);
   }

   return;
}

void mrua(float tiempoi, float tiempof, float espacio, float prec){

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

        printf("%f:%.*f\n",tm, (int)prec, mrua);
    }
    return;
}


