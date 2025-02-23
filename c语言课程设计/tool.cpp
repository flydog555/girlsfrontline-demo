#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")
#include "profile.h"

//png͸��Ч��
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

//BGM����
void homeBGM()
{
	mciSendString("open ./resource/home/������BGM.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);

}

//profile����Ĵ���

Profile* insert(Profile* h, const char* accontname, const char* code, const char* name)  //(Ҫ�������������λ�ã�����Ľڵ��е���������)
{
	Profile* p, * s;
	int j = 1;
	s = (Profile*)malloc(sizeof(Profile));//�����½ڵ㣬ͬʱҲ��Ҫ����Ľڵ�
	strcpy(s->accontname, accontname);
	strcpy(s->code, code);
	strcpy(s->name, name);
	s->level = 1;
	s->next = NULL;
	if (h == NULL) //�������h�ǿ�������Ҫ����Ľڵ����ͷ�ڵ�
	{
		h = s;
	}
	else //h���ǿ�����
	{
		p = h;
		while (p->next != NULL)//Ѱ��Ҫ����λ��֮ǰ��һ���ڵ�
		{
			p = p->next;
		}
		p->next = s;
		
		//s->next = p->next;
		//p->next = s;
	}
	return h;
}

//�����˺�����
Profile* createfromtail()
{
	Profile* head, * tail = NULL;
	head = (Profile*)malloc(sizeof(Profile));
	tail = head;

	/*int i;
	for (i = 0; i < n; i++)
	{
		p = (STU*)malloc(sizeof(STU));
		printf("������ѧ�ţ�");
		scanf("%d", &p->num);
		getchar();
		printf("������ɼ���");
		scanf("%d", &p->score);
		tail->next = p;
		tail = p;
	}*/
	tail->next = NULL;
	return head;
}
