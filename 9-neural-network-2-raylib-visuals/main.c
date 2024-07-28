#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dmatrix2.h"
#include "raylib.h"

#define BACKGROUND_COLOR (Color){32,25,40,255}
#define TEXT_COLOR (Color){200,160,250,120} 

#define NEURON_COLOR (Color){200,220,230,255}
#define WEIGHT_COLOR (Color){130,120,150,255}
//#define NOBALLS_COLOR (Color){230,80,110,255}

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	const int gapLeft = 125, gapRight = 125;
	const int gapTop = 100, gapBottom = 100;
	const int canvasWidth = screenWidth-gapLeft-gapRight;
	const int canvasHeight = screenHeight-gapTop-gapBottom;	

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "NN (Nizhniy Novgorod)");
	
	SetTargetFPS(120);

	// const int layerSizes[] = { 3, 5, 6, 5, 4 };
	// const int layerCount = sizeof(layerSizes)/sizeof(int);
	// int gapNeurons = canvasHeight/(6-1); // Where 5 is max entry
	
	// const int layerSizes[] = { 1, 3, 3, 2 };
        // const int layerCount = sizeof(layerSizes)/sizeof(int);
        // int gapNeurons = canvasHeight/(5-1); // Where 5 is max entry
	
	const int layerSizes[] = { 10, 20, 20, 20, 20, 20, 20, 10, 5 };
        const int layerCount = sizeof(layerSizes)/sizeof(int);
        int gapNeurons = canvasHeight/(20-1); // Where 5 is max entry

	while (!WindowShouldClose()) {
		
		BeginDrawing();
			
			ClearBackground(BACKGROUND_COLOR);
			
			for (int l = 0; l < layerCount; l++)
			{
				for (int n = 0; n < layerSizes[l]; n++)
				{
					int currentNeuronX = (float)gapLeft+(float)canvasWidth/(layerCount-1)*l;
					int currentNeuronY = screenHeight/2-gapNeurons*(layerSizes[l]-1)/2+gapNeurons*n;

					if (l != layerCount-1)
					{
						for (int nn = 0; nn < layerSizes[l+1]; nn++)
						{
							int nextNeuronX = (float)gapLeft+(float)canvasWidth/(layerCount-1)*(l+1);
							int nextNeuronY = screenHeight/2-gapNeurons*(layerSizes[l+1]-1)/2+gapNeurons*nn;
							DrawLineEx(
								(Vector2){currentNeuronX, currentNeuronY},
								(Vector2){nextNeuronX, nextNeuronY},
								3,
								WEIGHT_COLOR
							);
						}
					}
				}

				for (int n = 0; n < layerSizes[l]; n++)
				{
					int currentNeuronX = (float)gapLeft+(float)canvasWidth/(layerCount-1)*l;
					int currentNeuronY = screenHeight/2-gapNeurons*(layerSizes[l]-1)/2+gapNeurons*n;
					
					DrawCircle(
						currentNeuronX,
						currentNeuronY,
						10,
						NEURON_COLOR
					);
				}	
			}

			DrawRectangleLines(
				gapLeft, 
				gapTop, 
				canvasWidth, 
				canvasHeight,
				TEXT_COLOR
			);

		EndDrawing(); 
	}

	CloseWindow();

	return 0;
}

/*
// Activation functions
double ActivationSigmoid(char prime_flag)
{
	if (!prime_flag)
		return 1/(1+np.exp(-x))
	return s*(1-s);
}

// Layer implementation
typedef struct DenseLayer 
{
	DMatrix2 weights;
	DMatrix2 biases;
} Layer;
*/
