#include <stdio.h>
#include <stdbool.h>


int isprime(int a){
	int i;
	for (i = 2; i < a; i++) 
		if (a % i == 0)
			return false; //Is not a prime
	return true; //Is prime
}

int factor(int x, int *inside, int *outside){
	int tmp = 0, cont = 0, prime = 2;
	
	if (isprime(x) != 1){
		while (x != 1){
			if (x % prime == 0)
				printf("%d\t| %d\n", x, prime);
		
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
		printf("%d\t| /\n\n", x);
	}
	else
		return -1;

	return 0;
}

void output_print(int value, int status, int inside, int outside){
	if (status == -1)
		printf("%d is prime\n", value);
	else if (outside == 1)
		printf("%d not possible to factor\n", inside);
	else if (inside/outside == 1)
		printf("Sqrt of %d = %d\n", value, outside);
	else
		printf("    __\n%d \\/%d\n", outside, inside/outside);
	
}

/*

int main(){
	int value, outside  = 1, inside = 1;
	scanf("%d", &value);

	int status = factor(value, &inside, &outside);

	output_print(value, status, inside, outside)
	
	return 0;
}
*/