#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
    KAL_Startup(40, 20, "soundDemo");
    //load music file
    int music;
    music = KAL_LoadAudio("music.mp3");
    //play music
    printf("playing music\n");
    KAL_PlayAudio(music, 0);
    Sleep(5000);
    //pause music
    printf("pausing music\n");
    KAL_PauseAudio(music);
    Sleep(5000);
    //resume music
    printf("resuming music\n");
    KAL_ResumeAudio(music);
    Sleep(5000);
    //stop music
    printf("stopping music\n\n");
    KAL_StopAudio(music);
    printf("press ENTER to finish\n");
    getchar();
}
