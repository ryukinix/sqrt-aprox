#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define SLICES 8

/*
 * =================================================================================================
 *
 *       Filename:  proj.c
 *
 *    Description:  A heuristic solution for eval the sqrt(x) function
 *
 *        Version:  1.0
 *        Created:  5-06-2015 06:03:58
 *       Revision:  1.3
 *       Compiler:  gcc
 *
 *        Authors:  Manoel Vilela, Janderson Souza, Juliana Azevedo, Jeanderson Oliveira, Núria Rocha
 *   Organization:  UFPA  → Federal University of Para
 *        Contact:  manoel_vilela@mail.com
 *
 * ===================================================================================================
 */





/*
 *  Abstract: Verify the number a is prime
 *
 *    -*- Declaration Sets -*-
 *
 *	isprime: ℕ* → {0, 1}
 *
 *
 *	  -*- Definition -*-
 *
 *  isprime: a ↦ {true, false}
 *
 *  E.g.: (7) ↦ (true)
 *		 (4) ↦ (false)
 *
 */
int isprime(int a){
	int i;
	for (i = 2; i < a; i++)
		if (a % i == 0)
			return false; //Is not a prime
	return true; //Is prime
}



/*
 *  Abstract: factoring a sqrt(x) expression
 *
 *   -*- Input -*-
 *
 *  in: the value to factor, two variables to save the factor *inside and *outside
 *
 *   -*- Processing and Output -*-
 *
 *  processing: in-sqrt, out-sqrt.
 *
 *
 *  E.g.: Factor: (50, in, out) |-> (5, 2);
*/
int factor(int x, int *inside, int *outside){
	int tmp = 0, cont = 0, prime = 2;

	if (isprime(x) != 1){
		while (x != 1){
			if (x % prime == 0){
				x /= prime;
				tmp++;
				if (tmp == 2){
					*outside *= prime;
					tmp = 0;
				}
			}
			else {
				prime++;
				while(isprime(prime) != 1)
					prime++;
				tmp = 0;
			}

			if(tmp == 1)
				*inside *= prime;
		}
		*inside /= *outside;
	}
	else
		return -1;

	return 0;
}

//for debug the above functions
void output_print(int value, int status, int inside, int outside){
	if (status == -1)
		printf("%d is prime\n", value);
	else if (outside == 1)
		printf("%d not possible to factor\n", inside);
	else if (inside == 1)
		printf("Sqrt of %d = %d\n", value, outside);
	else
		printf("    __\n%d \\/%d\n", outside, inside);

}

//factorial function
long fact(int n){
	if(n <= 1)
		return 1;
	else
		return n * fact(n - 1);
}

//the pochhmaer symbol meta-function
double pochhammer_func(double x, int n, int sign){
	int k;
	double productory = 1;

	for(k = 0; k < n; k++)
		productory *= (x + k*sign);

	return productory;
}

//the dependency pochhamer symbol functions: rising e fallling factorial
double rising_fact(double x, int n){
	return pochhammer_func(x, n, 1);
}

double falling_fact(double x, int n){
	return pochhammer_func(x, n, -1);
}



//the serie proposed on the project!
double sav_serie(double x){
	int n;
	double accumulator = 1, productory = 1;

	for(n = 1; n <= SLICES; n++){
		productory = falling_fact(0.5, n);

		double pot = pow(x, n);

		long denominator = fact(n);

		double slice = (productory * pot)/denominator;

		//output
		printf("Slice %d: %lf <=> (* %lf * %.2lf) / %li\n", \
			n, slice, productory, pot, denominator);

		accumulator += slice;
	}

	return accumulator;
}


//the serie (I) found by Manoel
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

		//output
		printf("Slice %d: %lf <=> (%d * %lf * %.2lf) / %li\n" , \
			n, slice, sign, productory, pot, denominator);

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
		printf("Slice %d: %lf <=> (%d * %lf * %.2lf) / %li\n", \
			n, slice, sign, productory, pot, denominator);

		accumulator += slice;
	}

	return accumulator;

}


//The main function of this project with a concise method of call all the series.
double sqrt_(double z, int num){
	int k = 1, x = 1;
	double heuristic;

	factor(z, &x, &k);
	puts("-->Input!\n");
	printf("z = %lf => k = %d | x = %d <=> z^(1/2) = %dV%d\n\n", z, k, x, k, x);

	puts("-->Processing!\n");
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

//function for print all the outputs and reduce the code!
void out_print(int z, double our_value){
	double error, std_value;

	std_value = sqrt(z);
	error = std_value - our_value;

	puts("\n--> Results!");
	printf("\nOur sqrt(%d): %.10lf\nStandard sqrt(%d): %.10lf\nError: %.10lf\n", \
         	       z, our_value,	   z, std_value,        error );

}

//Main code!
int main(int argc, char *argv[]){
	int z = 50;

	printf("\n\t\t-*- Sav' Series -*-\n\n");
	out_print(z, sqrt_(z, 2));

	printf("\n\t\t -*- Man' Series -*-\n\n");
	out_print(z, sqrt_(z, 1));

	printf("\n\t\t-*- Wolf' Series -*-\n\n");
	out_print(z, sqrt_(z, 3));

	return 0;
}