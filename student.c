#include <getch.h>
#include "chief.h"
#include "student.h"
#include "student_tools.h"
#include "student_chief.h"

void student(void)
{
	//登录界面
	if(!land_student())
	{
		return;
	}
	for(;;)
	{
		switch(show_student_menu())	//界面显示
		{
			case '1':
				//显示成绩
				show_grade();
				break;
			case '2':
				//修改密码
				change_password();
				break;
			case '3':
				//查看个人信息
				look_information();
				break;
			case '0':
				//退出学生端
				return;
		}
	}
}
