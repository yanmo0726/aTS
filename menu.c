#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include "menu.h"
#include "admin.h"
#include "student.h"
#include "teacher.h"

//	限制输入长度
void limit(int num,char get_ret[]) 
{
	int cnt=0;
	char ch=0;//暂存
	while(ch != 10)
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存
		ch=getch();
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存
		get_ret[cnt++] = ch;
		if(ch == 10)
		{
			break;
		}
		else if(ch == 127 && cnt>=2)//退格
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			cnt-=2;
		}
		else if(ch==127)//仅输入退格键时
		{
			cnt--;
		}
		else if(cnt==num-1)
		{
			cnt--;
			continue;
		}
		else
		{
			printf("%c",ch);//打印
		}
	}
	cnt--;
	get_ret[cnt] = '\0';//添加\0结束
}

int limit_input(int len,char* str)
{
	int i=0;
	for(i=0; i<len; i++)
	{
		str[i]=getchar();
		if(str[i] == ' ' || str[i] == '\n')
		{
			str[i]='\0';
			break;
		}
	}
	if(i == len)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

//	整型转字符串
char *int_to_string(int num)
{
 	int cnt=0,y=0;
 	char temp[13];
 	while(num)
 	{
     	temp[cnt++]=num%10+'0';  
     	num/=10;        
 	}
    temp[cnt]='\0';
  	cnt=cnt-1;
  	while(cnt>=0)
  	{
    	str[y++]=temp[cnt--];   
    }
 	str[y]='\0';
 	             
 	return str;
}

//	隐藏密码
void pwd_hide(int len,char *pwd)
{
	int cnt=0;
	char ch=0;
	while(ch != 10)
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存
		ch=getch();
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存
		pwd[cnt++] = ch;
		if(ch == 10)
		{
			break;
		}
		else if(ch == 127 && cnt>=2)//退格
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			cnt-=2;
		}
		else if(ch==127)//仅输入退格键时
		{
			cnt--;
		}
		else if(cnt==len-1)
		{
			cnt--;
			continue;
		}
		else
		{
			putchar('*');//打印*号
		}
	}
	cnt--;
	pwd[cnt] = '\0';
}

//	加密
char* encrypt(char* str)
{
	int i=0;
	for(i=0;i<strlen(str);i++)
	{
		get_ret[i]=str[i]+i;
	}
	get_ret[i]='\0';
	return get_ret;
}

//	解密
char* decrypt(char* str)
{
	int i=0;
	for(i=0;i<strlen(str);i++)
	{
		get_ret[i]=str[i]-i;
	}
	get_ret[i]='\0';
	return get_ret;
}

void msg_show(const char* msg,float sec)
{
	//	提示信息
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}

//	输入任意键继续
void anykey_continue(void)
{
	puts("请输入任意键继续....");
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存
	getch();
}

bool T_login(void* p)					//老师登录
{
	Teacher *t1 = p; //定义教师结构指针t1指向教师结构指针tea
    Teacher t2;      //定义临时教师结构t2
    printf("请输入工号！！\n");
    limit(12, t2.id);
    printf("\n");
    for (int i = 0; i < T_num; i++)
    {
        while (t1[i].flag) //判断是否在职
        {
            if (strcmp(t1[i].id, t2.id) == 0) //判断帐号是否相同
            {
                if (3 == t1[i].count)
                {
                    msg_show("此用户名锁定，请找上级重置密码！！\n", 1.5);
                    return false;
                }
                printf("请输入密码(3~6)！！\n");
                do
                {
                    for (;;)
                    {
                        pwd_hide(8, t2.pwd);
                        printf("\n");
                        if (6 >= strlen(t2.pwd) && 3 <= strlen(t2.pwd)) //判断密码长度
                        {
                            break;
                        }
                        else
                        {
                            printf("密码不为3~6位，请重新输入\n");
                        }
                    }
                    if (strcmp(t1[i].pwd, t2.pwd) == 0) //判断密码是否相同
                    {
                        t1[i].count = 0;
                        pos = i;
                        if (0 == tea[pos].first) //是否首次登录
                        {
                            printf("首次登录，请修改密码(3~6)！\n");
                            T_modify_pwd();
                        }
                        return true;
                    }
                    else
                    {
                        printf("密码不正确!请重新输入密码(3~6)！！\n");
                        t1[i].count++;
                        if (3 == t1[i].count)
                        {
                            msg_show("三次密码错误，请找上级重置密码！！\n", 1.5);

                            return false;
                        }
                    }
                } while (strcmp(t1[i].pwd, t2.pwd) != 0); //密码输入不对，就继续循环
            }
            break; //结束循环
        }
    }
    msg_show("此用户名离职或者不存在，请重新选择服务\n", 1.5);
    return false;
}

