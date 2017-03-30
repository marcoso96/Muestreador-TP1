double fac(int n)
{
	int fac;
	int i;
	
	for(fac=1, i=1; i<=n ; i++){
		
		fac*=i;
	}
	
	return fac;
}

double power(base, exp)
{
	int i;
	double power;
	
	for(i=0, power=1 ; i<=n ; i++){
		power*=base;
	}
	
	if (exp>0) return power;
	
	else return 1/power;
}
