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
	double sum = 0.0;
	for (int c = 0; c < expected->rows; c++)
	{
		double value = expected->data[c][0] - actual->data[c][0];
		sum += value*value;
	}
	return sum / (double)expected->rows;
}

void MeanSquaredErrorPrime(DMatrix2 *expected, DMatrix2 *actual, DMatrix2 *result)
{
	DMATRIX2_FOREACH_ROW(result, r)
		result->data[r][0] =
			2.0 * (actual->data[r][0] - expected->data[r][0]) / expected->rows;
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
	NeuralNetworkActivation activation)
{
	if (size <= 0)
		return NULL;
	
	DMatrix2 *weights = NULL;
	DMatrix2 *biases = NULL;

	// TODO: Rewrite this shibe
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
		.weights         = weights,
		.biases          = biases,
		.input           = NULL,
		.activationInput = NULL,
		.size            = size,
		.activation      = activation,
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
	DMatrix2Destruct(layer->activationInput);	

	free(layer);
}

// - Network -

NeuralNetwork* NeuralNetworkConstruct(
		int layersCount,
		int *layersSizes,
		NeuralNetworkActivation activations[])
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
		layers[l] = NeuralNetworkLayerConstruct(
			layersSizes[l],
			(l != layersCount-1 ? layersSizes[l+1] : 0),
			(l != layersCount-1 ? activations[l] : ACTIVATION_NONE));

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

void NeuralNetworkLayerForward(NeuralNetworkLayer *layer, DMatrix2 *input, DMatrix2 *output)
{
	// Dense
	DMatrix2Destruct(layer->input);
	layer->input = DMatrix2ConstructCopy(input);

	DMatrix2Dot(layer->weights, input, output);
	DMatrix2Add(output, layer->biases, output);

	DMatrix2Destruct(layer->activationInput);
	layer->activationInput = DMatrix2ConstructCopy(output);

	// Activation
	DMatrix2Lambda(output, layer->activation.function);
}

void NeuralNetworkLayerBackward(
	NeuralNetworkLayer *layer,
	DMatrix2 *outputGradient,
	double learningRate)
{
	// Activation
	DMatrix2Lambda(layer->activationInput, layer->activation.functionPrime);
	DMatrix2Multiply(outputGradient, layer->activationInput, outputGradient);

	// Dense
	DMatrix2 *inputTransposed = DMatrix2Construct(layer->input->columns, layer->input->rows);
	DMatrix2Transpose(layer->input, inputTransposed);
	DMatrix2 *buffer = DMatrix2Construct(outputGradient->rows, inputTransposed->columns);
	DMatrix2Dot(outputGradient, inputTransposed, buffer);
	// TODO: Make more operators? or make without + speed
	DMATRIX2_FOREACH(layer->weights, r, c)
		layer->weights->data[r][c] -= learningRate*buffer->data[r][c];
	DMATRIX2_FOREACH(layer->weights, r, c)
		layer->biases->data[r][c] -= learningRate*outputGradient->data[r][c];
	DMatrix2Destruct(buffer);

	buffer = DMatrix2Construct(layer->input->rows, layer->input->columns);
	DMatrix2 *weightsTransposed = DMatrix2Construct(
			layer->weights->columns, layer->weights->rows);
	DMatrix2Transpose(layer->weights, weightsTransposed);
	DMatrix2Dot(weightsTransposed, outputGradient, buffer);

	outputGradient = DMatrix2ConstructCopy(buffer);
	DMatrix2Destruct(buffer);
}
