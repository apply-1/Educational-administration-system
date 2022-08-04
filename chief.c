#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include "chief.h"
#include "student.h"
#include "tools.h"
#include "admin.h"
#include "teacher.h"


//定义全局结构体指针变量
Teacher* Tea_in=NULL;
Teacher* Tea_out=NULL;
Student* Stu_in=NULL;
Student* Stu_out=NULL;

int Ret_stu_in;		//在校生文件总人数
int Ret_stu_out;	//离校生文件总人数
int Ret_tea_in;		//在校老师文件总人数
int Ret_tea_out;	//离校老师文件总人数

int* Now_teacher_no=NULL;	//存储老师工号的变量
int* Now_student_no=NULL;	//存储学生学号的变量
char* Admin_password=NULL;	//存储校长密码的变量

//显示界面
static int show_table(void)
{
	system("clear");
	printf("******欢迎使用教务系统******\n");
	printf("请选择你的登录身份\n");
	printf("**************************\n");
	printf("1、学生\n");
	printf("2、老师\n");
	printf("3、校长\n");
	printf("0、退出程序\n");
	printf("**************************\n");
	printf("请输入指令:");
	char cmd=getch();
	printf("%c\n",cmd);		//回显
	return cmd;
}

//将文件中的数据导入到变量中，初始化数据
bool init_program(void)
{
	//以只读的方式打开文件
	FILE* fp_admin=fopen("admin.txt","r");
	FILE* fp_stu_in=fopen("stu_in.txt","r");
	FILE* fp_stu_out=fopen("stu_out.txt","r");
	FILE* fp_tea_in=fopen("tea_in.txt","r");
	FILE* fp_tea_out=fopen("tea_out.txt","r");
	//判断是否成功打开文件
	if(fp_admin==NULL||fp_stu_in==NULL||fp_stu_out==NULL||fp_tea_in==NULL||fp_tea_out==NULL)
	{
		perror("__func__,fopen");
		return false;
	}
	//申请内存
	Now_teacher_no=malloc(4);
	Now_student_no=malloc(4);
	Admin_password=malloc(13);
	Stu_in=malloc(sizeof(Student)*MAX_STUDENT);
	Stu_out=malloc(sizeof(Student)*MAX_STUDENT);
	Tea_in=malloc(sizeof(Teacher)*MAX_TEACHER);
	Tea_out=malloc(sizeof(Teacher)*MAX_TEACHER);
	//从文件中读取数据并写入
	fscanf(fp_admin,"%d%d%s",Now_teacher_no,Now_student_no,Admin_password);
	int ret=1;
	//读取在校学生信息到内存中
	while(ret>0)	
	{
		ret=fscanf(fp_stu_in,"%s %c %d %s %hhd %lf %lf %lf\n",
						Stu_in[Ret_stu_in].name,&Stu_in[Ret_stu_in].sex,
						&Stu_in[Ret_stu_in].no,Stu_in[Ret_stu_in].password,
						&Stu_in[Ret_stu_in].state,&Stu_in[Ret_stu_in].chinese,
						&Stu_in[Ret_stu_in].math,&Stu_in[Ret_stu_in].english);
		Ret_stu_in++;
	}
	//读取离校学生信息到内存中
	ret=1;
	while(ret>0)	
	{
		ret=fscanf(fp_stu_out,"%s %c %d %s %hhd %lf %lf %lf\n",
						Stu_out[Ret_stu_out].name,&Stu_out[Ret_stu_out].sex,
						&Stu_out[Ret_stu_out].no,Stu_out[Ret_stu_out].password,
						&Stu_out[Ret_stu_out].state,&Stu_out[Ret_stu_out].chinese,
						&Stu_out[Ret_stu_out].math,&Stu_out[Ret_stu_out].english);
		Ret_stu_out++;
	}
	//读取在职老师信息到内存中
	ret=1;
	while(ret>0)	
	{
		ret=fscanf(fp_tea_in,"%s %c %d %s %hhd\n",
						Tea_in[Ret_tea_in].name,&Tea_in[Ret_tea_in].sex,
						&Tea_in[Ret_tea_in].no,Tea_in[Ret_tea_in].password,
						&Tea_in[Ret_tea_in].state);
		Ret_tea_in++;
	}
	//读取离职老师信息到内存中
	ret=1;
	while(ret>0)	
	{
		ret=fscanf(fp_tea_out,"%s %c %d %s %hhd\n",
						Tea_out[Ret_tea_out].name,&Tea_out[Ret_tea_out].sex,
						&Tea_out[Ret_tea_out].no,Tea_out[Ret_tea_out].password,
						&Tea_out[Ret_tea_out].state);
		Ret_tea_out++;
	}
	
	encryption(-8); //解密
						
	//关闭文件，并将文件指针置空
	fclose(fp_tea_out);
	fclose(fp_tea_in);
	fclose(fp_stu_in);
	fclose(fp_stu_out);
	fp_tea_out=NULL;
	fp_tea_in=NULL;
	fp_stu_in=NULL;
	fp_stu_out=NULL;
	return true;
}

