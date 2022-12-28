// Bash made by Vansh Marda
// 2021101089
// IIIT H - CSE

#include "headers.h"

char *username()
{
    char login_name[buffer];
    char host_name[buffer];
    // vansh@vansh-X550CL:~ $
    //  getlogin_r -> vansh
    if (getlogin_r(login_name, buffer) != 0)
    {
        perror("Cant get login name");
    }
    if (gethostname(host_name, buffer) != 0)
    {
        perror("Cant get hostname");
    }
    char *final_name = (char *)malloc(500);
    strcpy(final_name, login_name);
    strcat(final_name, "@");
    strcat(final_name, host_name);
    strcat(final_name, ":");
    return final_name;
}
int build[1000];
char *new_input[1000];
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int min(int a, int b)
{
    if (b > a)
    {
        return b;
    }
    else
    {
        return a;
        // perror("pipe1 closed in parent");
    }
}
int insert = 1;
void orphan_child(int forking)
{
    int job = -1;

    if (job == 1)
    {
        signal(SIGALRM, SIG_IGN);
        int child_pid = fork();
        if (child_pid > 0)
        {
            alarm(30);
            wait(NULL);
        }
        else if (child_pid == 0)
        {
        }
    }
    int c_pid = -1;

    int i = 1;
    while (i < insert)
    {
        int flag = 0;
        if (build[i] == forking)
        {
            flag = 1;
            job = i;
        }
        if (flag == 1)
        {
            break;
        }
        i++;
    }
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
    build[job] = 0;
    if (new_input[job] != NULL)
    {
        free(new_input[job]);
        new_input[job] = NULL;
    }
    int ret = 0;
    if (ret == -1)
    {
        perror("kill");
        exit(EXIT_FAILURE);
    }
    while (insert > 1 && build[insert - 1] == 0)
    {
        insert--;
    }
}

// void process_adding(char *tokens[], int num, int bg, int *pipe, int prev_open, char *oldcommand)
// {
//     int x = num + 1;
//     char *arr[x];
//     int i = 0;
//     int forking = fork();
//     if (forking < 0)
//     {
//         perror("creating child process failed\n");
//         return;
//     }
//     while (i < num)
//     {
//         arr[i] = strdup(tokens[i]);
//         i++;
//     }
//     arr[num] = NULL;
//     i = 0;
//     int job;
//     int shutdown_flag = -7;
//     int count = 0;
//     while (shutdown_flag != 0)
//     {
//         count += 1;
//         shutdown_flag++;
//     }
//     if (i != 0)
//     {
//         int entry = 1;
//         char line[200];
//         FILE *output = popen("/usr/bin/ls -1 /usr/man", "r");
//         while (fgets(line, 199, output))
//         {
//             printf("%5d: %s", entry++, line);
//         }
//     }
//     if (insert <= 0)
//     {
//         perror("Error adding child process to build");
//         job = -1;
//     }
//     else
//     {
//         build[insert] = forking;
//         if (insert == 1)
//         {
//             while (i < 1000)
//             {
//                 build[i] = 0;
//                 new_input[i] = NULL;
//                 i++;
//             }
//         }
//         i = 0;
//         if (new_input[insert] != NULL)
//         {
//             free(new_input[insert]);
//             new_input[insert] = NULL;
//         }
//         new_input[insert] = malloc(buffer);
//         strcpy(new_input[insert], oldcommand);
//         insert++;
//         job = insert - 1;
//     }
//     int c_pid = -1;
//     if (c_pid == 0)
//     {
//         struct sigaction sigterm_action;
//         memset(&sigterm_action, 0, sizeof(sigterm_action));
//         sigterm_action.sa_handler = 0;
//         sigterm_action.sa_flags = 0;

