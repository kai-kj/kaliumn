#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
    Startup(40, 20, "soundDemo");
    //load music file
    int music;
    music = LoadAudio("music.mp3");
    //play music
    printf("playing music\n");
    PlayAudio(music, 0);
    Sleep(5000);
    //pause music
    printf("pausing music\n");
    PauseAudio(music);
    Sleep(5000);
    //resume music
    printf("resuming music\n");
    ResumeAudio(music);
    Sleep(5000);
    //stop music
    printf("stopping music\n\n");
    StopAudio(music);
    printf("press ENTER to finish\n");
    getchar();
}
