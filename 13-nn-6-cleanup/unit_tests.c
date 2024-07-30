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

	if (src == NULL)
		goto cleanup;

	src->data[0][0] = +1.0; src->data[0][1] = -2.0; src->data[0][2] = +3.0;
	src->data[1][0] = -4.0; src->data[1][1] = +5.0; src->data[1][2] = -6.0;

	DMatrix2 *dst = DMatrix2ConstructCopy(src);

	if (dst == NULL)
		goto cleanup;
	
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
	
	DMatrix2* result = DMatrix2Construct(matrix1->rows, matrix2->columns);
	
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
	// +1.0 +2.0   -1.0 +4.0    0.0 +6.0
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

	d2[0][0] = -1.0; d2[0][1] = +4.0;
	d2[1][0] = +2.0; d2[1][1] = -4.0;

	DMatrix2* result = DMatrix2Construct(matrix1->rows, matrix1->columns);
		
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Add(matrix1, matrix2, result);

		flag &= result->data[0][0] == +0.0;
		flag &= result->data[0][1] == +6.0;
		flag &= result->data[1][0] == +5.0;
		flag &= result->data[1][1] == -8.0;
	}

cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return flag;
}

char DMatrix2UnitTestSubtract()
{	
	// +1.0 +2.0   -1.0 +3.0   +2.0 -1.0
	// +3.0 -4.0 - +2.0 -4.0 = +1.0  0.0
	
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

	DMatrix2* result = DMatrix2Construct(matrix1->rows, matrix1->columns);
		
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Subtract(matrix1, matrix2, result);

		flag &= result->data[0][0] == +2.0;
		flag &= result->data[0][1] == -1.0;
		flag &= result->data[1][0] == +1.0;
		flag &= result->data[1][1] ==  0.0;
	}

cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return flag;
}

char DMatrix2UnitTestMultiply()
{	
	// +1.0 +2.0   +2.0 -2.0   +2.0 -4.0
	// +3.0 -4.0 + +3.0 -3.0 = +9.0 +12.0
	
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

	d2[0][0] = +2.0; d2[0][1] = -2.0;
	d2[1][0] = +3.0; d2[1][1] = -3.0;

	DMatrix2* result = DMatrix2Construct(matrix1->rows, matrix1->columns);
		
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Multiply(matrix1, matrix2, result);

		flag &= result->data[0][0] == +2.0;
		flag &= result->data[0][1] == -4.0;
		flag &= result->data[1][0] == +9.0;
		flag &= result->data[1][1] == +12.0;
	}

cleanup:
	DMatrix2Destruct(matrix1);
	DMatrix2Destruct(matrix2);
	DMatrix2Destruct(result);

	return flag;
}

double MultiplyBy2d(double value)
{
	return value*2.0;
}

char DMatrix2UnitTestLambda()
{	
	// +1.0 +2.0    +2.0 +4.0
	// +3.0 -4.0 -> +6.0 +8.0
	
	char flag = 0;

	DMatrix2* matrix = DMatrix2Construct(2, 2);

	if (!matrix)
	{
		goto cleanup;
	}
	
	double** d = matrix->data;

	d[0][0] = +1.0; d[0][1] = +2.0;
	d[1][0] = +3.0; d[1][1] = -4.0;

	flag = 1;

	DMatrix2Lambda(matrix, MultiplyBy2d);

	flag &= d[0][0] == +2.0;
	flag &= d[0][1] == +4.0;
	flag &= d[1][0] == +6.0;
	flag &= d[1][1] == -8.0;

cleanup:
	DMatrix2Destruct(matrix);

	return flag;
}

char DMatrix2UnitTestTranspose()
{	
	// -1.0 +2.0      
	// +3.0 -4.0 T-> -1.0 +3.0 -5.0
	// -5.0 +6.0     +2.0 -4.0 +6.0
	
	char flag = 0;

	DMatrix2 *matrix = DMatrix2Construct(3, 2);

	if (!matrix)
		goto cleanup;
	
	double** d = matrix->data;

	d[0][0] = -1.0; d[0][1] = +2.0;
	d[1][0] = +3.0; d[1][1] = -4.0;
	d[2][0] = -5.0; d[2][1] = +6.0;

	DMatrix2 *result = DMatrix2Construct(matrix->columns, matrix->rows);

	if (!result)
		goto cleanup;

	DMatrix2Transpose(matrix, result);

	double** r = result->data;

	flag = 1;
	flag &= r[0][0] == -1.0;
	flag &= r[0][1] == +3.0;
	flag &= r[0][2] == -5.0;
	flag &= r[1][0] == +2.0;
	flag &= r[1][1] == -4.0;
	flag &= r[1][2] == +6.0;

cleanup:
	DMatrix2Destruct(matrix);
	DMatrix2Destruct(result);

	return flag;
}

// - Neural Network Tests -
char NNUnitTestInit()
{
	NeuralNetwork *nn = NeuralNetworkConstruct(
		4,
		(int[]){ 2, 3, 4, 1 },
		(NeuralNetworkActivation[]){
			ACTIVATION_LINEAR,
			ACTIVATION_LINEAR,
			ACTIVATION_LINEAR
		}
	);
	
	char flag = 1;
	flag &= nn->layers[0]->size == 2;
	flag &= nn->layers[1]->size == 3;
	flag &= nn->layers[2]->size == 4;
	flag &= nn->layers[3]->size == 1;

	NeuralNetworkDestruct(nn);

	return flag;
}

