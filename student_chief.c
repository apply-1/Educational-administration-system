#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_chief.h"
#include "student_tools.h"
#include "chief.h"
#include "tools.h"

//快排降序函数依据
static int compare(const void *a,const void *b)
{
	return *(double*)b-*(double*)a;
}

//显示成绩
void show_grade(void)
{
	int count=count_student();	//在校学生数量
	printf("名次|语 文   名次|数 学   名次|英 语   名次|总 分\n");
	//存放各科成绩的数组变量
	double chinese[MAX_STUDENT]={};
	double math[MAX_STUDENT]={};
	double english[MAX_STUDENT]={};
	double toal_score[MAX_STUDENT]={};
	//将成绩放到数组内
	for(int i=0,j=0;i<Ret_stu_in-1 && j<count;i++)
	{
		if(Stu_in[i].sex == 'm' || Stu_in[i].sex == 'w')	//判断此人是否存在
		{
			chinese[j]=Stu_in[i].chinese;
			math[j]=Stu_in[i].math;
			english[j]=Stu_in[i].english;
			toal_score[j]=Stu_in[i].chinese+Stu_in[i].math+Stu_in[i].english;
			j++;
		}	
	}
	//降序排序
	qsort(chinese,count,8,compare);
	qsort(math,count,8,compare);
	qsort(english,count,8,compare);
	qsort(toal_score,count,8,compare);
	//显示排名
	for(int i=1;i<=count;i++)
	{
		printf("%4d|%5.1lf   %4d|%5.1lf   %4d|%5.1lf   %4d|%5.1lf\n",	
					i,chinese[i-1],i,math[i-1],i,english[i-1],i,toal_score[i-1]);
	}
	printf("\n");
	//存放各科分数总和的变量
	double sum_chinese=0,sum_math=0,sum_english=0,sum_toal_score=0;
	//存放自己的排名
	int my_chinese=0,my_math=0,my_english=0,my_toal_score=0;
	//显示自己的名次
	for(int i=1;i<=count;i++)
	{
		//计算总和，用来计算平均数
		sum_chinese+=chinese[i-1];
		sum_math+=math[i-1];
		sum_english+=english[i-1];
		sum_toal_score+=toal_score[i-1];
		//计算该学生各科排名
		if(chinese[i-1] == Stu_in[Stu_index].chinese)	//语文
		{
			if(my_chinese==0)
			{
				my_chinese=i;
			}
		}
		if(math[i-1] == Stu_in[Stu_index].math)	//数学
		{
			if(my_math==0)
			{
				my_math=i;
			}
		}
		if(english[i-1] == Stu_in[Stu_index].english)//英语
		{
			if(my_english==0)
			{
				my_english=i;
			}
		}
		if(toal_score[i-1] == Stu_in[Stu_index].chinese+Stu_in[Stu_index].math+
					Stu_in[Stu_index].english)		//总分
		{
			if(my_toal_score==0)
			{
				my_toal_score=i;
			}
		}
	}
	//打印数据	
	printf("你当前的排名为：语文：%d  数学：%d  英语：%d  总分：%d\n\n",
							my_chinese,my_math,my_english,my_toal_score);
	printf("平均分：语文：%5.1lf  数学：%5.1lf  英语：%5.1lf  总分：%5.1lf\n",
				sum_chinese/count,sum_math/count,sum_english/count,sum_toal_score/count);
	printf("最高分：语文：%5.1lf  数学：%5.1lf  英语：%5.1lf  总分：%5.1lf\n",
		chinese[0],math[0],english[0],toal_score[0]);
	printf("最低分：语文：%5.1lf  数学：%5.1lf  英语：%5.1lf  总分：%5.1lf\n",
		chinese[count-1],math[count-1],english[count-1],toal_score[count-1]);
	anykey_continue();
}

//修改密码
void change_password(void)
{
	//定义存放密码的两个数组
	char password[20]={};
	printf("请输入你的密码：");
	secrecy(password);		//加密并输入密码到password这个数组中
	//判断输入密码是否是否与原密码正确
	if(strcmp(Stu_in[Stu_index].password,password))	
	{
		printf("密码不正确\n");
		anykey_continue();	//按任意键继续
		return;
	}
	if(judge_password(password))	//输入并判断两次密码是否一致
	{	
		strcpy(Stu_in[Stu_index].password,password);	//将新密码拷贝到该学生结构体中
		msg_show("修改成功！",1.5);
	}
	else
	{
		msg_show("两次密码不一致",1.5);
	}
}

//查看个人信息
void look_information(void)
{
	//显示数据
	printf("姓名：%s\n性别：%c\n学号：%d\n语文：%.1lf\n数学：%.1lf\n英语：%.1lf\n",
						Stu_in[Stu_index].name,Stu_in[Stu_index].sex,
						Stu_in[Stu_index].no,Stu_in[Stu_index].chinese,
						Stu_in[Stu_index].math,Stu_in[Stu_index].english);
	anykey_continue();	//按任意键继续
}
