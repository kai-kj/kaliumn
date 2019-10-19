/*---LAPTOP---
cd C:\Users\Kitagawa-Jones\Desktop\programing\Header
gcc demo.c -o demo.exe

*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"
int main(void){
	//ConsoleColour() demo
	int i, j, k, l;
	for(i = 0; i < 7; i++){
		for(j = 0; j < 7; j++){
			for(k = 0; k < 1; k++){
				for(l = 0; l < 1; l++){
					ConsoleColour(i, j, k, l);
					printf("ConsoleColour(%d, %d, %d, %d);\n", i, j, k, l);
				}
			}
		}
	}
	ConsoleColour(7, 0, 0, 0);
	printf("press any key to continue...");
	getchar();
}