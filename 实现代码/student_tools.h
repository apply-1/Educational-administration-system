#ifndef STUDENT_TOOLS_H
#define STUDENT_TOOLS_H

#include <stdbool.h>

extern int Stu_index; //记录当前学生的下标

//登录界面以及验证密码
bool land_student(void);

//学生界面菜单
int show_student_menu(void);

//计算在校学生总人数
int count_student(void);

#endif//STUDENT_TOOLS_H
