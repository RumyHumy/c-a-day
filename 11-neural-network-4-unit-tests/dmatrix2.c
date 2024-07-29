#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dmatrix2.h"

/*
typedef struct DMatrix2
{
	double **data;
	int columns;
	int rows;
} DMatrix2;
*/

DMatrix2* DMatrix2Construct(int columns, int rows)
{
	if (columns <= 0 || rows <= 0)
		return NULL;

	DMatrix2* matrix = malloc(sizeof(*matrix));

	if (matrix == NULL)
		return NULL;

	*matrix = (DMatrix2){ .data=NULL, .columns=columns, .rows=rows };

	matrix->data = calloc(columns, sizeof(*matrix->data));

	if (matrix->data == NULL)
		return NULL;

	for (int c = 0; c < columns; c++)
	{
		matrix->data[c] = calloc(rows, sizeof(double));
		
		if (matrix->data[c] == NULL)
		{
			for (int i = 0; i < c; i++)
				free(matrix->data[i]);

			free(matrix->data);

			return NULL;
		}
	}

	return matrix;
}

void DMatrix2Destruct(DMatrix2 *matrix)
{
	if (matrix == NULL)
		return;

	for (int c = 0; c < matrix->columns; c++)
		free(matrix->data[c]);

	free(matrix->data);

	free(matrix);
}

int DMatrix2Copy(DMatrix2 *src, DMatrix2 *dst)
{	
	if (src == NULL || dst == NULL)
		return 1;
	
	for (int c = 0; c < src->columns; c++)
	{
		for (int r = 0; r < src->rows; r++)
		{
			dst->data[c][r] = src->data[c][r];
		}
	}
}

double* DMatrix2At(DMatrix2 *matrix, int c, int r)
{
	if (c < 0 || r < 0 || c > matrix->columns || r > matrix->rows)
		return NULL;

	return &matrix->data[c][r];
}

void DMatrix2Log(DMatrix2 *matrix)
{
	if (matrix == NULL) {
		printf("(NULL)\n");
		return;
	}

	printf("cols - %d, rows - %d\n", matrix->columns, matrix->rows);
	for (int c = 0; c < matrix->columns; c++)
	{
		for (int r = 0; r < matrix->rows; r++)
			printf("%lf\t", *DMatrix2At(matrix, c, r));

		printf("\n");
	}
}

int DMatrix2Dot(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result)
{
	if (matrix1->rows != matrix2->columns)
		return 1;
		
	if (result == NULL)
		return 2;

	if (result->columns != matrix1->columns || result->rows != matrix2->rows)
		return 3;

	for (int c = 0; c < matrix1->columns; c++)
	{
		for (int r = 0; r < matrix2->rows; r++)
		{
			for (int k = 0; k < matrix1->rows; k++)
				result->data[c][r] += matrix1->data[c][k]*matrix2->data[k][r];
		}
	}

	return 0;
}

int DMatrix2Add(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result)
{
	if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns)
		return 1;

	if (result == NULL)
		return 1;

	for (int c = 0; c < matrix1->columns; c++)
	{
		for (int r = 0; r < matrix2->rows; r++)
		{
			result->data[c][r] = matrix1->data[c][r]+matrix2->data[c][r];
		}
	}

	return 0;
}
