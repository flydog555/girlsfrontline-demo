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
	
	//创建画面
	initgraph(1280, 720);
	cleardevice();

	//获取窗口句柄
	HWND hnd = GetHWnd();

	//设置窗口标题
	SetWindowText(hnd, "少女前线");

	//登录与注册

	login();
	
	
	
	
	//账号初始化
	/*int yesno=MessageBox(hnd, "是否已有帐号", "账号登陆", MB_YESNO);
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