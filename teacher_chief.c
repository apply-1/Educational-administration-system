#include <stdio.h>
#include <string.h>
#include <getch.h>
#include <stdlib.h>
#include "teacher_chief.h"
#include "teacher_tools.h"
#include "chief.h"
#include "tools.h"


void add_stu_single(void)   //单个添加学生
{   
	char sex[5]={};
	char name[21]={};
 	for(int i=0;i<MAX_STUDENT;i++)               //遍历所有人           
 	{
 		if(Stu_in[i].sex!='m' && Stu_in[i].sex!='w')   //判断该位置是否可以添加
   		{
 			for(;;)
 		{
 			printf("请输入学生姓名:");
 			my_fgets(name,21);                  //输入字符串
    		printf("请输入学生性别(男/女):");
    		my_fgets(sex,5);                    //输入性别
    		if((strcmp(sex,"男") && strcmp(sex,"女"))||strlen(name)>18)    //判断输入是否为男或女   
			{
				printf("输入不规范\n");
				if(choose()=='0')	//按0退出
		 		{
					return;
				}
				printf("请重新输入：");
				continue;
			}
			else
			{
				strcpy(Stu_in[i].name,name);
				Stu_in[i].sex=(strcmp(sex,"男")==0)?'m':'w';      //男为m  女为w
				break;
			}
		}
			if(Stu_in[i].no==0)      //如果该位置学号为空，在校生加1
			{
				Ret_stu_in++;
			}
    		Stu_in[i].no=*Now_student_no;    //添加学号
    		strcpy(Stu_in[i].password,"123456");  //密码初始化
    		Stu_in[i].state=0;              //帐号状态初始化
    		Stu_in[i].chinese=0.0;          //语文成绩初始化
    	 	Stu_in[i].math=0.0;             //数学成绩初始化
    		Stu_in[i].english=0.0;          //英语成绩初始化
    		(*Now_student_no)++;            //学号加1
    		if(choose()=='0')
			{
				return;
			}
 		}
 	}
 }
 
void add_stu_batch(void)   //批量添加学生
{
 		
 	char f_name[30];              //用于存文件名
   	puts("请输入要导入文件文件名");
   	my_fgets(f_name,30);
   	FILE *fstu=fopen(f_name,"r");
   	if(NULL ==fstu)             //判断文件是否存在
  	{
   		msg_show("未找到该文件！！",1.5);
   		return ;
  	}
  	char name[MAX_STUDENT][20]={};       //存储录入文件的姓名
  	char sex[MAX_STUDENT][20]={};        //存储录入文件的性别
  	int con=1;                           //用于接收fscanf的返回值
  	int count=0;                         //记录录入人数
  	for(int i=0;i<MAX_STUDENT;i++)
  	{
		con=fscanf(fstu,"%s %s\n",name[i],sex[i]);
		if(con<=0)   //判断录入是否结束
		{
				break;
		}
		count++;
	}
	int msg_count=0;             //录入人数
	for(int i=0,j=0;i<MAX_STUDENT;i++)
	{
		if(Stu_in[i].sex!='m' && Stu_in[i].sex!='w')     //判断该位置是否有人或可以覆盖
		{
			if(Stu_in[i].no==0)                         //判断在校人数是否要加
			{
				Ret_stu_in++;                               //在校人数加一
			}
			msg_count++;
			strcpy(Stu_in[i].name,name[j]);                   //姓名
			Stu_in[i].sex=strcmp(sex[j],"男")==0?'m':'w';
			Stu_in[i].no=*Now_student_no;             //学号
  			Stu_in[i].state=0;                 //帐号状态
  			strcpy(Stu_in[i].password,"123456");  //初始化
			Stu_in[i].chinese=0;
  			Stu_in[i].math=0;
  			Stu_in[i].english=0;
  			(*Now_student_no)++;               //累计学生数加一（学号加一）
  			j++;
  		}
  		if(j>=count)       //判断添加是否结束
  		{
  			break;
  		}
  	}
	printf("共录入%d条记录!\n",msg_count);
	anykey_continue();
	fclose(fstu);        //释放内存
	fstu=NULL;           //置空
}
 
void add_stu(void)    //添加学生
{
	puts("选择添加模式：按1逐个添加，按2导入.按0退出");      
	char ret=getch();
	switch(ret)
	{
		case '1':add_stu_single();break;
		case '2':add_stu_batch();break;
		case '0':return;
	}
} 		

