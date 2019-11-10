#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../cmd.h"

int **canvas;
int **texture;
int height = 0;
int width = 0;
int screenWidth, screenHeight;
char fileName[100] = "NULL";

#define INPUTSPEED 0.5
#define SLIDESPEED 0.1
#define BLINKSPEED 0.5

float timeFromStart()
{
	clock_t time = clock();

	return (double)time / CLOCKS_PER_SEC;

}

int newFile()
{
	int i, j;
	height = 0;
	width = 0;

	system("cls");

	ConsoleColor(0, 7, 0, 1);

	printf("Press ENTER To Continue...");

	getchar();

	while(height == 0 || width == 0)
	{
		ConsoleColor(0, 7, 0, 1);
		system("cls");
		printf("Enter Texture Width: ");
		scanf("%d", &width);
		printf("Enter Texture Height: ");
		scanf("%d", &height);
		printf("Enter File Name: ");
		scanf("%s", &fileName);

		if(width < 15)
		{
			screenWidth = 30;
		}
		else
		{
			screenWidth = (width + 1) * 2;
		}
		screenHeight = height;

		system("cls");
		Startup(screenWidth, screenHeight + 5, fileName);

		texture = (int **)malloc(width * sizeof(int *));

		for(i = 0; i < width; i++)
		{
			 texture[i] = (int *)malloc(height * sizeof(int));
		}

		for(i = 0; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				texture[i][j] = 71;

			}

		}
		
	}

}

int openFile()
{
	int i, j;
	int clear = 0;
	FILE *fp = NULL;

	system("cls");

	ConsoleColor(0, 7, 0, 1);

	printf("Press ENTER To Continue...");

	getchar();

	while(clear == 0)
	{
		ConsoleColor(0, 7, 0, 1);
		system("cls");
		printf("File Name: ");
		scanf("%s", &fileName);

		fp = fopen(fileName, "r");

		if(fp != NULL)
		{
			clear = 1;
		}

	}

	fscanf(fp, "%d, %d", &width, &height);

	if(width < 15)
	{
		screenWidth = 30;
	}
	else
	{
		screenWidth = (width + 1) * 2;
	}
	screenHeight = height;

	system("cls");
	Startup(screenWidth, screenHeight + 5, fileName);

	texture = (int **)malloc(width * sizeof(int *));

	for(i = 0; i < width; i++)
	{
		 texture[i] = (int *)malloc(height * sizeof(int));
	}

	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			fscanf(fp, "%d ", &texture[i][j]);
			/*if(j < width)
			{
				fseek(fp, 1, SEEK_CUR);
			}*/

		}

	}

	fclose(fp);

}

