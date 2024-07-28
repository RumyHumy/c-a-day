#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 600
#define PARTICLE_COUNT 500
#define REP_DIST 0.05f
#define MIN_DIST 0.01f

float frand() {
	return (float)rand()/RAND_MAX;
}

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										   640, 640, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	// Particles [x, y, vx, vy, charge]
	float particles[PARTICLE_COUNT*5] = { 0.0f };

	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i*5+0] = frand();
		particles[i*5+1] = frand();
		particles[i*5+2] = (frand()-0.5f)*0.03f;
		particles[i*5+3] = (frand()-0.5f)*0.03f;
		particles[i*5+4] = frand();
	} 


	// Delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltatime = 0; 

	// Main loop
	char quit_flag = 0;
	SDL_Event event;
	while (!quit_flag) {
	
		deltatime = (float)((NOW-LAST) / (float)SDL_GetPerformanceFrequency() / 1000000.0f );

		// Handle events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit_flag = 1;
					break;
			}
		}

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);	

		// Calculate the new positions
		for (int i = 0; i < PARTICLE_COUNT; i++) {
				
			float *x = particles+i*5+0;
			float *y = particles+i*5+1;
			float *vx = particles+i*5+2;
			float *vy = particles+i*5+3;
			float *q = particles+i*5+4;	
			
			for (int j = 0; j < PARTICLE_COUNT; j++) {
				
				if (i == j)
					continue;

				float *ox = particles+j*5+0;
				float *oy = particles+j*5+1;
				float *oq = particles+j*5+4;	
				
				float dx = *x-*ox;
				float dy = *y-*oy;
				
				float dist = sqrtf(dx*dx+dy*dy); 

				//dist = (dist < MIN_DIST ? MIN_DIST : dist);
				
				if (dist < MIN_DIST)
					continue;

				*vx += -(*q)*(*oq) / (dist*dist) * deltatime * (dx/dist) * 0.00001f; 
				*vy += -(*q)*(*oq) / (dist*dist) * deltatime * (dy/dist) * 0.00001f;
			}

			//quit_flag = 1;
		}
		
		printf("%f\n", deltatime);

		for (int i = 0; i < PARTICLE_COUNT; i++) {
			float *x = particles+i*5+0;
			float *y = particles+i*5+1;
			float *vx = particles+i*5+2;
			float *vy = particles+i*5+3;
			float *q = particles+i*5+4;
			
			// Add velocity
			*x += *vx*deltatime;
			*y += *vy*deltatime;

			// Prevent out of bounds
			//*x = (*x < 0.0f ? 0.0f : (*x > 1.0f ? 1.0f : *x));
			//*y = (*y < 0.0f ? 0.0f : (*y > 1.0f ? 1.0f : *y));
			
			// Draw particles
			int psize = 5+(int)((float)(*q<0 ? -*q : +*q)*20);
			SDL_SetRenderDrawColor(renderer, (*q > 0 ? 255 : 0), 64, (*q > 0 ? 0 : 255), 255);
			SDL_Rect rect = { (int)(*x*WIDTH)-psize/2, (int)(*y*HEIGHT)-psize/2, psize, psize };
			SDL_RenderFillRect(renderer, &rect);

		}

		// Present the rendered frame
		SDL_RenderPresent(renderer);
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
