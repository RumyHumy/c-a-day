#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dmatrix2.h"

/*
typedef struct DMatrix2
{
	double **data;
	int rows;
	int columns;
} DMatrix2;
*/

// -- CONSTRUCT & DESTRUCT --
DMatrix2* DMatrix2Construct(int rows, int columns)
{
	double **data = calloc(rows, sizeof(*data));

	if (data == NULL)
		return NULL;

	for (int r = 0; r < rows; r++)
	{
		data[r] = calloc(columns, sizeof(double));
		
		if (data[r] == NULL)
		{
			for (int i = 0; i < r; i++)
				free(data[i]);

			return NULL;
		}
	}
	
	DMatrix2* matrix = malloc(sizeof(*matrix));

	if (matrix == NULL)
		return NULL;

	*matrix = (DMatrix2){ .data=data, .rows=rows, .columns=columns };

	return matrix;
}

DMatrix2* DMatrix2ConstructCopy(DMatrix2 *src)
{
	DMatrix2 *dst = DMatrix2Construct(src->rows, src->columns);

	DMatrix2Copy(src, dst);

	return dst;
}

void DMatrix2Destruct(DMatrix2 *matrix)
{
	if (matrix == NULL)
		return;

	for (int r = matrix->rows-1; r >= 0; r--)
		free(matrix->data[r]);

	free(matrix->data);

	free(matrix);
}

// -- HANDY METHODS --

void DMatrix2Copy(DMatrix2 *src, DMatrix2 *dst)
{	
	DMATRIX2_FOREACH(src, r, c)
		dst->data[r][c] = src->data[r][c];
}

void DMatrix2Log(DMatrix2 *matrix)
{
	if (matrix == NULL) {
		printf("(NULL)\n");
		return;
	}

	printf("%d x %d\n", matrix->rows, matrix->columns);
	for (int r = 0; r < matrix->rows; r++)
	{
		for (int c = 0; c < matrix->columns; c++)
			printf("%lf\t", matrix->data[r][c]);

		printf("\n");
	}
}

// -- OPERATIONS --

// - Element-wise -

#define DMATRIX2_DECLARE_ELEMENTWISE(NAME, OPERATION) \
void NAME(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result) \
{ \
	DMATRIX2_FOREACH(matrix1, r, c) \
		result->data[r][c] = matrix1->data[r][c] OPERATION matrix2->data[r][c]; \
}

DMATRIX2_DECLARE_ELEMENTWISE(DMatrix2Add,+)
DMATRIX2_DECLARE_ELEMENTWISE(DMatrix2Subtract,-)
DMATRIX2_DECLARE_ELEMENTWISE(DMatrix2Multiply,*)
DMATRIX2_DECLARE_ELEMENTWISE(DMatrix2Divide,/)

void DMatrix2Lambda(DMatrix2 *matrix, double (*lambda)(double))
{
	DMATRIX2_FOREACH(matrix, r, c)
		matrix->data[r][c] = lambda(matrix->data[r][c]);
}

// - Other -

void DMatrix2Dot(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result)
{
	DMATRIX2_FOREACH_ROW(matrix1, r)
	{
		DMATRIX2_FOREACH_COLUMN(matrix2, c)
		{
			result->data[r][c] = 0;
			DMATRIX2_FOREACH_COLUMN(matrix1, k)
			{
				result->data[r][c] += matrix1->data[r][k]*matrix2->data[k][c];
			}
		}
	}
}

void DMatrix2Transpose(DMatrix2 *src, DMatrix2 *dst)
{
	DMATRIX2_FOREACH(dst, r, c)
		dst->data[r][c] = src->data[c][r];
}
