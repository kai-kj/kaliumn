/*
cmd.h
v0.13(2019-11-01)
Please include windows.h and link the winmm.dll library(for mingw add "-lwinmm").
*/

/*
ConsoleColour(int foreground, int background, int foreground_intensity, int background_intensity)
 Sets console text colour using SetConsoleTextAttribute(windows.h)
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
void ConsoleColour(int foreground, int background, int foreground_intensity, int background_intensity)
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
	//Set colours
	int colour = 16 * background + 128 * background_intensity + foreground + 8 * foreground_intensity;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
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

 int height
  window height (>= 0)
  default: 0

 int width
  window width (>= 0)
  default: 0

 char title
  console title
*/
void Startup(int width, int height, char title[100])
{
	char screenSize[100];
	sprintf(screenSize, "MODE %d, %d", width, height);
	//Check input
	if(height < 0)
	{
		height = 0;
	}
	if(width < 0)
	{
		width = 0;
	}
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