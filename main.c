#include <stdio.h>
#include "S_manage.h"

int main(int argc,const char* argv[])
{
	init_system();     //初始化,打开文件
	start_system();    //运行
	end_system();      //保存结束
}
