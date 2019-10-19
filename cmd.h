/*
cmd.h
v0.1(2019-10-19)
Please include windows.h
*/

/*
ConsoleColour(int foreground, int background, int foreground_intensity, int background_intensity)
Sets console text colour using SetConsoleTextAttribute(windows.h)
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
defualt: White

int background
0: Black
1: Blue
2: Green
3: Cyan
4: Red
5: Magenta
6: Yellow
7: White 
defualt: Black

int foreground_intensity
0: False
1: True
defualt: False

int background_intensity
0: False
1: True
defualt: False
*/
void ConsoleColour(int foreground, int background, int foreground_intensity, int background_intensity){
	//Check inputs
	if(foreground < 0 || foreground > 7){
		foreground = 7;
	}
	if(background < 0 || background > 7){
		background = 0;
	}
	if(foreground_intensity != 0 || foreground_intensity != 1){
		foreground_intensity = 0;
	}
	if(background_intensity != 0 || background_intensity != 1){
		background_intensity = 0;
	}
	//Set colours
	int colour = (16 * background + 8 * background_intensity)+ foreground + 8 * foreground_intensity;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
/*
CursorVisibility(int visibility)
Changes console cursor visibility using SetConsoleCursorInfo (windows.h)
https://docs.microsoft.com/en-us/windows/console/setconsolecursorinfo

int visibility
0: invisible
1: visible
deafult: visible
*/
void CursorVisibility(int visibility){
	CONSOLE_CURSOR_INFO cursor;
	//dwSize: "The percentage of the character cell that is filled by the cursor. This value is between 1 and 100."
	//more information on CONSOLE_CURSOR_INFO: https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	cursor.dwSize = 100;
	if(visibility == 0){
		cursor.bVisible = FALSE;
	}else{
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
defualt: 0

int y
y coord (>= 0)
defualt: 0
*/
void CursorPosition(int x, int y){
	//Check input
	if(x < 0){
		x = 0;
	}
	if(y < 0){
		y = 0;
	}
	COORD position;
    position.X = x;
    position.Y = y;
    //Set cursor position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}