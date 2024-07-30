#ifndef DMATRIX2_H
#define DMATRIX2_H

// -- Structure --

typedef struct DMatrix2
{
	double **data;
	int columns;
	int rows;
} DMatrix2;

// -- Methods --

// Construct & Destructk
DMatrix2* DMatrix2Construct(int columns, int rows);
void      DMatrix2Destruct(DMatrix2 *matrix);

int DMatrix2Copy(DMatrix2 *src, DMatrix2 *dst);

double* DMatrix2At(DMatrix2 *matrix, int c, int r);

void DMatrix2Log(DMatrix2 *matrix);

int DMatrix2Dot(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

int DMatrix2Add(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

int DMatrix2Subtract(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

int DMatrix2Hadamard(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

int DMatrix2ForEachLambda(DMatrix2 *matrix, double (*lambda)(double));

int DMatrix2Transpose(DMatrix2 *src, DMatrix2 *dst);

#endif // DMATRIX2_H
