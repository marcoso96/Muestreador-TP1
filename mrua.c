#include <stdio.h>
#include <math.h>

double mrua(double PASO_TEMP){
	
	double pos_in;
	double vel_in;
	double acel;
	double t;
	double mrua;
	
	printf("%s", "MSJ_MRUA_POS");
	scanf("%lf", &pos_in);
	while(getchar()!=0);
	
	printf("%s", "MSJ_MRUA_VEL");
	scanf("%lf", &vel_in)
	while(getchar()!=0);
	
	printf("%s", "MSJ_MRUA_ACEL");
	scanf("%lf", &acel)
	while(getchar()!=0);
	
	return for(t=t_in;t<t_fin;t+=PASO_TEMP){
				if(t==0) printf("%lf|%lf",t,pos_in);
			else{
				mrua=pos_in+(vel_in*t)+(1/2)*acel*pow(t,2);
				printf("%lf|%lf",t,mrua);
		}
	}
	
	
	
