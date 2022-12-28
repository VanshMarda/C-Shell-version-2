// Bash made by Vansh Marda
// 2021101089
// IIIT H - CSE

#include "headers.h"

void kill_background()
{
    int child = 9;
    int i=-1;
    int status;
    struct dirent *dir_stuff;
    DIR *dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("cannot access /proc");
        return;
    }
    while (child != 0)
    {
        child--;
    }
    int enter;
    while ((dir_stuff = readdir(dir)) != NULL)
    {
        if (i == 0)
        {
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }
        }
        if (isdigit(dir_stuff->d_name[0]))
        {
            char add[1000];
            sprintf(add, "/proc/%s/stat", dir_stuff->d_name);
            FILE *f = fopen(add, "r");
            if (f == NULL)
            {
                continue;
            }
            int pid, ppid;
            char state;
            char name[buffer];
            fscanf(f, "%d %s", &pid, name);
            fscanf(f, " %c ", &state);
            fscanf(f, " %d", &ppid);
            if (ppid == (int)getpid())
            {
                child++;
                kill(pid, SIGKILL);
            }
            fclose(f);
        }
    }
    closedir(dir);
    int x = 0;
    while (waitpid(-1, &status, WNOHANG) > 0)
    {
        x++;
    }
}

void background_process_killer()
{
    int status;
    int job = -1;
    int reaped_rc;
    struct dirent *dir_stuff;
    DIR *dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("cannot access /proc");
        return;
    }
    int count = 0;
    if (job == 1)
    {
        signal(SIGALRM, SIG_IGN);
        int child_pid = fork();
        if (child_pid > 0)
        {
            count++;
        }
        else if (child_pid == 0)
        {
        }
    }
    int pids[buffer];
    char *namess[buffer];
    int child = 0;
    // if(fork()==0) {
    //         printf("In child process ..c_pid: %d and p_pid : %d\n",getpid(),getppid());
    //         sleep(5);
    //         printf("sleep over .. now exiting \n");
    // }
    while ((dir_stuff = readdir(dir)) != NULL)
    {
        if (isdigit(dir_stuff->d_name[0]))
        {
            char add[1000];
            sprintf(add, "/proc/%s/stat", dir_stuff->d_name);
            FILE *f = fopen(add, "r");
            if (f == NULL)
            {
                continue;
            }
            // else { /*parent process */
            //         struct sigaction v;
            //         v.sa_handler=my_isr;/* SET THE HANDLER TO ISR */
            //         v.sa_flags=SA_NOCLDWAIT; /* it will not let child to become zombie */
            //         sigemptyset(&v.sa_mask);
            //         sigaction(17,&v,NULL);/* when parent receives SIGCHLD, IT GETS CALLED */
            //         while(1); /*for observation purpose, to make parent process alive */
            // }
            int pid, ppid;
            char state;
            char name[buffer];
            fscanf(f, "%d %s", &pid, name);
            fscanf(f, " %c ", &state);
            fscanf(f, " %d", &ppid);
            if (ppid == (int)getpid())
            {
                pids[child] = pid;
                namess[child] = strdup(name);
                child++;
            }
            fclose(f);
        }
    }
    closedir(dir);

    while ((reaped_rc = waitpid(-1, &status, WNOHANG)) > 0)
    {
        char stat[200];
        if (WIFEXITED(status))
        {
            int t = WEXITSTATUS(status);
            sprintf(stat, "normally with status %d", t);
        }
        else if (WIFSIGNALED(status))
        {
            int t = WTERMSIG(status);
            sprintf(stat, "because of signal %d", t);
        }
        else
        {
            sprintf(stat, "exited somehow");
        }
        if (count != 0)
        {
            for (int i = 0; i < 3; i++)
            {
                printf("Now ..  Forking !!\n");
                child = fork();

                if (child < 0)
                {
                    perror("Unable to fork");
                    break;
                }
                else if (child == 0)
                {
                    printf("In child #%d\n", (i + 1));
                    break;
                }
                else
                {
                    /* in parent */
                    if (waitpid(child, NULL, 0) < 0)
                    {
                        perror("Failed to collect child process");
                        break;
                    }
                }
            }
        }
        char text[buffer];
        char name[1000];
        strcpy(name, " ");
        int i = 0;
        while (i < child)
        {
            if (pids[i] == reaped_rc)
            {
                strcpy(name, namess[i]);
                break;
            }
            i++;
        }
        i = -1;
        int len = sprintf(text, "\nchild process %s %d has exited %s\n", name, reaped_rc, stat); // printf("Press enter to continue\n");
        char enter = 0;
        if (i == 0)
        {
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }
        }
        write(2, text, len);
    }
}
