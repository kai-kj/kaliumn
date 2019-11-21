#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
//textures
int *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;
int *dec, *add, *sub, *multi, *divi, *enter, *clear;
int beep;
int decState = 0;
int lButtonState = 0;
int mouseX, mouseY;
int mode = 0;
double currentValue = 0;
double previousValue = 0;
//input numbers
void Input(int input)
{
    if(decState == 0) //above decimal point
    {
        currentValue = currentValue * 10 + input;
    }
    else //below decimal point
    {
        float num = input;
        int i;
        for(i = 0; i < decState; i++)
        {
            num = num / 10;
        }
        currentValue = currentValue + num;
        decState++;
    }
}
//calculate awnser
void Calculate()
{
    switch(mode)
    {
        case 1:
            currentValue = previousValue + currentValue;
            break;
        case 2:
            currentValue = previousValue - currentValue;
            break;
        case 3:
            currentValue = previousValue * currentValue;
            break;
        case 4:
            currentValue = previousValue / currentValue;
            break;
        default:
            break;
        mode = 0;
    }
}
//c button
void Reset()
{
    decState = 0;
    mode = 0;
    currentValue = 0;
    previousValue = 0;
}
// mouse position and clicks
void Control()
{
    if((GetKeyState(VK_LBUTTON) & 0x8000))
	{
        if(lButtonState == 0)
        {
            lButtonState = 1;
            mouseX = KAL_GetMousePositionX() / 2;
            mouseY = KAL_GetMousePositionY();
            KAL_PlayAudio(beep, 0);
            //numbers
            if(mouseX > 6 - 1 && mouseX < 6 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                Input(0);
            }
            else if(mouseX > 1 - 1 && mouseX < 1 + 3 && mouseY > 17 - 1 && mouseY < 17 + 5)
            {
                Input(1);
            }
            else if(mouseX > 6 - 1 && mouseX < 6 + 3 && mouseY > 17 - 1 && mouseY < 17 + 5)
            {
                Input(2);
            }
            else if(mouseX > 11 - 1 && mouseX < 11 + 3 && mouseY > 17 - 1 && mouseY < 17 + 5)
            {
                Input(3);
            }
            else if(mouseX > 1 - 1 && mouseX < 1 + 3 && mouseY > 11 - 1 && mouseY < 11 + 5)
            {
                Input(4);
            }
            else if(mouseX > 6 - 1 && mouseX < 6 + 3 && mouseY > 11 - 1 && mouseY < 11 + 5)
            {
                Input(5);
            }
            else if(mouseX > 11 - 1 && mouseX < 11 + 3 && mouseY > 11 - 1 && mouseY < 11 + 5)
            {
                Input(6);
            }
            else if(mouseX > 1 - 1 && mouseX < 1 + 3 && mouseY > 5 - 1 && mouseY < 5 + 5)
            {
                Input(7);
            }
            else if(mouseX > 6 - 1 && mouseX < 6 + 3 && mouseY > 5 - 1 && mouseY < 5 + 5)
            {
                Input(8);
            }
            else if(mouseX > 11 - 1 && mouseX < 11 + 3 && mouseY > 5 - 1 && mouseY < 5 + 5)
            {
                Input(9);
            }
            //decimal point
            else if(mouseX > 11 - 1 && mouseX < 11 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                if(decState == 0)
                {
                    decState = 1;
                }
            }
            // add
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                mode = 1;
                previousValue = currentValue;
                currentValue = 0;
            }
            //substract
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 17 - 1 && mouseY < 5 + 17)
            {
                mode = 2;
                previousValue = currentValue;
                currentValue = 0;
            }
            //multiply
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 11 - 1 && mouseY < 11 + 5)
            {
                mode = 3;
                previousValue = currentValue;
                currentValue = 0;
            }
            //divide
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 5 - 1 && mouseY < 5 + 5)
            {
                mode = 4;
                previousValue = currentValue;
                currentValue = 0;
            }
            else if(mouseX > 21 - 1 && mouseX < 21 + 3 && mouseY > 17 - 1 && mouseY < 23 + 5)
            {
                Calculate();
            }
            else if(mouseX > 1 - 1 && mouseX < 1 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                Reset();
            }
        }
	}
    else
    {
        lButtonState = 0;
    }
}
void Draw()
{
    int i, j;
    char value[100];
    sprintf(value, "%lf", currentValue);
    i = 0;
    while(value[i] != 0)
    {
        i++;
    }
    int digits = i;
    KAL_CleanCanvas(01);
    //draw display background
    for(i = 0; i < 23; ++i)
    {
        KAL_DrawPixel(00, i + 1, 1);
        KAL_DrawPixel(00, i + 1, 2);
        KAL_DrawPixel(00, i + 1, 3);
    }
    //draw numbers to display
    KAL_DrawChar(value, 99, 24 - digits, 2);
    //draw textures to canvas
    KAL_DrawTexture(zero, 6, 23);
    KAL_DrawTexture(one, 1, 17);
    KAL_DrawTexture(two, 6, 17);
    KAL_DrawTexture(three, 11, 17);
    KAL_DrawTexture(four, 1, 11);
    KAL_DrawTexture(five, 6, 11);
    KAL_DrawTexture(six, 11, 11);
    KAL_DrawTexture(seven, 1, 5);
    KAL_DrawTexture(eight, 6, 5);
    KAL_DrawTexture(nine, 11, 5);
    KAL_DrawTexture(dec, 11, 23);
    KAL_DrawTexture(add, 15, 23);
    KAL_DrawTexture(sub, 15, 17);
    KAL_DrawTexture(multi, 15, 11);
    KAL_DrawTexture(divi, 15, 5);
    KAL_DrawTexture(enter, 21, 17);
    KAL_DrawTexture(clear, 1, 23);
    KAL_SetCursorPosition(0, 0);
    KAL_Display();
}
int main()
{
    //initialize canvas and screen
    KAL_Startup(25 * 2, 29, "Calculator");
    KAL_InitCanvas(25, 29, 01);
    //load textures
    zero = KAL_LoadTexture("assets/zero");
    one = KAL_LoadTexture("assets/one");
    two = KAL_LoadTexture("assets/two");
    three = KAL_LoadTexture("assets/three");
    four = KAL_LoadTexture("assets/four");
    five = KAL_LoadTexture("assets/five");
    six = KAL_LoadTexture("assets/six");
    seven = KAL_LoadTexture("assets/seven");
    eight = KAL_LoadTexture("assets/eight");
    nine = KAL_LoadTexture("assets/nine");
    dec = KAL_LoadTexture("assets/dec");
    add = KAL_LoadTexture("assets/add");
    sub = KAL_LoadTexture("assets/sub");
    multi = KAL_LoadTexture("assets/multi");
    divi = KAL_LoadTexture("assets/div");
    enter = KAL_LoadTexture("assets/enter");
    clear = KAL_LoadTexture("assets/clear");
    beep = KAL_LoadAudio("assets/beep.mp3");
    currentValue = 0;
    //main loop
    while(1)
    {
        Control();
        Draw();
    }
}
