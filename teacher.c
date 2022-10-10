#include <stdio.h>
#include <string.h>
#include <getch.h>
#include <unistd.h>
#include <stdlib.h>
#include "teacher.h"
#include "menu.h"

int pos = 0,z = 0;
static char id[13] = "100000";
char str[100];
//	添加学生
void S_add(void)
{
	char name[2000];
	char sex;
	char choice;	//	添加选项
	char filename[20];	//	需要批量导入的文件名

	printf("添加学生\n");
	printf("1.单个添加 2.批量导入\n");
	scanf("%c",&choice);
	if('1' == choice)	//	单个添加
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		printf("请输入要添加的学生姓名：");
		for(;;)	//	限制姓名输入长度
		{
			if(-1 == limit_input(20,name))
			{
				msg_show("输入格式有误!\n",1.5);	
				return;			
			}
			else
			{
				break;
			}
		}
		printf("请输入学生性别(w/m)：");
		//scanf(" %c",&sex);
		limit(3,&sex);	//	限制性别输入长度
		int pos = -1;	//	插入的位置
		for(int i=0; i<MAX;i++)
		{
			if('\0' == stu[i].sex && -1 == pos)	//	sex为空值则说明有位置可存入
			{
				pos = i;	//	提取下标值并进行初始值的替换
				stu[pos].flag = 1;	//	
				strcpy(stu[pos].name,name);
				stu[pos].sex = sex;
				strcpy(stu[pos].id,int_to_string(atoi(id)+i+1));	//	将学号从字符串转换为数值再自增
				strcpy(stu[pos].pwd,"000000");	//	赋初始密码
				msg_show("添加成功!\n",1.5);
				S_num++;
				break;
			}
		}
	}
	else if('2' == choice) // 批量导入
    {
        printf("请输入要导入的文件名:");
        limit(21,filename);
        printf("\n");
        FILE *sfrp = fopen(filename, "r");
        if (NULL == sfrp)
        {
            msg_show("文件打开失败\n",1.5);
            return;
        }
        for (z = S_num; z < MAX; z++)
        {
            fscanf(sfrp, "%s %c %s %s %lf %lf %lf %hhd %hhd %hhd", stu[z].name, &stu[z].sex, stu[z].id, stu[z].pwd, &stu[z].Chinese, &stu[z].Math, &stu[z].English, &stu[z].first, &stu[z].count, &stu[z].flag);
            for (int i = 0; i < z; i++)
            {
                if (0 == strcmp(stu[i].id, stu[z].id))
                {
                    continue;
                }
            }
            strcpy(stu[z].id,int_to_string(atoi(id)+z+1));
        }
        fclose(sfrp);
        msg_show("导入成功!\n", 1.5);
    }
    else
	{
		msg_show("输入的选项不合法，请重新输入\n",1.5);
	}
}

//	删除学生
void S_del(void)
{
	char id[13] = {};	//	用来存储输入要删除的学生学号
	printf("删除学生\n");
	printf("请输入要删除的学生学号：");
	limit(15,id);
	printf("\n");
	for(int i=0; i<MAX; i++)
	{
		if(0 == strcmp(id,stu[i].id))	//	以学号来查找是否找到该学生
		{
			stu[i].flag = 0;
			msg_show("删除成功!\n",1.5);
			break;
		}
		if(MAX-1 == i)
		{
			msg_show("查无此学号!\n",1.5);
		}
	}
	
}

//	查找学生
void S_find(void)
{
	char id[13] = {};	//	用来存储输入要查找的学生学号
	printf("查找学生\n");
	printf("请输入要查找的学生学号:");
	limit(15,id);
	printf("\n");
	for(int i=0; i<MAX; i++)
	{
		if(0 == strcmp(id,stu[i].id))	//	用学号来查找是否找到该学生
		{
			printf("姓名：%s 性别：%s 学号：%s 语文：%.2lf 数学：%.2lf 英语：%.2lf\n",stu[i].name,'w'==stu[i].sex?"女":"男",stu[i].id,stu[i].Chinese,stu[i].Math,stu[i].English);
			break;
		}
		else if(MAX-1 == i)
		{
			printf("查无此学号!\n");
		}
	}
	anykey_continue();
}