void delete_stu(void)   //删除学生
{
	int no=0,no1=0;       //输入的两次学号
 	for(;;)
 	{
 		printf("请输入要删除学生学号:");	
		if(!judge_no(&no))	//判断学号输入是否合法
		{
			if(choose()=='0')	//按0退出
			{
				return;
			}
			continue;
		}
		int i=0;
 		for(i=0;i<Ret_stu_in-1;i++)            //遍历找到要删除学生学号
 		{
  			if(no==Stu_in[i].no&&Stu_in[i].sex!='0')
  			{
  				for(;;)
  				{
  					printf("请再次确认学号：");
    				if(!judge_no(&no1))	//判断学号输入是否合法
					{
						if(choose()=='0')	//按0退出
						{
							return;
						}
						continue;
					}
					break;
				}
    			break;
  			}
 		}
    	if(i>=Ret_stu_in-1)                        //判断学生是否存在
    	{
     		printf("学生不存在!\n");
   			if(choose()=='0')	//按0退出
			{
				return;
			}
    	}
    	else 
    	{
    		break;
    	}
    } 
 	if(no==no1)         //判断两次输入是否相同，相同则将学生信息存到退学学生中
 	{
  		for(int i=0;i<Ret_stu_in-1;i++)
  		{
   			if(no==Stu_in[i].no&&Stu_in[i].sex!='0')
   			{   
    			for(int j=0;j<MAX_STUDENT;j++)
    			{
     				if(Stu_out[j].sex==0)
     				{
      					//msg_show("录入成功!\n",1.5);   
      					strcpy(Stu_out[j].name,Stu_in[i].name);       //转移信息
      					Stu_out[j].sex=Stu_in[i].sex;
      					Stu_out[j].no=Stu_in[i].no;     
      					strcpy(Stu_out[j].password,Stu_in[i].password);
      					Stu_out[j].state=Stu_in[i].state;
      					Stu_out[j].chinese=Stu_in[i].chinese;
      					Stu_out[j].math=Stu_in[i].math;
      					Stu_out[j].english=Stu_in[i].english;
      					Stu_in[i].sex='0';        //性别置0,表示该学生以删除，可以覆盖，不能读去
      					Ret_stu_out++;               //退学学生加一
      					msg_show("删除成功",1.5);
      					return;
    				 }
    			}
   			}
  		}
 	}
 	else
 	{
 		msg_show("两次输入不一致!\n",1.5);
 	}
}

void find_stu(void)    //查找学生
{
	char key[21];        //用于存姓名
	int count=0;         //用于存放找到次数，通过次数来判断是否存在
	puts("选择查找模式：按1姓名查找，按2学号查找");
	char ret=getch();
	if(ret=='1')
	{
		printf("请输入姓名:");
		my_fgets(key,21);
		for(int i=0;i<Ret_stu_in-1;i++)      //遍历寻找该姓名
		{	
			
			if(strstr(Stu_in[i].name,key))    //模糊查找
			{
				if(Stu_in[i].sex=='m' || Stu_in[i].sex=='w')          //判断是否存在
				{
					printf("姓名:%s  性别:%s  学号:%d  帐号状态:%s  语文:%.1lf  数学:%.1lf  英语:%.1lf    状态：在校\n",
						Stu_in[i].name,Stu_in[i].sex=='m'?"男":"女",
						Stu_in[i].no,
			            Stu_in[i].state>=3?"锁定":"正常",Stu_in[i].chinese,
						Stu_in[i].math,Stu_in[i].english);	
						count++;		//次数加一	
          		}
          	}
		}
		printf("--------------------------------------------------------------\n");
		for(int i=0;i<Ret_stu_out-1;i++)
		{
			if(strstr(Stu_out[i].name,key))    //模糊查找
			{
				if(Stu_out[i].sex=='m' || Stu_out[i].sex=='w')          //判断是否存在
				{
					printf("姓名:%s  性别:%s  学号:%d   状态：离校\n",
					Stu_out[i].name,Stu_out[i].sex=='m'?"男":"女",
					Stu_out[i].no);	
					count++;		//次数加一	
          		}
          	}
		}
		if(!count)    //没有找到
		{
			printf("未找到记录！！\n");
		}
		anykey_continue();
	}
	if(ret=='2')
	{
		int count=0;              //用于存放找到次数，通过次数来判断是否存在
		int key_num=0;              //存学号
		for(;;)
		{
			printf("请输入学号:");
			if(!judge_no(&key_num))     //判断学号是否合法  
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
			
			if(Stu_in[i].no==key_num)
			{
				if(Stu_in[i].sex=='m' || Stu_in[i].sex=='w')
				{
					printf("姓名:%s  性别:%s  学号:%d  帐号状态:%s  语文:%.1lf  数学:%.1lf  英语:%.1lf  状态:在校\n",
						Stu_in[i].name,Stu_in[i].sex=='m'?"男":"女",
						Stu_in[i].no,
			            Stu_in[i].state>=3?"锁定":"正常",Stu_in[i].chinese,
						Stu_in[i].math,Stu_in[i].english);
						count++;		
          		}
          	}
		}
		if(count==0)
		{
			for(int i=0;i<Ret_stu_out-1;i++)       //遍历找学号
			{	
				if(Stu_out[i].no==key_num)
				{
					if(Stu_out[i].sex=='m' || Stu_out[i].sex=='w')
					{
						printf("姓名:%s  性别:%s  学号:%d  状态:离校\n",
						Stu_out[i].name,Stu_out[i].sex=='m'?"男":"女",
						Stu_out[i].no);
						count++;		
          			}
          		}
			}
		}
		if(!count)      //没找到
		{
			printf("未找到记录！！");
		}
		anykey_continue();
	}
}

