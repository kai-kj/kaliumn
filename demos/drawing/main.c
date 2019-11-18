#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
#define SPEED 0.1
int main(void)
{
	int x, y;
	int WIDTH = 50;
	int HEIGHT = 30;
	int xDirection = 0;
	int yDirection = 0;
	char fpsChar[100];
	int *player = LoadTexture("texture");
	float lastFrame = 0;
	//Initialize Canvas
	Startup((WIDTH) * 2, HEIGHT, "test");
	InitCanvas(WIDTH, HEIGHT, 71);
	x = 0;
	y = 0;
	while(1)
	{
		if(GetTime() - lastFrame > SPEED)
		{
			lastFrame = GetTime();
			//Collision + Movement
			if(x == 0)
			{
				xDirection = 0;
			}
			if(x + player[0] == WIDTH)
			{
				xDirection = 1;
			}
			if(y == 0)
			{
				yDirection = 0;
			}
			if(y + player[1] == HEIGHT)
			{
				yDirection = 1;
			}
			if(xDirection == 0)
			{
				x++;
			}
			else
			{
				x--;
			}

			if(yDirection == 0)
			{
				y++;
			}
			else
			{
				y--;
			}
		}
		//Clean canvas
		CleanCanvas(71);
		//Draw ball and fps
		DrawTexture(player, x, y);
		sprintf(fpsChar, "fps: %f", GetFPS());
		DrawChar(fpsChar, 40, 0, 0);
		//Display canvas to screen
		Display();
	}
}
