

typedef enum {ERR, INICIO, ELEG_FUN, SALIR, MENU_FUN} t_stat;
typedef enum {TIEMPOI, TIEMPOF, CANT_MUESTRAS, PRECISION} t_parametros;


int main(){
	
	t_stat status=INICIO; 
	t_parametros param;
	
	float tiempoi;
	float tiempof;
	int muestras;
	int precision;	
	
	while(1){
			
			switch (stat){
			
					case INICIO:
								
								status=menu_inicio();
								
								break;
					
					case ERR_OPC:
								
								fprintf(stderr,"%s\n",MSJ_ERR_OPC);
								
								
								break;
								
					case ERR_DAT:
								
								fprintf(stderr,"%s\n", MSJ_ERR_DAT);
								
								return EXIT_FAILURE;
								
								break;
								
					case FUNC:
								tiempoi=param_float();
								tiempof=param_float();
								cant_muestras=param_int();
								precision=param_int();
								
								break;
								
					case SALIR: 
								return EXIT_SUCCESS;
								
								break;
					}
}

t_stat menu_inicio(void){

	t_stat stat;
	
	
	fprintf(stderr,"%s\n\n%s\t%s\n%s\t%s\n\n\n", MSJ_MENU, MSJ_MENU_OPC1, MSJ_MUESTREAR, MSJ_MENU_OPC0, MSJ_SALIR );
	
	stat=leer_int();
	
	return stat;

}
	

int param_int(){
	
	int dato;
	t_bool j;
	
	do{
		
		limpiar_buffer();
		
		j=scanf("%d", &dato);
		
		if(j==FALSE||dato<FALSE) fprintf(stderr, "\n%s\n", MSJ_MENU_ERR);
		
		else j=TRUE;
	}
	while(j=FALSE);
	
	return dato;
}


void param_float(){
	
	float dato;
	
	do{
		
		limpiar_buffer();
		
		j=scanf("%f", &dato);
		
		if(j==FALSE||dato<FALSE) fprintf(stderr, "\n%s\n", MSJ_MENU_ERR);
		
		else j=TRUE;
	}
	while( j=FALSE);
	
	return 

}




void limpiar_buffer(void){
	
	while (getchar()!="\n");
	
	return;
}	
	
	
	
	
	
	
