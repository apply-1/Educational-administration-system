#include "teacher.h"
#include "teacher_tools.h"
#include "teacher_chief.h"
#include "chief.h"
void teacher(void)
{
	if(!Determine_password())	//判断密码 
	{
		return;
	} 
	for(;;)
	{
		//	显示主界面
		switch(menu_teacher())	
		{
		    case '1':	add_stu();	    break;
			case '2':	delete_stu();	break;
			case '3':	find_stu();	    break;
			case '4':	shout_stu();	break;
			case '5':	input_stu();	break;
			case '6':	reset_stu();	break;
			case '7':	show_all_in();	break;
			case '8':	show_all_out();	break;
			case '9':	unlock_tea();	break;
			case 'a':	change_tea_password();	break;
			case '0':	return ;
		}
	}
}

