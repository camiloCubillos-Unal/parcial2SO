#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

int WRONG_SUDOKU[9][9] = {
	{5, 3, 4, 6, 7, 8, 9, 1, 2},
	{6, 7, 2, 1, 9, 5, 3, 4, 8},
	{1, 9, 8, 3, 4, 2, 5, 6, 7},
	{8, 5, 9, 7, 6, 1, 4, 2, 3},
	{4, 2, 6, 8, 5, 3, 7, 9, 1},
	{7, 1, 3, 9, 2, 4, 8, 5, 6},
	{9, 6, 1, 5, 3, 7, 2, 8, 4},
	{2, 8, 7, 4, 1, 9, 6, 3, 5},
	{3, 4, 5, 2, 8, 6, 1, 7, 1} // Valor repetido (1) en la última celda
};

int VALID_SUDOKU[9][9] = {
	{5, 3, 4, 6, 7, 8, 9, 1, 2},
	{6, 7, 2, 1, 9, 5, 3, 4, 8},
	{1, 9, 8, 3, 4, 2, 5, 6, 7},
	{8, 5, 9, 7, 6, 1, 4, 2, 3},
	{4, 2, 6, 8, 5, 3, 7, 9, 1},
	{7, 1, 3, 9, 2, 4, 8, 5, 6},
	{9, 6, 1, 5, 3, 7, 2, 8, 4},
	{2, 8, 7, 4, 1, 9, 6, 3, 5},
	{3, 4, 5, 2, 8, 6, 1, 7, 9}};

void printSudoku(int sudoku[9][9])
{
	printf("\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%i\t", sudoku[i][j]);
			if ((j + 1) % 3 == 0)
			{
				printf("|\t");
			}
		}
		if ((i + 1) % 3 == 0)
		{
			printf("\n\n");
			for (int k = 0; k < 9 + 3; k++)
			{
				printf("-\t");
			}
			printf("\n\n");
		}

		printf("\n");
	}
	printf("\n");
}

bool checkFilas(int sudoku[9][9])
{
	printf("[+] Revisando filas...\n");
	for (int row = 0; row < 9; row++)
	{
		int sum = 0;
		for (int col = 0; col < 9; col++)
		{
			sum += sudoku[row][col];
		}
		if (sum != 45)
		{
			return false;
		}
	}
	return true;
}

bool checkColumnas(int sudoku[9][9])
{
	printf("[+] Revisando columnas...\n");
	for (int col = 0; col < 9; col++)
	{
		int sum = 0;
		for (int row = 0; row < 9; row++)
		{
			sum += sudoku[row][col];
		}
		if (sum != 45)
		{
			return false;
		}
	}
	return true;
}

bool checkGrupos(int sudoku[9][9])
{
	printf("[+] Revisando grupos...\n");
	for (int row = 0; row < 9; row += 3)
	{
		for (int col = 0; col < 9; col += 3)
		{
			int sum = sudoku[row][col] + sudoku[row][col + 1] + sudoku[row][col + 2] +
					  sudoku[row + 1][col] + sudoku[row + 1][col + 1] + sudoku[row + 1][col + 2] +
					  sudoku[row + 2][col] + sudoku[row + 2][col + 1] + sudoku[row + 2][col + 2];
			printf("SUMA CELDA (%i,%i): %i\n", row / 3, col / 3, sum);
			if (sum != 45)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	int(*sudoku)[9] = WRONG_SUDOKU;

	printSudoku(sudoku);

	// IMPLEMENTACIÓN HILOS

	pthread_t filasT;
	pthread_t columnasT;
	pthread_t gruposT;

	pthread_create(&filasT, NULL, checkFilas, sudoku);
	pthread_create(&columnasT, NULL, checkColumnas, sudoku);
	pthread_create(&gruposT, NULL, checkGrupos, sudoku);

	bool *filasOk;
	bool *columnasOk;
	bool *gruposOk;

	pthread_join(filasT, &filasOk);
	pthread_join(columnasT, &columnasOk);
	pthread_join(gruposT, &gruposOk);

	if (filasOk)
	{
		printf("Filas OK\n");
	}
	else
	{
		printf("Filas FALLO\n");
	}

	if (columnasOk)
	{
		printf("Columnas OK\n");
	}
	else
	{
		printf("Columnas FALLO\n");
	}

	if (gruposOk)
	{
		printf("Grupos OK\n");
	}
	else
	{
		printf("Grupos FALLO\n");
	}

	// IMPLEMENTACIÓN SECUENCIAL

	// if (checkFilas(sudoku))
	// {
	// 	printf("Filas OK\n");
	// }
	// else
	// {
	// 	printf("Filas FALLO\n");
	// }

	// if (checkColumnas(sudoku))
	// {
	// 	printf("Columnas OK\n");
	// }
	// else
	// {
	// 	printf("Columnas FALLO\n");
	// }

	// if (checkGrupos(sudoku))
	// {
	// 	printf("Grupos OK\n");
	// }
	// else
	// {
	// 	printf("Grupos FALLO\n");
	// }
	return 0;
}
