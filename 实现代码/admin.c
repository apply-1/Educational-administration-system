#include "admin_tools.h"
#include "admin_chief.h"
#include <stdio.h>
#include "chief.h"
#include "tools.h"
#include <stdlib.h>
#include "admin.h"

void admin(void)
{
	if(!acont_in())	//密码判断
	{
		return;
	}
	for(;;)
	{
		switch(menu())	//界面显示
		{
		case '1':reset_me(); break;		//重置自己密码
		case '2':reset_t();  break;		//重置教师密码
		case '3':add_tch();  break;		//添加教师
		case '4':del_tch();  break;		//删除教师
		case '5':show_tch(); break;		//显示所有在职教师
		case '6':show_lev(); break;		//显示所有离职教师
		case '7':unlock();   break;		//解锁教师账号
		case '0':return;				//退出程序
		}
	}
}
