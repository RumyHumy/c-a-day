#include "dmatrix2.h"
#include "ramenn.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: Check for unsafe code
// TODO: Make transposing fast

NeuralNetworkLayer* NeuralNetworkLayerConstruct(int size, int nextLayerSize)
{
	if (size <= 0)
		return NULL;
	
	DMatrix2 *weights = NULL;
	DMatrix2 *biases = NULL;

	if (nextLayerSize > 0)
	{
		weights = DMatrix2Construct(size, nextLayerSize);
		
		if (weights == NULL)
			return NULL;

		biases = DMatrix2Construct(size, 1);

		if (biases == NULL)
			return NULL;
	}

	NeuralNetworkLayer* layer = calloc(1, sizeof(*layer));

	*layer = (NeuralNetworkLayer){
		.weights=weights,
		.biases=biases,
		.input=NULL,
		.output=NULL,
		.size=size,
		.nextLayerSize=nextLayerSize,
		.activationFunctionPtr=NULL
	};
	
	return layer;
}

void NeuralNetworkLayerDestruct(NeuralNetworkLayer* layer)
{
	if (layer == NULL)
		return;

	DMatrix2Destruct(layer->weights);
	DMatrix2Destruct(layer->biases);
}

NeuralNetwork* NeuralNetworkConstruct(int layersCount, int *layersSizes)
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
		.layers=layers,
		.layersCount=layersCount
	};

	for (int l = 0; l < layersCount; l++)
	{
		layers[l] = NeuralNetworkLayerConstruct(
			layersSizes[l],
			(l != layersCount-1 ? layersSizes[l+1] : 0)
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
