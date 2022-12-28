//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#include "headers.h"

void processInput(char **tok, int num_tok, int bg, int *pipe, int prev_open, char *oldcommand)
{
    if (strcmp(tok[0], "cd") == 0)
    {
        if (num_tok == 1)
        {
            tok[1] = malloc(4);
            strcpy(tok[1], "~");
        }
        cd(tok);
    }
    else if (strcmp(tok[0], "pwd") == 0)
    {
        printf("%s\n", workingDirectory);
    }
    else if (strcmp(tok[0], "echo") == 0)
    {
        echo(tok, num_tok);
    }
    else if (strcmp(tok[0], "clear") == 0)
    {
        printf("\e[1;1H\e[2J");
    }
    else if (strcmp(tok[0], "history") == 0)
    {
        if (num_tok == 1)
        {
            show_history(10);
        }
        else
        {
            if (strtol(tok[1], NULL, 10) <= 0)
            {
                if (strtol(tok[1], NULL, 10) > 20)
                {
                    printf("history <int n> \n n > 0 && n <= 20\n");
                    return;
                }
            }
            show_history(atoi(tok[1]));
        }
    }
    else if (strcmp(tok[0], "pinfo") == 0)
    {
        if (num_tok == 1)
        {
            tok[1] = malloc(10);
            sprintf(tok[1], "%d", getpid());
        }
        pinfo_handler(tok);
    }
    else if (strcmp(tok[0], "ls") == 0)
    {
        ls_handler(tok, num_tok, workingDirectory, initialDirector);
    }
    else if (strcmp(tok[0], "discover") == 0)
    {
        discover_handler(tok, num_tok, workingDirectory, initialDirector);
    }
    else if (strcmp(tok[0], "exit") == 0)
    {
        kill_background();
        printf("bye bye \n");
        _exit(0);
    }
    else if (strcmp(tok[0], "fg") == 0)
    {
        fg(tok, num_tok);
    }
    else if (strcmp(tok[0], "bg") == 0)
    {
        bgg(tok, num_tok);
    }
    else if (strcmp(tok[0], "jobs") == 0)
    {
        job_handler(tok,num_tok);
    }
    else if (strcmp(tok[0], "sig") == 0)
    {
        sig_handler(tok, num_tok);
    }
    else
        process_adding(tok, num_tok, bg, pipe, prev_open, oldcommand);
}
void redirectionHandler(char *input, int bg, int *pipe, int prev_open)
{
    int n1 = strlen(input);
    char *command[1000];
    int num_command = 0;
    if (n1 == 0)
    {
        printf("error : arguments passed !!\n");
        return;
    }
    char input2[n1 + 1];
    strcpy(input2, input);
    char *tokens[buffer];
    int num_tokens = 0;
    if (n1 <= 0)
    {
        printf("wrong argument");
        return;
    }
    tokens[0] = strtok(input, " \t\n");
    while (tokens[num_tokens] != NULL)
    {
        tokens[++num_tokens] = strtok(NULL, " \t");
    }
    if (num_tokens == 0)
    {
        return;
    }
    int i=0;
    while(i < num_tokens)
    {
        if (strcmp(tokens[i], "<") == 0)
        {
            if (i + 1 == num_tokens || tokens[i + 1] == NULL)
            {
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            else if(tokens[i+1]==NULL){
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            redirection_handler_2(tokens[i], tokens[i + 1]);
            i++;
        }
        else if(strcmp(tokens[i], ">") == 0){
            if (i + 1 == num_tokens)
            {
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            else if(tokens[i + 1] == NULL){
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            redirection_handler_2(tokens[i], tokens[i + 1]);
            i++;   
        }
        else if(strcmp(tokens[i], ">>")==0){
            if (i + 1 == num_tokens)
            {
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            else if(tokens[i + 1] == NULL)
            {
                fprintf(stderr, "unexpected token after %s \n", tokens[i]);
                return;
            }
            redirection_handler_2(tokens[i], tokens[i + 1]);
            i++;   
        }
        else
        {
            command[num_command] = malloc(buffer);
            strcpy(command[num_command], tokens[i]);
            num_command++;
        }
        i++;
    }
    i=0;
    processInput(command, num_command, bg, pipe, prev_open, input2);
    while(i<num_command){
        free(command[i]);
        i++;
    }
    return;
}
// checks for pipes
void pipeChecker(char *cmd, int bg)
{
    //printf("%d",bg);
     char *commands[1000];
     int n = 0;
    int pipee = 0;
    int n1 = strlen(cmd);
    int i = 0;
    int k = 0;
    while (i < n1)
    {
        if (cmd[i] == '|')
        {
            pipee++;
        }
        i++;
    }
    if (pipee != 0) // error handling
    {
        if (cmd[0] == '|')
        {
            fprintf(stderr, "pipe cannot be at starting or ending \n");
            return;
        }
        else if(cmd[strlen(cmd) - 1] == '|'){
            fprintf(stderr, "pipe cannot be at starting or ending \n");
            return;   
        }
    }
    else
    {
        redirectionHandler(cmd, bg, NULL, -1);
        return;
    }
    if (k == -1)
    {
        i = 0;
        while (cmd[i] != '\0')
        {
            if (cmd[i] == '|')
                return;
            i++;
        }
    }
    int out = dup(1);
    int in = dup(0);
    char *t = strtok(cmd, "|");
    while (t != NULL)
    {
        commands[n] = malloc(buffer);
        strcpy(commands[n], t);
        t = strtok(NULL, "|");
        n++;
    }
    int prev_open = -1;
    i = 0;
    if (k == -1)
    {
        i = 0;
        while (cmd[i] != '\0')
        {
            if (cmd[i] == '|')
                return;
            i++;
        }
        int j = 0;
        while (cmd != NULL)
        {
            cmd = strtok_r(NULL, " \n\t\r", &cmd);
            j++;
        }
    }
    while (i < n - 1)
    {
        int pipes[2];
        if (pipe(pipes) == -1)
        {
            return;
        }
        if (prev_open != -1)
        {
            dup2(prev_open, 0);
            close(prev_open);
        }
        dup2(pipes[1], 1);
        close(pipes[1]);
        redirectionHandler(commands[i], bg, pipes, prev_open);
        prev_open = pipes[0];
        free(commands[i]);
        i++;
    }
    if (k == -1)
    {
        while (k != 2)
        {
            k++;
            cmd = strtok(NULL, " \n\t\r");
        }
    }
    dup2(out, 1);
    close(out);
    if (prev_open != -1)
    {
        dup2(prev_open, 0);
        close(prev_open);
    }
    redirectionHandler(commands[n - 1], bg, NULL, prev_open);
    dup2(in, 0);
    close(in);
}