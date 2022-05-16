//CYP05
#include <stdio.h>

int main()
{
	int total;
	int datos = 0;
	float calif[2000];
	float memoria;
	unsigned int cuenta[2000];

	scanf_s("%i", &total);

	for (int i = 0; i < total; i++)
	{
		scanf_s("%u", &cuenta[i]);
		scanf_s("%f", &calif[i]);
	}
	int pasada, compara;
	for (pasada = 0; pasada < total; pasada++)
	{
		for (compara = 0; compara < total - pasada; compara++)
		{
			if (cuenta[compara] >= cuenta[compara + 1])
			{
				int aux = cuenta[compara];
				float aux2 = calif[compara];
				cuenta[compara] = cuenta[compara + 1];
				calif[compara] = calif[compara + 1];
				cuenta[compara + 1] = aux;
				calif[compara + 1] = aux2;
			}

		}

	}
	for (int k = 0; k < total; k++)
	{
		if (cuenta[k] != cuenta[k + 1])
			datos++;
	}
	printf("%i", datos);
	memoria = 0;
	for (int j = 0; j < total; j++)
	{
		if (cuenta[j] != cuenta[j + 1])
			printf("\n%u %f", cuenta[j], calif[j]);
		else
		{
			for (j = j; cuenta[j] == cuenta[j + 1]; j++)
			{
				if (calif[j] >= memoria)
				{
					memoria = calif[j];
				}
			}
			if (cuenta[j] == cuenta[j - 1])
			{
				if (calif[j] >= memoria)
				{
					memoria = calif[j];
				}
			}
			printf("\n%u %f", cuenta[j], memoria);
			memoria = 0;
		}
	}
}