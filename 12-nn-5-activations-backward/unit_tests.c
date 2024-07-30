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

	DMatrix2* result = DMatrix2Construct(matrix1->columns, matrix1->rows);
		
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

char DMatrix2UnitTestHadamard()
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

	DMatrix2* result = DMatrix2Construct(matrix1->columns, matrix1->rows);
		
	if (result != NULL)
	{
		flag = 1;

		DMatrix2Hadamard(matrix1, matrix2, result);

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

char DMatrix2UnitTestForEachLambda()
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

	DMatrix2ForEachLambda(matrix, MultiplyBy2d);

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

	DMatrix2 *result = DMatrix2Construct(matrix->rows, matrix->columns);
	DMatrix2Transpose(matrix, result);

	if (!result)
		goto cleanup;

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
	int layersSizes[] = { 2, 3, 4, 1 };
	const int nnSize = sizeof(layersSizes)/sizeof(int);

	NeuralNetwork *nn = NeuralNetworkConstruct(nnSize, layersSizes, NULL, NULL); // SEGFAULT
	
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

	NeuralNetwork *nn = NeuralNetworkConstruct(nnSize, layersSizes, NULL, NULL);

	nn->layers[0]->weights->data[0][0] = -0.4;
	nn->layers[0]->weights->data[0][1] = +0.3;
	nn->layers[0]->biases->data[0][0] = -1.2;
	nn->layers[1]->weights->data[0][0] = +0.5;

	DMatrix2 *input = DMatrix2Construct(2, 1);
	DMatrix2* output = DMatrix2Construct(1, 1);

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

char NNUnitTestActivation()
{	
	char flag = 0;

	int layersSizes[] = { 1, 1, 1 };

	double (*activationFunctions[])(double) = {
		ActivationLinear,
		ActivationSigmoid};

	double (*activationPrimeFunctions[])(double) = {
		ActivationLinearPrime,
		ActivationSigmoidPrime};

	const int nnSize = sizeof(layersSizes)/sizeof(int);

	NeuralNetwork *nn = NeuralNetworkConstruct(
			nnSize,
			layersSizes,
			activationFunctions,
			activationPrimeFunctions);	

	nn->layers[0]->weights->data[0][0] = -1.0;
	nn->layers[0]->biases->data[0][0] = -2.0;
	nn->layers[1]->weights->data[0][0] = 1.0;

	DMatrix2 *input =  DMatrix2Construct(1, 1);
	DMatrix2* output = DMatrix2Construct(1, 1);

	if (input == NULL || output == NULL)
		goto cleanup;

	input->data[0][0] = -1.0;

	NeuralNetworkForward(nn, input, output);
	
	flag = 1;
	flag &= (float)round(output->data[0][0]*1000)/1000 == 0.269f;

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(input);
	DMatrix2Destruct(output);
	
	return flag;
}

// char NNUnitTestMeanSquaredError()
// {
// 	DMatrix2 *m1 = DMatrix2Construct(5, 1);
// 	double **d1 = m1->data;
// 	
// 	d1[0][0] = 0.1;
// 	d1[1][0] = 0.2;
// 	d1[2][0] = 0.3;
// 	d1[3][0] = 0.4;
// 	d1[4][0] = 0.5;
// 
// 	DMatrix2 *m2 = DMatrix2Construct(5, 1);
// 	double **d2 = m2->data;
// 
// 	d2[0][0] = 1.0;
// 	d2[1][0] = 0.5;
// 	d2[2][0] = 0.0;
// 	d2[3][0] = -0.5;
// 	d2[4][0] = -1.0;
// 	
// 	DMatrix2 *result = DMatrix2Construct(5, 1);
// 	
// 	MeanSquaredErrorPrime(m1, m2, result);
// 
// 	printf("MSE: %lf\n", MeanSquaredError(m1, m2));
// 	printf("MSEP:\n");
// 	DMatrix2Log(result);
// }

char NNUnitTestBackward()
{
	char flag = 0;

	int layersSizes[] = { 1, 1 };

	double (*activationFunctions[])(double) = {
		ActivationSigmoid,
		ActivationSigmoid};

	double (*activationPrimeFunctions[])(double) = {
		ActivationSigmoidPrime,
		ActivationSigmoidPrime};

	const int nnSize = sizeof(layersSizes)/sizeof(int);

	NeuralNetwork *nn = NeuralNetworkConstruct(
			nnSize,
			layersSizes,
			activationFunctions,
			activationPrimeFunctions);	

	DMatrix2 *input = DMatrix2Construct(1, 1);
	DMatrix2* output = DMatrix2Construct(1, 1);
	DMatrix2* expectedOutput = DMatrix2Construct(1, 1);

	if (input == NULL || output == NULL)
		goto cleanup;

	input->data[0][0] = -1.0;
	expectedOutput->data[0][0] = 0.77;

	DMatrix2 *outputGradient = DMatrix2Construct(1, 1);

	for (int i = 0; i < 10000; i++)
	{
		NeuralNetworkForward(nn, input, output);
		MeanSquaredErrorPrime(expectedOutput, output, outputGradient);
		NeuralNetworkBackward(nn, outputGradient, 0.1);
	}

	DMatrix2Log(nn->layers[0]->weights);
	DMatrix2Log(nn->layers[0]->biases);

	NeuralNetworkForward(nn, input, output);

	printf("---OUTPUT: %lf\n", output->data[0][0]);

	flag = 1;
	flag &= (float)round(output->data[0][0]*1000)/1000 == expectedOutput->data[0][0];

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(input);
	DMatrix2Destruct(output);
	DMatrix2Destruct(expectedOutput);
	DMatrix2Destruct(outputGradient);
	
	return flag;
}

char NNUnitTestBackward2()
{
	char flag = 0;

	int layersSizes[] = { 2, 3, 1 };

	double (*activationFunctions[])(double) = {
		ActivationSigmoid,
		ActivationSigmoid,
		ActivationSigmoid};

	double (*activationPrimeFunctions[])(double) = {
		ActivationSigmoidPrime,
		ActivationSigmoidPrime,
		ActivationSigmoidPrime};

	const int nnSize = sizeof(layersSizes)/sizeof(int);

	NeuralNetwork *nn = NeuralNetworkConstruct(
			nnSize,
			layersSizes,
			activationFunctions,
			activationPrimeFunctions);	

	DMatrix2 *input0 = DMatrix2Construct(2, 1);
	DMatrix2 *input1 = DMatrix2Construct(2, 1);
	DMatrix2 *input2 = DMatrix2Construct(2, 1);
	DMatrix2 *input3 = DMatrix2Construct(2, 1);
	DMatrix2* output = DMatrix2Construct(1, 1);
	DMatrix2* expectedOutput0 = DMatrix2Construct(1, 1);
	DMatrix2* expectedOutput1 = DMatrix2Construct(1, 1);
	DMatrix2* expectedOutput2 = DMatrix2Construct(1, 1);
	DMatrix2* expectedOutput3 = DMatrix2Construct(1, 1);


	input0->data[0][0] = 0.0; input0->data[1][0] = 0.0;
	input1->data[0][0] = 0.0; input1->data[1][0] = 1.0;
	input2->data[0][0] = 1.0; input2->data[1][0] = 0.0;
	input3->data[0][0] = 1.0; input3->data[1][0] = 1.0;
	expectedOutput0->data[0][0] = 0.0;
	expectedOutput1->data[0][0] = 1.0;
	expectedOutput2->data[0][0] = 1.0;
	expectedOutput3->data[0][0] = 0.0;

	DMatrix2 *outputGradient = DMatrix2Construct(1, 1);

	for (int i = 0; i < 10000; i++)
	{
		NeuralNetworkForward(nn, input0, output);
		MeanSquaredErrorPrime(expectedOutput0, output, outputGradient);
		NeuralNetworkBackward(nn, outputGradient, 0.1);

		NeuralNetworkForward(nn, input1, output);
		MeanSquaredErrorPrime(expectedOutput1, output, outputGradient);
		NeuralNetworkBackward(nn, outputGradient, 0.1);

		NeuralNetworkForward(nn, input2, output);
		MeanSquaredErrorPrime(expectedOutput2, output, outputGradient);
		NeuralNetworkBackward(nn, outputGradient, 0.1);
		
		NeuralNetworkForward(nn, input3, output);
		MeanSquaredErrorPrime(expectedOutput3, output, outputGradient);
		NeuralNetworkBackward(nn, outputGradient, 0.1);
	}

	DMatrix2Log(nn->layers[0]->weights);
	DMatrix2Log(nn->layers[0]->biases);

	NeuralNetworkForward(nn, input0, output);
	printf("OUTPUT0: %lf\n", output->data[0][0]);
	NeuralNetworkForward(nn, input1, output);
	printf("OUTPUT1: %lf\n", output->data[0][0]);
	NeuralNetworkForward(nn, input2, output);
	printf("OUTPUT2: %lf\n", output->data[0][0]);
	NeuralNetworkForward(nn, input3, output);
	printf("OUTPUT3: %lf\n", output->data[0][0]);

	flag = 1;

cleanup:
	NeuralNetworkDestruct(nn);
	DMatrix2Destruct(output);
	DMatrix2Destruct(outputGradient);
	
	return flag;
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
	printf("DMatrix2 Unit Test Hadamard:         ");
	printf(DMatrix2UnitTestHadamard()      ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test For Each lambda:  ");
	printf(DMatrix2UnitTestForEachLambda() ? "TRUE\n" : "FALSE\n");
	printf("DMatrix2 Unit Test Transpose:        ");
	printf(DMatrix2UnitTestTranspose()     ? "TRUE\n" : "FALSE\n" );
	// Neural Network
	printf("Neural Network Unit Test Init:       ");
	printf(NNUnitTestInit()       ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Forward 1:  ");
	printf(NNUnitTestForward()    ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Activation: ");
	printf(NNUnitTestActivation() ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Backward 1: ");
	printf(NNUnitTestBackward()   ? "TRUE\n" : "FALSE\n");
	printf("Neural Network Unit Test Backward 2: ");
	printf(NNUnitTestBackward2()  ? "TRUE\n" : "FALSE\n");

}
