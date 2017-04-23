#ifndef ES__H
#define ES__H

#define MSJ_INGRESO_PARAMETROS "Ingrese los parametros de las muestras"
#define MSJ_SALIDA "ADIOS!"
#define MSJ_FUNCION "Funcion"
#define MSJ_T_FINAL      "Tiempo final "
#define MSJ_T_INICIAL    "Tiempo inicial "
#define MSJ_CANT_MUESTRAS "Cantidad de muestras "
#define MSJ_PRECISION "Ingrese la precision a utilizar "
#define MSJ_MENU         "Seleccione lo que desea hacer  "
#define MSJ_MENU_2         "Seleccione la funcion que desea muestrear  "
#define MSJ_ERROR "Error"
#define MSJ_ERROR_OPC "Ingreso mal la opcion"
#define MSJ_ERROR_DATO "Ingreso mal el dato"
#define MSJ_ERROR_CANTMAX_INTENTOS "Supero la cantidad de intentos posibles para ingresar datos"
#define MSJ_MUESTREAR    "Muestrear una funcion predefinida"
#define MSJ_SALIR        "Salir "
#define MSJ_SENOIDAL        "Senoidal "
#define MSJ_LOGARITMICA     "Logaritmica "
#define MSJ_LOGLINEAL       "Loglineal "
#define MSJ_EXPONENCIAL     "Exponencial "
#define MSJ_ESCALON   "Escalon o Heaviside "
#define MSJ_MRUA        "MRUA "
#define MSJ_PARAB     "Paraboloide Hiperbolico "
#define MSJ_VOLVER      "Volver al menu principal"

#define MSJ_LEER_AMP   "Amplitud  "
#define MSJ_LEER_FREC  "Frecuencia  "
#define MSJ_LEER_FASE  "Fase  "

#define FUNCION_SENOIDAL    "v (t)= amplitud * Sen(2 * pi * frecuencia * tiempo + fase)"
#define FUNCION_MRUA        " x(t)= x+ v*t + 0.5*a*t^2 "
#define FUNCION_HIPERBOLICA   " /f(x,y)/ = ( (x/a)^2 - (y/b)^2 ) con x=y "

#define MSJ_FASE      "Fase en radianes (Considerando un rango de 0 a 2*pi, (pi=3.1416) "
#define MSJ_FRECUENCIA  "Frecuencia "

#define TABLA_XY "t|f(t)"
#define MSJ_MRUA_POS "Ingrese la posicion inicial "
#define MSJ_MRUA_VEL "Ingrese la velocidad inicial "
#define MSJ_MRUA_ACEL "Ingrese la aceleracion "

#define MSJ_VALOR        "Ingresar el valor  "

#define MSJ_CONS_A       "Ingrese valor de 'a'   "
#define MSJ_CONS_B       "Ingrese valor de 'b'   "

#define ENCABEZADO_XY "t|f(t)"

#endif
