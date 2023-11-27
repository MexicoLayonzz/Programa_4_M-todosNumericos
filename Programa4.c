#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>

/*
	INTEGRANTES: 
		Aguilar Martinez Fernando, 
		Gonzalez Ordaz Ariel, 
		Gutierrez Tapia Marco Antonio, 
		Sandoval Madrigal Michelle
*/

bool CrearColumnas(double ***, int);
bool CrearFilas(double **, int);
void LlenarMatriz(double**, int);
void ImprimirMatriz(double**, int);
void Continuar();
bool CrearVector(double **, int);
void LlenarVector(double *, int);

double Determinante(double **, int);

double Cholesky(double**, double *, int);

int main()
{
	double **md = NULL;
	double **mdc = NULL;
	double *vec = NULL;
	int num = 1, i = 0, j = 0;
	double determinante;
	
	int opc = 0,opcVector = 0;
	do
	{
		if(CrearColumnas(&md, num))
		{
			if (CrearFilas(md, num))
			{
				do
				{
					system("cls");
					printf("Menu Principal\n"
						"2-Solucion De Sistema De Ecuaciones\n"
						"\t1 = Definir Tamanio De La Matriz\n"
						"\t2 = Llenar Matriz\n"
						"\t3 = Imprimir Matriz\n"
						"\t4 = Calcular Determinante\n"
						"\t5 = Solucion De Sistema\n"
						"\t0 = Salir Del Programa\n");
					scanf("%d",&opc);
					switch(opc)
					{
						case 1:
							printf("Ingrese el tamanio de la matriz: ");
							scanf("%d", &num);
							Continuar();
							break;
						case 2:
							LlenarMatriz(md, num);
		    				if (CrearColumnas(&mdc, num) && CrearFilas(mdc, num))
							{
		    					for (i = 0; i < num; i++)
								{
									for (j = 0; j < num; j++)
									{
										mdc[i][j] = md[i][j];
		    					    }
		    					}
		    				}
							Continuar();
							break;
						case 3:
							ImprimirMatriz(md, num);
							Continuar();
							break;
						case 4:
							determinante = Determinante(md, num);
							printf("Determinante: %lf\n",determinante);
							Continuar();
							break;
						case 5:
							if(CrearVector(&vec, num))
							{
								do
								{
									printf("Vector Independiente\n");
									LlenarVector(vec, num);
									Cholesky(md, vec, num);
									printf("\nQuiere Repetir Proceso?\n"
										"1 - Si\n"
										"Cualquier Tecla - No\n");
									scanf("%d",&opcVector);
								}
								while(opcVector == 1);
							}
							Continuar();
							break;
						case 0:
							break;
						default:
							printf("No Ingresaste Un Valor Correcto");
							Continuar();
					}
				}
				while(opc != 0 && opc != 1);
			}
			else
			{
				for (i = 0; i < num; i++)
		    	{
		        	free(md[i]);
		    	}
				free(md);
			    for (i = 0; i < num; i++)
				{
			        free(mdc[i]);
			    }
			    free(mdc);
				exit(1);
			}
		}
		else
		{
			exit(1);
		}
	}
	while(opc != 0);
	printf("Gracias Por Usar El Programa");
}

void Continuar()
{
	printf("\nIngrese Tecla Para Continuar\n");
	getch();
}

