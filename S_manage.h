#ifndef S_MANAGE_H
#define S_MANAGE_H

#include <stdio.h>

extern FILE* S_fp;	//学生文件
extern FILE* T_fp;	//教师文件
extern FILE* A_fp; //校长文件



void init_system(void);     //初始化
void start_system(void);    //运行
void end_system(void);      //保存结束

#endif//S_MANAGE_H
