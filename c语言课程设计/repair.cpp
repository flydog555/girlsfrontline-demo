#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

extern void home();

void repair()
{
	//ÏÔÊ¾±³¾°
	cleardevice();
	IMAGE rbg;
	loadimage(&rbg, "./resource/rbg.jpg", 1280, 720);
	putimage(0, 0 ,&rbg );

	setbkmode(TRANSPARENT);
	setfillcolor(RGB(48, 48, 48));
	solidroundrect(0, 0, 0 + 100, 0 + 100, 10, 10);

	//°´¼ü
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 0 && msg.x <= 0 + 100 && msg.y >= 0 && msg.y <= 0 + 100)
				{
					printf("·µ»Ø\n");
					home();
				}
				break;
			default:
				break;
			}
		}

	}

}