#ifndef TEACHER_CHIEF_H
#define TEACHER_CHIEF_H


void add_stu(void);  //单个添加学生
void add_stu_batch(void);//批量添加
void add_stu(void);    //添加学生
void delete_stu(void);  //删除学生
void find_stu(void);     //查找学生
void shout_stu(void);    //修改学生信息
void input_stu(void);     //录入学生成绩
void input_stu_batch(void);//单个录入成绩
void input_stu_single(void);//批量录入成绩
void reset_stu(void);      //重置学生密码
void show_all_in(void);       //显示所有在校学生信息
void show_all_out(void);      //显示所有退出学生信息
void unlock_tea(void);		//解锁学生帐号
void change_tea_password(void);	//修改自己密码
#endif //TEACHER_CHIEF_H
