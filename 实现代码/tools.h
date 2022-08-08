#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>

char choose (void);
void msg_show(const char* msg,float sec);
void anykey_continue(void);
void secrecy(char* password);
bool judge_password(char* password);
void my_fgets(char* str,int size);
bool judge_no(int* no);
bool verify_password(char* true_password,char* password);
void encryption(char key);

#endif//TOOLS_H
