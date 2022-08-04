#ifndef CHIEF_H
#define CHIEF_H

#include <stdbool.h>
#define MAX_TEACHER 100		//宏定义最大教师数
#define MAX_STUDENT 2000	//宏定义最大学生数

//定义学生结构体
typedef struct Student
{
	char name[20];	
	char sex;	
	int no;   
	char password[13];
	char state;
	double chinese;	
	double math;
	double english;
}Student;

//定义老师结构体
typedef struct Teacher
{
	char name[20];	
	char sex;	
	int no; 
	char password[13];	
	char state;
}Teacher;

//全局变量的声明
extern Student* Stu_in;
extern Student* Stu_out;
extern Teacher* Tea_in;
extern Teacher* Tea_out;
extern int Ret_stu_in;
extern int Ret_stu_out;
extern int Ret_tea_in;
extern int Ret_tea_out;
extern int* Now_teacher_no;
extern int* Now_student_no;
extern char* Admin_password;

//将文件中的数据导入到变量中，初始化数据
bool init_program(void);
//开始程序
void start_program(void);
//结束程序
void end_program(void);

#endif//CHIEF_H
