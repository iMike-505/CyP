/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Contreras Ortiz Miguel		31729455-6
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/
#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");//abre el archivo del que se extraerá el diccionario
	if (archivo == NULL)
	{
		printf("No se puede leer archivo");
		return;
	}
	char PalabraPrincipal[TAMTOKEN];//palabra extraída del archivo
	PalabraPrincipal[TAMTOKEN - 1] = '\0';
	iNumElementos = 0;

	// Agrega palabras al diccionario
	for (int Conta1 = 0; Conta1 < NUMPALABRAS; Conta1++)
	{
		fscanf_s(archivo, "%s", &PalabraPrincipal, TAMTOKEN);//lectura de la palabra actual

															 // Proceso de eliminacion de signos 
		int Conta2 = 0;
		char PalabraAux[TAMTOKEN];//cadena auxiliar
		PalabraAux[TAMTOKEN - 1] = '\0';
		for (int Conta3 = 0; PalabraPrincipal[Conta3] != '\0'; Conta3++)// El cilco se repetira dependiendo de cuantas letras contenga la palabra 
		{
			if (PalabraPrincipal[Conta3] != ',' && PalabraPrincipal[Conta3] != '.' && PalabraPrincipal[Conta3] != ';' && PalabraPrincipal[Conta3] != ')' && PalabraPrincipal[Conta3] != '(' && PalabraPrincipal[Conta3] != '¿' && PalabraPrincipal[Conta3] != '?'&& PalabraPrincipal[Conta3] != '!' && PalabraPrincipal[Conta3] != '¡'&& PalabraPrincipal[Conta3] != '-'&& PalabraPrincipal[Conta3] != '\\' )
			{
				PalabraAux[Conta2] = PalabraPrincipal[Conta3];
				Conta2++;
			}
		}
		PalabraAux[Conta2] = '\0';
		strcpy_s(PalabraPrincipal, PalabraAux);//se copia la palabra sin signos 

		_strlwr_s(PalabraPrincipal);//Pasa todo a minusculas equisde

									// Esta parte saca la frecuencia, si no existe la palabra que se dio, la agrega 
		int agrega = 1;
		for (int Fconta = 0; Fconta <= iNumElementos; Fconta++) //Fconta= Frecuencia contador
		{
			if (strcmp(szPalabras[Fconta], PalabraPrincipal) == 0)//Concidicion que solo se cumple si la palabra ya existe en el diccionario
			{
				agrega = 0;
				iEstadisticas[Fconta]++; //Aumenta su frecuencia
			}
		}



		if (agrega) // Condicion que se cumple si la palabra no existe enel diccionario ( la agrega )
		{
			strcpy_s(szPalabras[iNumElementos], PalabraPrincipal);//guarda la palabra en el diccionario
			iEstadisticas[iNumElementos]++;
			iNumElementos++;
		}


		if (feof(archivo))//fuerza salir del ciclo si se encuentra el final del archivo
			Conta1 = NUMPALABRAS;
	}


	fclose(archivo);//cierra el archivo

					// Ciclo de la burbuja que ordena el diccionario

	char Pburbuja[TAMTOKEN];// Pburbuja= Palabra que se ocupara para este ciclo como auxiliar

	Pburbuja[49] = '\0';
	int NumAuxBurbuja;
	for (int Conta = 0; Conta < iNumElementos - 1; Conta++)
	{
		for (int Conta2 = 0; Conta2 < iNumElementos - Conta - 1; Conta2++)
		{
			if (strcmp(szPalabras[Conta2], szPalabras[Conta2 + 1]) > 0)
			{
				strcpy_s(Pburbuja, szPalabras[Conta2]);
				NumAuxBurbuja = iEstadisticas[Conta2];
				strcpy_s(szPalabras[Conta2], szPalabras[Conta2 + 1]);
				iEstadisticas[Conta2] = iEstadisticas[Conta2 + 1];
				strcpy_s(szPalabras[Conta2 + 1], Pburbuja);
				iEstadisticas[Conta2 + 1] = NumAuxBurbuja;
			}
		}
	}

	iNumElementos++;
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(char	szPalabrasSugeridas[][TAMTOKEN],int	iNumSugeridas,char	szPalabras[][TAMTOKEN],	int	iEstadisticas[],int	iNumElementos,char	szListaFinal[][TAMTOKEN],int iPeso[],int &	iNumLista)							
{
	iNumElementos--;
	iNumLista = 0;
	int Conta3 = 0;
	for (int Conta1 = 0; Conta1 < iNumElementos; Conta1++)//para cada palabra del diccionario
	{
		for (int Conta2 = 0; Conta2 < iNumSugeridas; Conta2++)//comparar con cada la lista de palabras clonadas
		{
			if (strcmp(szPalabrasSugeridas[Conta2], szPalabras[Conta1]) == 0)//cuando la palabra del diccionario existe en las sugerencias
			{
				strcpy_s(szListaFinal[Conta3], szPalabras[Conta1]);//se agrega a la lista final
				iPeso[Conta3] = iEstadisticas[Conta1];
				iNumLista++;
				Conta3++;
				Conta2 = iNumSugeridas;
			}
		}
	}


	// Ciclo de burbuja
	char AuxBurbuja[TAMTOKEN];
	AuxBurbuja[49] = '\0';
	int NumAuxBurbuja;
	for (int BConta1 = 0; BConta1 < iNumLista - 1; BConta1++)
	{
		for (int BConta2 = 0; BConta2 < iNumLista - BConta1 - 1; BConta2++)
		{
			if (iPeso[BConta2] < iPeso[BConta2 + 1])
			{
				strcpy_s(AuxBurbuja, szListaFinal[BConta2]);
				NumAuxBurbuja = iPeso[BConta2];
				strcpy_s(szListaFinal[BConta2], szListaFinal[BConta2 + 1]);
				iPeso[BConta2] = iPeso[BConta2 + 1];
				strcpy_s(szListaFinal[BConta2 + 1], AuxBurbuja);
				iPeso[BConta2 + 1] = NumAuxBurbuja;
			}
		}
	}
	
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(char *szPalabraLeida,char	szPalabrasSugeridas[][TAMTOKEN], int &	iNumSugeridas)						//Numero de elementos en la lista
{
	char palabra_aux[50]; 
	char abe[] = "abcdefghijklmnñopqrstuvwxyzáéíóú"; 											  
	int num_letras = strlen(szPalabraLeida); 
	int num_letras_abe = strlen(abe);  
	iNumSugeridas = 0;
						   
	for (int i = 0; i < num_letras; i++) 
	{
		strcpy_s(palabra_aux, szPalabraLeida); 
		for (int k = 0; k < num_letras_abe; k++) 
		{
			int n = (i * num_letras_abe) + k; 
			palabra_aux[i] = abe[k];   
			strcpy_s(szPalabrasSugeridas[n], palabra_aux);
			iNumSugeridas++;
		}
	}

	for (int M = 0; M <= num_letras; M++)   
	{
		
		if (M == 0)   
		{
			for (int DESPUES1 = 0; DESPUES1 < num_letras_abe; DESPUES1++) 
			{
				palabra_aux[0] = abe[DESPUES1];   
				int C = 1;
				for (C; C <= num_letras; C++) 
				{
					palabra_aux[C] = szPalabraLeida[C - 1]; 
				}
				palabra_aux[C] = '\0';
				int posicion = ((num_letras)*num_letras_abe) + DESPUES1; 
																		
				strcpy_s(szPalabrasSugeridas[posicion], palabra_aux);
				iNumSugeridas++;
			}
		}
		
		else
		{
			if (M == (num_letras))
				
			{
				for (int ANTES1 = 0; ANTES1 < num_letras_abe; ANTES1++)
				{
					palabra_aux[num_letras] = abe[ANTES1];
					for (int C = 0; C < num_letras; C++) 
					{
						palabra_aux[C] = szPalabraLeida[C]; 
					}
					int posicion = ((num_letras)*num_letras_abe) + (M * num_letras_abe) + ANTES1;																		 
					strcpy_s(szPalabrasSugeridas[posicion], palabra_aux);
					iNumSugeridas++;
				}
			}
			else
			{
				
				for (int I = 0; I < num_letras_abe; I++) 
				{
					for (int ANTES = 0; ANTES < M; ANTES++) 
					{
						palabra_aux[ANTES] = szPalabraLeida[ANTES];
					}
					for (int DESPUES = M + 1; DESPUES < num_letras; DESPUES++) 
					{
						palabra_aux[DESPUES] = szPalabraLeida[DESPUES - 1];
					}
					palabra_aux[M] = abe[I];                                     
					int posicion = ((num_letras)*num_letras_abe) + (M * num_letras_abe) + I;
																							
					strcpy_s(szPalabrasSugeridas[posicion], palabra_aux);
					iNumSugeridas++;
				}

			}
		}
	}

	for (int o = 0 : o < num_letras; o++)
	{
		for (int n= 0 : n < num_letras; n++)
		{
			if (strcmp(szPalabras[Fc], PalabraPrincipal) == 0)
			{

			}
		}
	}




	for (int i = 0; i < num_letras; i++)
	{
		int j = 0;
		for (int k = 0; k < num_letras; k++)
		{
			if (k != i)
			{
				palabra_aux[j] = szPalabraLeida[k];
				j++;
			}
		}
		palabra_aux[j] = '\0';
		strcpy_s(szPalabrasSugeridas[iNumSugeridas], palabra_aux);
		iNumSugeridas++;									
	}
	for (int i = 0; i<num_letras; i++)
	{
		strcpy_s(palabra_aux, szPalabraLeida);
		palabra_aux[i] = szPalabraLeida[i + 1];
		palabra_aux[i + 1] = szPalabraLeida[i];
		strcpy_s(szPalabrasSugeridas[iNumSugeridas], palabra_aux);
		iNumSugeridas++;
	}
	

	char aux[50];
	int ia, ja, ka;

	for (ia = 0; ia < iNumSugeridas - 1; ia++)
	{
		ka = ia;
		strcpy_s(aux, szPalabrasSugeridas[ia]);
		for (ja = ia + 1; ja <iNumSugeridas; ja++)
		{
			if (strcmp(szPalabrasSugeridas[ja], aux) < 0)
			{
				ka = ja;

				strcpy_s(aux, szPalabrasSugeridas[ja]);
			}
		}
		strcpy_s(szPalabrasSugeridas[ka], szPalabrasSugeridas[ia]);
		strcpy_s(szPalabrasSugeridas[ia], aux);
	}
}
