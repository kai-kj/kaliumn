#include <stdlib.h>
#include <stdio.h>
#include "../kaliumn.h"
int main(void)
{
    Startup(60, 30, "mousePositionDemo");
    int x, y;
    while (1)
    {
        x = GetMousePositionX() / 8;
        y = GetMousePositionY() / 16;
        system("cls");
        printf("%d, %d", x, y);
    }
}
