#include "dmatrix2.h"
#include "ramenn.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// DMatrix2 Tests
char DMatrix2UnitTestCopy()
{
	char flag = 0;
	
	DMatrix2 *src = DMatrix2Construct(2, 3);
	DMatrix2 *dst = DMatrix2Construct(src->columns, src->rows);

	if (src == NULL || dst == NULL)
		goto cleanup;

	src->data[0][0] = +1.0; src->data[0][1] = -2.0; src->data[0][2] = +3.0;
	src->data[1][0] = -4.0; src->data[1][1] = +5.0; src->data[1][2] = -6.0;

	DMatrix2Copy(src, dst);
	
	flag = 1;
	flag &= dst->data[0][0] == +1.0 && dst->data[0][1] == -2.0 && dst->data[0][2] == +3.0;
	flag &= dst->data[1][0] == -4.0 && dst->data[1][1] == +5.0 && dst->data[1][2] == -6.0;

cleanup:
	DMatrix2Destruct(src);
	DMatrix2Destruct(dst);

	return flag;
}

char DMatrix2UnitTestDot()
{
	// +1.0 +2.0     -1.0     3.0
	// +3.0 -4.0 dot +2.0 = -11.0
	
	char flag = 0;

	DMatrix2* matrix1 = DMatrix2Construct(2, 2);
	DMatrix2* matrix2 = DMatrix2Construct(2, 1);

	if (!matrix1 || !matrix2)
	{
		goto cleanup;
	}
	
	double** d1 = matrix1->data;
	double** d2 = matrix2->data;

	d1[0][0] = +1.0; d1[0][1] = +2.0;
	d1[1][0] = +3.0; d1[1][1] = -4.0;

	d2[0][0] = -1.0;
	d2[1][0] = +2.0;

	DMatrix2* result = DMatrix2Construct(matrix1->columns, matrix2->rows);
	
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Dot(matrix1, matrix2, result);

		flag &= result->data[0][0] == +3.0;
		flag &= result->data[1][0] == -11.0;
	}

cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return flag;
}

char DMatrix2UnitTestAdd()
{	
	// +1.0 +2.0   -1.0 +3.0    0.0 +5.0
	// +3.0 -4.0 + +2.0 -4.0 = +5.0 -8.0
	
	char flag = 0;

	DMatrix2* matrix1 = DMatrix2Construct(2, 2);
	DMatrix2* matrix2 = DMatrix2Construct(2, 2);

	if (!matrix1 || !matrix2)
	{
		goto cleanup;
	}
	
	double** d1 = matrix1->data;
	double** d2 = matrix2->data;

	d1[0][0] = +1.0; d1[0][1] = +2.0;
	d1[1][0] = +3.0; d1[1][1] = -4.0;

	d2[0][0] = -1.0; d2[0][1] = +3.0;
	d2[1][0] = +2.0; d2[1][1] = -4.0;

	DMatrix2* result = DMatrix2Construct(matrix1->columns, matrix1->rows);
		
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Add(matrix1, matrix2, result);

		flag &= result->data[0][0] == +0.0;
		flag &= result->data[0][1] == +5.0;
		flag &= result->data[1][0] == +5.0;
		flag &= result->data[1][1] == -8.0;
	}

cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return flag;
}

// Neural Network Tests
char NNUnitTestInit()
{
	int layersSizes[] = { 2, 3, 4, 1 };
	const int nnSize = sizeof(layersSizes)/sizeof(int);
	NeuralNetwork *nn = NeuralNetworkConstruct(nnSize, layersSizes);
	
	char flag = 1;
	flag &= nn->layers[0]->size == 2;
	flag &= nn->layers[1]->size == 3;
	flag &= nn->layers[2]->size == 4;
	flag &= nn->layers[3]->size == 1;

	NeuralNetworkDestruct(nn);

	return flag;
}

char NNUnitTestForward()
{
	char flag = 0;

	int layersSizes[] = { 2, 1, 1 };
	const int nnSize = sizeof(layersSizes)/sizeof(int);
	NeuralNetwork *nn = NeuralNetworkConstruct(nnSize, layersSizes);	
	nn->layers[0]->weights->data[0][0] = -0.4;
	nn->layers[0]->weights->data[0][1] = +0.3;
	nn->layers[0]->biases->data[0][0] = -1.2;
	nn->layers[1]->weights->data[0][0] = +0.5;

	DMatrix2 *input = DMatrix2Construct(2, 1);
	DMatrix2* output = DMatrix2Construct(1, layersSizes[nnSize-1]);

	if (input == NULL || output == NULL)
		goto cleanup;

	input->data[0][0] = 8.0;
	input->data[1][0] = 9.0;

	NeuralNetworkForward(nn, input, output);

	flag = 1;
	flag &= (float)round(output->data[0][0]*100)/100 == -0.85f;

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(input);
	DMatrix2Destruct(output);
	
	return flag;
}

// All Unit Tests
void UnitTests()
{
	// DMatrix2
	printf("DMatrix2 Unit Test Copy:            ");
	printf(DMatrix2UnitTestCopy() ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Dot Product:     ");
	printf(DMatrix2UnitTestDot() ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Add:             ");
	printf(DMatrix2UnitTestAdd() ? "TRUE\n" : "FALSE\n");

	// Neural Network
	printf("Neural Network Unit Test Init:      ");
	printf(NNUnitTestInit()      ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Forward 1: ");
	printf(NNUnitTestForward()   ? "TRUE\n" : "FALSE\n");
}
