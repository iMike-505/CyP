//CYP03
#include <stdio.h>
int main()
{
	int dia, mes, year;
	scanf_s("%i %i %i", &dia, &mes, &year);
	if ((dia == 31 && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) || (dia == 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) || (dia == 29 && mes == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) || (dia == 28 && mes == 2 && !(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)))
	{
		dia = 1;
		if (mes == 12)
		{
			mes = 1;
			year = year + 1;
		}
		else
			mes = mes + 1;
	}
	else
		if (year == 1582 && dia == 4)
			dia = dia + 11;
		else
			dia = dia + 1;
	printf("%2i %2i %4i", dia, mes, year);
}