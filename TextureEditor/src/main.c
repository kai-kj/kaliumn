#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../kaliumn.h"

int **screen;
int **texture;
int height = 0;
int width = 0;
int screenWidth, screenHeight;
char fileName[100] = "NULL";
int cursor_x = 0;
int cursor_y = 0;
float currentTime = 0;
float inputTime = 0;
float blinkTime = 0;
float inputTimeU = 0;
float inputTimeD = 0;
float inputTimeR = 0;
float inputTimeL = 0;
int inputU = 0;
int inputD = 0;
int inputR = 0;
int inputL = 0;
int color = 0;

#define INPUTSPEED 0.5
#define SLIDESPEED 0.1
#define BLINKSPEED 0.5

int newFile()
{
	int i, j;
	height = 0;
	width = 0;

	system("cls");

	SetColor(0, 71);

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	while(height == 0 || width == 0)
	{
		SetColor(0, 71);
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

	SetColor(0, 71);

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	while(clear == 0)
	{
		SetColor(0, 71);
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

int saveFile()
{
	FILE *fp = fopen(fileName, "w");

	fprintf(fp, "%d, %d\n", width, height);

	/*for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			fprintf(fp, "%02d ", texture[i][j]);
		}

		fprintf(fp, "\n");

	}*/

	fclose(fp);
}

int control()
{

	POINT cursorPos;
	HWND hwnd = FindWindow(NULL, "SpriteEditor");

	//mouse

	/*if(GetCursorPos(&cursorPos) != 0)
	{
		ScreenToClient(hwnd, &cursorPos);
		if(cursorPos.x < width && cursorPos.x > 0)
		{
			cursor_x = cursorPos.x;
		}
		if(cursorPos.y < height && cursorPos.y > 0)
		{
			cursor_y = cursorPos.y;
		}

	}*/

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

	if((GetKeyState(VK_DOWN) & 0x8000) && cursor_y < height - 1 && currentTime - inputTimeU > INPUTSPEED)
	{
		cursor_y++;
	}
	else if((GetKeyState(VK_DOWN) & 0x8000) && cursor_y < height - 1)
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

		saveFile();

	}

	if((GetKeyState(0x4E) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
	{

		newFile();

	}

	if((GetKeyState(0x4F) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
	{

		openFile();

	}
}

int main(void)
{

	int i, j;

	screenWidth = 30;
	screenHeight = 20;

	Startup(screenWidth, screenHeight, "SpriteEditor");

	system("COLOR F0");

	while(1)
	{

		currentTime = timeFromStart();

		control();

		//draw

		SetCursorPosition(0, 0);

		/*if(color == 99)
		{
			for(i = 0; i < screenWidth; ++i)
			{
				SetColor(11, 71);
				printf("*");
			}

		}
		else
		{
			SetColor(0, color);
			for(i = 0; i < screenWidth; ++i)
			{
				printf(" ");
			}
		}*/

		SetColor(71, 00);

		printf("%d, %d", cursor_x, cursor_y);

		printf("\n");

		for(i = 0; i < width + 1; ++i)
		{
			SetColor(0, 71);
			printf("##");
		}

		printf("\n");

		for(i = 0; i < height; ++i)
		{

			SetColor(0, 71);
			printf("#");

			for(j = 0; j < width; ++j)
			{
				if(i == cursor_y && j == cursor_x)
				{
					if(currentTime - blinkTime > 0.1)
					{
						if(texture[i][j] / 10 % 10 == 0)
						{
							SetColor(71, 71);
							printf("  ");

						}
						else
						{
							SetColor(0, 0);
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
							SetColor(11, 71);
							printf("* ");
						}
						else
						{
						SetColor(0, texture[i][j]);
						printf("  ");
						}
					}

				}
				else
				{
					if(texture[i][j] == 99)
					{
						SetColor(11, 71);
						printf("* ");
					}
					else
					{
					SetColor(0, texture[i][j]);
					printf("  ");
					//printf("%02d", i);
					}

				}

			}

			SetColor(0, 71);
			printf("#\n");

		}

		for(i = 0; i < width + 1; ++i)
		{
			SetColor(0, 71);
			printf("##");
		}

		printf("\n");

		SetColor(0, 10);
		printf(" 1 ");
		SetColor(0, 20);
		printf(" 2 ");
		SetColor(0, 30);
		printf(" 3 ");
		SetColor(0, 40);
		printf(" 4 ");
		SetColor(0, 50);
		printf(" 5 ");
		SetColor(0, 60);
		printf(" 6 ");
		SetColor(0, 70);
		printf(" 7 ");
		SetColor(1, 71);
		printf(" 9 ");
		SetColor(7, 0);
		printf(" 0 \n");

		SetColor(0, 11);
		printf("   ");
		SetColor(0, 21);
		printf("   ");
		SetColor(0, 31);
		printf("   ");
		SetColor(0, 41);
		printf("   ");
		SetColor(0, 51);
		printf("   ");
		SetColor(0, 61);
		printf("   ");
		SetColor(0, 71);
		printf("   ");
		SetColor(1, 71);
		printf(" * ");
		SetColor(0, 01);
		printf("   ");

	}

}