void shout_stu(void)    //修改学生信息
{
	puts("选择修改模式：按1修改学生基础信息，按2修改学生成绩");
	char ret = getch();
	if(ret=='1')
	{
		change_msg();		
	}
	if(ret=='2')
	{
		int key=0;       //学号
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
		for(int i=0;i<Ret_stu_in-1;i++)     //找学号
		{	
			if(Stu_in[i].no==key)
			{
				if(Stu_in[i].sex!='0')
				{
					double chinese,math,english;
					printf("请输入要修改的学生成绩:语文 数学 英语\n");
					//判断是否正确取到三个值，且三个值是否正确，不满足重新输入或退出
					while(scanf("%lf%lf%lf",&chinese,&math,&english)!=3 ||
							 chinese>100 || chinese<0 ||
							 math>100 || math<0 ||
							 english>100 || english<0)
					{
						getch();
						puts("输入非法内容\n");
  						if(choose()=='0')
						{
							return;
						}
     					else
     					{
     						printf("请重新输入该学生的语文 数学 英语:");
            				stdin->_IO_read_ptr = stdin->_IO_read_end;
            			} 
 					}
 					Stu_in[i].chinese=chinese;
 					Stu_in[i].math=math;
 					Stu_in[i].english=english;
					printf("修改成功\n");
					break;									
          		}
          	}
		}
		printf("未找到该学生\n");
		anykey_continue();
	}    
}