//	修改学生信息
void S_modify(void)
{
	char id[13] = {};	//	用来存储输入要修改信息的学生学号
	printf("修改学生信息\n");
	printf("请输入要修改的学生学号:");
	limit(15,id);
	printf("\n");
	for(int i=0; i<MAX; i++)
	{
		if(0 == strcmp(id,stu[i].id))	// 	以学号来查找是否找到该学生
		{
			
			printf("原信息：姓名：%s 性别：%s\n",stu[i].name,'w'==stu[i].sex?"女":"男");
			printf("请输入新的信息,（姓名，性别(w/m)）:");
			for(;;)	//	死循环，直到输入的学号合法为止
			{
				scanf("%s %c",stu[i].name,&stu[i].sex);
				if(strlen(stu[i].name)<=20)
				{
					break;
				}
				else
				{
					printf("姓名输入不合法，请重新输入\n");
				}
			}
			
			msg_show("信息修改成功!\n",1.5);
			break;
		}
		else if(MAX-1 == i)
		{
			printf("查无此学号!");
		}
	}
}
//	录入学生成绩
void enter_S_grades(void)
{
	char id[13] = {};	//	用来存储输入要录入成绩的学生学号
	char choice;
	char filename[MAX];

	Student* std;
	std = calloc(sizeof(Student),MAX);	//	申请临时std堆内存
	
	printf("录入学生成绩\n");
	printf("1、单个录入 2、批量录入\n");
	scanf("%c",&choice);
	if('1' == choice)
	{
		printf("请输入要录入的学生学号:");
		limit(15,id);
		printf("\n");
		for(int i=0; i<MAX; i++)
		{
			if(0 == strcmp(id,stu[i].id))	//	以学号查找是否找到该学生
			{
				char Chinese[MAX] = {};
				char Math[MAX] = {};
				char English[MAX] = {};
				int count = 0;	//	用count来做标识符，只要语文数学英语成绩中，有一个成绩输入不合法，count就加一
				
				printf("原信息：语文：%.2lf 数学：%.2lf 英语：%.2lf\n",stu[i].Chinese,stu[i].Math,stu[i].English);
				printf("请输入新的语文成绩:");
				scanf("%s",Chinese);
				for(int i=0; i<strlen(Chinese); i++)
				{
					if(strlen(Chinese)<=3 && '0' <= Chinese[i] && '9' >= Chinese[i])
					{
						break;
					}
					else
					{
						count++;
					}
				}
				if(0 != count)
				{
					printf("输入成绩不合法,将改为为0\n");
					count = 0;
				}
				printf("请输入新的数学成绩:");
				scanf("%s",Math);
				for(int i=0; i<strlen(Math); i++)
				{
					if(strlen(Math)<=3 && '0' <= Math[i] && '9' >= Math[i])
					{
						break;
					}
					else
					{
						count++;
					}
				}
				if(0 != count)
				{
					printf("输入成绩不合法,将改为为0\n");
					count = 0;
				}
				printf("请输入新的英语成绩:");
				scanf("%s",English);
				for(int i=0; i<strlen(English); i++)
				{
					if(strlen(English)<=3 && '0' <= English[i] && '9' >= English[i])
					{
						break;
					}
					else
					{
						count++;
					}
				}
				if(0 != count)
				{
					printf("输入成绩不合法,将改为为0\n");
					count = 0;
				}
				
				stu[i].Chinese = atoi(Chinese);	//	录入语文新成绩
				stu[i].Math = atoi(Math);	//	录入数学新成绩
				stu[i].English = atoi(English);	//	录入英语新成绩
				msg_show("信息修改成功!\n",1.5);
				break;
			}
			else if(MAX-1 == i)
			{
				msg_show("查无此学号!\n",1.5);
			}
		}
	}
	else if('2' == choice)
	{
		printf("请输入要录入的文件名:");
		limit(21,filename);
		printf("\n");
		FILE* sfrp = fopen(filename,"r");
		if(NULL == sfrp)
		{
			msg_show("文件打开失败\n",1.5);
			return;
		}
		for(int i=0; i<MAX; i++)
		{
			fscanf(sfrp,"%s %lf %lf %lf",std[i].id,&std[i].Chinese,&std[i].Math,&std[i].English);
		}
		fclose(sfrp);
		for(int i=0; i<MAX; i++)	//	拿着学号去原数据中找到该学生，并覆盖修改他的语数英成绩
		{
			for(int j=0; j<MAX; j++)
			{
				if(0 == strcmp(stu[j].id,std[i].id))
				{
					 stu[j].Chinese = std[i].Chinese;
					 stu[j].Math = std[i].Math;
					 stu[j].English = std[i].English;
				}
			}
		}
		msg_show("录入成功!\n",1.5);
	}
	else
	{
		msg_show("输入的选项不合法，请重新输入\n",1.5);
	}
	free(std);
}

