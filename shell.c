// Bash made by Vansh Marda
// 2021101089
// IIIT H - CSE

#include "headers.h"

char *remove_whitespace(char *line)
{
    // Calculating length of the array
    //  len = sizeof(str)/sizeof(str[0]);

    // Checks for space character in array if its there then ignores it and swap str[i] to str[i+1];
    int t = 0;
    int i = 0;
    // for(i = 0; i < len; i++){
    //     if(str[i] == ' '){
    //         for(j=i;j<len;j++)
    //     {
    //         str[j]=str[j+1];
    //     }
    //     len--;
    //     }
    // }

    while (i < strlen(line))
    {
        if (line[i] == '\n')
        {
            t++;
        }
        else if(line[i]=='\t'){
            t++;
        }
        else if(line[i]==' '){
            t++;
        }
        else
        {
            break;
        }
        i++;
    }
    i = 0;
    while (i < t)
    {
        line++;
        i++;
    }
    i = strlen(line) - 1;

    while (i >= 0)
    {
        if (line[i] == '\n')
        {
            line[i]='\0';
        }
        else if(line[i]=='\t'){
            line[i]='\0';
        }
        else if(line[i]==' '){
            line[i]='\0';
        }
        else
        {
            break;
        }
        i--;
    }
    // printf(%s", line);
    return line;
}

// separates commands by ;

void input_commands(char *arr)
{
    char *command;
    char arr2[buffer];
    char arr3[buffer];
    strcpy(arr2, arr);
    strcpy(arr3, arr);
    int c = 0;
    command = strtok(arr, ";&");
    int x = strlen(command);
    int z = 0;
    for (int i = 0; i < x; i++)
    {
        z++;
    }
    while (command != NULL)
    {
        c++;
        command = strtok(NULL, ";&");
    }
    if (c <= 0)
    {
        return;
    }
    char *input_commands[c + 1];
    int i = 0;
    char *beg = arr2;
    input_commands[0] = strtok(arr2, ";&");
    int c_pid = -1;
    if (c_pid == 0)
    {
        struct sigaction sigterm_action;
        memset(&sigterm_action, 0, sizeof(sigterm_action));
        sigterm_action.sa_handler = 0;
        sigterm_action.sa_flags = 0;

        // Mask other signals from interrupting SIGTERM handler
        if (sigfillset(&sigterm_action.sa_mask) != 0)
        {
            perror("sigfillset");
            exit(EXIT_FAILURE);
        }
        // Register SIGTERM handler
        if (sigaction(SIGTERM, &sigterm_action, NULL) != 0)
        {
            perror("sigaction SIGTERM");
            exit(EXIT_FAILURE);
        }
    }
    while (input_commands[i] != NULL && strcmp(input_commands[i], "") != 0)
    {
        i++;
        input_commands[i] = strtok(NULL, ";&");
    }
    int j = 0;
    while (j < c)
    {
        bool bg = false;
        if (arr3[strlen(input_commands[j]) + (input_commands[j] - beg)] == '&')
        {
            bg = true;
        }
        input_commands[j] = remove_whitespace(input_commands[j]);
        int backup_stdout = dup(STDOUT_FILENO);
        int backup_stdin = dup(STDIN_FILENO);
        pipeChecker(input_commands[j], bg);
        dup2(backup_stdout, 1);
        close(backup_stdout);
        dup2(backup_stdin, 0);
        close(backup_stdin);
        j++;
    }
}
void signalHandler(int sig_num) //  handles the signals like Ctrl+C , Ctrl+D
{
    if (sig_num == SIGINT)
    {
    }
    return;
}

void rip_child(int signum)
{
    if (signum == SIGCHLD)
        background_process_killer();
}

void exit_2(int signum)
{
    if (signum == SIGINT)
    {
        kill_background();
        _exit(0);
    }
}

int main()
{
    printf("\e[1;1H\e[2J");
    printf(" ---------------\n");
    printf("|   Welcome     |\n");
    printf("|     to        |\n");
    printf("| Vansh Marda's |\n");
    printf("|    Shell  ;)  |\n");
    printf(" ---------------\n");

    // vansh@vansh-X550CL:
    char *shellName;
    shellName = username();

    // Get the pathname of the current working directory
    //  home dir ---> /home/vansh/Desktop/osn/assignment/assignment2/
    if (getcwd(initialDirector, buffer) == NULL)
    {
        perror("Cannot get path to home dir failed");
    }
    strcat(initialDirector, "/");
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    strcpy(workingDirectory, initialDirector);
    TransformDir();
    while (1)
    {
        printf("%s", "\033[1m\033[33m");
        printf("%s", "\033[1m\033[0m");
        printInitials(shellName, showingDirectory);
        char *arr = malloc(buffer);
        if (fgets(arr, buffer, stdin) == NULL)
        {
            kill_background();
            printf("cya\n");
            _exit(0);
        }
        int ln = strlen(arr) - 1;
        if (*arr)
        {
            if (arr[ln] == '\n')
            {
                arr[ln] = '\0';
            }
        }
        arr = remove_whitespace(arr);
        if (strcmp(arr, "") != 0)
        {
            add_history(arr);
            input_commands(arr);
        }
    }
}
