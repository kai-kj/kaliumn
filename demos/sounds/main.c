#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
    Startup(40, 20, "soundDemo");
    int music;
    music = LoadAudio("music.mp3");
    printf("playing music\n");
    PlayAudio(music, 0);
    Sleep(5000);
    printf("pausing music\n");
    PauseAudio(music);
    Sleep(5000);
    printf("resuming music\n");
    ResumeAudio(music);
    Sleep(5000);
    printf("stopping music\n\n");
    StopAudio(music);
    printf("press ENTER to finish\n");
    getchar();
}
