//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#ifndef UNTITLED_REDIR_H
#define UNTITLED_REDIR_H
void processInput(char **tok, int num_tok, int bg, int *pipe, int prev_open, char * oldcommand);
void pipeChecker(char *cmd, int bg);
void redirectionHandler(char *input, int bg, int *pipe, int prev_open);
void redirection_handler_2(char *in_out_redir, char *input_file);
#endif //UNTITLED_UTIL_H
