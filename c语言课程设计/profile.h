#pragma once
#ifndef PROFILE_H  
#define PROFILE_H  
typedef struct profile
{
	char accontname[100];
	char code[20];
	char name[100];
	int level;
	int manpower; //����
	int ammunition; //��ҩ
	int pation; //����
	int part; //���
	struct profile* next;
} Profile;

#endif