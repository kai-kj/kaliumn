/*
cmd.h
v0.21(2019-11-10)
Please link the winmm.dll library(for mingw add "-lwinmm").

Demos are included in the "demos" folder

See "colors.png" for colors

Use the Texture Editor included in the "TextureEditor" folder to make sprites
*/

#include <windows.h>
#include <time.h>

int *canvas;
char *text;
int *textColor;
float lastDraw = 0;
float fps;

float timeFromStart()
{
	clock_t time = clock();
	return (double)time / CLOCKS_PER_SEC;
}

/*
SetColor(int foreground, int background, int foreground_intensity, int background_intensity)
 Sets console text Color using SetConsoleTextAttribute(windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute

 int foreground
  0: Black
  1: Blue
  2: Green
  3: Cyan
  4: Red
  5: Magenta
  6: Yellow
  7: White
  default: White

 int background
  0: Black
  1: Blue
  2: Green
  3: Cyan
  4: Red
  5: Magenta
  6: Yellow
  7: White 
  default: Black

 int foreground_intensity
  0: False
  1: True
  default: False

 int background_intensity
  0: False
  1: True
  default: False
*/
void SetColor(int foreground, int background, int foreground_intensity, int background_intensity)
{
	//Check inputs
	if(foreground < 0 || foreground > 7)
	{
		foreground = 7;
	}
	if(background < 0 || background > 7)
	{
		background = 0;
	}
	if(foreground_intensity < 0 || foreground_intensity > 1)
	{
		foreground_intensity = 0;
	}
	if(background_intensity < 0 || background_intensity > 1)
	{
		background_intensity = 0;
	}
	//Set Colors
	int Color = 16 * background + 128 * background_intensity + foreground + 8 * foreground_intensity;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

/*
CursorVisibility(int visibility)
 Changes console cursor visibility using SetConsoleCursorInfo (windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsolecursorinfo

 int visibility
  0: invisible
  1: visible
  default: visible
*/
void CursorVisibility(int visibility)
{
	CONSOLE_CURSOR_INFO cursor;
	//dwSize: "The percentage of the character cell that is filled by the cursor. This value is between 1 and 100."
	//more info: https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	cursor.dwSize = 100;
	if(visibility == 0)
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
SetCursorPosition(int x, int y)
 Changes cursor position using SetConsoleSetCursorPosition (windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsoleSetCursorPosition

 int x
  x coord (>= 0)
  default: 0

 int y
  y coord (>= 0)
  default: 0
*/
void SetCursorPosition(int x, int y)
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
Startup(int width, int height, char title)
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
void Startup(int width, int height, char title[100])
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
	//Clear screen
	system("cls");
	//Hide cursor
	printf("\e[?25l");
	//Set window size
	system(screenSize);
	//Use UTF-8
	system("chcp 65001");
	//Set console title
	SetConsoleTitle(title);
	//Disable quick edit
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
	//Clear screen
	system("cls");
}

/*
ScreenSize(int width, int height)
 Changes the screen size

 int width
  window width (characters) (>= 0)
  default: 0

 int height
  window height (characters) (>= 0)
  default: 0
*/
void ScreenSize(int width, int height)
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
ScreenTitle(char title[100])
 Changes the screen title

 char title
  console title
*/
void ScreenTitle(char title[100])
{
	SetConsoleTitle(title);
}

/*
PlayAudio(char path[100], int repeat)
 Uses mciSendString() to play sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 char path
  path to audio file(mp3)

 int repeat
  0: false
  1: true
  default: 0
*/
void PlayAudio(char path[100], int repeat)
{
	char close[100];
	char open[100];
	char play[100];
	if (repeat == 1)
	{
		sprintf(close, "close %s", path);
		sprintf(open, "open %s type MPEGVideo alias %s", path, path);
		sprintf(play, "play %s repeat", path);
	}
	else
	{
		sprintf(close, "close %s", path);
		sprintf(open, "open %s type MPEGVideo alias %s", path, path);
		sprintf(play, "play %s", path);
	}
	//Close(sometimes sounds won't play the second time you want to play the same sound)
	mciSendString(close, NULL, 0, 0);
	//Open
	mciSendString(open, NULL, 0, 0);
	//Start
	mciSendString(play, NULL, 0, 0);
}

/*
PauseAudio(char path[100])
 Uses mciSendString() to pause sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 char path
  path to audio file(mp3)
*/
void PauseAudio(char path[100])
{
	char pause[100];
	sprintf(pause, "pause %s", path);
	mciSendString(pause, NULL, 0, 0);
}

/*
ResumeAudio(char path[100])
 Uses mciSendString() to resume paused sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 char path
  path to audio file(mp3)
*/
void ResumeAudio(char path[100])
{
	char resume[100];
	sprintf(resume, "resume %s", path);
	mciSendString(resume, NULL, 0, 0);
}

/*
StopAudio(char path[100])
 Uses mciSendString() to stop sounds.
 https://docs.microsoft.com/en-us/previous-versions/dd757161(v%3Dvs.85)

 char path
  path to audio file(mp3)
*/
void StopAudio(char path[100])
{
	char stop[100];
	sprintf(stop, "stop %s", path);
	mciSendString(stop, NULL, 0, 0);
}

/*
*LoadTexture(char path[100])
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
  [pixel x, y]: color code of pixel(same code as SetColor())
   first digit: color
   second digit: intensity
  (99: transparent)

 char path
  path to file
*/
int *LoadTexture(char path[100])
{
	int i, j;
	int x, y;
	FILE *fp = fopen(path,"r");
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
InitCanvas(int width, int height, int color)
 Initializes canvas to be displayed to the console

 int width
  width of canvas

 int height
  height of canvas

 int color
  background color for canvas
*/
void InitCanvas(int width, int height, int color)
{
	int i, j;
	//Variable length array
	canvas = (int *)malloc((width * height + 2) * sizeof(int));
	text = (char *)malloc((width * height + 1) * sizeof(char));
	textColor = (int *)malloc((width * height) * sizeof(int));
	//The first element stores the width and the second the height
	canvas[0] = width;
	canvas[1] = height;
	//Initialize with background color
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			canvas[(i * width) + j + 2] = color;
			text[(i * width) + j] = '\0';
			textColor[(i * width) + j] = 00;
		}
	}
	text[width * height + 1] = '\0';
}

/*
CleanCanvas(int color)
 Cleans canvas

 int color
  background color for canvas
*/
void CleanCanvas(int color)
{
	int i, j;
	//Get width and height
	int width = canvas[0];
	int height = canvas[1];
	//Clean with background color
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			canvas[(i * width) + j + 2] = color;
		}
	}
}

