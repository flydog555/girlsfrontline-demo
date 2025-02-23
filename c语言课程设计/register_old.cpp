#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <easyx.h>
#include <share.h>

extern int sign;

//void creataccount()
//{
//	FILE* file,*signfile,*signfilea;
//	char filename[20];
//	//读取命名次数
//	signfile=fopen("sign.txt", "r");
//	fscanf(signfile, "%d", &sign);
//	fclose(signfile);
//	sprintf(filename, "file%d.txt", sign);
//	printf("%d\n", sign);
//	signfilea = fopen("sign.txt", "w");
//	fprintf(signfilea, "%d", sign+1);
//	fclose(signfilea);
//	file=fopen(filename, "w+");//创建配置文件
//
//
//
//	printf("请输入用户名：");
//	char accountname[100];//写入用户名
//	scanf("%s", accountname);
//	fprintf(file, "accountname:%s\n", accountname);
//	printf("请输入密码：");
//	int password;//写入密码
//	scanf("%d", &password);
//	fprintf(file, "password:%d\n", password);
//	printf("请输入游戏昵称：");
//	char name[100];//写入游戏名
//	scanf("%s", name);
//	fprintf(file, "name:%s\n", name);
//	fprintf(file, "level:1\n");//写入初始等级
//	fprintf(file, "manpower:10000\n");//写入初始人力
//	fprintf(file, "ammunition:10000\n");//写入初始弹药
//	fprintf(file, "pation:10000\n");//写入初始口狼
//	fprintf(file, "part:10000\n");//写入初始零件
//	printf("注册成功！\n");
//	fclose(file);
//}

//int login()
//{
//	FILE* file;
//	printf("请输入用户名：");
//	char laccountname[100];//从键盘输入的用户名
//	char filename[20];
//	char temp[100];//文件中读取的用户名
//	scanf("%s", laccountname);
//	FILE*signfile = fopen("sign.txt", "r");
//	fscanf(signfile, "%d", &sign);
//	fclose(signfile);
//	int i;
//	for (i = 1; i <= sign; i++)
//	{
//		sprintf(filename, "file%d.txt", i);
//		file = fopen(filename, "r");
//		fgets(temp, sizeof(temp), file);
//		char* colon = strchr(temp, ':');
//		if (colon != NULL) 
//		{
//			char* value = colon + 1; // 指向冒号后一个字符  
//			// 去掉换行符  
//			value[strcspn(value, "\n")] = '\0'; // 替换换行符为结束符
//			//printf("提取的字符串是：%s\n", value);
//			if (strcmp(laccountname, value) == 0)
//			{
//				printf("请输入密码：");
//				int lcode;//键盘输入的密码
//				int tempcode;//从文件读取的密码
//				scanf("%d", &lcode);
//				fscanf(file, "password:%d", &tempcode);
//				if (tempcode == lcode)
//				{
//					printf("登录成功！\n");
//					fclose(file);
//					return 1;
//				}
//				else
//				{
//					printf("密码错误！\n");
//					return 0;
//				}
//			}
//			else
//			{
//				if (i == sign)
//				{
//					printf("未找到该账户\n");
//					return 0;
//				}
//				
//			}
//		}
//		
//	}
//	printf("请输入密码：");
//}