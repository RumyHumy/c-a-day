#ifndef RAMENN_H
#define RAMENN_H

#include "dmatrix2.h"

// Logic
typedef struct NeuralNetworkLayer
{
	DMatrix2 *weights; // next x curr
	DMatrix2 *biases;  // next x 1
	DMatrix2 *input;   // size x 1
	int size;
	double (*activationFunctionPtr)(double, char); // (inputValue, isPrime): outputValue
} NeuralNetworkLayer;

typedef struct NeuralNetwork
{
	NeuralNetworkLayer **layers;
	int layersCount;
} NeuralNetwork;

NeuralNetworkLayer* NeuralNetworkLayerConstruct(int size, int nextLayerSize);

void NeuralNetworkLayerDestruct(NeuralNetworkLayer* layer);

NeuralNetwork* NeuralNetworkConstruct(int layersCount, int *layersSizes);

void NeuralNetworkDestruct(NeuralNetwork* layer);

int NeuralNetworkForward(NeuralNetwork *network, DMatrix2* input, DMatrix2* output);

char NNUnitTestInit();

char NNUnitTestForward();

#endif // RAMENN_H
