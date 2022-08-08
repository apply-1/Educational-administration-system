#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include "chief.h"
#include "student_tools.h"
#include "tools.h"

int Stu_index=0; //记录当前学生的下标

//显示登录界面以及验证密码
bool land_student(void)
{
 	char password[20]={};		//输入的密码
 	int account=0;
	for(;;)
	{ 
		int i=0;	
  		for(;;)
		{
			printf("请输入:\n帐号：");
			if(!judge_no(&account))
			{
				if(choose()=='0')
				{
					return false;
				}
				continue;
			}
			break;
		}
		//判断帐号是否在文件中
		for(i=0;i<Ret_stu_in-1;i++)
		{
			if(Stu_in[i].no==account && (Stu_in[i].sex=='m' || Stu_in[i].sex=='w'))	//判断帐号是否正确并该学生是否存在
			{
				break;
			}
		}
		//判断是否存在该学生
		if(i>=Ret_stu_in-1)
		{
			printf("查无此人\n");
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}
		//判断该帐号是否被锁定
		if(Stu_in[i].state>=3)
		{
			printf("该帐号已被锁定，请找老师进行恢复\n");
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}
		printf("请输入密码：");
		secrecy(password);	//加密输入密码
		//判断密码是否正确
		if(verify_password(Stu_in[i].password,password))
		{
			Stu_index=i;
			Stu_in[i].state=0;
			msg_show("登录成功\n",1.5);
			return true;
		}
		else
		{
			printf("输入密码错误！！\n");
			Stu_in[i].state++;	//输入错误次数
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}	
	}
}

//显示学生界面菜单
int show_student_menu(void)
{
	system("clear");
	printf("*********学生系统**********\n");
	printf("1、查询成绩\n");
	printf("2、修改密码\n");
	printf("3、查看个人信息\n");
	printf("0、退回主界面\n");
	printf("**************************\n");
	printf("请输入指令:");
	char cmd=getch();
	printf("%c\n",cmd);		//回显
	return cmd;
}

//计算在校学生总人数
int count_student(void)
{
	int count=0;
	for(int i=0;i<Ret_stu_in-1;i++)
	{
		if(Stu_in[i].sex!='0')	//判断该学生是否在校
		{
			count++;
		}
	}
	return count;
}
