#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")
#include "profile.h"

//png透明效果
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

//BGM播放
void homeBGM()
{
	mciSendString("open ./resource/home/主界面BGM.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);

}

//profile链表的创建

Profile* insert(Profile* h, const char* accontname, const char* code, const char* name)  //(要插入链表，插入的位置，插入的节点中的两个数据)
{
	Profile* p, * s;
	int j = 1;
	s = (Profile*)malloc(sizeof(Profile));//申请新节点，同时也是要插入的节点
	strcpy(s->accontname, accontname);
	strcpy(s->code, code);
	strcpy(s->name, name);
	s->level = 1;
	s->next = NULL;
	if (h == NULL) //如果链表h是空链表，则要插入的节点便是头节点
	{
		h = s;
	}
	else //h不是空链表
	{
		p = h;
		while (p->next != NULL)//寻找要插入位置之前的一个节点
		{
			p = p->next;
		}
		p->next = s;
		
		//s->next = p->next;
		//p->next = s;
	}
	return h;
}

//创建账号链表
Profile* createfromtail()
{
	Profile* head, * tail = NULL;
	head = (Profile*)malloc(sizeof(Profile));
	tail = head;

	/*int i;
	for (i = 0; i < n; i++)
	{
		p = (STU*)malloc(sizeof(STU));
		printf("请输入学号：");
		scanf("%d", &p->num);
		getchar();
		printf("请输入成绩：");
		scanf("%d", &p->score);
		tail->next = p;
		tail = p;
	}*/
	tail->next = NULL;
	return head;
}
