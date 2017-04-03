#include <stdio.h>
#include <math.h>


#include "muestreador.h"

void menu(int caso,float tiempoi, float tiempof, float espacio, int prec);
void opciones(int caso2);
void par(double tin_xy, double tfin_xy, double espacio, int prec);  
void opc_par(int caso3);
void mrua(double tiempoi, double tiempof, double espacio, int prec);
void senoid(double tiempoi, double tiempof, double espacio, int prec);

int main (void)
{
    int inicio, opcmenu,prec;
    float Prm[3]; /* vector que sirve para guardar los parametros basicos*/
    float esp; 
    int f_1, i;         /* variable espacio que se deja por cada muestra*/
    

    printf ("%s", Msj_ENTRADA);

    do
    {
        printf ("%s", Msj_INICIO); /*se pregunta si se quiere muestrar una fucion, si tipean 0 el programa termina*/
        scanf("%d", &inicio);

        if(inicio==0)
        {
            printf ("%s", Msj_CIERRE);
        }

        else
        {
            do
            {
                if(f_1>0) printf("%s", Msj_ER_Menu);
                else printf("%s", Msj_MENU);

                scanf("%d", &opcmenu);
                f_1++;
            }
            while(opcmenu<0 && opcmenu>9);

            f_1=0;

            /*if (opcmenu!=7)
            {*/
			for (i=0; i<=2 ; i++)
			{                /*ESte ciclo for es para ir rellenando el vector con parametros*/

				opciones(i);                    /*Es una funcion que cree para no tener tantos printf y scanf*/
				scanf ("%f", &Prm[i]);
			}  
			
			printf("%s", MSJ_INI_PRE);
			scanf("%d", &prec);
									  /* Prm[0]=tiempoinicial, Prm[1]= tiempofinal, Prm[2]=cantidaddemuestras, Prm[3]=precision*/
			/*prec=err_pre(int prec);*/
			
			esp = (Prm[1]-Prm[0])/Prm[2];

			if(Prm[1]<Prm[0])
			{                               /*Esto es para evitar un BUCL*/
				printf("ERROR, el tiempo final es menor al inicial\n");
			}

			menu(opcmenu,Prm[0],Prm[1],esp,prec);                        /*HUbiera estado bueno cambiar el nombre de los prm[] pero me da error :( */

            }
        }
    while (inicio!=0);

    return 0;
}


    /*Termino el programa*/

void menu(int caso,float tiempoi, float tiempof, float espacio, int prec)
{
    float aux=0;
    float t;
                             /*Esta variable usenla como quieran, sirve como variable auxiliar*/
    switch(caso)
    {
        case 1:
                senoid(tiempoi, tiempof, espacio, prec);

                break;

        case 2:
                for (t=tiempoi ; t<=tiempof ; aux++, t+=aux*espacio){

                    printf("%f:%f\n", t, log10(t));

                    }

                break;

        case 3:
                for (t=tiempoi ; t<tiempof ; t+=espacio){

                    aux= t*log10(tiempoi);
                    printf("%f:%f\n", t, aux);

                   }
                  break;

        case 4:
                for (t=tiempoi; t<tiempof; t+=espacio){

                    printf("%f:%f", t, exp((double)t));
                }

        case 5:
                for (t=tiempoi; t<tiempof; t+=espacio){

                    if (t>=0) printf("%f:%d", t, 1);

                    else printf("%f:%d", t, 0);
                }
                break;

        case 6:
			   mrua(tiempoi, tiempof, espacio, prec);
			   break;

        case 7: 
				par(tiempoi, tiempof, espacio, prec); 
				break;
   }

   return;
}

void par(double tin_xy, double tfin_xy, double espacio, int prec) /*funcion paraboloide*/
{	
	float cons_a, cons_b, t;
	
	printf("%s", MSJ_CONS_A);
	scanf("%f", &cons_a);
	
	
	printf("%s", MSJ_CONS_B);
	scanf("%f", &cons_b);
	
    printf("%s", TABLA_XY);
    

    for(t=tin_xy; t<=tfin_xy; t+=espacio)
    {

        printf("%f|%f|%f\n", tin_xy, tin_xy, pow((tin_xy/cons_a),2)-pow((tin_xy/cons_b),2));

    }

    return;
}

void opciones(int caso2)
{
    switch (caso2){

        case 0: printf("%s", MSJ_INI_TI); break;
        case 1: printf("%s", MSJ_INI_TF); break;
        case 2: printf("%s", MSJ_INI_MUE); break;
    }

    return;
}

void opc_par(int caso3)
{
    switch (caso3)
    {
        case 0: printf("%s", MSJ_PAR_XO); break;
        case 1: printf("%s", MSJ_PAR_YO); break;            /* definir mensajes*/
        case 2: printf("%s", MSJ_PAR_A); break;
        case 3: printf("%s", MSJ_PAR_B); break;
        case 4: printf("%s", MSJ_PAR_INTER); break;
        case 5: printf("%s", MSJ_PAR_MUES); break;
    }

	return;
}
void senoid(double tiempoi, double tiempof, double espacio, int prec){

        float fase=0;
        float amp;
        float frq;                                /*prsn=Parametros seno*/
        float t;
        float arg;

        printf("%s",MSJ_SEN_FRQ);
        scanf("%f",&frq);

        printf("%s",MSJ_SEN_AMP);               /*declare variables por separado, los arrays me fallaban siempre*/
        scanf("%f",&amp);

        printf("%s",MSJ_SEN_FAS);
        scanf("%f",&fase);

        for(t=tiempoi ; t<=tiempof ; t+=espacio){

            arg=sin((2*pi*(frq)*t)+fase);
            printf("%.*f:	%.*f\n", prec,  t, prec, amp*arg);
       }

       return;
    }

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
/*int err_pre(int prec){
			
			do
			{	if(prec<0){
				
						printf("%s", MSJ_ERR_PRE);
						scanf("%d", &prec);     	
						}
			}
			while (prec<0);
			return prec;*/
			
