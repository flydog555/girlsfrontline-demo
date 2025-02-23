#pragma once
#ifndef PROFILE_H  
#define PROFILE_H  

typedef struct dollprofile
{
	int id; //���
	char name[100];
	int level; //����ȼ�
	int blood; //Ѫ��
	int attack; //�˺�
	int speed; //����
	int penetration; //��͸��
	int defense; //������
	long manpower; //���ĵ�����
	long ammunition; //���ĵĵ�ҩ
	long pation; //���ĵĿ���
	long part; //����ά�����ĵ����
} DollProfile;

DollProfile HK416 = { 1,"HK416",1,620,54,77,60,0,100,100,100,100 };
DollProfile SCARH = { 2,"SCAR-H",1,425,114,41,80,0,100,100,100,100 };
DollProfile RPK16 = { 3,"RPK-16",1,825,85,129,70,0,200,200,200,150 };
DollProfile AA12 = { 4,"AA12",1,1345,30,39,30,70,200,200,200,150 };
DollProfile RO635 = { 5,"RO635",1,1000,34,85,50,0,100,100,100,100 };




#endif