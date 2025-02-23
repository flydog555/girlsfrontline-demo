#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <stdlib.h>  
#include <time.h>  
#include <graphics.h>

extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
extern void home();

int gacha(int sign)
{
	int randam;
	char filenames[10][100] = {"./resource/character/5ÐÇ/card/AA12.png","./resource/character/5ÐÇ/card/HK416.png","./resource/character/5ÐÇ/card/RO635.png","./resource/character/5ÐÇ/card/RPK16.png","./resource/character/5ÐÇ/card/SCARH.png"};

	if (sign == 5) {
		srand(time(NULL));
		randam = rand() % 5;
		printf("%d\n", randam);
		IMAGE ch;
		loadimage(&ch, filenames[randam], 127*2, 193*2);
		cleardevice();
		transparentimage3(NULL, 600, 300, &ch);
		Sleep(1000);
		home();
		return randam;
	}
	else if (sign == 4)
	{
		srand(time(NULL));
		randam = rand() % 6+6;
		return randam;
	}
	else if (sign == 3)
	{
		srand(time(NULL));
		randam = rand() % 6 + 12;
		return randam;
	}
	else if (sign == 2)
	{
		srand(time(NULL));
		randam = rand() % 6 + 18;
		return randam;
	}
}