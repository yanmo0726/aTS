#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include "admin.h"
#include "menu.h"

static char id[13] = "20000000";

//	修改自己密码
void modify_M_pwd(void)
{
	char old_pwd[7] = {};	//	原密码
	char new_pwd[7] = {};	//	新密码
	char new_two_pwd[7] = {};	//	第二次输入的新密码
	printf("请输入原密码:");
	pwd_hide(8,old_pwd);	//	隐藏密码
	printf("\n");
	printf("请输入新密码:");
	for(;;)	//	死循环，直到输入的密码符合要求为止
	{
		pwd_hide(8,new_pwd);	//	隐藏密码
		printf("\n");
		if(6>=strlen(new_pwd)&&3<=strlen(new_pwd))	//	限制密码为3~6位
		{
			if(0 == strcmp(admin[A_num-1].A_pwd, new_pwd))	//	输入的新密码与原密码相同，需要重新输入
			{
				printf("新旧密码相同，请重新输入：(3~6 位):\n");
			}
			else
			{
				break;
			}
		}
		else
		{
			msg_show("密码不为3~6位，请重新输入\n",1.5);
		}
	}
	printf("\n");
	printf("请再次输入新密码:");
	for(;;)
	{
		pwd_hide(8,new_two_pwd);
		printf("\n");
		if(6>=strlen(new_two_pwd)&&3<=strlen(new_two_pwd))
		{
			if(0 == strcmp(old_pwd,admin[A_num-1].A_pwd))	//	判断输入的新密码和原密码是否相同
			{
				if(0 == strcmp(new_pwd,new_two_pwd))	//	判断两次输入的新密码是否相同
				{
					msg_show("密码修改成功!\n",1.5);
					if(0 == admin[A_num-1].first)	//	如果该帐号是第一次登录，修改完密码后将标识符first赋为1
					{
						admin[A_num-1].first = 1;
					}
					strcpy(admin[A_num-1].A_pwd,new_pwd);	//	将原密码修改为新密码
				}
				else
				{
					printf("两次密码输入不一致!\n");
				}
			}
			else
			{
				printf("原密码输入错误!\n");
			}
			break;
		}
		else
		{
			msg_show("密码不为3~6位，请重新输入\n",1.5);
		}
	}
	printf("\n");
}

//	重置教师密码
void modify_T_pwd(void)
{
	char key[20] = { "000000" };
	printf("请输入老师的工号:");
	limit(10,key);//限制工号输入长度，防止误触输入使Tea.id[]越界
	printf("\n");
	for (int i = 0; i < MAX; i++)//遍历数组查找所需修改教师位置
	{
		if (tea[i].sex && 0 == strcmp(key, tea[i].id))
		{
			strcpy(tea[i].pwd, "000000");
			tea[i].count = 0;		//教师登录错误次数清零
			msg_show("修改成功\n", 1.5);
			return;
		}
		if (199 == i)
		{
			msg_show("没找到，修改失败!\n", 1.5);
		}
	}
}

//	添加教师
void T_add(void)
{
	int i = 0;
	while (tea[i].sex)  
	{
		i++;
	}
	printf("请输入新老师的姓名\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	for(;;)	//限制姓名输入长度
	{
		if(-1 == limit_input(20,tea[i].name))
		{
			msg_show("输入格式有误!\n",1.5);	
			return;			
		}
		else
		{
			break;
		}
	}
	printf("请输入新老师的性别\n");
	//scanf("%c",&tea[i].sex);
	limit(3,&tea[i].sex);	//限制性别输入长度，只能输入一位
	strcpy(tea[i].pwd, "000000");//密码初始化
	strcpy(tea[i].id,int_to_string(atoi(id)+i+1));
	tea[i].flag = 1;
	tea[i].count = 0;
	tea[i].first = 0;

	msg_show("添加成功!\n", 1.5);
	T_num++;//数据库中教师信息个数
}

//	删除教师
void T_del(void)
{
	char key[20] = {};
	printf("请输入老师的工号:");
	limit(10,key);//限制工号输入长度，防止误触输入使Tea.id[]越界
	printf("\n");
	for (int i = 0; i < MAX; i++)//遍历数组查找所需修改教师位置
	{
		if (tea[i].sex && 0 == strcmp(key, tea[i].id))
		{
			tea[i].flag = 0;//离职标志位置0,表示已离职

			msg_show("删除成功\n", 1.5);
			return;
		}
		if (199 == i)
		{
			msg_show("没找到，删除失败!\n", 1.5);
		}
	}
}

//	显示所有在职教师信息
void T_A_show(void)
{
	for (int i = 0; i < T_num; i++)
	{
		if (0 != tea[i].sex)//遍历Tea.sex
		{
			if (1== tea[i].flag)//判断离职标志位信息
			{
				printf("%s %s %s\n", tea[i].name, 'w'==tea[i].sex?"女":"男", tea[i].id);
			}
		}
		else
		{
			break;
		}
	}

	anykey_continue();
}

//	显示所有在职教师信息
void T_L_show(void)
{
	for (int i = 0; i < T_num; i++)
	{
		if (0 != tea[i].sex)//遍历Tea.sex
		{
			if (0 == tea[i].flag)//判断离职标志位信息
			{
				printf("%s %s %s\n", tea[i].name, 'w'==tea[i].sex?"女":"男", tea[i].id);
			}
		}
		else
		{
			break;
		}
	}

	anykey_continue();
}

//	解锁教师帐号
void Unlock_T_account(void)
{
	char key[20] = {};
	printf("请输入老师的工号:");
	limit(15,key);
	printf("\n");
	for (int i = 0; i < T_num; i++)//遍历数组查找解锁教师位置
	{
		if (tea[i].sex && 0 == strcmp(key, tea[i].id))
		{
			if(3 == tea[i].count)
			{
				tea[i].count = 0;//登录错误次数清0
				msg_show("解锁成功\n", 1.5);
			}
			else
			{
				msg_show("当前老师帐号未锁定\n",1.5);
			}
			return;
		}
		if (199 == i)
		{
			msg_show("没找到，解锁失败!\n", 1.5);
		}
	}
}
