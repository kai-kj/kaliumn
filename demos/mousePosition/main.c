#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
    //initialize screen
    KAL_Startup(60, 30, "mousePositionDemo");
    int x, y;
    while (1)
    {
        //get mouse position
        x = KAL_GetMousePositionX();
        y = KAL_GetMousePositionY();
        system("cls");
        printf("%d, %d", x, y);
    }
}
