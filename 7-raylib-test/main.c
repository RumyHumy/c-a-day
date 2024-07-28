#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define BACKGROUND_COLOR (Color){32,25,40,255}
#define TEXT_COLOR (Color){200,160,250,120} 

#define BALL_COLOR (Color){200,220,230,255}
#define CURSOR_BALL_COLOR (Color){90,100,170,255}
#define NOBALLS_COLOR (Color){230,80,110,255}

typedef struct Ball {
	Vector2 position;
	Vector2 velocity;
	float mass;
} Ball;

int main(void)
{
	// Window configuration
	const int screenWidth = 800;
	const int screenHeight = 600;

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Balls hangin' low");

	SetTargetFPS(120);
	
	// Constants
	const float MIN_FORCE_DIST = 10.0f;
	const int MAX_BALLS_COUNT = 10000;
	const int startBallsCount = 200;
	const int minMass = 1, maxMass = 50, startMass = 10;
	
	// Logic
	int ballsCount = 0;
	Ball balls[MAX_BALLS_COUNT];

	for (int i = 0; i < startBallsCount; i++) {
		ballsCount++;
		balls[ballsCount-1] = (Ball){
			.position = (Vector2){
				(float)rand()/RAND_MAX*screenWidth,
				(float)rand()/RAND_MAX*screenHeight,
			},
			.velocity = (Vector2){
				((float)rand()/RAND_MAX-0.5)*2.0,
				((float)rand()/RAND_MAX-0.5)*2.0
			},
			.mass = ((float)rand()/RAND_MAX)*(maxMass-minMass)*0.1+minMass
		};
	}

	int currentMass = startMass;
	
	while (!WindowShouldClose()) {
		
		float deltaTime = GetFrameTime();
		
		currentMass += (int)GetMouseWheelMove()*2;

		currentMass = (currentMass < minMass ? minMass : currentMass);
		currentMass = (currentMass > maxMass ? maxMass : currentMass);
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (ballsCount < MAX_BALLS_COUNT)
			{
				ballsCount++;
				balls[ballsCount-1] = (Ball){
					.position = GetMousePosition(),
					.velocity = (Vector2){ 0.0, 0.0 },
					.mass = currentMass
				};
			}
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			if (ballsCount > 0)
			{
				ballsCount--;
				balls[ballsCount] = (Ball){
					.position = GetMousePosition(),
					.velocity = (Vector2){ 0.0, 0.0 },
					.mass = currentMass
				};
			}
		}


		for (int i = 0; i < ballsCount; i++)
		{
			float *ix = &(balls+i)->position.x;
			float *iy = &(balls+i)->position.y;
			float *ivx = &(balls+i)->velocity.x;
			float *ivy = &(balls+i)->velocity.y;
			float *im = &(balls+i)->mass;

			for (int j = 0; j < ballsCount; j++)
			{
				if (i == j)
					continue;
					
				float *jx = &(balls+j)->position.x;
				float *jy = &(balls+j)->position.y;
				float *jm = &(balls+j)->mass;
				
				float dx = *ix-*jx;
				float dy = *iy-*jy;
				float dist = sqrt(dx*dx+dy*dy);
				
				if (dist < MIN_FORCE_DIST)
					continue;

				if (dist < *im+*jm) {
					*ivx += (*jm)/(dist*dist)*(dx/dist)*deltaTime*100.0*5.0;
					*ivy += (*jm)/(dist*dist)*(dy/dist)*deltaTime*100.0*5.0;
					continue;
				}

				*ivx += (*jm)/(dist*dist)*(-dx/dist)*deltaTime*300.0;
				*ivy += (*jm)/(dist*dist)*(-dy/dist)*deltaTime*300.0;
			}
		}
		
		for (int i = 0; i < ballsCount; i++)
		{	
			balls[i].position.x += balls[i].velocity.x;
			balls[i].position.y += balls[i].velocity.y;
		}

		BeginDrawing();

			ClearBackground(BACKGROUND_COLOR);
			
			Vector2 ballPosition = GetMousePosition();

			DrawCircleV(ballPosition, 2+currentMass,
				(ballsCount < MAX_BALLS_COUNT ? CURSOR_BALL_COLOR : NOBALLS_COLOR));
			
			for (int i = 0; i < ballsCount; i++)
				DrawCircleV(balls[i].position, 1+balls[i].mass, BALL_COLOR);

			char currentMass_str[32];
			char ballsCount_str[32];

			sprintf(currentMass_str, "%d", currentMass);
			sprintf(ballsCount_str, "%d", ballsCount);

			DrawText("Raylib is sexy", 20, 20, 20, TEXT_COLOR);
			DrawText("Ball mass:", 20, 50, 20, TEXT_COLOR);
			DrawText(currentMass_str, 150, 50, 20, TEXT_COLOR);
			DrawText("Ball count:", 20, 80, 20, TEXT_COLOR);
			DrawText(ballsCount_str, 150, 80, 20, TEXT_COLOR);


		EndDrawing();
	}

	CloseWindow();

	return 0;
}
