#pragma once
#ifndef PROFILE_H  
#define PROFILE_H  
typedef struct profile
{
	char accontname[100];
	char code[20];
	char name[100];
	int level;
	int manpower; //人力
	int ammunition; //弹药
	int pation; //口粮
	int part; //零件
	struct profile* next;
} Profile;

#endif