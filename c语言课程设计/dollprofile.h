#pragma once
#ifndef PROFILE_H  
#define PROFILE_H  

typedef struct dollprofile
{
	int id; //编号
	char name[100];
	int level; //人物等级
	int blood; //血量
	int attack; //伤害
	int speed; //攻速
	int penetration; //穿透力
	int defense; //防御力
	long manpower; //消耗的人力
	long ammunition; //消耗的弹药
	long pation; //消耗的口粮
	long part; //单次维修消耗的零件
} DollProfile;

DollProfile HK416 = { 1,"HK416",1,620,54,77,60,0,100,100,100,100 };
DollProfile SCARH = { 2,"SCAR-H",1,425,114,41,80,0,100,100,100,100 };
DollProfile RPK16 = { 3,"RPK-16",1,825,85,129,70,0,200,200,200,150 };
DollProfile AA12 = { 4,"AA12",1,1345,30,39,30,70,200,200,200,150 };
DollProfile RO635 = { 5,"RO635",1,1000,34,85,50,0,100,100,100,100 };




#endif