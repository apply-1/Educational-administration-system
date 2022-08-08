#include <stdio.h>
#include "chief.h"

int main(int argc,const char* argv[])
{
	//将文件中的数据导入到变量中，初始化数据
	if(!init_program())  //为假说明文件打开不正常
	{
		return 1;
	}
	//开始程序
	start_program();
	//结束程序
	end_program();
}