void input_stu_single(void)  //录入学生成绩
{	
	//定义局部的名字和学号
	char name1[21]={};		
	int no=0;
	for(;;)
	{
		int i=0,count=0;//用于循环遍历
		printf("输入学生姓名:");
		my_fgets(name1,21);
		for(;;)
		{
			printf("请输入学号:");
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
		for( i=0;i<Ret_stu_in-1;i++)
		{
			if(Stu_in[i].sex!='0'&&!strcmp(Stu_in[i].name,name1)&&Stu_in[i].no==no)//学号姓名相同且没被删除
			{
				double chinese,math,english;//接语数英成绩
				printf("输入学生成绩,语文 数学 英语:\n");
				//判断是否正确取到三个值，且三个值是否正确，不满足重新输入或退出
				while(scanf("%lf%lf%lf",&chinese,&math,&english)!=3 ||
						chinese>100 || chinese<0 ||
						math>100 || math<0 ||
						english>100 || english<0)
				{
					getch();
					puts("输入非法内容\n");
  					if(choose()=='0')
					{
						return;
					}
     				else
     				{
     					printf("请重新输入该学生的语文 数学 英语:");
            			stdin->_IO_read_ptr = stdin->_IO_read_end;
            		} 
 				}
 					//成功则赋值 					
				Stu_in[i].chinese=chinese;
				Stu_in[i].math=math;
				Stu_in[i].english=english;
				printf("录入成功!\n\n");
				count++;
				if(choose()=='0')
				{
					return;
				}
				continue;
     		}
		}
		if(!count)//遍历完没找到学生，退出或继续
     	{
     		printf("学生不存在!\n\n");
			if(choose()=='0')
			{
				return;
			}
			continue;
     	}
	}
}
void input_stu_batch(void)//选择文件导入
{
	char f_name[30];//接文件名
   	puts("请输入要导入文件文件名");
   	my_fgets(f_name,30);
   	FILE *fstu=fopen(f_name,"r");	//打开指定的文件
   	if(NULL ==fstu)
  	{
   		msg_show("未找到该文件！！",1.5);
   		return ;
  	}
  	int no[MAX_STUDENT];		//存学号
  	double chinese[MAX_STUDENT];       //存语文成绩
  	double math[MAX_STUDENT];        //存数学成绩
  	double english[MAX_STUDENT];        //存英语成绩
  	int ret=1;	//循环判断条件，赋一让循环能开始
  	int sum=0; 	//记录人数，当下标
  	while(ret>0)	//循环判断条件，ret为1,必能近一次
  	{
		ret=fscanf(fstu,"%d %lf %lf %lf",&no[sum],&chinese[sum],&math[sum],&english[sum]);//读取数据并拿返回值
		if(ret<=0)   //判断是否成功录入
		{
			break;
		}
		sum++;	//人数加一
	}
	int count=0;
  	for(int i=0;i<Ret_stu_in-1;i++)		//遍历在校学生
  	{
  		for(int j=0;j<=sum;j++)		//遍历读取的数据
  		{
  			if(Stu_in[i].sex!='0'&&Stu_in[i].no==no[j])	//学号相同且为在校学生，进行赋值
  			{
  				Stu_in[i].chinese=chinese[j];
  				Stu_in[i].math=math[j];
  				Stu_in[i].english=english[j];
  				count++;
  			}
  		}
  	}
  	printf("共录入%d条记录!\n",count);	//成功提示
  	anykey_continue();
  	fclose(fstu);	//关闭文件
  	fstu=NULL;		//置空
}


void input_stu(void)  //录入学生成绩
{	
	//打印菜单
	printf("请选择:\n");
	printf("-----------:\n");
	printf("1、单个录入:\n");
	printf("2、批量导入:\n");
	printf("-----------:\n");
	char cmd = getch();		//获取键值
	switch(cmd)
	{
		case '1':input_stu_single();
		case '2':input_stu_batch();break;
		case '0':return;
	}
}
void reset_stu(void)    //重置学生密码
{
	char name1[21]={};
	int no;
	printf("输入学生姓名:");
	my_fgets(name1,21);
	printf("输入学生学号:\n");
	scanf("%d",&no);
	for(int i=0;i<Ret_stu_in-1;i++)
	{
		if(Stu_in[i].sex!='0'&&!strcmp(Stu_in[i].name,name1)&&Stu_in[i].no==no)	//比较在校的学生里姓名学号相同的，次数归零，密码初始化为123456
		{
			strcpy(Stu_in[i].password,"123456");
			Stu_in[i].state=0;
			msg_show("重置密码成功!\n",1.5);
			return;
		}
	}
	msg_show("学生不存在!\n",1.5);
	return;
}

void show_all_in(void)        //显示所有在校学生信息
{
	printf("姓  名    性别  学 号   语 文   数 学  英 语\n");
	for(int i=0;i<Ret_stu_in-1;i++)
	{
		if(Stu_in[i].sex!='0')	//在校
		{
			printf("%-8s  %s    %-6d  %5.1lf  %5.1lf  %5.1lf\n",
						Stu_in[i].name,Stu_in[i].sex=='m'?"男":"女",
						Stu_in[i].no,Stu_in[i].chinese,Stu_in[i].math,Stu_in[i].english);
		}
	}
	anykey_continue();
}
void show_all_out(void)           //显示所有退出学生信息
{
	printf("姓  名  性别  学 号\n");
	for(int i=0;i<Ret_stu_out-1;i++)
	{
		if(Stu_out[i].sex!='0')		//离校
		{
		printf("%-6s  %s    %-6d\n",
						Stu_out[i].name,Stu_in[i].sex=='m'?"男":"女",
						Stu_out[i].no);
		}
	}
	anykey_continue();
}

void unlock_tea(void)
{
	int key=0;
	for(;;)
	{
		printf("请输入要解锁的学生学号：\n");
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
	int i=0;
	for(i=0;i<Ret_stu_in-1;i++)
	{
		if(key == Stu_in[i].no)		//循环有内容的信息
		{
			if(Stu_out[i].sex== 'm' || Stu_out[i].sex == 'w')	//通过工号找到教师,且帐号被锁s=3
			{
				if(Stu_in[i].state==3)			//通过工号找到教师,且帐号被锁s=3
				{
					Stu_in[i].state= 0;
					msg_show("已解锁\n",1.5);			//密码锁归零
					return;
				}
				else
				{
					msg_show("帐号没被锁定\n",1.5);
					return;
				}
			}
		}
	}
	if(i>=Ret_stu_in-1)
	{
		msg_show("查无此人\n",1.5);
		return;
	}
}

void change_tea_password(void)	//修改自己密码
{
	//定义存放密码的两个数组
	char password[20]={};
	printf("请输入你的密码：");
	secrecy(password);		//加密并输入密码到password这个数组中
	//判断输入密码是否是否与原密码正确
	if(strcmp(Tea_in[Tea_index].password,password))	
	{
		printf("密码不正确\n");
		anykey_continue();	//按任意键继续
		return;
	}
	if(judge_password(password))	//输入并判断两次密码是否一致
	{	
		strcpy(Tea_in[Tea_index].password,password);	//将新密码拷贝到该学生结构体中
		msg_show("修改成功！",1.5);
	}
	else
	{
		msg_show("两次密码不一致",1.5);
	}
}
