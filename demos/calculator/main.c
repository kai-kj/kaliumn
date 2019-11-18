#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;
int *dec, *add, *sub, *multi, *divi, *enter, *clear;
int beep;
int decState = 0;
int lButtonState = 0;
int mouseX, mouseY;
int mode = 0;
double currentValue = 0;
double previousValue = 0;
void Input(int input)
{
    if(decState == 0)
    {
        currentValue = currentValue * 10 + input;
    }
    else
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
void Calculate()
{
    switch(mode)
    {
        case 1:
            currentValue = currentValue + previousValue;
            break;
        case 2:
            currentValue = currentValue - previousValue;
            break;
        case 3:
            currentValue = currentValue * previousValue;
            break;
        case 4:
            currentValue = currentValue / previousValue;
            break;
        default:
            break;
        mode = 0;
    }
}
void Reset()
{
    decState = 0;
    mode = 0;
    currentValue = 0;
    previousValue = 0;
}
void Control()
{
    if((GetKeyState(VK_LBUTTON) & 0x8000))
	{
        if(lButtonState == 0)
        {
            lButtonState = 1;
            mouseX = GetMousePositionX() / 2;
            mouseY = GetMousePositionY();
            PlayAudio(beep, 0);
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
            else if(mouseX > 11 - 1 && mouseX < 11 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                if(decState == 0)
                {
                    decState = 1;
                }
            }
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 23 - 1 && mouseY < 23 + 5)
            {
                mode = 1;
                previousValue = currentValue;
                currentValue = 0;
            }
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 17 - 1 && mouseY < 5 + 17)
            {
                mode = 2;
                previousValue = currentValue;
                currentValue = 0;
            }
            else if(mouseX > 15 - 1 && mouseX < 15 + 3 && mouseY > 11 - 1 && mouseY < 11 + 5)
            {
                mode = 3;
                previousValue = currentValue;
                currentValue = 0;
            }
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
    CleanCanvas(01);
    for(i = 0; i < 23; ++i)
    {
        DrawPixel(00, i + 1, 1);
        DrawPixel(00, i + 1, 2);
        DrawPixel(00, i + 1, 3);
    }
    DrawChar(value, 99, 24 - digits, 2);
    DrawTexture(zero, 6, 23);
    DrawTexture(one, 1, 17);
    DrawTexture(two, 6, 17);
    DrawTexture(three, 11, 17);
    DrawTexture(four, 1, 11);
    DrawTexture(five, 6, 11);
    DrawTexture(six, 11, 11);
    DrawTexture(seven, 1, 5);
    DrawTexture(eight, 6, 5);
    DrawTexture(nine, 11, 5);
    DrawTexture(dec, 11, 23);
    DrawTexture(add, 15, 23);
    DrawTexture(sub, 15, 17);
    DrawTexture(multi, 15, 11);
    DrawTexture(divi, 15, 5);
    DrawTexture(enter, 21, 17);
    DrawTexture(clear, 1, 23);
    SetCursorPosition(0, 0);
    Display();
}
int main()
{
    Startup(25 * 2, 29, "Calculator");
    InitCanvas(25, 29, 01);
    zero = LoadTexture("assets/zero");
    one = LoadTexture("assets/one");
    two = LoadTexture("assets/two");
    three = LoadTexture("assets/three");
    four = LoadTexture("assets/four");
    five = LoadTexture("assets/five");
    six = LoadTexture("assets/six");
    seven = LoadTexture("assets/seven");
    eight = LoadTexture("assets/eight");
    nine = LoadTexture("assets/nine");
    dec = LoadTexture("assets/dec");
    add = LoadTexture("assets/add");
    sub = LoadTexture("assets/sub");
    multi = LoadTexture("assets/multi");
    divi = LoadTexture("assets/div");
    enter = LoadTexture("assets/enter");
    clear = LoadTexture("assets/clear");
    beep = LoadAudio("assets/beep.mp3");
    currentValue = 0;
    while(1)
    {
        Control();
        Draw();
    }
}
