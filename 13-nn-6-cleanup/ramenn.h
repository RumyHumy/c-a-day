#ifndef RAMENN_H
#define RAMENN_H

#include "dmatrix2.h"

// -- MEAN SQARED ERROR --

double MeanSquaredError(DMatrix2 *expected, DMatrix2 *actual);
void MeanSquaredErrorPrime(DMatrix2 *expected, DMatrix2 *actual, DMatrix2 *result);

// -- STRUCTURES --

// - Activation -
// ACTIVATION: function, derivative
typedef struct NeuralNetworkActivation
{
	double (*function     )(double);
	double (*functionPrime)(double);
} NeuralNetworkActivation;

// - Layer -
// LAYER: -> input -> DENSE -> activationInput -> ACTIVATION -> output -> ...
typedef struct NeuralNetworkLayer
{
	DMatrix2 *weights; // next x curr
	DMatrix2 *biases;  // next x 1
	DMatrix2 *input;   // size x 1
	DMatrix2 *activationInput;   // size x 1
	int size;
	NeuralNetworkActivation activation;
} NeuralNetworkLayer;

// - Network -
// NETWORK LAYER_1 -> LAYER_2 -> ... -> LAYER_N
typedef struct NeuralNetwork
{
	NeuralNetworkLayer **layers;
	int layersCount;
} NeuralNetwork;

// -- ACTIVATIONS --

// - None (for the last layer) -
#define ACTIVATION_NONE (NeuralNetworkActivation){NULL,NULL}

// - Linear -
double ActivationLinear(double value);
double ActivationLinearPrime(double value);

#define ACTIVATION_LINEAR (NeuralNetworkActivation){ActivationLinear,ActivationLinearPrime}

// - Sigmoid -
double ActivationSigmoid(double value);
double ActivationSigmoidPrime(double value);

#define ACTIVATION_SIGMOID (NeuralNetworkActivation){ActivationSigmoid,ActivationSigmoidPrime}

// -- METHODS --

// - Layer -
NeuralNetworkLayer* NeuralNetworkLayerConstruct(
	int size,
	int nextLayerSize,
	NeuralNetworkActivation activation);

void NeuralNetworkLayerDestruct(NeuralNetworkLayer* layer);

// - Network -
NeuralNetwork* NeuralNetworkConstruct(
	int layersCount,
	int *layersSizes,
	NeuralNetworkActivation activations[]);

void NeuralNetworkDestruct(NeuralNetwork* layer);

void NeuralNetworkLayerForward(NeuralNetworkLayer *layer, DMatrix2* input, DMatrix2* output);

void NeuralNetworkLayerBackward(
	NeuralNetworkLayer *layer,
	DMatrix2 *outputGradient,
	double learningRate);

#endif // RAMENN_H
