#include <stdio.h>
#include <getch.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "menu.h"

Student* stu_tp;
int temp=0;


void find(void)
{
	stu_tp=calloc(sizeof(Student),MAX);		//申请临时堆内存
	
	memcpy(stu_tp,stu,sizeof(Student)*MAX);		//创建副本
	
	for(;;)
	{
		system("clear");
		puts("-----请选择科目------");		//选择科目
		puts("	1、语文");
		puts("	2、数学");
		puts("	3、英语");	
		puts("	4、返回");
		puts("---------------------");
		switch(getch())
		{	
			case '1':printf("语文成绩:\n");
			S_report_Ch();		//查询成绩
			break;
			case '2':printf("数学成绩:\n");
			S_report_Math();
			break;
			case '3':printf("英语成绩:\n");
			S_report_Eng();
			break;
			case '4':free(stu_tp);return;
		}
	}
}

//	语文成绩处理函数
void S_report_Ch(void)
{	
	Student tp={};
	double sum=0;
	int rank=1;
	int L_num=0;
	for(int i=0;i<S_num-1;i++)
		{			
			for(int j=i+1;j<S_num;j++)
			{	
							
				if(stu_tp[i].Chinese<stu_tp[j].Chinese)		//对成绩降序比较
				{
					tp=stu_tp[i];
					stu_tp[i]=stu_tp[j];		//交换
					stu_tp[j]=tp;
										
				}
			}
		}
	
	for(int i=0;i<S_num;i++)
	{
		if(1==stu_tp[i].flag)		//从在校学生中对比
		{
			printf("%.2lf\n",stu_tp[i].Chinese);
			if(stu[temp].Chinese<stu_tp[i].Chinese)		//成绩对比，比人分数低则加1
			{								
				rank++;		//排名
			}	
		}
		else
		{
			L_num++;		//离校学生数量
		}		
	}
	printf("排名:%d 成绩:%.2lf\n",rank,stu[temp].Chinese);
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)		//在校学生成绩总和
		{						
			sum+=stu_tp[i].Chinese;//获取总分			
		}
	}	
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)		//在校学生最高分
		{	
			printf("最高分:%lf\n",stu_tp[i].Chinese);
			break;
		}
	}
	
	for	(int i=S_num-1;i>=0;i--)
	{
		if(1==stu_tp[i].flag)		//在校学生最低分
		{
			printf("最低分:%lf\n",stu_tp[i].Chinese);
			break;
		}
	}
	printf("平均分:%.2lf\n",sum/(S_num-L_num));		//总分除人数
	anykey_continue();	
}

//	数学成绩处理函数
void S_report_Math(void)
{
	Student tp;	
	double sum=0;
	int rank=1;
	int L_num=0;
	for(int i=0;i<S_num-1;i++)
		{			
			for(int j=i+1;j<S_num;j++)
			{	
			if(1==stu_tp[i].flag)
			{				
				if(stu_tp[i].Math<stu_tp[j].Math)	//对成绩降序比较
				{
					tp=stu_tp[i];
					stu_tp[i]=stu_tp[j];	//交换结构体
					stu_tp[j]=tp;
										
				}
			}
			}
		}
	for(int i=0;i<S_num;i++)
	{
		if(1==stu_tp[i].flag)
		{
		printf("%.2lf\n",stu_tp[i].Math);		
		if(stu[temp].Math<stu_tp[i].Math)	//成绩对比
		{								
			rank++;//排名
		}	
		}
		else
		{
			L_num++;
		}		
	}
	printf("排名:%d 成绩:%.2lf\n",rank,stu[temp].Math);
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)
		{					
			sum+=stu_tp[i].Math;//获取总分			
		}
	}	
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)
		{	
			printf("最高分:%lf\n",stu_tp[i].Math);
			break;
		}
	}		
	for	(int i=S_num-1;i>=0;i--)
	{
		if(1==stu_tp[i].flag)
		{
			printf("最低分:%lf\n",stu_tp[i].Math);
			break;
		}
	}
	printf("平均分:%.2lf\n",sum/(S_num-L_num));
	anykey_continue();		
}

//	英语成绩处理函数
void S_report_Eng(void)
{
	Student tp;
	double sum=0;
	int rank=1;
	int L_num=0;
	for(int i=0;i<S_num-1;i++)
		{			
			for(int j=i+1;j<S_num;j++)
			{					
				if(stu_tp[i].English<stu_tp[j].English)//对成绩降序比较
				{
					tp=stu_tp[i];
					stu_tp[i]=stu_tp[j];//交换
					stu_tp[j]=tp;
										
				}
			}
		}
	for(int i=0;i<S_num;i++)
	{
		if(1==stu_tp[i].flag)
		{
		printf("%.2lf\n",stu_tp[i].English);		
		if(stu[temp].English<stu_tp[i].English)	//成绩对比
		{								
		rank++;//排名
		}	
		}
		else
		{	
			L_num++;
		}		
	}
	printf("排名:%d 成绩:%.2lf\n",rank,stu[temp].English);
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)
		{					
			sum+=stu_tp[i].English;	//获取总分		
		}
	}
	for(int i=0;i<S_num;i++)
	{	
		if(1==stu_tp[i].flag)
		{			
			printf("最高分:%lf\n",stu_tp[i].English);	
			break;
		}
	}
	for	(int i=S_num-1;i>=0;i--)
	{
		if(1==stu_tp[i].flag)
		{
			printf("最低分:%lf\n",stu_tp[i].English);
			break;
		}
	}
	printf("平均分:%.2lf\n",sum/(S_num-L_num));
	anykey_continue();		
}

//	修改密码
void S_modify_pwd(void)
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
			if(0 == strcmp(stu[temp].pwd, new_pwd))	//	输入的新密码与原密码相同，需要重新输入
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
			if(0 == strcmp(old_pwd,stu[temp].pwd))	//	判断输入的新密码和原密码是否相同
			{
				if(0 == strcmp(new_pwd,new_two_pwd))	//	判断两次输入的新密码是否相同
				{
					msg_show("密码修改成功!\n",1.5);
					if(0 == stu[temp].first)	//	如果该帐号是第一次登录，修改完密码后将标识符first赋为1
					{
						stu[temp].first = 1;
					}
					strcpy(stu[temp].pwd,new_pwd);	//	将原密码修改为新密码
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
	
	anykey_continue();
}
void show(void)
{
	printf("姓名:%s 性别:%s 学号:%s 语文:%.2lf 数学:%.2lf 英语:%.2lf\n",stu[temp].name,'w'==stu[temp].sex?"女":"男",stu[temp].id,stu[temp].Chinese,stu[temp].Math,stu[temp].English);//展示个人信息
	anykey_continue();
}


