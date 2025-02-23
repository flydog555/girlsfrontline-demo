#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<time.h>
#include "profile.h"
#include "shared.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

extern void repair();
extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
extern void homeBGM();
extern int gacha(int sign);
void home()
{
	cleardevice();
	//播放bgm
	homeBGM();

	//显示背景
	IMAGE img;
	IMAGE button1;
	IMAGE button2;
	IMAGE button3;
	IMAGE top;
	IMAGE lr;

	loadimage(&img, "./resource/home/bg.jpg", 1280, 720);
	loadimage(&button1, "./resource/home/1.png", 400, 100);
	loadimage(&button2, "./resource/home/2.png", 400, 100);
	loadimage(&button3, "./resource/home/3.png", 420, 105);
	loadimage(&top, "./resource/home/top.png", 1280, 150);
	loadimage(&lr, "./resource/home/levelround.png", 45, 45);

	//显示人物
	IMAGE ch;
	loadimage(&ch, "./resource/character/5星/HK416.png", 585, 1024);

	//显示名称
	setbkmode(TRANSPARENT);
	
	int currentLine = 0;
	//int sign = 0;
	int tempcode;
	int tempmanpower;
	int tempammunition;
	int temppation;
	int temppart;

	char filename[20];
	char name[100];
	char tempname[100];
	char levelStr[10]; // 确保数组足够大以容纳转换后的字符串
	char levelStr1[10];
	char levelStr2[10];
	char levelStr3[10];
	char levelStr4[10];

	//读取配置文件
	sprintf(filename, "file%d.txt", 1);  ////////
	FILE* file = fopen(filename, "r");
	while (fgets(tempname, sizeof(tempname), file) != NULL)
	{
		currentLine++;
		if (currentLine == 3)
		{
			
			char* colon = strchr(tempname, ':');
			char* value = colon + 1;
			value[strcspn(value, "\n")] = '\0';
			strcpy(name, value);
			fscanf(file, "level:%d", &tempcode); //等级
			sprintf(levelStr, "%d", tempcode);
			
			
		}
		else if (currentLine == 4)
		{
			fscanf(file, "manpower:%d", &tempmanpower);//人力
			sprintf(levelStr1, "%d", tempmanpower);
		}
		else if (currentLine == 5)
		{
			fscanf(file, "ammunition:%d", &tempammunition);//弹药
			sprintf(levelStr2, "%d", tempammunition);
		}
		else if (currentLine == 6)
		{
			fscanf(file, "pation:%d", &temppation);//口粮
			sprintf(levelStr3, "%d", temppation);
		}
		else if (currentLine == 7)
		{
			fscanf(file, "part:%d", &temppart);//零件
			sprintf(levelStr4, "%d", temppart);
		}
	}
	fclose(file);
	

	
	//显示
	time_t start_time = time(NULL);
	while (difftime(time(NULL), start_time) < 1)
	{
		BeginBatchDraw();
		putimage(0, 0, &img);
		transparentimage3(NULL, 800, 260, &button1);//透明png
		transparentimage3(NULL, 800, 150, &button2);
		transparentimage3(NULL, 780, 375, &button3);
		transparentimage3(NULL, 100, 100, &ch);
		transparentimage3(NULL, 0, 0, &top);
		transparentimage3(NULL, 10, 5, &lr);
		settextcolor(RGB(255, 255, 255));
		settextstyle(35, 0, "黑体");
		outtextxy(70, 10, name); 
		settextstyle(20, 0, "黑体");
		outtextxy(27, 17, levelStr);
		settextstyle(30, 0, "黑体");
		settextcolor(RGB(250, 164, 19));
		outtextxy(800, 12, levelStr1);
		outtextxy(900, 12, levelStr2);
		outtextxy(1000, 12, levelStr3);
		outtextxy(1100, 12, levelStr4);
		EndBatchDraw();
	}
	
	
	




	//按键
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 800 && msg.x <= 800 + 200 && msg.y >= 150 && msg.y <= 150 + 100)//1键区域
				{
					printf("1\n");
					repair();
				}
				if (msg.x >= 800 && msg.x <= 800 + 200 && msg.y >= 260 && msg.y <= 260 + 100)//2键区域
				{
					//printf("2\n");
					printf("%d\n",gacha(5));
				}
				if (msg.x >= 1000 && msg.x <= 1000 + 200 && msg.y >= 260 && msg.y <= 260 + 100)//3键区域
				{
					printf("3\n");
				}
				if (msg.x >= 780 && msg.x <= 780 + 210 && msg.y >= 375 && msg.y <= 375 + 105)//4键区域
				{
					printf("4\n");
				}
				if (msg.x >= 990 && msg.x <= 990 + 210 && msg.y >= 375 && msg.y <= 375 + 105)//5键区域
				{
					printf("5\n");
				}
				break;
			default:
				break;
			}
		}

	}
}