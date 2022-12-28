//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#ifndef UNTITLED_UTIL_H
#define UNTITLED_UTIL_H

#define buffer 5000
char initialDirector[buffer];
char workingDirectory[buffer];
char showingDirectory[buffer];


int max(int a, int b);
int min(int a, int b) ;
void absolute_relativer_addressing(char *new_address, char *cd_location, const char *curr_dir, const char *home_dir);
void clearScreen();
void printInitials(char* shellName , char* showDir);
char* username();
void process_adding(char *tokens[], int num, int bg, int *pipe, int prev_open, char *oldcommand);
void bgg(char **tokens, int n) ;
void fg(char **tokens, int n);
void sig_handler(char **tokens, int n);
void orphan_child(int rc);
void job_handler(char **token , int num);
#endif //UNTITLED_UTIL_H
