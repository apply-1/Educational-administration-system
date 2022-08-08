#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>
#include "teacher_tools.h"
#include "tools.h"
#include "chief.h"

int Tea_index=0;

char menu_teacher(void)
{
	system("clear");
	puts("**********教师系统**********");
	puts("1、添加学生");
	puts("2、删除学生");
	puts("3、查找学生");
	puts("4、修改学生信息");
	puts("5、录入学生成绩");
	puts("6、重置学生密码");
	puts("7、显示所有在校学生信息");
	puts("8、显示所有退出学生信息");
	puts("9、解锁学生帐号");
	puts("a、修改密码");
	puts("0、返回主界面");
	puts("**************************");
	printf("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);		//	回显
	return cmd;
}


bool Determine_password(void)   //判断密码
{
 	char password[20]={};		//输入的密码
 	int account=0;
	for(;;)
	{ 
		int i=0;
		printf("请输入:\n帐号：");	
		if(!judge_no(&account))
		{
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}
  		//判断帐号是否在文件中
  		for(i=0;i<Ret_tea_in-1;i++)
  		{
   			if(Tea_in[i].no==account && (Tea_in[i].sex=='m'||Tea_in[i].sex=='w'))		//帐号正确且学生存在
   			{
    			break;
   			}
  		}
  		if(i>=Ret_tea_in-1)		//遍历完没有正确帐号或学生不存在
  		{
   			printf("查无此人\n");
   			if(choose()=='0')
			{
				return false;
			}
			continue;
  		}
  		//判断该帐号是否被锁定
  		if(Tea_in[i].state>=3)		//判断是否会被锁
  		{
   			printf("该帐号已被锁定，请找校长进行恢复\n");
			if(choose()=='0')
			{
				return false;
			}
			continue;
  		}
  		printf("请输入密码：");
		secrecy(password);	//加密输入密码
		//判断密码是否正确
		if(verify_password(Tea_in[i].password,password))
		{
			Tea_index=i;
			Tea_in[i].state=0;
			msg_show("登录成功\n",1.5);
			return true;
		}
		else
		{
			printf("输入密码错误！！\n");
			Tea_in[i].state++;	//输入错误次数
			if(choose()=='0')
			{
				return false;
			}
			continue;
		}	
 	}
}

void change_msg(void)	//修改学生基础信息
{
	int key=0;       //存学号
		for(;;)
		{
			printf("请输入学号:");
			if(!judge_no(&key))
			{
				if(choose()=='0')
				{
					return;
				}
				continue;
			}
			break;
		}
		for(int i=0;i<Ret_stu_in-1;i++)       //遍历找学号
		{	
			
			if(Stu_in[i].no==key && Stu_in[i].sex!='0')
			{
				for(;;)
				{
					char name[21]={},sex[5]={};
					printf("请输入要修改的学生信息\n姓名:");
					my_fgets(name,21);
					printf("性别:\n");
					my_fgets(sex,5);
					if(strcmp(sex,"男")||strcmp(sex,"女"))     //判断输入格式是否有误
					{
						printf("输入不规范，请重新输入：");
						if(choose()=='0')
						{
							return;
						}
						continue;
					}
					else
					{
						strcpy(Stu_in[i].name,name);
						Stu_in[i].sex=strcmp(sex,"男")?'m':'w';
						return;
					}
				}									
          	}
		}
		printf("未找到该学生\n");
		anykey_continue();
}
