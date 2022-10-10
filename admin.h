#ifndef ADMIN_H
#define ADMIN_H

void modify_M_pwd(void);   		//重置自己密码
void modify_T_pwd(void);   		//重置老师密码
void T_add(void);          		//添加老师
void T_del(void);          		//删除老师
void T_A_show(void);       		//显示所有在职教师
void T_L_show(void);       		//显示所有离职教师
void Unlock_T_account(void); 	//解锁教师帐号

#endif//ADMIN_H