char NNUnitTestLayerForward()
{
	// W: +0.0 +1.0 B: +0.5
	//    +0.5 +0.0    -0.5
	//    -0.5 -2.0     0.0
	char flag = 0;

	NeuralNetwork *nn = NeuralNetworkConstruct(
		2,
		(int[]){ 2, 3 },
		(NeuralNetworkActivation[]){ACTIVATION_SIGMOID}
	);

	if (nn == NULL)
		goto cleanup;

	DMatrix2 *input = DMatrix2Construct(2, 1);
	DMatrix2 *output = DMatrix2Construct(3, 1);

	double **id = input->data;
	double **wd = nn->layers[0]->weights->data;
	double **bd = nn->layers[0]->biases->data;

	id[0][0] = -1.0;
	id[1][0] = +0.5;

	wd[0][0] =  0.0; wd[0][1] = +1.0;
	wd[1][0] = +0.5; wd[1][1] = +0.0;
	wd[2][0] = -0.5; wd[2][1] = -2.0;

	bd[0][0] = +0.5;
	bd[1][0] = -0.5;
	bd[2][0] =  0.0;

	NeuralNetworkLayerForward(nn->layers[0], input, output);

	
	flag = 1;
	flag &= roundf(output->data[0][0]*1000)/1000 == roundf(0.731*1000)/1000;
	flag &= roundf(output->data[1][0]*1000)/1000 == roundf(0.269*1000)/1000;
	flag &= roundf(output->data[2][0]*1000)/1000 == roundf(0.378*1000)/1000;

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(input);
	DMatrix2Destruct(output);
	
	return flag;
}

char NNUnitTestMeanSquaredError()
{
	char flag = 0;

	DMatrix2 *m1 = DMatrix2Construct(5, 1);
	DMatrix2 *m2 = DMatrix2Construct(5, 1);
	DMatrix2 *res = DMatrix2Construct(5, 1);
	
	if (m1 == NULL || m2 == NULL || res == NULL)
		goto cleanup;

	double **d1 = m1->data;
	double **d2 = m2->data;
	double **dr = res->data;
	
	d1[0][0] = 0.1;
	d1[1][0] = 0.2;
	d1[2][0] = 0.3;
	d1[3][0] = 0.4;
	d1[4][0] = 0.5;

	d2[0][0] = 1.0;
	d2[1][0] = 0.5;
	d2[2][0] = 0.0;
	d2[3][0] = -0.5;
	d2[4][0] = -1.0;
	
	MeanSquaredErrorPrime(m1, m2, res);
	flag = 1;
	flag &= roundf(MeanSquaredError(m1, m2)*1000)/1000 != +0.81;
	flag &= dr[0][0] == +0.36;
	flag &= dr[1][0] == +0.12;
	flag &= dr[2][0] == -0.12;
	flag &= dr[3][0] == -0.36;
	flag &= dr[4][0] == -0.60;

cleanup:
	DMatrix2Destruct(m1);
	DMatrix2Destruct(m2);
	DMatrix2Destruct(res);

	return flag;
}

char NNUnitTestBackward()
{	
	char flag = 0;

	NeuralNetwork *nn = NeuralNetworkConstruct(
		2,
		(int[]){ 2, 3 },
		(NeuralNetworkActivation[]){ACTIVATION_SIGMOID}
	);

	if (nn == NULL)
		goto cleanup;

	DMatrix2 *input = DMatrix2Construct(2, 1);
	DMatrix2 *output = DMatrix2Construct(3, 1);
	DMatrix2 *expectedOutput = DMatrix2Construct(3, 1);

	double **id = input->data;
	double **od = output->data;
	double **ed = expectedOutput->data;

	id[0][0] = -1.0;
	id[1][0] = +1.0;

	ed[0][0] = +1.000;
	ed[1][0] = +0.666;
	ed[2][0] = +0.077;

	for (int i = 0; i < 100000; i++)
	{
		DMatrix2 *errorGradient = DMatrix2Construct(3, 1);
		NeuralNetworkLayerForward(nn->layers[0], input, output);
		MeanSquaredErrorPrime(expectedOutput, output, errorGradient);
		NeuralNetworkLayerBackward(nn->layers[0], errorGradient, 0.001);
		DMatrix2Destruct(errorGradient);
	}

	NeuralNetworkLayerForward(nn->layers[0], input, output);

	DMatrix2Log(nn->layers[0]->activationInput);
	
	flag = 1;
	flag &= roundf(output->data[0][0]*1000)/1000 == roundf(+1.000*1000)/1000;
	flag &= roundf(output->data[1][0]*1000)/1000 == roundf(+0.666*1000)/1000;
	flag &= roundf(output->data[2][0]*1000)/1000 == roundf(+0.077*1000)/1000;

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(input);
	DMatrix2Destruct(output);
	
	return flag;
}

char NNUnitTestBackward2()
{
}

// All Unit Tests
void UnitTests()
{
	// DMatrix2
	printf("DMatrix2 Unit Test Copy:             ");
	printf(DMatrix2UnitTestCopy()          ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Dot Product:      ");
	printf(DMatrix2UnitTestDot()           ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Add:              ");
	printf(DMatrix2UnitTestAdd()           ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Subtract:         ");
	printf(DMatrix2UnitTestSubtract()      ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Multiply:         ");
	printf(DMatrix2UnitTestMultiply()      ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Lambda:           ");
	printf(DMatrix2UnitTestLambda() ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Transpose:        ");
	printf(DMatrix2UnitTestTranspose()     ? "TRUE\n" : "FALSE\n" );

	// Neural Network
	printf("Neural Network Unit Test Init:       ");
	printf(NNUnitTestInit()       ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Forward 1:  ");
	printf(NNUnitTestLayerForward()    ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test MSE:        ");
	printf(NNUnitTestMeanSquaredError() ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Backward 1: ");
	printf(NNUnitTestBackward()   ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Backward 2: ");
	printf(NNUnitTestBackward2()  ? "TRUE\n" : "FALSE\n");

}