//	重置学生密码
void modify_S_pwd(void)
{
	char id[13] = {};	//	用来存储输入要重置的学生学号
	char pwd[7] = "000000";	//	默认初始密码为000000
	printf("重置密码\n");
	printf("请输入要重置的学生学号：");
	limit(15,id);
	printf("\n");
	for(int i=0; i<MAX; i++)
	{
		if(0 == strcmp(stu[i].id,id))	//	以学号是否相同来找到文件中该学生的信息
		{
			stu[i].flag = 1;	//	若学生为退学状态，则变更为在校状态
			stu[i].count = 0;	//	实现解锁功能
			strcpy(stu[i].pwd,pwd);	//	将学生密码重置初始密码
			msg_show("重置成功!\n",1.5);
			break;
		}
		if(MAX-1 == i)	//	遍历结束后，显示查无此学号
		{
			msg_show("查无此学号!\n",1.5);
		}
	}
}

//	显示所有在校学生的信息
void show_At(void)
{
	printf("显示所有在校学生");
	for(int i=0; i<MAX; i++)
	{
		if('\0' != stu[i].sex)	//	判断是否有空位
		{
			if(1 == stu[i].flag)	//	flag=1 在校
			{
				printf("\n姓名：%s 性别：%s 学号：%s 语文：%.2lf 数学：%.2lf 英语：%.2lf",stu[i].name,'w'==stu[i].sex?"女":"男",stu[i].id,stu[i].Chinese,stu[i].Math,stu[i].English);
			}
		}
		else
		{
			break;
		}
	}
	printf("\n");
	anykey_continue();
}

//	显示所有退学学生的信息
void show_leave(void)
{
	printf("显示所有退学学生");
	for(int i=0; i<MAX; i++)
	{
		if('\0' != stu[i].sex)	//	判断是否有空位
		{
			if(0 == stu[i].flag)	//	flag=0 退学
			{
				printf("\n姓名：%s 性别：%s 学号：%s 语文：%.2lf 数学：%.2lf 英语：%.2lf",stu[i].name,'w'==stu[i].sex?"女":"男",stu[i].id,stu[i].Chinese,stu[i].Math,stu[i].English);
			}
		}
		else
		{
			break;
		}
	}
	printf("\n");
	anykey_continue();
}

//	修改老师自己的密码
void T_modify_pwd(void)
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
			if(0 == strcmp(tea[pos].pwd, new_pwd))	//	输入的新密码与原密码相同，需要重新输入
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
			if(0 == strcmp(old_pwd,tea[pos].pwd))	//	判断输入的新密码和原密码是否相同
			{
				if(0 == strcmp(new_pwd,new_two_pwd))	//	判断两次输入的新密码是否相同
				{
					msg_show("密码修改成功!\n",1.5);
					if(0 == tea[pos].first)	//	如果该帐号是第一次登录，修改完密码后将标识符first赋为1
					{
						tea[pos].first = 1;
					}
					strcpy(tea[pos].pwd,new_pwd);	//	将原密码修改为新密码
				}
				else
				{
					msg_show("两次密码输入不一致!\n",1.5);
				}
			}
			else
			{
				msg_show("原密码输入错误!\n",1.5);
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

//	解锁学生帐号
void Unlock_S_account(void)
{
	char id[13] = {};	//	用来存储输入要解锁的学生学号
	printf("解锁学生帐号\n");
	printf("请输入要解锁的学生学号：");
	limit(15,id);
	printf("\n");
	for(int i=0; i<MAX; i++)
	{
		if(0 == strcmp(stu[i].id,id))	//	以学号是否相同来找到文件中该学生的信息
		{
			stu[i].count = 0;	//	实现解锁功能
			msg_show("解锁成功!\n",1.5);
			break;
		}
		if(MAX-1 == i)	//	遍历结束后，显示查无此学号
		{
			msg_show("查无此学号!\n",1.5);
		}
	}
}


