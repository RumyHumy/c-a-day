#ifndef RAMENN_H
#define RAMENN_H

#include "dmatrix2.h"

// Logic
typedef struct NeuralNetworkLayer
{
	DMatrix2 *weights; // size x nextLayerSize
	DMatrix2 *biases;  // size x 1
	DMatrix2 *input;   // size x 1
	DMatrix2 *output;  // size x 1
	int size;
	int nextLayerSize;
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

// DMatrix2* NeuralNetworkForward(DMatrix2* input);

#endif // RAMENN_H