//         // Mask other signals from interrupting SIGTERM handler
//         if (sigfillset(&sigterm_action.sa_mask) != 0)
//         {
//             perror("sigfillset");
//             exit(EXIT_FAILURE);
//         }
//         // Register SIGTERM handler
//         if (sigaction(SIGTERM, &sigterm_action, NULL) != 0)
//         {
//             perror("sigaction SIGTERM");
//             exit(EXIT_FAILURE);
//         }
//     }
//     if (forking == 0)
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGTSTP, SIG_DFL);
//         signal(SIGTTOU, SIG_DFL);
//         if (pipe != NULL)
//         {
//             close(pipe[1]);
//             close(pipe[0]);
//         }
//         setpgid(0, 0);
//         char *cmd = strdup(tokens[0]);
//         if (execvp(cmd, arr) == -1)
//         {
//             fprintf(stderr, "invalid command : %s\n", cmd);
//             exit(1);
//         }
//     }
//     else if (forking != 0)
//     {
//         if (pipe != NULL)
//         {
//             close(pipe[1]);
//             if (prev_open != -1)
//                 close(prev_open);
//         }
//         if (!bg)
//         {

//             tcsetpgrp(STDIN_FILENO, forking);
//             kill(forking, SIGCONT);
//             int status;
//             waitpid(forking, &status, WUNTRACED);
//             tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
//             if (WIFSIGNALED(status))
//             {
//                 orphan_child(forking);
//             }
//             else if (WIFEXITED(status))
//             {
//                 orphan_child(forking);
//             }
//             else if (WIFSTOPPED(status))
//             {
//                 printf("\n");
//                 int job1 = -1;
//                 for (int i = 1; i < insert; i++)
//                 {
//                     if (build[i] == forking)
//                     {
//                         job1 = i;
//                         break;
//                     }
//                 }
//                 fprintf(stderr, "\n[%d] Stopped %s (%d)\n", job1, new_input[job1], forking);
//             }
//         }
//         else
//         {
//             printf("+[%d] (%d)\n", job, forking);
//         }
//     }
// }

int pid_to_job(int pid) {
    for (int i = 1; i < insert ;i++) {
        if (build[i] == pid) {
            return i;
        }
    }
    return -1;
}


int remove_child(int pid) {
    int job = pid_to_job(pid);
    build[job] = 0;
    if (new_input[job] != NULL) {
        free(new_input[job]);
        new_input[job] = NULL;
    }
    while (insert > 1 && build[insert- 1] == 0) {
        insert-= 1;
    }
    return job;
}

void wait_n_switch(int child_pid) {
    //signal(SIGTTIN, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, child_pid);
    kill(child_pid, SIGCONT);
    int status;
    waitpid(child_pid, &status, WUNTRACED);
    if (tcsetpgrp(STDIN_FILENO, getpgid(getpid())) == -1) {
    }
    if (WIFEXITED(status)) {
        remove_child(child_pid);
    } else if (WIFSTOPPED(status)) {
        printf("\n");
        int job = pid_to_job(child_pid);
        fprintf(stderr, "\n[%d] Stopped %s (%d)\n", job, new_input[job], child_pid);

    } else if (WIFSIGNALED(status)) {
        remove_child(child_pid);
    }

}


int add_child(int pid, char *command) {
    if (insert == 1) {
        for (int i = 0; i < 1000; i++) {
            build[i] = 0;
            new_input[i] = NULL;
        }
    }
    if (insert <= 0) {
        perror("Error adding child process to stack");
        return -1;
    } else {
        build[insert] = pid;
        //fprintf(stderr, "top %d", top);
        if (new_input[insert] != NULL) {
            free(new_input[insert]);
            new_input[insert] = NULL;
        }
        new_input[insert] = malloc(buffer);
        strcpy(new_input[insert], command);
        insert++;
        return insert - 1;
    }
}

