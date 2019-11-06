
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "cmd.h"

int **canvas;

int WIDTH = 10;
int HEIGHT = 10;

int main(void)
{

	int x, y;
	int i, j;

	int *player;

	Startup(50 * 2, 50, "test");

	ConsoleColour(7, 0, 1, 0);

	player = LoadTexture("player");

	printf("%d, %d\n\n", player[0], player[1]);

	Draw(player);

	getchar();

}