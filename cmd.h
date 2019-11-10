/*
cmd.h
v0.20(2019-11-07)
Please include windows.h and link the winmm.dll library(for mingw add "-lwinmm").
*/

#include <windows.h>

/*
ConsoleColor(int foreground, int background, int foreground_intensity, int background_intensity)
 Sets console text Color using SetConsoleTextAttribute(windows.h)
 ttps://docs.microsoft.com/en-us/windows/console/setconsoletextattribute

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
void ConsoleColor(int foreground, int background, int foreground_intensity, int background_intensity)
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
	//more information on CONSOLE_CURSOR_INFO: https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	cursor.dwSize = 100;
	if(visibility == 0)
	{
		cursor.bVisible = FALSE;
	}
	else
	{
		cursor.bVisible = TRUE;
	}
	//Set visibility
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

/*
CursorPosition(int x, int y)
 Changes cursor position using SetConsoleCursorPosition (windows.h)
 https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition

 int x
  x coord (>= 0)
  default: 0

 int y
  y coord (>= 0)
  default: 0
*/
void CursorPosition(int x, int y)
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
    //Set cursor position
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
	//Clear screen
	system("cls");
}

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
	//Set window size
	system(screenSize);
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
	//Close(sometimes sounds won't play the second time you want to play it)
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
	//Pause
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
	//Resume
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
	//Stop
	mciSendString(stop, NULL, 0, 0);
}

/*
*LoadTexture(char path[100])
 Loads texture to *int to be drawn by Draw()
 Texture format

  height width
  [pixel 0, 0] [pixel 1, 0] [pixel 2, 0]
  [pixel 0, 1] [pixel 1, 1] [pixel 2, 1] . . .
  [pixel 0, 2] [pixel 1, 2] [pixel 2, 2]
                   .
                   .
                   .

  height: height of texture
  width: width of texture
  [pixel x, y]: color code of pixel(same code as ConsoleColor())
   first digit: color
   second digit: intensity (intensity 2 == trasparent)

 char path
  path to file
*/
int *LoadTexture(char path[100])
{
	int i, j;
	int x, y;
	FILE *fp = fopen(path,"r");
	fscanf(fp, "%d, %d", &x, &y);

	int *texture = (int *)malloc((x * y + 2) * sizeof(int));

	texture[0] = x;
	texture[1] = y;

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
Draw(int *texture)
 Draws texture loaded by *LoadTexture()

 int *texture
  texture
*/
void Draw(int *texture, int xPos, int yPos)
{
	int i, j;
	int x = texture[0];
	int y = texture[1];

	CursorPosition(xPos * 2, yPos);

	for(i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			if(texture[(i * x) + j + 2] == 99)
			{
				CursorPosition(xPos * 2 + j * 2 + 2, yPos + i);
			}
			else
			{
				ConsoleColor(0, texture[(i * x) + j + 2] / 10 % 10, 0, texture[(i * x) + j + 2] % 10);
				printf("  ");
			}

		}

		if(i < y - 1)
		{
			CursorPosition(xPos * 2, yPos + i);
		}

	}

}