//开始程序
void start_program(void)
{
	for(;;)	//死循环进入界面
	{
		switch(show_table())	//界面显示并接收键值
		{
			case '1':
				student();	//学生端
				break;
			case '2':
				teacher();	//教师端
				break;
			case '3':
				admin();	//校长端
				break;
			case '0':		//退出循环
				return;
		}
	}
}

//结束程序
void end_program(void)
{
	encryption(8);	//加密
	//以只写的方式打开文件
	FILE* fp_stu_in=fopen("stu_in.txt","w");
	FILE* fp_stu_out=fopen("stu_out.txt","w");
	FILE* fp_tea_in=fopen("tea_in.txt","w");
	FILE* fp_tea_out=fopen("tea_out.txt","w");
	FILE* fp_admin=fopen("admin.txt","w");
	//判断是否成功打开文件
	if(fp_admin==NULL||fp_stu_in==NULL||fp_stu_out==NULL||fp_tea_in==NULL||fp_tea_out==NULL)
	{
		perror("__func__,fopen");
		return;
	}
	//将全局变量中的数据写入文件中
	fprintf(fp_admin,"%d %d %s",*Now_teacher_no,*Now_student_no,Admin_password);
	//将在校学生信息写入文件中
	for(int i=0;i<Ret_stu_in-1;i++)
	{
		fprintf(fp_stu_in,"%s %c %d %s %hhd %lf %lf %lf\n",
						Stu_in[i].name,Stu_in[i].sex,
						Stu_in[i].no,Stu_in[i].password,
						Stu_in[i].state,Stu_in[i].chinese,
						Stu_in[i].math,Stu_in[i].english);
	}
	//将离校学生信息学入文件中
	for(int i=0;i<Ret_stu_out-1;i++)	
	{
		fprintf(fp_stu_out,"%s %c %d %s %hhd %lf %lf %lf\n",
						Stu_out[i].name,Stu_out[i].sex,
						Stu_out[i].no,Stu_out[i].password,
						Stu_out[i].state,Stu_out[i].chinese,
						Stu_out[i].math,Stu_out[i].english);
	}
	//将在校老师信息写入文件中
	for(int i=0;i<Ret_tea_in-1;i++)
	{
		fprintf(fp_tea_in,"%s %c %d %s %hhd\n",
						Tea_in[i].name,Tea_in[i].sex,
						Tea_in[i].no,Tea_in[i].password,
						Tea_in[i].state);
	}
	//将离校老师信息写入文件中
	for(int i=0;i<Ret_tea_out-1;i++)	
	{
		fprintf(fp_tea_out,"%s %c %d %s %hhd\n",
						Tea_out[i].name,Tea_out[i].sex,
						Tea_out[i].no,Tea_out[i].password,
						Tea_out[i].state);
	}
	//关闭文件，并将文件指针置空
	fclose(fp_tea_out);
	fclose(fp_tea_in);
	fclose(fp_stu_in);
	fclose(fp_stu_out);
	fp_tea_out=NULL;
	fp_tea_in=NULL;
	fp_stu_in=NULL;
	fp_stu_out=NULL;
}
