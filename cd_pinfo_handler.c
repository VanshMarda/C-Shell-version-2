//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#include  "headers.h"

void pinfo_handler(char *tok[])
{
    char add[buffer];
    char exe[buffer];
    strcpy(exe, "defunct :");
    sprintf(add, "/proc/%s/stat", tok[1]);
    FILE *ptr = fopen(add, "r");
    if (ptr == NULL)
    {
        printf("Cannot access the process \n");
        return;
    }
    // char hostbuffer[256];
    // char *IPbuffer;
    // struct hostent *host_entry;
    // int hostname;

    // // To retrieve hostname
    // hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    // if (hostentry == NULL)
    // {
    //     perror("gethostbyname");
    //     exit(1);
    // }
    int pid;
    char exec_name[1000];
    char st;
    fscanf(ptr, "%d ", &pid);
    fscanf(ptr, "%s ", exec_name);
    fscanf(ptr, "%c ", &st);
    sprintf(add, "/proc/%s/exe", tok[1]);
    int t = readlink(add, exe, buffer);
    if (t != -1)
    {
        exe[t] = '\0';
    }
    else
    {
        strcat(exe, exec_name);
    }
    sprintf(add, "/proc/%s/status", tok[1]);
    fclose(ptr);
    // // To retrieve host information
    // host_entry = gethostbyname(hostbuffer);
    // if (hostentry == NULL)
    // {
    //     perror("gethostbyname");
    //     exit(1);
    // };

    // // To convert an Internet network
    // // address into ASCII string
    // IPbuffer = inet_ntoa(*((struct in_addr*)
    //                        host_entry->h_addr_list[0]));

    // printf("Hostname: %s\n", hostbuffer);
    // printf("Host IP: %s", IPbuffer);
    ptr = fopen(add, "r");
    if (ptr == NULL)
    {
        printf("Cannot access the process \n");
        return;
    }
    char word[buffer];
    while (fscanf(ptr, " %499s", word) == 1)
    {
        if (strcmp(word, "VmSize:") == 0)
        {
            fscanf(ptr, " %499s", word);
            break;
        }
    }
    fclose(ptr);
    printf("pid : %d\n", pid);
    printf("Process Status : %c\n", st);
    printf("memory : %s\n", word);
    printf("Executable Path : %s\n", exe);
    printf("\n");
}


void TransformDir()
{
    int n1 = strlen(initialDirector);
    if (strlen(workingDirectory) < n1)
    {
        strcpy(showingDirectory, workingDirectory);
        if (showingDirectory[strlen(showingDirectory) - 1] == '/')
        {
            showingDirectory[strlen(showingDirectory) - 1] = '\0';
        }
        return;
    }
    int i = 0;
    while (i < n1)
    {
        if (initialDirector[i] != workingDirectory[i])
        {
            strcpy(showingDirectory, workingDirectory);
            return;
        }
        i++;
    }
    strcpy(showingDirectory, "~/");
    strcat(showingDirectory, workingDirectory + n1);
    int n2 = strlen(showingDirectory);
    if (showingDirectory[n2 - 1] == '/')
    {
        showingDirectory[n2 - 1] = '\0';
    }
}

// handles cd
void cd(char *token[])
{
    char cd_location[buffer];
    strcpy(cd_location, token[1]);
    char new_address[buffer];
    absolute_relativer_addressing(new_address, cd_location, workingDirectory, initialDirector);
    struct stat stats_dir;
    if (stat(new_address, &stats_dir) == 0 && (S_IFDIR & stats_dir.st_mode))
    {
        if (chdir(new_address) == -1)
        {
            printf("Directory does not exist  or getcwd failed\n");
        }
        else if(getcwd(workingDirectory, buffer) == NULL){
            printf("Directory does not exist  or getcwd failed\n");
        }
        strcat(workingDirectory, "/");
        TransformDir();
    }
    else
    {
        printf("Directory does not exist%s\n", token[1]);
    }
}