bool S_login(void* p)					//学生登录
{
	Student *t1 = p; //定义学生结构指针t1指向学生结构指针stu
    Student t2;      //定义临时学生结构t2
    printf("请输入学号！！\n");
    limit(12, t2.id);
    printf("\n");
    
    for (int i = 0; i < S_num; i++)
    {
        while (t1[i].flag) //判断是否在学
        {
            if (strcmp(t1[i].id, t2.id) == 0) //判断学号是否相同
            {
                if (3 == t1[i].count)
                {
                    msg_show("此用户名锁定，请找老师重置密码！！\n", 1.5);
                    return false;
                }
                printf("请输入密码(3~6)！！\n");
                do
                {
                    for (;;)
                    {
                        pwd_hide(8, t2.pwd);
                        printf("\n");
                        if (6 >= strlen(t2.pwd) && 3 <= strlen(t2.pwd)) //判断密码长度
                        {
                            break;
                        }
                        else
                        {
                            printf("密码不为3~6位，请重新输入\n");
                        }
                    }
                    if (strcmp(t1[i].pwd, t2.pwd) == 0) //判断密码是否相同
                    {
                        t1[i].count = 0;
                        temp = i;

                        if (0 == stu[temp].first) //是否首次登录
                        {
                            printf("首次登录，请修改密码(3~6)！\n");
                            S_modify_pwd();
                            //stu[temp].first = 1;
                        }
                        return true;
                    }
                    else
                    {
                        printf("密码不正确!请重新输入密码(3~6)！！\n");
                        t1[i].count++;
                        if (3 == t1[i].count)
                        {
                            msg_show("三次密码错误，请找老师重置密码！！\n", 1.5);

                            return false;
                        }
                    }
                } while (strcmp(t1[i].pwd, t2.pwd) != 0); //密码输入不对，就继续循环
            }
            break; //退出循环
        }
    }
    msg_show("此用户名退学或者不存在，请重新选择服务\n", 1.5);
    return false;
}


bool A_login(void* p)
{
	Admin* t1=p;//定义校长结构指针t1指向校长结构指针admin
	Admin t2;//定义校长临时结构体
	printf("请输入用户！！\n");
	for (int i = 0; i < A_num; i++)
	{
		limit(10,t2.name);
		printf("\n");
		if (0==strcmp(t2.name,t1[i].name))//判断用户
        {
			printf("请输入密码(3~6)！！\n");
			do
			{
				for(;;)
				{
					pwd_hide(8,t2.A_pwd);
					printf("\n");
					if(6>=strlen(t2.A_pwd)&&3<=strlen(t2.A_pwd))//判断密码长度
					{
						break;
					}
					else
					{
						printf("密码不为3~6位，请重新输入\n");
					}
				}
				if (strcmp(t1[i].A_pwd, t2.A_pwd) == 0)//判断密码
				{
                    if(0==t1[i].first)
					{
						printf("首次登录，请修改密码(3~6)！\n");
						modify_M_pwd();//修改密码
						
					}
					return true;
				}
                else
                {
                    printf("密码不正确!请重新输入密码！！\n"); 
                }
			} while (strcmp(t1[i].A_pwd, t2.A_pwd) != 0);
        }
        break;
    }
	msg_show("此用户名不存在，请重新选择服务\n", 1.5);
	return false;
		
}

int menu(void)
{
	system("clear");
	puts("***欢迎使用猫大学生信息管理系统***");
	puts("\t1.校长登录");
	puts("\t2.教师登录");
	puts("\t3.学生登录");
	puts("\tq.退出程序");
	puts("**********************************");
	printf("*********请选择服务*********** ");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}

int S_menu(void)
{
	system("clear");
	puts("***********学生界面**************");
	puts("\t1.查询成绩");
	puts("\t2.修改密码");
	puts("\t3.查看个人信息");
	puts("\tq.退出程序");
	puts("*********************************");
	printf("*****请选择服务**************** ");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}

int T_menu(void)
{
	system("clear");
	puts("**********教师界面**********");
	puts("\t1.添加学生");
	puts("\t2.删除学生");
	puts("\t3.查找学生");
	puts("\t4.修改学生信息");
	puts("\t5.录入学生成绩");
	puts("\t6.重置学生密码");
	puts("\t7.显示所有在校学生信息");
	puts("\t8.显示所有退学学生信息");
	puts("\t9.修改自己的密码");
	puts("\t0.解锁学生帐号");
	puts("\tq.退出程序");
	puts("****************************");
	printf("*****请选择服务*********** ");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}

int A_menu(void)
{
	system("clear");
	puts("**********校长界面********");
	puts("\t1.重置自己密码");
	puts("\t2.重置教师密码");
	puts("\t3.添加教师");
	puts("\t4.删除教师");
	puts("\t5.显示所有在职教师");
	puts("\t6.显示所有离职教师");
	puts("\t7.解锁教师帐号");
	puts("\tq.退出程序");
	puts("**************************");
	printf("*****请选择服务*********** ");
	stdin->_IO_read_ptr = stdin->_IO_read_end; 
	char cmd = getch();
	printf("%c\n",cmd);
	return cmd;
}

void A_option(void)
{
	for(;;)
	{
		switch(A_menu())
		{
			case '1':modify_M_pwd();
			break;
			case '2':modify_T_pwd(); 
			break;
			case '3':T_add();
			break;
			case '4':T_del();
			break;
			case '5':T_A_show(); 
			break;
			case '6':T_L_show();
			break;
			case '7':Unlock_T_account();
			break;
			case 'q':return;
			}
	}
}
void T_option(void)
{
	for(;;)
    {
        switch (T_menu())
        {
        case '1':
            S_add();
            break;
        case '2':
            S_del();
            break;
        case '3':
            S_find();
            break;
        case '4':
            S_modify();
            break;
        case '5':
            enter_S_grades();
            break;
        case '6':
            modify_S_pwd();
            break;
        case '7':
            show_At();
            break;
        case '8':
            show_leave();
            break;
        case '9':
            T_modify_pwd();
            break;
        case '0':
            Unlock_S_account();
            break;
        case 'q':
            return;
        }
    }
}

void S_option(void)
{
	for(;;)
    {
        switch (S_menu())
        {
        case '1':
            find();
            break;
        case '2':
            S_modify_pwd();
            break;
        case '3':
            show();
            break;
        case 'q':
            return;
        }
    }
}

