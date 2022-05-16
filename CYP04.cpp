//CYP04
#include "stdafx.h"
#include <math.h>

int main()
{
	double limite_inicial, limite_final,incremento;
	scanf_s("%lf", &limite_inicial);
	scanf_s("%lf", &limite_final);
	scanf_s("%lf", &incremento);
	if (limite_inicial == 0 && limite_final == 0 && incremento == 0)
	{
		printf("%f %f %f\n", limite_inicial, exp(0), exp(0));
	}
	else
	{
		if (limite_inicial > limite_final)
		{
			return 1;
		}
		double e = 0;
		double iteracciones, x;
		int factorial;
		int n = 0;
		int j = 0;
		int k = 0;
		for (x = limite_inicial; x <= limite_final; x = limite_inicial + (incremento*j))
		{
			for (iteracciones = limite_inicial; iteracciones <= limite_final; iteracciones = limite_inicial + (incremento*k))
			{
				if (n == 0)
				{
					factorial = 1;
				}
				else
				{
					factorial = 1;
					for (int i = 1; i <= n; i++)
					{
						factorial = factorial * i;
					}
				}
				e = e + (pow(x, n) / factorial);
				n++;
				k++;
			}
			k = 0;
			printf("%f %f %f\n", x, e, exp(x));
			n = 0;
			e = 0;
			j++;
		}
	}
}




