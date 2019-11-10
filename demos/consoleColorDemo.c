#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "../cmd.h"
int main(void){
	//ConsoleColour() demo
	int i, j, k, l;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			for(k = 0; k < 2; k++){
				for(l = 0; l < 2; l++){
					ConsoleColour(i, j, k, l);
					printf("ConsoleColour(%d, %d, %d, %d);\n", i, j, k, l);
				}
			}
		}
	}
	ConsoleColour(7, 0, 0, 0);
	printf("press ENTER to continue...");
	getchar();
}