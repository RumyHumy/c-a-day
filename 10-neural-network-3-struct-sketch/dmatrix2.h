#ifndef DMATRIX2_H
#define DMATRIX2_H

typedef struct DMatrix2
{
	double **data;
	int columns;
	int rows;
} DMatrix2;

DMatrix2* DMatrix2Construct(int columns, int rows);

void DMatrix2Destruct(DMatrix2 *matrix);

double* DMatrix2At(DMatrix2 *matrix, int c, int r);

void DMatrix2Log(DMatrix2 *matrix);

DMatrix2* DMatrix2Dot(DMatrix2 *matrix1, DMatrix2 *matrix2);



#endif // DMATRIX2_H
