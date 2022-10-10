#include <stdio.h>
#include <stdlib.h>
#include "S_manage.h"
#include "menu.h"

	Student* stu;
 	Teacher* tea;
	Admin* admin;
	int S_num=0;//学生数量初始化
	int T_num=0;//老师数量初始化
	int A_num=0;//校长数量初始化
	
	char get_ret[MAX];//用于传递返回值
	
	FILE* S_fp;	//学生文件
	FILE* T_fp;	//教师文件
	FILE* A_fp; //校长文件

void init_system(void)
{
	FILE* S_fp = fopen("S_At.txt","r");//打开学生只读文件
	if(NULL == S_fp)
	{
		perror("fopen");
		return;
	}
	
	FILE* T_fp = fopen("T_atjob.txt","r");//打开老师只读文件
	if(NULL == T_fp)
	{
		perror("fopen");
		return;
	}
	
	FILE* A_fp = fopen("admin.txt","r");//打开校长只读文件
	if(NULL == A_fp)
	{
		perror("fopen");
		return;
	}
	
	tea = calloc(sizeof(Teacher),MAX);//申请老师堆内存
	stu = calloc(sizeof(Student),MAX);//申请学生堆内存
	admin = calloc(sizeof(Admin),MAX);//申请校长堆内存

	//遍历教师文件
	while(-1!=fscanf(T_fp, "%s %c %s %s %hhd %hhd %hhd",
		tea[T_num].name, &tea[T_num].sex,tea[T_num].id, tea[T_num].pwd,&tea[T_num].first,&tea[T_num].count,&tea[T_num].flag))
	{
		printf("%s\n",tea[T_num].name);
        T_num++;
	}
	printf("%d\n",T_num);
	
	fclose(T_fp);//关闭老师文件
	
	//遍历学生文件
	while(-1!=fscanf(S_fp, "%s %c %s %s %lf %lf %lf %hhd %hhd %hhd",stu[S_num].name, &stu[S_num].sex,stu[S_num].id, stu[S_num].pwd,&stu[S_num].Chinese,&stu[S_num].Math,&stu[S_num].English,&stu[S_num].first,&stu[S_num].count,&stu[S_num].flag))
	{
		S_num++;
	}
	fclose(S_fp);//关闭学生文件
	
	//遍历校长文件	
	while(-1!=fscanf(A_fp,"%s %s %hhd",admin[A_num].name,admin[A_num].A_pwd,&admin[A_num].first))
	{
		A_num++;
		
	}
	printf("%d\n",A_num);
	fclose(A_fp);//关闭校长文件
}
void start_system(void)
{
	for(;;)
	{
		switch(menu())
		{
			case '1':if(A_login(admin))//判断登录
				{
					A_option();//校长菜单选项
				}	
				
			break;
			case '2':if(T_login(tea))//判断登录
				{
					T_option();//老师菜单选项
				}
			break;
			case '3':if(S_login(stu))//判断登录
				{
					S_option();//学生菜单选项
				}
			break;
			case 'q':return;
		}
	}
}
void end_system(void)
{
	T_fp = fopen("T_atjob.txt","w");//打开老师只写文件
	if(NULL == T_fp)
	{
		perror("fopen");
		return;
	}
	for(int i=0;i<T_num;i++)//把教师信息打印的文件中
	{
		fprintf(T_fp, "%s %c %s %s %hhd %hhd %hhd\n",
        tea[i].name, tea[i].sex,tea[i].id, tea[i].pwd,tea[i].first,tea[i].count,tea[i].flag);
	}
	fclose(T_fp);
	tea=NULL;
	
	S_fp = fopen("S_At.txt","w");//打开学生只写文件
	if(NULL == S_fp)
	{
		perror("fopen");
		return;
	}
	for(int i=0;i<S_num;i++)//把学生信息打印的文件中
	{
		 if(0!=stu[i].sex)
		 {
		 	fprintf(S_fp, "%s %c %s %s %lf %lf %lf %hhd %hhd %hhd\n",stu[i].name, stu[i].sex,stu[i].id, stu[i].pwd,stu[i].Chinese,stu[i].Math,stu[i].English,stu[i].first,stu[i].count,stu[i].flag);
		 }
	}
	fclose(S_fp);
	stu=NULL;
	
	A_fp = fopen("admin.txt","w");//打开校长只写文件
	if(NULL == A_fp)
	{
		perror("fopen");
		return;
	}
	for(int i=0;i<A_num;i++)//把校长信息打印的文件中
	{
		fprintf(A_fp, "%s %s %hhd\n",admin[i].name,admin[i].A_pwd,admin[i].first);
        
	}
	fclose(A_fp);
	admin=NULL;
//	printf("-------------S------%d-------------------\n",S);
	
	free(stu);//释放堆内存
	free(tea);//释放堆内存
	free(admin);//释放堆内存
	
}








