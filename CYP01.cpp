//CYP01
#include <stdio.h>

int main()
{
	int Ancho, Altura;
	int X, Y;
	int X2, Y2;
	float Px, Py;
	float PAnch, PAlt;
	scanf_s("%d %d %f %f %f %f", &Ancho, &Altura, &Px, &Py, &PAnch, &PAlt);
	/*Operaciones:
	se calculan los valores para las coordenadas de la esquina superior izquierda y la coordenada de la
	esquina inferior derecha*/
	X = Ancho * Px;
	Y = Altura * Py;
	X2 = (PAnch * Ancho) + X;
	Y2 = (PAlt * Altura) + Y;
	printf("%d %d %5.2f %5.2f %5.2f %5.2f %d %d %d %d", Ancho, Altura, Px, Py, PAnch, PAlt, X, Y, X2, Y2);
	return 0;
}
