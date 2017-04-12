#ifndef es__h
#define es__h

#define pi 3.1416
#define IND_SEN 1
#define IND_LOG 2
#define IND_LOGLIN 3
#define IND_EXP 4
#define IND_ESC 5
#define IND_MRUA 6
#define IND_PARAB 7
#define IND_VOLVER 0

#define MSJ_FUNCION "Funcion"
#define MSJ_T_FINAL      "Tiempo final: "
#define MSJ_T_INICIAL    "Tiempo inicial: "
#define MSJ_CANT_MUESTRAS "Cantidad de muestras: "
#define MSJ_PRECISION "Ingrese la precision a utilizar: "
#define MSJ_MENU         "Seleccione lo que desea hacer:  "
#define MSJ_MENU_2         "Seleccione la funcion que desea muestrear:  "
#define MSJ_MENU_ERR_OPC "Error: ingreso mal la opcion\n"
#define MSJ_MENU_ERRD "Error: ingreso mal el dato\n"
#define MSJ_MUESTREAR    "Muestrear una funcion predefinida"
#define MSJ_SALIR        "Salir "
#define MSJ_SENOIDAL        "Senoidal: "
#define MSJ_LOGARITMICA     "Logaritmica: "
#define MSJ_LOGLINEAL       "Loglineal: "
#define MSJ_EXPONENCIAL     "Exponencial: "
#define MSJ_ESCALON   "Escalon o Heaviside: "
#define MSJ_MRUA        "MRUA: "
#define MSJ_PARAB     "Paraboloide Hiperbolico: "
#define MSJ_VOLVER      "Volver al menu principal: "

#define MSJ_ERROR         0
#define MSJ_VALIDO        1
#define MSJ_LEER_AMP   "Amplitud:  "
#define MSJ_LEER_FREC  "Frecuencia:  "
#define MSJ_LEER_FASE  "Fase:  "

#define FUNCION_SENOIDAL    "v (t)= amplitud * Sen(2 * pi * frecuencia * tiempo + fase)"
#define FUNCION_MRUA        " x(t)= x+ v*t + 0.5*a*t^2 "
#define FUNCION_HIPERBOLICA   " /f(x,y)/ = ( (x/a)^2 - (y/b)^2 ) con x=y "

#define MSJ_FASE      "Fase en radianes (Considerando un rango de 0 a 2*pi, (pi=3.1416): "
#define MSJ_FRECUENCIA  "Frecuencia: "

#define TABLA_XY "\t T\t\tValor\n\n"
#define MSJ_MRUA_POS "\nIngrese la posicion inicial: "
#define MSJ_MRUA_VEL "\nIngrese la velocidad inicial: "
#define MSJ_MRUA_ACEL "\nIngrese la aceleracion: "

#define MSJ_VALOR        "Ingresar el valor:  "

#define MSJ_CONS_A       "\n\nIngrese valor de 'a' :  "
#define MSJ_CONS_B       "\n\nIngrese valor de 'b' :  "
#define MSJ_MENU         "Seleccione lo que desea hacer:  "

#define MSJ_MENU_OPC0     "1."
#define MSJ_MENU_OPC1	  "0."	

#endif 
