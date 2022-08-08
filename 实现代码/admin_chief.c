#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include "chief.h"
#include "tools.h"
#include "admin_chief.h"


void reset_me(void)	//重置校长密码
{
	printf("按y确认，按n返回！\n");	//再次输入 确认重置密码
	printf("请输入操作:");
	char ret=getch();
	printf("%c\n",ret);		//获取键盘输入
	if(ret=='y')
	{
		strcpy(Admin_password,"123456");	//将字符串123456作为默认密码赋给密码
		msg_show("重置成功!",1.5);
	}
}

void reset_t(void)	//重置教师密码
{
	int no=0;		//存储教师工号
	for(;;)		//输入要查找老师的工号
	{
		printf("请输入要重置的教师工号:");
		if(!judge_no(&no))
		{
			if(choose()=='0')
			{
				return;
			}
			continue;
		}
		break;
	}			
	for(int i = 0;i < Ret_tea_in-1;i++) 		  //遍历在校老师
	{
		if(no == Tea_in[i].no && (Tea_in[i].sex == 'm' ||Tea_in[i].sex == 'w'))	 //按照工号查找，且性别是男或女
		{
			strcpy(Tea_in[i].password,"123456"); //重置密码
			Tea_in[i].state=0;
			msg_show("重置成功！\n",1.5);      		//显示成功信息
			return; 	//最后退出函数
		}
		else
		{
			printf("查无此人\n"); 	//循环到底后还没有查找，显示找不到
		}
		anykey_continue();
		return;
	}
}


void add_tch(void) //添加教师信息
{
	int i = 0;
	if(MAX_TEACHER <= Ret_tea_in) 			//判断在职教师是否满员
	{
		printf("教师满人\n");
		anykey_continue();		//满员就退出
		return;
	}
	while(Tea_in[i].sex == 'm' || Tea_in[i].sex == 'w')	//按性别找空行，空行有两种，一种是被删除，一种是原本就是空
	{ 
		i++;	
	}
	char sex[5]={};		//定义一个字符数组给用户输入性别
	char name[21]={};
	for(;;)
	{
		printf("请输入教师姓名:");		//输入新教师信息
		my_fgets(name,21);  
		printf("请输入性别(男/女):");
		my_fgets(sex,5);
		if((strcmp(sex,"男") && strcmp(sex,"女")) || strlen(name)>18)//对输入判断是否合规，不行重新输入
		{
			printf("输入不规范\n");
			if(choose()=='0')
			{
				return;
			}
			printf("请重新输入：");
			continue;
		}
		else
		{
			Tea_in[i].sex=(strcmp(sex,"男")==0)?'m':'w';
			break;
		}
	}
	if(Tea_in[i].no==0)		//判断该行在下面还是在中间
	{
		Ret_tea_in++;
	}
	strcpy(Tea_in[i].password,"123456");         //初始化密码
	Tea_in[i].state=0;							//帐号状态限制归零
	strcpy(Tea_in[i].name,name);				
	Tea_in[i].no=*Now_teacher_no;                //分配工号
	(*Now_teacher_no)++;				//自动生成新的工号
	msg_show("添加成功!",1.5);			//显示添加成功
}

void del_tch(void) //删除教师信息
{
	int key=0;	//用来存储教师工号
	int i = 0;
	for(;;)
	{
		printf("请输入要删的教师的工号：\n");
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
	for(i=0;i < Ret_tea_in-1;i++) //循环 
	{
		if(key == Tea_in[i].no && '0'!= Tea_in[i].sex)//通过工号找到教师，性别判断教师是否存在
		{
			for(int j=0;j < MAX_TEACHER;j++)//在离职表增加一条信息
			{
				if(Tea_out[j].sex == 0)//找到一行空行，添加离职信息，添加成功后离开这一层循环
				{
					strcpy(Tea_out[j].name ,Tea_in[i].name);		//在离职表添加姓名，性别，工号，密码等信息
					Tea_out[j].sex = Tea_in[i].sex;
					Tea_out[j].no=Tea_in[i].no;
					strcpy(Tea_out[j].password,Tea_in[i].password);
					break;
				}
			}
			Tea_in[i].sex = '0';//员工性别归零
			Ret_tea_out++;
			msg_show("删除成功！\n",1.5);			//显示成功信息
			return ;            //退出外层循环
		}
	}
	if(i>=Ret_tea_in-1)
	{
		msg_show("查无此人！\n",1.5);
	}
}

void show_tch(void)				//显示所有在职教师
{
	printf("入职名单\n");
	for(int i=0;i < Ret_tea_in-1;i++) 			//由于删除操作时只删除了性别，所以要循环教师表每一行
	{
		if(Tea_in[i].sex == 'm' || Tea_in[i].sex == 'w')	//判断性别是否为空，为空跳到下一行
		{
			printf("%d %s %s\n",Tea_in[i].no ,Tea_in[i].name ,Tea_in[i].sex=='m'?"男":"女");
		}
	}
	anykey_continue();				//循环结束 信息在终端显示 暂停展示，按任意键退出
}

void show_lev(void)				//显示离职
{
	printf("离职名单是\n");
	int i = 0;
	while(Tea_out[i].sex == 'm' || Tea_out[i].sex == 'w')	//判断性别是否为空，为空跳到下一行
	{
		printf("%d %s %s\n",Tea_out[i].no,Tea_out[i].name,Tea_out[i].sex=='m'?"男":"女");
		i++;
	}
	anykey_continue();				//循环结束 信息在终端显示 暂停展示，按任意键退出
}

void unlock(void)		//解锁某一个教师帐号
{
	int key=0;
	printf("请输入要解锁的教师工号：\n");
	scanf("%d",&key);
	int i=0;
	for(i=0;i<Ret_tea_in-1;i++)
	{
		if(key == Tea_in[i].no)		//循环有内容的信息
		{
			if(Tea_out[i].sex== 'm' || Tea_out[i].sex == 'w')	//通过工号找到教师,且帐号被锁s=3
			{
				if(Tea_in[i].state==3)			//通过工号找到教师,且帐号被锁s=3
				{
					Tea_in[i].state= 0;
					msg_show("已解锁\n",1.5);			//密码锁归零
					return ;
				}
				else
				{
					msg_show("帐号没被锁定\n",1.5);
					return;
				}
			}
		}
	}
	if(i>=Ret_tea_in-1)
	{
		msg_show("查无此人\n",1.5);
		return;
	}
}
