#include "dmatrix2.h"
#include "ramenn.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// TODO: Remove output and input and do shit correctly

// - Check for unsafe code
// - Make transposing fast

// -- ERROR --
// -- Mean Squared Error --
double MeanSquaredError(DMatrix2 *expected, DMatrix2 *actual)
{
	// TODO: Clean
	if (expected->columns != actual->columns || expected->rows != actual->rows)
		return 0.0;

	if (expected->rows != 1)
		return 0.0;
	
	double sum = 0.0;
	for (int c = 0; c < expected->columns; c++)
	{
		double value = expected->data[c][0] - actual->data[c][0];
		sum += value*value;
	}
	return sum / (double)expected->columns;
}

void MeanSquaredErrorPrime(DMatrix2 *expected, DMatrix2 *actual, DMatrix2 *result)
{	
	// TODO: Clean
	if (expected->columns != actual->columns || expected->rows != actual->rows)
		return;

	if (expected->rows != 1)
		return;
	
	for (int c = 0; c < expected->columns; c++)
		result->data[c][0] =
			2.0 * (actual->data[c][0] - expected->data[c][0]) / expected->columns;
}

// -- ACTIVATION FUNCTIONS --

// - Linear -

double ActivationLinear(double value)
{
	return value;
}

double ActivationLinearPrime(double value)
{
	return 1.0;
}

// - Sigmoid -

double ActivationSigmoid(double value)
{
	return 1.0 / (1.0 + exp(-value));
}

double ActivationSigmoidPrime(double value)
{
	double sigmoid = ActivationSigmoid(value);
	return sigmoid * (1 - sigmoid);
}

// -- METHODS --

// - Layer -

NeuralNetworkLayer* NeuralNetworkLayerConstruct(
	int size,
	int nextLayerSize,
	double (*activationFunction     )(double),
	double (*activationPrimeFunction)(double))
{
	if (size <= 0)
		return NULL;
	
	DMatrix2 *weights = NULL;
	DMatrix2 *biases = NULL;

	if (nextLayerSize > 0)
	{
		weights = DMatrix2Construct(nextLayerSize, size);
		
		if (weights == NULL)
			return NULL;

		biases = DMatrix2Construct(nextLayerSize, 1);

		if (biases == NULL)
			return NULL;
	}

	NeuralNetworkLayer* layer = calloc(1, sizeof(*layer));

	*layer = (NeuralNetworkLayer){
		.weights = weights,
		.biases  = biases,
		.input   = NULL,
		.size    = size,
		.activationFunction      = activationFunction,
		.activationPrimeFunction = activationPrimeFunction 
	};
	
	return layer;
}

void NeuralNetworkLayerDestruct(NeuralNetworkLayer* layer)
{
	if (layer == NULL)
		return;

	DMatrix2Destruct(layer->weights);
	DMatrix2Destruct(layer->biases);
	DMatrix2Destruct(layer->input);	

	free(layer);
}

// - Network -

NeuralNetwork* NeuralNetworkConstruct(
		int layersCount,
		int *layersSizes,
		double (*activationFunctions[])(double),
		double (*activationPrimeFunctions[])(double))
{
	NeuralNetworkLayer **layers = NULL;
	NeuralNetwork *network = malloc(sizeof(*network));

	if (network == NULL)
		return NULL;
	
	layers = calloc(layersCount, sizeof(*layers));

	if (layers == NULL)
	{
		free(network);
		return NULL;
	}

	*network = (NeuralNetwork){
		.layers      = layers,
		.layersCount = layersCount
	};

	for (int l = 0; l < layersCount; l++)
	{
		double (*currentActivationFunction)(double) =
			(activationFunctions != NULL ? activationFunctions[l] : NULL);
		double (*currentActivationPrimeFunction)(double) =
			(activationPrimeFunctions != NULL ? activationPrimeFunctions[l] : NULL);

		layers[l] = NeuralNetworkLayerConstruct(
			layersSizes[l],
			(l != layersCount-1 ? layersSizes[l+1] : 0),
			currentActivationFunction,
			currentActivationPrimeFunction
		);

		if (layers[l] == NULL)
		{
			for (int c = 0; c < l; c++)
				NeuralNetworkLayerDestruct(layers[c]);
			
			free(layers);

			free(network);

			return NULL;
		}
	}

	return network;
}

