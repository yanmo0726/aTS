#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>

#define MAX 256

typedef struct Student
{
	char name[20];
	char sex;
	char id[13];
	char pwd[7];
	double Chinese;
	double Math;
	double English;
	char first; //是否初次登录
	char count;	//密码输入次数
	char flag;	//是否在校
}Student;

typedef struct Teacher
{
	char name[20];
	char sex;
	char id[13];
	char pwd[7];
	char first; //是否初次登录
	char count;	//密码输入次数
	char flag;	//是否在校
}Teacher;

typedef struct Admin
{
	char name[20];
	char A_pwd[7];
	char first;
}Admin;

extern Student* stu;
extern Teacher* tea;
extern Admin* admin;

extern int S_num;	//学生人数
extern int T_num;	//老师人数
extern int A_num;	//校长人数

extern char get_ret[MAX];	//用于传递返回值

void limit(int num,char secret[]);				//限制输入长度
int limit_input(int len,char* str);				//限制中文输入长度
void pwd_hide(int len,char *pwd);				//隐藏密码
void msg_show(const char *msg, float sec);		//提示信息
void anykey_continue(void);						//按任意键继续
char *int_to_string(int num);					//整型转字符串
bool T_login(void* p);					//老师登录
bool S_login(void* p);					//学生登录
bool A_login(void* p);					//校长登录
char* encrypt(char* str);		//加密
char* decrypt(char* str);		//解密
int menu(void);     //主菜单
int S_menu(void);   //学生菜单
int T_menu(void);   //老师菜单
int A_menu(void);   //校长菜单
void A_option(void);//校长菜单选项
void T_option(void);//老师菜单选项
void S_option(void);//学生菜单选项

#endif//MENU_H

