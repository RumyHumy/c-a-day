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
#define DMATRIX2_FOREACH_ROW(matrix, r)    for (int r = 0; r < matrix->rows;    r++)
#define DMATRIX2_FOREACH_COLUMN(matrix, c) for (int c = 0; c < matrix->columns; c++)

#define DMATRIX2_FOREACH(matrix, r, c) \
DMATRIX2_FOREACH_ROW(matrix, r) \
	DMATRIX2_FOREACH_COLUMN(matrix, c)

// - Construct & Destruct -
DMatrix2* DMatrix2Construct    (int columns, int rows);
DMatrix2* DMatrix2ConstructCopy(DMatrix2 *matrix);
void      DMatrix2Destruct     (DMatrix2 *matrix);

void DMatrix2Copy(DMatrix2 *src, DMatrix2 *dst);

void DMatrix2Log(DMatrix2 *matrix);

void DMatrix2Add     (DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);
void DMatrix2Subtract(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);
void DMatrix2Multiply(DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);
void DMatrix2Divide  (DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

void DMatrix2Dot     (DMatrix2 *matrix1, DMatrix2 *matrix2, DMatrix2* result);

void DMatrix2Lambda  (DMatrix2 *matrix, double (*lambda)(double));

void DMatrix2Transpose(DMatrix2 *src, DMatrix2 *dst);

#endif // DMATRIX2_H