void NeuralNetworkDestruct(NeuralNetwork* network)
{
	if (network == NULL)
		return;

	for (int l = 0; l < network->layersCount; l++)
	{
		NeuralNetworkLayerDestruct(network->layers[l]);
	}

	free(network->layers);
	
	free(network);
}

int NeuralNetworkForward(NeuralNetwork *network, DMatrix2 *input, DMatrix2 *output)
{
	for (int l = 0; l < network->layersCount; l++)
	{
		DMatrix2Destruct(network->layers[l]->input);
		network->layers[l]->input = NULL;
	}

	network->layers[0]->input = DMatrix2Construct(input->columns, input->rows);

	DMatrix2Copy(input, network->layers[0]->input);

	DMatrix2 *currentOutput = NULL;

	for (int l = 0; l < network->layersCount; l++)
	{
		NeuralNetworkLayer *current = network->layers[l];
		NeuralNetworkLayer *next =
			(l == network->layersCount-1 ? NULL : network->layers[l+1]);

		if (next == NULL)
			break;

		currentOutput = DMatrix2Construct(1, next->size);
		
		DMatrix2Dot(current->weights, current->input, currentOutput);

		DMatrix2Add(currentOutput, current->biases, currentOutput);

		DMatrix2ForEachLambda(
			currentOutput,
			(current->activationFunction != NULL ? current->activationFunction : NULL));

		next->input = currentOutput;
	}

	DMatrix2Copy(currentOutput, output);

	return 0;
}

int NeuralNetworkBackward(
	NeuralNetwork *network,
	DMatrix2 *outputGradient,
	double learningRate)
{
	
	DMatrix2 *currentOutputGradient = DMatrix2Construct(
		outputGradient->columns, outputGradient->rows);
	DMatrix2Copy(outputGradient, currentOutputGradient);

	for (int l = network->layersCount-1; l >= 0; l--)
	{
		NeuralNetworkLayer *current = network->layers[l];
		NeuralNetworkLayer *previous =
			(l == 0 ? NULL : network->layers[l-1]);

		if (previous == NULL)
			break;

		// Activation
		DMatrix2* activationInputGradient = DMatrix2Construct(
			currentOutputGradient->columns, currentOutputGradient->rows);

		DMatrix2ForEachLambda(previous->input, previous->activationPrimeFunction);

		DMatrix2Hadamard(currentOutputGradient, previous->input, activationInputGradient);

		DMatrix2Log(currentOutputGradient);
		
		// Dense
		DMatrix2* transposedInput = DMatrix2Construct(
				previous->input->rows, previous->input->columns);
		DMatrix2Transpose(previous->input, transposedInput);

		DMatrix2* weightsGradient = DMatrix2Construct(
			activationInputGradient->columns, transposedInput->rows);

		DMatrix2Dot(activationInputGradient, transposedInput, weightsGradient);

		DMatrix2Destruct(transposedInput);

		// TODO: Add multiply by as a matrix func
		for (int c = 0; c < previous->weights->columns; c++)
			for (int r = 0; r < previous->weights->rows; r++)
				previous->weights->data[c][r] -=
					learningRate*weightsGradient->data[c][r];

		for (int c = 0; c < previous->biases->columns; c++)
			previous->biases->data[c][0] -=
				learningRate*activationInputGradient->data[c][0];

		DMatrix2Destruct(currentOutputGradient);


		DMatrix2* transposedWeights = DMatrix2Construct(
				previous->weights->rows, previous->weights->columns);
		DMatrix2Transpose(previous->weights, transposedWeights);
		currentOutputGradient = DMatrix2Construct(
				transposedWeights->columns, activationInputGradient->rows);
		DMatrix2Dot(transposedWeights, activationInputGradient, currentOutputGradient);
		DMatrix2Destruct(transposedWeights);
	}
	DMatrix2Destruct(currentOutputGradient);

	return 0;
}
