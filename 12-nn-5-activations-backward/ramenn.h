#ifndef RAMENN_H
#define RAMENN_H

#include "dmatrix2.h"

// -- MEAN SQARED ERROR --

double MeanSquaredError(DMatrix2 *expected, DMatrix2 *actual);
void MeanSquaredErrorPrime(DMatrix2 *expected, DMatrix2 *actual, DMatrix2 *result);

// -- ACTIVATIONS --

// - Linear -
double ActivationLinear(double value);
double ActivationLinearPrime(double value);

// - Sigmoid -
double ActivationSigmoid(double value);
double ActivationSigmoidPrime(double value);

// -- STRUCTURES --

// - Layer -

typedef struct NeuralNetworkLayer
{
	DMatrix2 *weights; // next x curr
	DMatrix2 *biases;  // next x 1
	DMatrix2 *input;   // size x 1
	int size;
	double (*activationFunction     )(double);
	double (*activationPrimeFunction)(double);
} NeuralNetworkLayer;

// - Network -
typedef struct NeuralNetwork
{
	NeuralNetworkLayer **layers;
	int layersCount;
} NeuralNetwork;

// -- METHODS --

// - Layer -
NeuralNetworkLayer* NeuralNetworkLayerConstruct(
	int size,
	int nextLayerSize,
	double (*activationFunction     )(double),
	double (*activationPrimeFunction)(double));

void NeuralNetworkLayerDestruct(NeuralNetworkLayer* layer);

// - Network -
NeuralNetwork* NeuralNetworkConstruct(
	int layersCount,
	int *layersSizes,
	double (*activationFunctions[]     )(double),
	double (*activationPrimeFunctions[])(double));

void NeuralNetworkDestruct(NeuralNetwork* layer);

int NeuralNetworkForward(NeuralNetwork *network, DMatrix2* input, DMatrix2* output);

int NeuralNetworkBackward(
	NeuralNetwork *network,
	DMatrix2 *outputGradient,
	double learningRate);

#endif // RAMENN_H
