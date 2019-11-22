/*
cmd.h
Please link the winmm.dll library(for mingw add "-lwinmm").

Demos are included in the "demos" folder

See "colors.png" for colors

Use the Texture Editor included in the "TextureEditor" folder to make sprites
*/

#ifndef KALIUMN
#define KALIUMN

//includes
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//functions
float KAL_GetTime();
void KAL_SetColor(const int FOREGROUND, const int BACKGROUND);
void KAL_SetCursorVisibility(const int VISIBILITY);
void KAL_SetCursorPosition(int x, int y);
int KAL_GetMousePositionX();
int KAL_GetMousePositionY();
void KAL_Startup(int width, int height, const char TITLE[]);
void KAL_ScreenSize(int width, int height);
void KAL_ScreenTitle(const char TITLE[]);
int KAL_LoadAudio(const char TITLE[]);
void KAL_PlayAudio(const int INPUT, const int REPEAT);
void KAL_PauseAudio(const int INPUT);
void KAL_ResumeAudio(const int INPUT);
void KAL_StopAudio(const int INPUT);
int *KAL_LoadTexture(const char PATH[]);
void KAL_InitCanvas(const int WIDTH, const int HEIGHT, const int COLOR);
void KAL_CleanCanvas(const const int COLOR);
void KAL_DrawTexture(const int *TEXTURE, const int XPOS, const int YPOS);
void KAL_DrawPixel(const int COLOR, const int XPOS, const int YPOS);
void KAL_DrawChar(const char INPUT[], const int COLOR, const int XPOS, const int YPOS);
void KAL_Display();
float KAL_GetFPS();
#endif
