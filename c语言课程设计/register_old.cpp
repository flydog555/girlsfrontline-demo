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
//	//��ȡ��������
//	signfile=fopen("sign.txt", "r");
//	fscanf(signfile, "%d", &sign);
//	fclose(signfile);
//	sprintf(filename, "file%d.txt", sign);
//	printf("%d\n", sign);
//	signfilea = fopen("sign.txt", "w");
//	fprintf(signfilea, "%d", sign+1);
//	fclose(signfilea);
//	file=fopen(filename, "w+");//���������ļ�
//
//
//
//	printf("�������û�����");
//	char accountname[100];//д���û���
//	scanf("%s", accountname);
//	fprintf(file, "accountname:%s\n", accountname);
//	printf("���������룺");
//	int password;//д������
//	scanf("%d", &password);
//	fprintf(file, "password:%d\n", password);
//	printf("��������Ϸ�ǳƣ�");
//	char name[100];//д����Ϸ��
//	scanf("%s", name);
//	fprintf(file, "name:%s\n", name);
//	fprintf(file, "level:1\n");//д���ʼ�ȼ�
//	fprintf(file, "manpower:10000\n");//д���ʼ����
//	fprintf(file, "ammunition:10000\n");//д���ʼ��ҩ
//	fprintf(file, "pation:10000\n");//д���ʼ����
//	fprintf(file, "part:10000\n");//д���ʼ���
//	printf("ע��ɹ���\n");
//	fclose(file);
//}

//int login()
//{
//	FILE* file;
//	printf("�������û�����");
//	char laccountname[100];//�Ӽ���������û���
//	char filename[20];
//	char temp[100];//�ļ��ж�ȡ���û���
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
//			char* value = colon + 1; // ָ��ð�ź�һ���ַ�  
//			// ȥ�����з�  
//			value[strcspn(value, "\n")] = '\0'; // �滻���з�Ϊ������
//			//printf("��ȡ���ַ����ǣ�%s\n", value);
//			if (strcmp(laccountname, value) == 0)
//			{
//				printf("���������룺");
//				int lcode;//�������������
//				int tempcode;//���ļ���ȡ������
//				scanf("%d", &lcode);
//				fscanf(file, "password:%d", &tempcode);
//				if (tempcode == lcode)
//				{
//					printf("��¼�ɹ���\n");
//					fclose(file);
//					return 1;
//				}
//				else
//				{
//					printf("�������\n");
//					return 0;
//				}
//			}
//			else
//			{
//				if (i == sign)
//				{
//					printf("δ�ҵ����˻�\n");
//					return 0;
//				}
//				
//			}
//		}
//		
//	}
//	printf("���������룺");
//}