/*
DrawTexture(int *texture, int xPos, int yPos)
 Draws texture to canvas (use between ClearCanvas() and Display())

 int *texture
  texture to be drawn to canvas

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void DrawTexture(int *texture, int xPos, int yPos)
{
	int i, j;
	//Get width and height of texture
	int x = texture[0];
	int y = texture[1];
	//Get width of canvas
	int width = canvas[0];
	//Draw
	for(i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(texture[(i * x) + j + 2] != 99)
			{
				canvas[(i + yPos) * width + j + xPos + 2] = texture[(i * x) + j + 2];
			}
		}
	}
}

/*
DrawPixel(int color, int xPos, int yPos)
 Draws pixel to canvas (use between ClearCanvas() and Display())

 int color
  color of pixel

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void DrawPixel(int color, int xPos, int yPos)
{
	//Get width of canvas
	int width = canvas[0];
	//Draw
	canvas[yPos * width + xPos + 2] = color;
}

/*
DrawChar(char input[], int color, int xPos, int yPos)
 Draws text to canvas (use between ClearCanvas() and Display())

 char input[]
  text to be drawn to canvas

 int color
  color of text

 int xPos
  x position(The top left corner is the origin)

 int yPos
  x position(The top left corner is the origin)
*/
void DrawChar(char input[], int color, int xPos, int yPos)
{
	int i = 0;
	//Get width of canvas
	int width = canvas[0];
	//Draw
	while(input[i] != '\0')
	{
		text[yPos * width + i + xPos] = input[i];
		textColor[yPos * width + i + xPos] = color;
		i++;
	}
}

/*
Display()
 Displays canvas to console
*/
void Display()
{
	int i, j;
	//Log fps
	float currentTime = timeFromStart();
	fps = 1 / (currentTime - lastDraw);
	lastDraw = timeFromStart();
	//Get width and height
	int x = canvas[0];
	int y = canvas[1];
	//Moves cursor to top left of the console to draw over previous frame (Using system("cls") makes the screen flicker)
	SetCursorPosition(0, 0);
	//Draw
	for(i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(text[(i * x) + j] != '\0')
			{
				SetColor(textColor[(i * x) + j] / 10 % 10, canvas[(i * x) + j + 2] / 10 % 10, textColor[(i * x) + j] % 10, canvas[(i * x) + j + 2] % 10);
				printf("%c ", text[(i * x) + j]);
			}
			else
			{
				SetColor(0, canvas[(i * x) + j + 2] / 10 % 10, 0, canvas[(i * x) + j + 2] % 10);
				printf("  ");
			}
		}
		if(i < y - 1)
		{
			printf("\n");
		}
	}
}

/*
GetFPS()
 Returns fps
*/
float GetFPS()
{
	return fps;
}