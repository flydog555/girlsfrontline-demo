#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include "profile.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
//#include<bits/stdc++.h>
#include "shared.h"
using namespace std;
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")



extern void repair();
extern void home();
extern Profile* insert(Profile* h, const char* accontname, const char* code, const char* name);
extern Profile* createfromtail();
extern void creataccount();
extern void login();

int main()
{
	
	//��������
	initgraph(1280, 720);
	cleardevice();

	//��ȡ���ھ��
	HWND hnd = GetHWnd();

	//���ô��ڱ���
	SetWindowText(hnd, "��Ůǰ��");

	//��¼��ע��

	login();
	
	
	
	
	//�˺ų�ʼ��
	/*int yesno=MessageBox(hnd, "�Ƿ������ʺ�", "�˺ŵ�½", MB_YESNO);
	Profile* p = createfromtail();
	char tempaccontname[100];
	char tempcode[20];
	char tempname[100];*/
	//if (yesno == IDYES)
	/*if (1)
	{
		while (1)
		{
			if (login() == 1)
			{
				break;
			}
		}
	}*/
	/*else if (yesno == IDNO)
	{
		creataccount();
	}*/
		home();

		getchar();
		closegraph;
		return 0;
}