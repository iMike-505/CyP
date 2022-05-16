// CYP02.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

int main()
{
	int bfSize;
	int Pixel;

		scanf_s("%i %i", &bfSize, &Pixel);

		printf("BM%08x%016x", bfSize, Pixel);
		return 0;
}

/*La variable bfize es el tmaño de la imagen y 
la variable Pixel es la poscicion del pixel*/