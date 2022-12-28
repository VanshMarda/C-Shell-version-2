//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#ifndef ECHO_H
#define ECHO_H
void echo(char *tokens[], int num);
void add_history(char * tokens);
void show_history(int n);
void ls_handler(char *tokens[], int no, const char* curr_dir, const char * home_dir);
#endif