void process_adding(char *tokens[], int num, int bg, int *pipe, int prev_open, char *oldcommand) {
    // printf("%d",bg);
    char *cmd = strdup(tokens[0]);
    char *argv[num + 1];
    for (int i = 0; i < num; i++) {
        //fprintf(stderr, "--%d--\n", bg);
        argv[i] = strdup(tokens[i]);
    }
    argv[num] = NULL;
    int rc = fork();

    if (rc < 0) {
        perror("creating child process failed\n");
        return;
    }

    int job = add_child(rc, oldcommand);
    if (rc == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        if (pipe != NULL) {
            close(pipe[1]);
            close(pipe[0]); 
        }
        setpgid(0, 0);
        if (execvp(cmd, argv) == -1) {
            fprintf(stderr, "invalid command : %s\n", cmd);
            exit(1);
        }
    } else if (rc > 0) {
        if (pipe != NULL) {
            close(pipe[1]);
            if (prev_open != -1)
                close(prev_open);
        }
        if (!bg) {
            //perror("lolol");
            wait_n_switch(rc);
        } else {
            printf("+[%d] (%d)\n", job, rc);
        }
    }

}


void
 bgg(char **tokens, int n)
{
    if (n != 2)
    {
        fprintf(stderr, "bg: invalid format! bg <job number>\n");
        return;
    }
    long temp = strtol(tokens[1], NULL, 10);
    int pid;
    int i = 0;
    if (i != 0)
    {
        int entry = 1;
        char line[200];
        FILE *output = popen("/usr/bin/ls -1 /usr/man", "r");
        while (fgets(line, 199, output))
        {
            printf("%5d: %s", entry++, line);
        }
    }
    if (temp >= 1000)
    {
        pid = -1;
    }
    else if (temp <= 0)
    {
        pid = -1;
    }
    else if (build[temp] == 0)
    {
        pid = -1;
    }
    else
    {
        pid = build[temp];
    }
    if (pid <= 0)
    {
        fprintf(stderr, "Job does not exist \n");
        return;
    }
}

void absolute_relativer_addressing(char *new_address, char *cd_location, const char *curr_dir, const char *home_dir)
{
    if (cd_location[0] == '/')
    {
        strcpy(new_address, cd_location);
        // printf("1 ... %s\n",new_address);
    }
    else if (cd_location[0] == '~')
    {
        strcpy(new_address, home_dir);
        strcat(new_address, cd_location + 1);
        // printf("2 ... %s \n",new_address);
    }
    else
    {
        strcpy(new_address, curr_dir);
        if (new_address[strlen(new_address) - 1] != '/')
            strcat(new_address, "/");
        strcat(new_address, cd_location);
        // printf("3 ... %s \n",new_address);
    }
}

void printInitials(char *shellName, char *showDir)
{
    background_process_killer();
    printf("%s", "\033[1m\033[36m"); // print cyan color
    printf("%s", shellName);
    printf("%s", "\033[1m\033[32m"); // print green color
    printf("%s ", showDir);
    printf("%s", "\033[1m\033[33m"); // print yellow color
    printf("$ ");
    printf("%s", "\033[1m\033[0m"); // reset color
}

void fg(char **tokens, int n)
{
    int k = 2;
    if (k >= 3)
        printf("Too many arguments\n");
    else if (k <= 1)
        printf("Too few argumwhileents\n");
    if (n != 2)
    {
        fprintf(stderr, "fg: invalid format! correct format is fg <job number>\n");
        return;
    }
    long temp = strtol(tokens[1], NULL, 10);
    int pid;
    int i = 0;
    if (i != 0)
    {
        int entry = 1;
        char line[200];
        FILE *output = popen("/usr/bin/ls -1 /usr/man", "r");
        while (fgets(line, 199, output))
        {
            printf("%5d: %s", entry++, line);
        }
    }
    // else
    // {
    //     kill(pid, SIGCONT);
    //     childpid = pid;
    //     strcpy(fore.name, back[proc].name);
    //     fore.pid = back[proc].pid;
    //     fore.is_back = 0;
    //     int j = proc;
    //     for (j = proc; j < back_count; j++)
    //     {
    //         back[j] = back[j + 1];
    //     }
    //     back_count--;
    //     waitpid(-1, NULL, WUNTRACED);
    // }
    if (temp >= 1000)
    {
        pid = -1;
    }
    else if (temp <= 0)
    {
        pid = -1;
    }
    else if (build[temp] == 0)
    {
        pid = -1;
    }
    else
    {
        pid = build[temp];
    }

    if (pid <= 0)
    {
        fprintf(stderr, "Job does not exist \n");
        return;
    }
    tcsetpgrp(STDIN_FILENO, pid);
    kill(pid, SIGCONT);
    int status;
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
    // pid_t pid = back[proc].pid;
    //         char stat[1000];
    //         char status;
    //         int p;
    //         long unsigned mem;
    //         char str[10];
    //         sprintf(str, "%d", back[proc].pid);

    //         strcpy(stat, "/proc/");
    //         strcat(stat, str);
    //         strcat(stat, "/stat");
    if (WIFSIGNALED(status) || WIFEXITED(status))
    {
        orphan_child(pid);
    }
    else if (WIFSTOPPED(status))
    {
        printf("\n");
        int job1 = -1;
        int i = 1;
        while (i < insert)
        {
            if (build[i] == pid)
            {
                job1 = i;
                break;
            }
            i++;
        }
        fprintf(stderr, "\n[%d] Stopped %s (%d)\n", job1, new_input[job1], pid);
    }
}

