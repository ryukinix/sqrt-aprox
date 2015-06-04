#include<stdio.h>


int eprimo(int a)
{
	int i;
	for (i = 2; i < a; i++) 
	{
		if (a%i == 0)
		return 0; //Nao e primo
	}
	return 1; //E primo
}


int main()
{
	int x, e , a, primo = 2, fora  = 1, dentro = 1, tmp = 0, cont =0;
	scanf("%d", &x);
	e = x;
	if (eprimo(x) == 1)
	{
		printf("%d e primo\n", x);
	}
	else
	{
		while (x!=1)
		{
			if (x%primo == 0)
			printf("%d\t| %d\n", x, primo);
		
			if (x%primo == 0)
			{
				x /= primo;
				tmp++;
				if (tmp == 2)
				{
					fora *= primo;
					tmp = 0;
				}
			}
			else
			{
				primo++;
				while(eprimo(primo) != 1)
				{
					primo++;
				}
				tmp = 0;
			}
			if(tmp == 1)
			{
				dentro *= primo;
			}
		}
		printf("%d\t| /\n\n", x);
		if (fora == 1)
		{printf("%d nao da pra fatorar\n", dentro);}
		else if (dentro/fora == 1)
		printf("Raiz de %d = %d\n", e, fora);
		else
		{
			printf("    __\n%d \\/%d\n",fora, dentro/fora);
		}
	}
}
