
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cmd.h"

int WIDTH = 50;
int HEIGHT = 30;

int main(void)
{

	int x, y;
	int i, j;
	int xMode = 0;
	int yMode = 0;

	int *player;

	Startup(WIDTH * 2, HEIGHT, "test");
	Init(WIDTH, HEIGHT);

	x = 0;
	y = 0;

	while(1)
	{

		system("COLOR 0F");

		ConsoleColor(7, 0, 1, 0);

		player = LoadTexture("texture");

		Draw(player, x, y);

		Display();

		if(x == 0)
		{
			xMode = 0;
		}
		if(x + player[0] == WIDTH)
		{
			xMode = 1;
		}
		if(y == 0)
		{
			yMode = 0;
		}
		if(y + player[1] == HEIGHT)
		{
			yMode = 1;
		}

		
		if(xMode == 0)
		{
			x++;
		}
		else
		{
			x--;
		}

		if(yMode == 0)
		{
			y++;
		}
		else
		{
			y--;
		}

		Sleep(100);

	}

}