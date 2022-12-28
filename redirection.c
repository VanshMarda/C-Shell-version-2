//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#include "headers.h"

void redirection_handler_2(char *in_out_redir, char *input_file)
{
    // printf("%s %s\n",in_out_redir,input_file);
    //  changing inpput using <
    if (strcmp(in_out_redir, "<") == 0)
    {
        int new_fd = open(input_file, O_RDONLY);
        if (new_fd != -1)
        {
            close(STDIN_FILENO);
            dup(new_fd);
            close(new_fd);
        }
        else
        {
            perror("cannot redirect input");
        }
    }
    // change output using >
    else if (strcmp(in_out_redir, ">") == 0)
    {
        int new_fd = open(input_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (new_fd != -1)
        {
            close(STDOUT_FILENO);
            dup(new_fd);
            close(new_fd);
        }
        else
        {
            perror("cannot redirect output");
        }
    }
    // appending the output to the file using >>
    else if (strcmp(in_out_redir, ">>") == 0)
    {
        int new_fd = new_fd = open(input_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (new_fd != -1)
        {
            close(STDOUT_FILENO);
            dup(new_fd);
            close(new_fd);
        }
        else
        {
            perror("cannot redirect output");
        }
    }
}