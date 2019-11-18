#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"
int main(void)
{
    PlayAudio("sound.mp3", 0);
    Sleep(1000);
    PauseAudio("sound.mp3");
    Sleep(1000);
    ResumeAudio("sound.mp3");
    Sleep(1000);
    StopAudio("sound.mp3");
}
