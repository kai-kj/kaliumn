/*
cmd.h
Please link the winmm.dll library(for mingw add "-lwinmm").

Demos are included in the "demos" folder

See "colors.png" for colors

Use the Texture Editor included in the "TextureEditor" folder to make sprites
*/

//includes
#include "kaliumn.h"

//global variables
int *KAL_canvas;
int *KAL_previousCanvas;
char *KAL_text;
char *KAL_previousText;
int *KAL_textColor;
int *KAL_previousTextColor;
int KAL_soundID;
float KAL_lastDraw = 0;
float KAL_fps;

//returnes time
float KAL_GetTime()
{
	clock_t time = clock();
	return (double)time / CLOCKS_PER_SEC;
}

/*
KAL_SetColor(int foreground, int backgrounds)
 Sets console text Color using SetConsoleTextAttribute(windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute

 int foreground
  see Colors.png
  default: 71;

 int background
  see Colors.png
  default: 00

*/
void KAL_SetColor(const int FOREGROUND, const int BACKGROUND)
{
	int f = FOREGROUND / 10 % 10;
	int fi = FOREGROUND % 10;
	int b = BACKGROUND / 10 % 10;
	int bi = BACKGROUND % 10;
	//Check inputs
	if(f < 0 || f > 7)
	{
		f = 7;
	}
	if(b < 0 || b > 7)
	{
		b = 0;
	}
	if(fi < 0 || fi > 1)
	{
		fi = 0;
	}
	if(bi < 0 || bi > 1)
	{
		bi = 0;
	}
	//Set Colors
	int Color = 16 * b + 128 * bi + f + 8 * fi;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

/*
KAL_SetCursorVisibility(int visibility)
 Changes console cursor visibility using SetConsoleCursorInfo (windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsolecursorinfo

 int visibility
  0: invisible
  1: visible
  default: visible
*/
void KAL_SetCursorVisibility(const int VISIBILITY)
{
	CONSOLE_CURSOR_INFO cursor;
	//dwSize: "The percentage of the character cell that is filled by the cursor. This value is between 1 and 100."
	//more info: https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	cursor.dwSize = 100;
	if(VISIBILITY == 0)
	{
		cursor.bVisible = FALSE;
	}
	else
	{
		cursor.bVisible = TRUE;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

/*
KAL_SetCursorPosition(int x, int y)
 Changes cursor position using SetConsoleKAL_SetCursorPosition (windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsoleKAL_SetCursorPosition

 int x
  x coord (>= 0)
  default: 0

 int y
  y coord (>= 0)
  default: 0
*/
void KAL_SetCursorPosition(int x, int y)
{
	//Check input
	if(x < 0)
	{
		x = 0;
	}
	if(y < 0)
	{
		y = 0;
	}
	COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/*
KAL_GetMousePositionX()
 Returns x mouse position
*/
int KAL_GetMousePositionX()
{
	POINT p;
	HWND hWnd = GetForegroundWindow();
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	return(p.x / 8);
}

/*
KAL_GetMousePositionY()
 Returns y mouse position
*/
int KAL_GetMousePositionY()
{
	POINT p;
	HWND hWnd = GetForegroundWindow();
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	return(p.y / 16);
}

/*
KAL_Startup(int width, int height, char title)
 Changes the screen size, hides the cursor, sets the console encoding to utf-8 and sets the console title

 int width
  window width (characters) (>= 0)
  default: 0

 int height
  window height (characters) (>= 0)
  default: 0

 char title
  console title
*/
void KAL_Startup(int width, int height, const char TITLE[])
{
	char KAL_ScreenSize[100];
	//Check input
	if(height < 0)
	{
		height = 0;
	}
	if(width < 0)
	{
		width = 0;
	}
	sprintf(KAL_ScreenSize, "MODE %d, %d", width, height);
	//Clear screen
	system("cls");
	//Hide cursor
	printf("\e[?25l");
	//Set window size
	system(KAL_ScreenSize);
	//Use UTF-8
	system("chcp 65001");
	//Set console title
	SetConsoleTitle(TITLE);
	//Disable quick edit
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
	//Clear screen
	system("cls");
}

/*
KAL_ScreenSize(int width, int height)
 Changes the screen size

 int width
  window width (characters) (>= 0)
  default: 0

 int height
  window height (characters) (>= 0)
  default: 0
*/
void KAL_ScreenSize(int width, int height)
{
	char screenSize[100];
	//Check input
	if(height < 0)
	{
		height = 0;
	}
	if(width < 0)
	{
		width = 0;
	}
	sprintf(screenSize, "MODE %d, %d", width, height);
	system(screenSize);
}

/*
KAL_ScreenTitle(char title[100])
 Changes the screen title

 char title
  console title
*/
void KAL_ScreenTitle(const char TITLE[])
{
	SetConsoleTitle(TITLE);
}

/*
KAL_LoadAudio(char path[100])
 Loads mp3 file to int and prepares the sound to be used by other functions

 char path[100]
  path to audio file(mp3)
*/
int KAL_LoadAudio(const char TITLE[])
{
	char open[100];
	sprintf(open, "open %s type MPEGVideo alias %d", TITLE, KAL_soundID);
	mciSendString(open, NULL, 0, 0);
	KAL_soundID++;
	return(KAL_soundID - 1);
}

/*
KAL_PlayAudio(char path[100], int repeat)
 Uses mciSendString() to play sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 int input
  sound name(assign sound with KAL_LoadAudio())

 int repeat
  0: false
  1: true
  default: 0
*/
void KAL_PlayAudio(const int INPUT, const int REPEAT)
{
	char close[100];
	char play[100];
	if (REPEAT == 1)
	{
		sprintf(close, "close %d", INPUT);
		sprintf(play, "play %d repeat", INPUT);
	}
	else
	{
		sprintf(close, "close %d", INPUT);
		sprintf(play, "play %d", INPUT);
	}
	//Start
	mciSendString(play, NULL, 0, 0);
}

/*
KAL_PauseAudio(char path[100])
 Uses mciSendString() to pause sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 int input
  sound name(assign sound with KAL_LoadAudio())
*/
void KAL_PauseAudio(const int INPUT)
{
	char pause[100];
	sprintf(pause, "pause %d", INPUT);
	mciSendString(pause, NULL, 0, 0);
}

/*
KAL_ResumeAudio(char path[100])
 Uses mciSendString() to resume paused sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 int input
  sound name(assign sound with KAL_LoadAudio())
*/
void KAL_ResumeAudio(const int INPUT)
{
	char resume[100];
	sprintf(resume, "resume %d", INPUT);
	mciSendString(resume, NULL, 0, 0);
}

/*
KAL_StopAudio(char path[100])
 Uses mciSendString() to stop sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 int input
  sound name(assign sound with KAL_LoadAudio())
*/
void KAL_StopAudio(const int INPUT)
{
	char stop[100];
	sprintf(stop, "stop %d", INPUT);
	mciSendString(stop, NULL, 0, 0);
}

/*
*KAL_LoadTexture(char path[100])
 Loads texture to *int to be drawn by Draw()
 Textures can be drawn using the TextureEditor Tool
 Texture format (* = space)

  height,*width
  [pixel 0, 0]*[pixel 1, 0]*[pixel 2, 0]*
  [pixel 0, 1]*[pixel 1, 1]*[pixel 2, 1]*  . . .
  [pixel 0, 2]*[pixel 1, 2]*[pixel 2, 2]*
                   .
                   .
                   .

  height: height of texture
  width: width of texture
  [pixel x, y]: color code of pixel(same code as KAL_SetColor())
   first digit: color
   second digit: intensity
  (99: transparent)

 char path
  path to file
*/
int *KAL_LoadTexture(const char PATH[])
{
	int i, j;
	int x, y;
	FILE *fp = fopen(PATH,"r");
	fscanf(fp, "%d, %d", &x, &y);
	//Variable length array
	int *texture = (int *)malloc((x * y + 2) * sizeof(int));
	//The first element stores the width of the texture and the second element stores the height of the texture
	texture[0] = x;
	texture[1] = y;
	//Load texture
	for(i = 0; i < y; ++i)
	{
		for(j = 0; j < x; ++j)
		{
			fscanf(fp, "%d", &texture[(i * x) + j + 2]);
			if(j < x)
			{
				fseek(fp, 1, SEEK_CUR);
			}
		}
	}
	fclose(fp);
	return texture;
}

/*
KAL_DestroyTexture(int texture)
 Frees memory used by texture

 int texture
  texture name
*/
void KAL_DestroyTexture(int *texture)
{
	free(texture);
}

/*
KAL_InitCanvas(int width, int height, int color)
 Initializes canvas to be displayed to the console

 int width
  width of canvas

 int height
  height of canvas

 int color
  background color for canvas
*/
void KAL_InitCanvas(const int WIDTH, const int HEIGHT, const int COLOR)
{
	int i, j;
	//Variable length array
	KAL_canvas = (int *)malloc((WIDTH * HEIGHT + 2) * sizeof(int));
	KAL_previousCanvas = (int *)malloc((WIDTH * HEIGHT) * sizeof(int));
	KAL_text = (char *)malloc((WIDTH * HEIGHT + 1) * sizeof(char));
	KAL_previousText = (char *)malloc((WIDTH * HEIGHT + 1) * sizeof(char));
	KAL_textColor = (int *)malloc((WIDTH * HEIGHT) * sizeof(int));
	KAL_previousTextColor = (int *)malloc((WIDTH * HEIGHT) * sizeof(int));
	//The first element stores the width and the second the height
	KAL_canvas[0] = WIDTH;
	KAL_canvas[1] = HEIGHT;
	//Initialize with background color
	for(i = 0; i < HEIGHT; ++i)
	{
		for(j = 0; j < WIDTH; ++j)
		{
			KAL_canvas[(i * WIDTH) + j + 2] = COLOR;
			KAL_previousCanvas[(i * WIDTH) + j] = 99;
			KAL_text[(i * WIDTH) + j] = '\0';
			KAL_previousText[(i * WIDTH) + j] = '\0';
			KAL_textColor[(i * WIDTH) + j] = 00;
			KAL_previousTextColor[(i * WIDTH) + j] = 00;
		}
	}
	KAL_text[WIDTH * HEIGHT + 1] = '\0';
	KAL_previousText[WIDTH * HEIGHT + 1] = '\0';
}

/*
KAL_KAL_CleanCanvas(int color)
 Cleans canvas

 int color
  background color for canvas
*/
void KAL_CleanCanvas(const const int COLOR)
{
	int i, j;
	//Get width and height
	int width = KAL_canvas[0];
	int height = KAL_canvas[1];
	//Clean with background color
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			KAL_canvas[(i * width) + j + 2] = COLOR;
			KAL_text[(i * width) + j] = '\0';
		}
	}
}

/*
KAL_DrawTexture(int *texture, int xPos, int yPos)
 Draws texture to canvas (use between ClearCanvas() and KAL_Display())

 int *texture
  texture to be drawn to canvas

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void KAL_DrawTexture(const int *TEXTURE, const int XPOS, const int YPOS)
{
	int i, j;
	//Get width and height of texture
	int x = TEXTURE[0];
	int y = TEXTURE[1];
	//Get width of canvas
	int width = KAL_canvas[0];
	//Draw
	for(i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(TEXTURE[(i * x) + j + 2] != 99)
			{
				KAL_canvas[(i + YPOS) * width + j + XPOS + 2] = TEXTURE[(i * x) + j + 2];
			}
		}
	}
}

/*
KAL_DrawPixel(int color, int xPos, int yPos)
 Draws pixel to canvas (use between ClearCanvas() and KAL_Display())

 int color
  color of pixel

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void KAL_DrawPixel(const int COLOR, const int XPOS, const int YPOS)
{
	//Get width of canvas
	int width = KAL_canvas[0];
	//Draw
	KAL_canvas[YPOS * width + XPOS + 2] = COLOR;
}

/*
KAL_DrawChar(char input[], int color, int xPos, int yPos)
 Draws text to canvas (use between ClearCanvas() and KAL_Display())

 char input[]
  text to be drawn to canvas

 int color
  color of text

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void KAL_DrawChar(const char INPUT[], const int COLOR, const int XPOS, const int YPOS)
{
	int i = 0;
	//Get width of canvas
	int width = KAL_canvas[0];
	//Draw
	while(INPUT[i] != '\0')
	{
		KAL_text[YPOS * width + i + XPOS] = INPUT[i];
		KAL_textColor[YPOS * width + i + XPOS] = COLOR;
		i++;
	}
}

/*
KAL_Display()
 KAL_Displays canvas to console
*/
void KAL_Display()
{
	int i, j;
	//Log fps
	float currentTime = KAL_GetTime();
	KAL_fps = 1 / (currentTime - KAL_lastDraw);
	KAL_lastDraw = KAL_GetTime();
	//Get width and height
	int x = KAL_canvas[0];
	int y = KAL_canvas[1];
	//Moves cursor to top left of the console to draw over previous frame (Using system("cls") makes the screen flicker)
	KAL_SetCursorPosition(0, 0);
	//Draw
	for(i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(KAL_text[(i * x) + j] != '\0')
			{
				KAL_SetCursorPosition(j * 2, i);
				KAL_SetColor(KAL_textColor[(i * x) + j], KAL_canvas[(i * x) + j + 2]);
				printf("%c ", KAL_text[(i * x) + j]);
			}
			else
			{
				if(KAL_canvas[(i * x) + j + 2] != KAL_previousCanvas[(i * x) + j] || KAL_text[(i * x) + j + 2] != KAL_previousText[(i * x) + j] || KAL_textColor[(i * x) + j + 2] != KAL_previousTextColor[(i * x) + j])
				{
					KAL_SetCursorPosition(j * 2, i);
					KAL_SetColor(0, KAL_canvas[(i * x) + j + 2]);
					printf("  ");
				}
			}
			KAL_previousCanvas[(i * x) + j] = KAL_canvas[(i * x) + j + 2];
			KAL_previousText[(i * x) + j] = KAL_text[(i * x) + j];
			KAL_previousTextColor[(i * x) + j] = KAL_textColor[(i * x) + j];
		}
		if(i < y - 1)
		{
			printf("\n");
		}
	}
}

/*
KAL_GetFPS()
 Returns fps
*/
float KAL_GetFPS()
{
	return KAL_fps;
}
