#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Matrix implimentation
typedef struct DMatrix2
{
	double **data;
	int columns;
	int rows;
} DMatrix2;

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

double* DMatrix2At(DMatrix2 *matrix, int c, int r)
{
	if (c < 0 || r < 0 || c > matrix->columns || r > matrix->rows)
		return NULL;

	return &matrix->data[c][r];
}

void DMatrix2Log(DMatrix2 *matrix)
{
	printf("%d %d\n", matrix->columns, matrix->rows);
	for (int c = 0; c < matrix->columns; c++)
	{
		for (int r = 0; r < matrix->rows; r++)
			printf("%lf ", *DMatrix2At(matrix, c, r));

		printf("\n");
	}
}

DMatrix2* DMatrix2Dot(DMatrix2 *matrix1, DMatrix2 *matrix2)
{
	if (matrix1->rows != matrix2->columns)
		return NULL;

	DMatrix2* resultMatrix = DMatrix2Construct(matrix1->columns, matrix2->rows);

	for (int c = 0; c < matrix1->columns; c++)
	{
		for (int r = 0; r < matrix2->rows; r++)
		{
			for (int k = 0; k < matrix1->rows; k++)
				*DMatrix2At(resultMatrix, c, r) +=
					(*DMatrix2At(matrix1, c, k))*(*DMatrix2At(matrix2, k, r));
		}
	}

	return resultMatrix;
}

int MatrixTest()
{
	// +1.0 +2.0     -1.0     3.0
	// +3.0 -4.0 dot +2.0 = -11.0
	
	DMatrix2* matrix1 = DMatrix2Construct(2, 2);
	DMatrix2* matrix2 = DMatrix2Construct(2, 1);

	if (!matrix1 || !matrix2)
		goto cleanup;
	
	double** d1 = matrix1->data;
	double** d2 = matrix2->data;

	d1[0][0] = +1.0; d1[0][1] = +2.0;
	d1[1][0] = +3.0; d1[1][1] = -4.0;

	d2[0][0] = -1.0;
	d2[1][0] = +2.0;

	DMatrix2Log(matrix1);
	printf("    dot\n");
	DMatrix2Log(matrix2);

	DMatrix2* result = DMatrix2Dot(matrix1, matrix2);
	
	if (result == NULL)
		goto cleanup;

	printf("    equals\n");
	DMatrix2Log(result);
	
cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return 0;
}

int main()
{
	MatrixTest();

	return 0;
}

/*
// Activation functions
double ActivationSigmoid(char prime_flag)
{
	if (!prime_flag)
		return 1/(1+np.exp(-x))
	return s*(1-s);
}

// Layer implementation
typedef struct DenseLayer 
{
	DMatrix2 weights;
	DMatrix2 biases;
} Layer;
*/
