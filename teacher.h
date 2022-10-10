#ifndef TEACHER_H
#define TEACHER_H

extern int pos;
extern char str[100];


void S_add(void);  		     	//添加学生
void S_del(void);       		//删除学生
void S_find(void);      		//查找学生
void S_modify(void);    		//修改学生信息
void enter_S_grades(void);  	//录入学生成绩
void modify_S_pwd(void);    	//重置学生密码并解锁
void show_At(void);        		//显示所有在校学生信息
void show_leave(void);     		//显示所有退出学生信息
void T_modify_pwd(void);    	//修改老师自己密码
void Unlock_S_account(void);	//解锁学生帐号

#endif//TEACHER_H
