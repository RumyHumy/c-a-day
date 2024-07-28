#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dmatrix2.h"
#include "ramenn.h"

int main()
{		
	int layersSizes[] = { 2, 4, 66, 4, 3 };
	const int nnSize = sizeof(layersSizes)/sizeof(int);

	NeuralNetwork *nn = NeuralNetworkConstruct(nnSize, layersSizes);

	for (int i = 0; i < nnSize; i++)
	{
		if (i == 0 || i == nnSize-1)
			printf(i == 0 ? "Input Layer\n" : "Output Layer\n");
		else
			printf("Hidden Layer %d\n", i);

		printf("- Size: %d\n", nn->layers[i]->size);
	}

	NeuralNetworkDestruct(nn);

	return 0;
}