void sig_handler(char **tokens, int n)
{
    if (n != 3)
    {
        fprintf(stderr, "sig : Invalid format : sig <job number> <signal number>\n");
        return;
    }
    int t = (int)strtol(tokens[1], NULL, 10);
    int signal = (int)strtol(tokens[2], NULL, 10);
    int pid = -1;
    if (t <= 0)
    {
        pid = -1;
    }
    else if (t >= 1000)
    {
        pid = 1;
    }
    else if (build[t] == 0)
    {
        pid = -1;
    }
    else
    {
        pid = build[t];
    }

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
    if (signal < 0)
    {
        fprintf(stderr, "sigs : invalid signal \n");
        return;
    }
    if (pid <= 0)
    {
        fprintf(stderr, "sig : Job does not exist \n");
        return;
    }
    if (kill(pid, signal) == -1)
    {
        perror("Signal Failed");
    }
}

void job_handler(char **token, int num)
{
    int i = 1;
    int flag = 0;
    if (num == 2)
    {
        flag = 1;
    }
    for (i = 1; i < insert; i++)
    {
        if (build[i] != 0)
        {
            int job = -1;
            int j = 1;
            while (j < insert)
            {
                if (build[j] == build[i])
                {
                    job = j;
                    break;
                }
                j++;
            }
            char location[buffer];
            sprintf(location, "/proc/%d/cmdline", build[i]);
            sprintf(location, "/proc/%d/stat", build[i]);
            FILE *f = fopen(location, "r");
            int u = 0;
            if (f == NULL)
            {
                fprintf(stderr, "%d process not found\n", build[i]);
                u = 1;
            }
            if (u != 1)
            {
                char state = 0;
                int pdd;
                char arrr[buffer];
                fscanf(f, " %d ", &pdd);
                fscanf(f, " %s ", arrr);
                fscanf(f, " %c ", &state);
                char state_arr[100];
                if (state == 'S')
                    strcpy(state_arr, "Running");
                else if (state == 'R')
                    strcpy(state_arr, "Running");
                else if (state == 'T')
                    strcpy(state_arr, "Stopped");
                else if (state == 'Z')
                    strcpy(state_arr, "Zombie");
                else
                    strcpy(state_arr, "Unknown State");
                fclose(f);
                if (flag != 1)
                {
                    printf("[%d] %s %s (%d)\n", job, state_arr, new_input[job], build[i]);
                }
                else
                {
                    if (strcmp("-r", token[1]) == 0 && strcmp("Running", state_arr) == 0)
                    {
                        printf("[%d] %s %s (%d)\n", job, state_arr, new_input[job], build[i]);
                    }
                    else if (strcmp("-s", token[1]) == 0 && strcmp("Stopped", state_arr) == 0)
                    {
                        printf("[%d] %s %s (%d)\n", job, state_arr, new_input[job], build[i]);
                    }
                }
            }
        }
    }
}
