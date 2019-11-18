#include <stdlib.h>
#include <stdio.h>
#include "../kaliumn.h"
int main(void)
{
    Startup(60, 30, "mousePositionDemo");
    int x, y;
    while (1)
    {
        x = GetMousePositionX();
        y = GetMousePositionY();
        system("cls");
        printf("%d, %d", x, y);
    }
}
