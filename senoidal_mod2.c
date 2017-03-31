#include <stdio.h>
#include <math.h>
#define pi 3.1416

double senoid(double PASO_TEMP);

int main(void){
	double s;
	scanf("%lf",&s);
	printf("senoid(s)");
	
	return 0;
	
	}

double senoid(double PASO_TEMP){
	
	double frec;
	double fase;
	double amp;
	double senoid;
	double arg;
	double t
	
	printf("%s", "MSJ_SEN_FRQ");
	scanf("%lf", &frec);
	while(getchar()!='\n');
	
	printf("%s", "MSJ_SEN_FAS");
	scanf("%lf", &fase);
	if(getchar()=='\n') fase=0;
	while(getchar()!='\n');
	
	printf("%s", "MSJ_SEN_AMP");
	scanf("%lf", &amp);
	while(getchar()!='\n');
	
	for(t=t_in;t<t_fin;t+=PASO_TEMP){
		
		arg=2*pi*frec*PASO_TEMP+fase;
		senoid=amp*(sin(arg));
		printf("%lf | %lf",PASO_TEMP,senoid);
	}
	return EXIT_SUCCESS;
}


	
