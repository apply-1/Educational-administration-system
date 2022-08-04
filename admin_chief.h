#ifndef ADMIN_CHIEF_H
#define ADMIN_CHIEF_H

void reset_me(void);	//重置自己密码
void reset_t(void);		//重置教师密码
void add_tch(void);		//添加教师
void del_tch(void);		//删除教师
void show_tch(void);	//显示所有在职教师
void show_lev(void);	//显示所有离职教师
void unlock(void);		//解锁教师账号

#endif //ADMIN_CHIEF_H
