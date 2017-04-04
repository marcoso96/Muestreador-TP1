#ifndef es__h
#define es__h
#endif // es__h

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
#define MSJ_MENU_ERR "Error: ingreso mal la opcion\n"
#define MSJ_MENU_ERRD "Error: ingreso mal el dato\n"
#define MSJ_MUESTREAR    "1 Muestrear una funcion predefinida"
#define MSJ_SALIR        "0 Salir "
#define MSJ_SENOIDAL        "1. Senoidal: "
#define MSJ_LOGARITMICA     "2. Logaritmica: "
#define MSJ_LOGLINEAL       "3. Loglineal: "
#define MSJ_EXPONENCIAL     "4. Exponencial: "
#define MSJ_ESCALON_HEAVISIDE   "5. Escalon o Heaviside: "
#define MSJ_MRUA        "6. MRUA: "
#define MSJ_PARABOLOIDE_HIPERBOLICO     "7. Paraboloide Hiperbolico: "
#define MSJ_VOLVER      "0. Volver al menu principal: "
#define MSJ_ERROR         0
#define MSJ_VALIDO        1
#define MSJ_AMPLITUD   "Amplitud:  "

#define FUNCION_SENOIDAL    "v (t)= amplitud * Sen(2 * pi * frecuencia * tiempo + fase)"
#define FUNCION_MRUA        " x(t)= x+ v*t + 0.5*a*t^2 "
#define FUNCION_HIPERBOLICA   " /f(x,y)/ = ( (x/a)^2 - (y/b)^2 ) con x=y "

#define MSJ_FASE      "Fase en radianes (Considerando un rango de 0 a 2*pi, (pi=3.1416): "
#define MSJ_FRECUENCIA  "Frecuencia: "

#define FUNCION_A_MUESTREAR  "Funcion a muestrear: "
#define TABLA_XY "\t T\t\tValor\n\n"
#define MSJ_MRUA_POS "\nIngrese la posicion inicial: "
#define MSJ_MRUA_VEL "\nIngrese la velocidad inicial: "
#define MSJ_MRUA_ACEL "\nIngrese la aceleracion: "

#define MSJ_VALOR        "Ingresar el valor:  "

#define VALOR_Z       "\n\nIngrese valor de 'z' :  "
#define VALOR_A       "\n\nIngrese valor de 'a' :  "
#define VALOR_B       "\n\nIngrese valor de 'b' :  "
