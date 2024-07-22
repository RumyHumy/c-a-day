#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 60
#define HEIGHT 30
#define PART_COUNT 300

void add_value(float buffer[HEIGHT][WIDTH], int x, int y, float v) {

	x = (x<0 ? 0 : x);
	x = (x>=WIDTH ? WIDTH-1 : x);
	y = (y<0 ? 0 : y);
	y = (y>=HEIGHT ? HEIGHT-1 : y);
	v = (v<0 ? 0 : v);
	
	buffer[y][x] = v;
}

int main() {
	
	float particles[PART_COUNT*3]; // x y value
	
	for (int i = 0; i < PART_COUNT*3; i++)
		particles[i] = 0.0;

	while (1) {
		
		float buffer[HEIGHT][WIDTH];

		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				buffer[y][x] = 0.0;
			}
		}
		
		for (int i = 0; i < PART_COUNT; i++) {
			
			if (particles[i*3+0] <= 0.0 || particles[i*3+0] >= 1.0
			|| particles[i*3+1] <= 0.0
			|| particles[i*3+2] <= 0.0) {
				particles[i*3+0] = 0.5-(float)(rand()%100-50)/50.0*0.1;
				particles[i*3+1] = 1.0-(float)(rand()&50)/50.0*0.2;
				particles[i*3+2] = 1.0-(float)(rand()&50)/50.0*0.5;
			}

			int x, y;
			y = (int)((float)HEIGHT*particles[i*3+1]);
			x = (int)((float)WIDTH*particles[i*3+0]);

			//buffer[y][x] += particles[i*3+2];
			add_value(buffer, x, y, particles[i*3+2]);
			add_value(buffer, x, y-1, particles[i*3+2]-0.1);
			add_value(buffer, x-1, y, particles[i*3+2]-0.1);
			add_value(buffer, x-1, y-1, particles[i*3+2]-0.2);

	"ramic5003"		particles[i*3+0] += (float)(rand()%100-50)/50.0*0.02;
			particles[i*3+1] -= (float)(rand()%50)/50.0*0.08;
			particles[i*3+2] -= (float)(rand()%50)/50.0*0.12;
		}

		printf("\n\e[1;1H\e[2J");
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				char i = (char)(buffer[y][x]*7);
				i = (i<0 ? 0 : i);
				i = (i>=7 ? 7-1 : i);
				putchar(" .-+=#@"[i]);
			}
			putchar('\n');
		}
		printf("\n");
		usleep(100000);
	}

	return 0;
}
