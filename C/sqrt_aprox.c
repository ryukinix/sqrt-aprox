#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "declarations.h"
#define SLICES 8


long fact(int n){
	if(n <= 1)
		return 1;
	else
		return n * fact(n - 1);
}


double pochhammer_func(double x, int n, int sign){
	int k;
	double productory = 1;
	
	for(k = 0; k < n; k++)
		productory *= (x + k*sign);

	return productory;	
}


double rising_fact(double x, int n){
	return pochhammer_func(x, n, 1);
}

double falling_fact(double x, int n){
	return pochhammer_func(x, n, -1);
}

double man_serie(double x){
	int n, k;
	double accumulator = 1, productory;
	int sign = 1;

	for(n = 1; n <= SLICES; n++){
		sign = pow(-1, n + 1);
		
		double pot = pow((x - 1), n);

		long denominator = pow(2, n) * fact(n);

		productory = 1;
		for(k = -1; k < n - 1; k++){
			productory = productory * abs((2*k) + 1);
		}
		

		double slice = (sign * productory * pot)/denominator;
		//debug
		printf("Slice %d: %lf <=> (%d * %lf * %lf) / %li\n" , \
			n, slice, sign, productory, pot, denominator);

		accumulator += slice;

	}

	return accumulator;

}

double sav_serie(double x){
	int n;
	double accumulator = 1, productory = 1;

	for(n = 1; n <= SLICES; n++){
		productory = falling_fact(0.5, n);
		
		double pot = pow(x, n);

		long denominator = fact(n);

		double slice = (productory * pot)/denominator;
		//debug
		printf("Slice %d: %lf <=> (* %lf * %lf) / %li\n", \
			n, slice, productory, pot, denominator);

		accumulator += slice;
	}

	return accumulator;
}

double wolf_serie(double x){
	int n;
	double accumulator = 0, productory = 1;
	int sign = 1;

	for(n = 0; n <= SLICES; n++){
		sign = pow(-1, n);
		
		productory = rising_fact(-0.5, n);
		
		double pot = pow((x - 1), n);

		long denominator = fact(n);

		double slice = (sign * productory * pot)/denominator;

		//debug
		printf("Slice %d: %lf <=> (%d * %lf * %lf) / %li\n", \
			n, slice, sign, productory, pot, denominator);

		accumulator += slice;
	}

	return accumulator;

}


double sqrt_(double z, int num){
	int k = 1, x = 1;
	double heuristic;

	factor(z, &x, &k);
	printf("z = %lf | k = %d | x = %d <=> z^(1/2) = %dV%d\n\n", z, k, x, k, x);
	
	switch(num){
		case 1:
			heuristic = man_serie(x);
			break;
		case 2:
			heuristic = sav_serie(x - 1);
			break;
		case 3:
			heuristic = wolf_serie(x);
			break;
		default:
			puts("WAT'?! What you are doing with me? D:");
			exit(EXIT_FAILURE);
	}

	return k * heuristic;
}

void out_print(int z, double our_value){
	double error, std_value;

	std_value = sqrt(z);
	error = our_value - std_value;

	printf("Our sqrt(%d): %.10lf\nStandard sqrt(%d): %.10lf\nError: %.10lf\n", \
         	       z, our_value,	   z, std_value,        error );

}


int main(int argc, char *argv[]){
	int z = 50;

	printf("\n\t\t -*- Man' Series -*-\n\n");
	out_print(z, sqrt_(z, 1));

	printf("\n\t\t-*- Sav' Series -*-\n\n");
	out_print(z, sqrt_(z, 2));

	printf("\n\t\t-*- Wolf' Series -*-\n\n");
	out_print(z, sqrt_(z, 3));
	
	return 0;
}