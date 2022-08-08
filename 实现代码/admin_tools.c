#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getch.h>
#include "chief.h"
#include "tools.h"
#include "admin_tools.h"


//登录界面
int menu(void)
{
	system ("clear");
	printf("**********校长系统**********\n");
	printf("1.重置自己密码\n");
	printf("2.重置教师密码\n");
	printf("3.添加教师\n");
	printf("4.删除教师\n");
	printf("5.显示所有在职教师\n");
	printf("6.显示所有离职教师\n");
	printf("7.解锁教师账号\n");
	printf("0.返回主界面\n");
	printf("**************************\n");
	printf("请输入操作:");
	char cmd = getch();
	printf("%c \n",cmd);
	return cmd;
}

//密码界面并判断
bool acont_in(void)
{
	char account[8] = {},password[20]={};
	for(;;)
	{
		printf("请输入帐号：");
		my_fgets(account,8);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		if(strcmp(account,"admin") == 0) //判断帐号
		{
			printf("请输入密码：");
			secrecy(password);
			if(verify_password(Admin_password,password))
			{
				msg_show("登录成功\n",1.5);
				return true;
			}
			else
			{
				printf("输入密码错误！！\n");
				if(choose()=='0')
				{
					return false;
				}
				continue;
			}
		}	
		else	//帐号不一致
		{
			printf("帐号错误\n");
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}
	}
}
