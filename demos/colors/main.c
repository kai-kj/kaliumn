#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../kaliumn.h"
int main(void)
{
	int i, j;
	KAL_SetColor(00, 71);
	printf("                 \n");
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 2; j++)
		{
			KAL_SetColor(00, 71);
			printf("Color: %02d  ", i * 10 + j);
			KAL_SetColor(00, i * 10 + j);
			printf("    ");
			KAL_SetColor(00, 71);
			printf("  \n");
			printf("                 \n");
		}
	}
	KAL_SetColor(71, 00);
	printf("press ENTER to continue...");
	getchar();
}