bool CrearColumnas(double ***matriz, int num)
{
	*matriz = (double **) malloc(sizeof(double *) * num);
	if(*matriz == NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

bool CrearFilas(double **md, int num)
{
	int i, j;
	for(i = 0; i < num; ++i)
	{
		*(md + i) = (double *) malloc(sizeof(double) * num);
		if(*(md + i) == NULL)
		{
			printf("\nNo hay memoria suficiente");
			for(j = 0; j < i; ++j)
			{
				free(*( md +j ));
			}
			free(md);
			return false;
		}
	}
	return true;
}

void LlenarMatriz(double **md, int num)
{
	int i, j;
	for (i = 0; i < num; ++i)
	{
		for (j = 0; j < num; ++j)
		{
			printf("\nIngrese el elemento [%d, %d]: ", i, j);
			scanf("%lf", *(md + i) + j);
		}
	}
}

void ImprimirMatriz(double **md, int num)
{
	int i, j;
	for (i = 0; i < num; ++i)
	{
		printf("\n");
		for(j = 0; j < num; ++j)
		{
			printf("%lf\t", *(*(md + i) + j));
		}
	}
}

bool CrearVector(double **vec, int num)
{
	*vec = (double *) malloc(sizeof(double) * num);
	if (vec = NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

void LlenarVector(double *vec, int num)
{
	int i;
	putchar('\n');
	for (i = 0; i < num; i++) {
    	printf("\nIngrese el elemento %d del vector: ", i + 1);
    	scanf("%lf", &vec[i]);
    }
}

double Determinante(double **md, int num)
{
	double **matriz_copia = NULL;
    int i, j, k;
    double determinante = 1.0;
    
    if (CrearColumnas(&matriz_copia, num) && CrearFilas(matriz_copia, num))
	{
        for (i = 0; i < num; i++)
		{
            for (j = 0; j < num; j++)
			{
                matriz_copia[i][j] = md[i][j];
            }
        }
    }
	else
	{
        return 0.0;
    }

    for (i = 0; i < num; i++) {
        for (j = i + 1; j < num; j++)
		{
            double factor = matriz_copia[j][i] / matriz_copia[i][i];
            for (k = i; k < num; k++)
			{
                matriz_copia[j][k] -= factor * matriz_copia[i][k];
            }
        }
        determinante *= matriz_copia[i][i];
    }

    for (i = 0; i < num; i++)
	{
        free(matriz_copia[i]);
    }
    free(matriz_copia);

    return determinante;
}

double Cholesky(double **md, double *vec, int num)
{
    int i, j, k;
	double **matriz_copia = NULL;
	double **matriz_l = NULL;
    double suma;

    if (CrearColumnas(&matriz_copia, num) && CrearFilas(matriz_copia, num))
	{
        for (i = 0; i < num; i++)
		{
            for (j = 0; j < num; j++)
			{
                matriz_copia[i][j] = md[i][j];
            }
        }
    }
	else
	{
        return 0.0;
    }

    if (CrearColumnas(&matriz_l, num) && CrearFilas(matriz_l, num))
	{
        for (i = 0; i < num; i += 1)
		{
            for (j = 0; j < num; j += 1)
			{
                matriz_l[i][j] = 0;
            }
        }
    }
	else
	{
        return 0.0;
    }

    for(i = 0; i < num; i += 1)
	{
        for(j = 0; j <= i; j += 1)
		{
            suma = 0;
            if (i == j)
			{
                for (k = 0; k < j; k += 1)
				{
                    suma += pow(matriz_l[j][k], 2);
                }
                matriz_l[j][j] = sqrt(matriz_copia[j][j] - suma);
            }
			else
			{
                for(k = 0; k < j; k += 1)
				{
                    suma += (matriz_l[i][k] * matriz_l[j][k]);
                }
                matriz_l[i][j] = (matriz_copia[i][j] - suma) / matriz_l[j][j];
            }
        }
    }
    
    ImprimirMatriz(matriz_l, num);
    
    double y[num];
	for (i = 0; i < num; i += 1)
	{
		double sum = 0;
		for (j = 0; j < i; j++)
		{
			sum += matriz_l[i][j] * y[j];
		}
		y[i] = (vec[i] - sum) / matriz_l[i][i];
	}

	double x[num];
	for (i = num - 1; i >= 0; i -= 1)
	{
		double sum = 0;
		for (j = i + 1; j < num; j += 1)
		{
			sum += matriz_l[j][i] * x[j];
		}
		x[i] = (y[i] - sum) / matriz_l[i][i];
	}
    
    printf("\nSolución del sistema de ecuaciones:\n");
    for (i = 0; i < num; i += 1)
	{
        printf("x[%d] = %lf\n", i + 1, x[i]);
    }
    
    for (i = 0; i < num; i++)
	{
        free(matriz_copia[i]);
    }
    free(matriz_copia);

    for (i = 0; i < num; i++)
	{
        free(matriz_l[i]);
    }
    free(matriz_l);
}

