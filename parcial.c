
#define ARG_OP 0
#define CANT_OP 4

typedef struct {
			int id;
			char *username;
			int edad;
		} struct_user
	
typedef enum  {ALTA, BAJA} t_op;
typedef enum {TRUE, FALSE} t_bool;

void op_struct(struct_user ***lista, char *str_op){
	
	char operacion[CANT_OP];
	char delim[2]={",","\0");
	t_op op;
	t_bool existe;
	char **endptr;/*para strtol*/
		
	operacion[ARG_OP]=strtok(str_op, delim);
	 
	if(operacion[ARG_OP]=="alta") op=ALTA;
	
	else{	 
			if(operacion[ARG_OP]=="baja") op=BAJA;
			
			else{
				
				fprintf(stderr, "%s", MSJ_OP_INVALIDA);
				return;
			}
		}
	
	switch(op){
			
			case ALTA:
					
					if(lista==NULL){
						
						(*lista)=(struct_user **)malloc(sizeof(struct_user *));
						
						(**lista)=(struct_user *)malloc(sizeof(struct_user));
						(*lista)[NULL_ARG]=NULL;
						
						operacion[ARG_ID]=strtok(NULL, delim);
						(**lista)->id=strtol(operacion[ARG_ID], &endptr, 10);
						
						operacion[ARG_NAME]=strtok(NULL, delim);
						strcpy((**lista)->name, operacion[ARG_NAME];
						
						operacion[ARG_EDAD]=strtok(NULL, delim);
						(**lista)->edad=strtol(operacion[ARG_EDAD], &endptr, 10);
						
						fprintf(stderr, "%s", MSJ_OP_EXITOSA);
						
						return;
					}
					else{
						
						operacion[ARG_ID]=strtok(NULL, delim);
						/*supongo que la lista siempre tiene un puntero a NULL en el ultimo campo (*lista)[i]==NULL
						 * la otra opcion seria hacer un sizeof(vector de punteros)/sizeof(structuser *)*/
						for(i=0, existe=FALSE; existe=TRUE i<(sizeof(lista)/sizeof(struct_user *)); i++){
							
							if((*lista)[i]->edad==strtol(operacion[ARG_ID], &endptr, 10)){
								
								existe=TRUE
							}
						}
						
						if(existe==TRUE){
							
							fprintf(stderr, "%s", MSJ_USER_EXIST);
							return; 
						}
						
						else{
							
							(*lista)=(struct_user **)realloc(*lista, sizeof(*lista)+sizeof(structuser *));
							
							operacion[ARG_ID]=strtok(NULL, delim);
							(*lista)[i+1]->id=strtol(operacion[ARG_ID], &endptr, 10);
						
							operacion[ARG_NAME]=strtok(NULL, delim);
							strcpy((*lista)[i+1]->name, operacion[ARG_NAME];
						
							operacion[ARG_EDAD]=strtok(NULL, delim);
							(*lista)[i+1]->edad=strtol(operacion[ARG_EDAD], &endptr, 10);
						
							fprintf(stderr, "%s", MSJ_OP_EXITOSA);
					
						}
					
						
						
					
							
						  
					
				  
			