int main(void)
{

	int i, j;

	int brushSize = 0;

	screenWidth = 30;
	screenHeight = 20;

	Startup(screenWidth, screenHeight, "SpriteEditor");

	system("COLOR F0");

	int cursor_x = 0;
	int cursor_y = 0;
	float currentTime = timeFromStart();
	float inputTime = timeFromStart();
	float blinkTime = timeFromStart();
	float inputTimeU = timeFromStart();
	float inputTimeD = timeFromStart();
	float inputTimeR = timeFromStart();
	float inputTimeL = timeFromStart();
	int inputU = 0;
	int inputD = 0;
	int inputR = 0;
	int inputL = 0;
	int color = 0;

	while(1)
	{

		currentTime = timeFromStart();

		//cursor

		if((GetKeyState(VK_RIGHT) & 0x8000) && cursor_x < width - 1 && currentTime - inputTimeR > INPUTSPEED)
		{
			cursor_x++;
		}
		else if((GetKeyState(VK_RIGHT) & 0x8000) && cursor_x < width - 1)
		{
			if(inputR == 0)
			{
				cursor_x++;
				inputR = 1;
			}
		}
		else
		{
			inputTimeR = timeFromStart();
			inputR = 0;
		}

		if((GetKeyState(VK_LEFT) & 0x8000) && cursor_x > 0 && currentTime - inputTimeL > INPUTSPEED)
		{
			cursor_x--;
		}
		else if((GetKeyState(VK_LEFT) & 0x8000) && cursor_x > 0)
		{
			if(inputL == 0)
			{
				cursor_x--;
				inputL = 1;
			}
		}
		else
		{
			inputTimeL = timeFromStart();
			inputL = 0;
		}

		if((GetKeyState(VK_DOWN) & 0x8000) && cursor_y < width - 1 && currentTime - inputTimeU > INPUTSPEED)
		{
			cursor_y++;
		}
		else if((GetKeyState(VK_DOWN) & 0x8000) && cursor_y < width - 1)
		{
			if(inputU == 0)
			{
				cursor_y++;
				inputU = 1;
			}
		}
		else
		{
			inputTimeU = timeFromStart();
			inputU = 0;
		}

		if((GetKeyState(VK_UP) & 0x8000) && cursor_y > 0 && currentTime - inputTimeD > INPUTSPEED)
		{
			cursor_y--;
		}
		else if((GetKeyState(VK_UP) & 0x8000) && cursor_y > 0)
		{
			if(inputD == 0)
			{
				cursor_y--;
				inputD = 1;
			}
		}
		else
		{
			inputTimeD = timeFromStart();
			inputD = 0;
		}

		//draw

		if(GetKeyState(VK_SPACE) & 0x8000)
		{
			texture[cursor_y][cursor_x] = color;
			
		}

		//colors

		if(GetKeyState(0x30) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 01;
			}
			else
			{
			color = 00;
			}
		}
		if(GetKeyState(0x31) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 11;
			}
			else
			{
			color = 10;
			}
		}
		if(GetKeyState(0x32) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 21;
			}
			else
			{
			color = 20;
			}
		}
		if(GetKeyState(0x32) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 21;
			}
			else
			{
			color = 20;
			}
		}
		if(GetKeyState(0x33) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 31;
			}
			else
			{
			color = 30;
			}
		}
		if(GetKeyState(0x34) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 41;
			}
			else
			{
			color = 40;
			}
		}
		if(GetKeyState(0x35) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 51;
			}
			else
			{
			color = 50;
			}
		}
		if(GetKeyState(0x36) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 61;
			}
			else
			{
			color = 60;
			}
		}
		if(GetKeyState(0x37) & 0x8000)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
			color = 71;
			}
			else
			{
			color = 70;
			}
		}
		if(GetKeyState(0x39) & 0x8000)
		{
			color = 99;
		}

		//shortcuts

		if((GetKeyState(0x53) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
		{

			FILE *fp = fopen(fileName, "w");

			fprintf(fp, "%d, %d\n", width, height);

			for(i = 0; i < height; ++i)
			{
				for(j = 0; j < width; ++j)
				{
					fprintf(fp, "%02d ", texture[i][j]);
				}

				if(i < height - 1)
				{
					fprintf(fp, "\n");
				}

			}

			fclose(fp);

		}

		if((GetKeyState(0x4E) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
		{

			newFile();

		}

		if((GetKeyState(0x4F) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
		{

			openFile();

		}

		//draw

		CursorPosition(0, 0);

		if(color == 99)
		{
			for(i = 0; i < screenWidth; ++i)
			{
				ConsoleColor(1, 7, 1, 1);
				printf("*");
			}
			
		}
		else
		{
			ConsoleColor(0, color / 10 % 10, 0, color % 10);
			for(i = 0; i < screenWidth; ++i)
			{
				printf(" ");
			}
		}
		
		printf("\n");

		for(i = 0; i < width + 1; ++i)
		{
			ConsoleColor(0, 7, 0, 1);
			printf("##");
		}

		printf("\n");

		for(i = 0; i < height; ++i)
		{

			ConsoleColor(0, 7, 0, 1);
			printf("#");

			for(j = 0; j < width; ++j)
			{
				if(i == cursor_y && j == cursor_x)
				{
					if(currentTime - blinkTime > 0.1)
					{
						if(texture[i][j] / 10 % 10 == 0)
						{
							ConsoleColor(7, 7, 1, 1);
							printf("  ");

						}
						else
						{
							ConsoleColor(0, 0, 0, 0);
							printf("  ");

						}

						if(currentTime - blinkTime > BLINKSPEED)
						{
							blinkTime = timeFromStart();
						}

					}
					else
					{
						if(texture[i][j] == 99)
						{
							ConsoleColor(1, 7, 1, 1);
							printf("* ");
						}
						else
						{
						ConsoleColor(0, texture[i][j] / 10 % 10, 0, texture[i][j] % 10);
						printf("  ");
						}
					}

				}
				else
				{
					if(texture[i][j] == 99)
					{
						ConsoleColor(1, 7, 1, 1);
						printf("* ");
					}
					else
					{
					ConsoleColor(0, texture[i][j] / 10 % 10, 0, texture[i][j] % 10);
					printf("  ");
					}
					
				}

			}

			ConsoleColor(0, 7, 0, 1);
			printf("#\n");

		}

		for(i = 0; i < width + 1; ++i)
		{
			ConsoleColor(0, 7, 0, 1);
			printf("##");
		}

		printf("\n");

		ConsoleColor(0, 1, 0, 0);
		printf(" 1 ");
		ConsoleColor(0, 2, 0, 0);
		printf(" 2 ");
		ConsoleColor(0, 3, 0, 0);
		printf(" 3 ");
		ConsoleColor(0, 4, 0, 0);
		printf(" 4 ");
		ConsoleColor(0, 5, 0, 0);
		printf(" 5 ");
		ConsoleColor(0, 6, 0, 0);
		printf(" 6 ");
		ConsoleColor(0, 7, 0, 0);
		printf(" 7 ");
		ConsoleColor(1, 7, 1, 1);
		printf(" 9 ");
		ConsoleColor(7, 0, 1, 0);
		printf(" 0 \n");

		ConsoleColor(0, 1, 0, 1);
		printf("   ");
		ConsoleColor(0, 2, 0, 1);
		printf("   ");
		ConsoleColor(0, 3, 0, 1);
		printf("   ");
		ConsoleColor(0, 4, 0, 1);
		printf("   ");
		ConsoleColor(0, 5, 0, 1);
		printf("   ");
		ConsoleColor(0, 6, 0, 1);
		printf("   ");
		ConsoleColor(0, 7, 0, 1);
		printf("   ");
		ConsoleColor(1, 7, 1, 1);
		printf(" * ");
		ConsoleColor(0, 0, 0, 1);
		printf("   ");

	}

}