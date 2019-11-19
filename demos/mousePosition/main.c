#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
    //initialize screen
    Startup(60, 30, "mousePositionDemo");
    int x, y;
    while (1)
    {
        //get mouse position
        x = GetMousePositionX();
        y = GetMousePositionY();
        system("cls");
        printf("%d, %d", x, y);
    }
}
