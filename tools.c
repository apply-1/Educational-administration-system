#include <stdio.h>
#include <unistd.h>
#include <getch.h>
#include <stdlib.h>
#include <string.h>
#include "chief.h"

#include "tools.h"

//按0退出,按任意键继续
char choose (void)
{
	printf("按0退出,按任意键继续...\n");
   	stdin->_IO_read_ptr = stdin->_IO_read_end; 
   	char ret = getch();
   	return ret;
}

//打印提示信息
void msg_show(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}

//	按任意键继续
void anykey_continue(void)
{
	puts("按任意键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}

//输入密码且加密
void secrecy(char* password)
{
	int i=0;
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	for(i=0;;)
	{
		password[i]=getch();
		if(password[i]==10)		//回车
		{
			break;
		}
		else if(password[i]==127)	//删除
		{
			if(i>0)
			{
				putchar('\b');     //退格
           	 	putchar(' ');      //赋为空
            	putchar('\b');	   //再次退格，将空格盖住		
				i--;
			}
		}
		else
		{
			if(i<=11)
			{
				printf("*");
				i++;
			}	
		}	
	}
	password[i]='\0';
	printf("\n");
	return ;
}

bool judge_password(char* password) //判断两次密码是否一致
{
	//定义存放密码的两个数组
	char password2[20]={};
	printf("请输入你要设置的新密码：");
	for(;;)
	{
		secrecy(password);		//加密并输入密码到password这个数组中
		//判断输入的密码是否符合规范
		if(strcmp(password,"123456")==0 || strlen(password)>=13 || strlen(password)<3)	
		{
			printf("输入密码不规范，请重新输入：");
			continue;
		}
		else
		{
			break;
		}
	}
	printf("请再次确认：");
	secrecy(password2);		//加密并输入密码到password2这个数组中
	//判断两次密码是否一致
	if(strcmp(password,password2)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//输入字符串并将末尾的\n变为\0
void my_fgets(char* str,int size)	
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	fgets(str,size,stdin); 
	str[strlen(str)-1]='\0';	//将\n置为\0 
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

bool judge_no(int* no)	//判断no输入是否合法
{
	char no_str[9]={};		//输入学号	
  	my_fgets(no_str,9);      //输入8位
  	*no=atoi(no_str);        //转为整形     
  	int temp=*no;
  	int temp_len=0;
  	while(temp)      //计算学号有几位
  	{
  		temp=temp/10;
  		temp_len++;
  	}
  	if(temp_len!=strlen(no_str))
  	{
  		printf("帐号输入不合法！\n");
  		return false;
  	}
  	return true;
}

//验证密码是否正确
bool verify_password(char* true_password,char* password)
{
	//判断密码是否正确
	if(strcmp(true_password,password)==0)
	{
		if(strcmp(password,"123456")==0)	//判断是否为初始密码
		{
			printf("由于你是第一次登录，请修改密码：");
			for(;;)
			{
				if(judge_password(password))
				{	
					strcpy(true_password,password);	//将新密码拷贝到该学生结构体中
					msg_show("修改成功！\n",1.5);
					return true;
				}
				else
				{
					printf("两次密码不一致,请重新输入:");
    			}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

//加密解密密码
void encryption(char key)
{
	for(int i=0;i<Ret_stu_in-1;i++)
	{
		for(int j=0;j<12;j++)
		{
			Stu_in[i].password[j]+=key;
		}
		Stu_in[i].password[12]='\0';
	}
	
	for(int i=0;i<Ret_tea_in-1;i++)
	{
		for(int j=0;j<12;j++)
		{
			Tea_in[i].password[j]+=key;
		}
		Tea_in[i].password[12]='\0';
	}
	
	for(int i=0;i<12;i++)
	{
		Admin_password[i]+=key;
	}
	Admin_password[12]='\0';
}
