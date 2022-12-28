// Bash made by Vansh Marda
// 2021101089
// IIIT H - CSE

#include "headers.h"

// echo

void echo(char *arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        printf("%s ", arr[i]);
    }
    printf("\n");
}
#define history_file "/tmp/.shell_history"

// history

static const char *history[buffer];
int history_count = 0;

void add_history(char tokens[])
{
    FILE *fd;
    fd = fopen(history_file, "a");
    fclose(fd);
    fd = fopen(history_file, "r");
    char *arr[100];
    int n = 0;
    if (n == -1)
    {
        if (history_count >= buffer)
        {
            int index=1;
            while(index < buffer)
            {
                history[index - 1] = history[index];
                index++;
            }
            history[buffer - 1] = strdup(tokens);
        }
        else
        {
            history[history_count++] = strdup(tokens);
        }
    }
    if (fd != NULL)
    {

        arr[n] = malloc(buffer);
        size_t s = buffer;
        while (getline(&arr[n], &s, fd) != -1)
        {
            if (strcmp(arr[n], "\n") != 0)
                arr[++n] = malloc(buffer);
        }
    }
    fclose(fd);

    fd = fopen(history_file, "w");
    int i = max(0, n - 20);
    while (i < n)
    {
        fprintf(fd, "%s", arr[i]);
        i++;
    }

    // result = access (filename, W_OK); // W_OK for writeable
    // if ( result == 0 ) {
    //  array_permission[id]='w';
    // } else {
    //     array_permission[id]='-';
    // }
    char new[buffer];
    sprintf(new, "%s\n", tokens);
    if (i == 0)
    {
        fprintf(fd, "%s", new);
    }
    else if (strcmp(new, arr[i - 1]) != 0)
    {
        fprintf(fd, "%s", new);
    }
    fclose(fd);
    i = 0;
    while (i <= n)
    {
        free(arr[i]);
        i++;
    }
}


// ls
void array_permission_format(int mode, char *array_permission)
{
    int i = 8;
    int id = 0;
    while (i >= 0)
    {

        // char *filename = (char *)malloc(512);
        // if (argc < 2) {
        //     strcpy(filename, "/usr/bin/adb");
        // } else {
        //     strcpy(filename, argv[1]);
        // }
        // result = access (filename, R_OK); // R_OK for readable
        // if ( result == 0 ) {
        // array_permission[id]='r';
        // } else {
        //    array_permission[id]='-';
        // }
        if (mode & i << i)
        {
            if (i % 3 == 1)
            {
                array_permission[id] = 'w';
            }
            else if (i % 3 == 0)
            {
                array_permission[id] = 'x';
            }
            // result = access (filename, X_OK); // X_OK for executable
            // if ( result == 0 ) {
            //     printf("%s is executable\n",filename);
            // } else {
            //     printf("%s is not executable\n",filename);
            // }
            // //free allocated memory
            // free(filename);
            else
            {
                array_permission[id] = 'r';
            }
        }
        else
        {
            array_permission[id] = '-';
        }
        id++;
        i--;
    }
    array_permission[id] = '\0';
}

void show_history(int number)
{
    FILE *fd;
    int count = 1;
    for (int i = 0; i < number; i++)
    {
        count++;
    }
    int n = 0;
    fd = fopen(history_file, "r");
    char *arr[100];
    if (fd != NULL)
    {
        arr[n] = malloc(buffer);
        size_t s = buffer;
        while (getline(&arr[n], &s, fd) != -1)
        {
            if (strcmp(arr[n], "\n") != 0)
                arr[++n] = malloc(buffer);
        }
    }

    int i = 0;
    if (count == 0)
    {
        if (fd != NULL)
        {
            arr[n] = malloc(buffer);
            size_t s = buffer;
            while (getline(&arr[n], &s, fd) != -1)
            {
                if (strcmp(arr[n], "\n") != 0)
                    arr[++n] = malloc(buffer);
            }
        }
        while (i < n)
        {
            printf("%s\n", arr[i]);
            free(arr[i]);
            i++;
        }
    }

    fclose(fd);
    i = max(0, n - number);
    while (i < n)
    {
        printf("%s\n", arr[i]);
        free(arr[i]);
        i++;
    }
}

char *detail_of_months(int number, char *name)
{
    number++;
    if (number == 1)
    {
        strcpy(name, "Jan");
    }
    else if (number == 2)
    {
        strcpy(name, "Feb");
    }
    else if (number == 3)
    {
        strcpy(name, "Mar");
    }
    else if (number == 4)
    {
        strcpy(name, "Apr");
    }
    else if (number == 5)
    {
        strcpy(name, "May");
    }
    else if (number == 6)
    {
        strcpy(name, "Jun");
    }
    else if (number == 7)
    {
        strcpy(name, "Jul");
    }
    else if (number == 8)
    {
        strcpy(name, "Aug");
    }
    else if (number == 9)
    {
        strcpy(name, "Sep");
    }
    else if (number == 10)
    {
        strcpy(name, "Oct");
    }
    else if (number == 11)
    {
        strcpy(name, "Nov");
    }
    else if (number == 12)
    {
        strcpy(name, "Dec");
    }
    return name;
}

void printing_details(const char *add, char *name, int detail)
{
    struct stat data;
    if (lstat(add, &data) == -1)
    {
        printf("%s\n", add);
        perror("Error getting stat struct");
        return;
    }
    time_t l_m = data.st_mtime;
    struct tm last_mod;
    localtime_r(&l_m, &last_mod);
    int month = last_mod.tm_mon;
    int day = last_mod.tm_mday;
    // time_t t;   // not a primitive datatype
    // time(&t);
    // struct passwd *pws = getpwuid(data.st_uid);
    // char *user_name = pws->pw_name;
    // struct group *grp = getgrgid(data.st_gid);
    // char *group_name = grp->gr_name;
    int min = last_mod.tm_min;
    int hour = last_mod.tm_hour;
    int links = data.st_nlink;
    int count = 0;
    for (int i = 0; i < detail; i++)
    {
        count++;
    }
    
    struct passwd *pws = getpwuid(data.st_uid);
    char *user_name = pws->pw_name;
    struct group *grp = getgrgid(data.st_gid);
    char *group_name = grp->gr_name;
    long long bytes = data.st_size;
    char array_permission[100];
    char perm[100];
    if (data.st_mode & S_IXUSR)
    {
        printf("%s", "\033[1m\033[32m");
    }
    if (data.st_mode & S_IFDIR)
    {
        strcpy(array_permission, "d");
        printf("%s", "\033[1m\033[34m");
    }
    else if (S_ISLNK(data.st_mode))
    {
        strcpy(array_permission, "l");
        printf("%s", "\033[1m\033[33m");
    }
    else
    {
        strcpy(array_permission, "-");
    }
    if (!detail)
    {
        printf("%s\n", name);
        printf("%s", "\033[1m\033[0m");
        return;
    }
    // 	while ((d = readdir(dh)) != NULL)
    // {
    // 	//If hidden files are found we continue
    // 	if (!op_a && d->d_name[0] == '.')
    // 		continue;
    // 	printf("%s  ", d->d_name);
    // 	if(op_l) printf("\n");
    // }
    array_permission_format(data.st_mode, perm);
    char monthName[5];
    detail_of_months(month, monthName);
    strcat(array_permission, perm);

    printf("%s%5d%10s%10s%10lld %s %02d %02d:%02d %s\n", array_permission, links, user_name, group_name, bytes, monthName, day, hour, min, name);
    printf("%s", "\033[1m\033[0m");
}

void ls_printing(const char *loc, int hide_loc, int details, int file, char *arrr, int detail)
{
    struct dirent *dir_stuff;
    if (strcmp(arrr, "") != 0 && detail)
        printf("%s :\n", arrr);
    if (file == 1)
    {
        printing_details(loc, arrr, details);
        return;
    }
    int total_blocks = 0;
    DIR *dir = opendir(loc);
    int total = 0;
    // 	while ((d = readdir(dh)) != NULL)
    // {
    // 	//If hidden files are found we continue
    // 	if (!op_a && d->d_name[0] == '.')
    // 		continue;
    // 	printf("%s  ", d->d_name);
    // 	if(op_l) printf("\n");
    // }
    while (readdir(dir) != NULL)
    {
        total++;
    }
    closedir(dir);
    char names[total][buffer];
    dir = opendir(loc);
    int count = 0;
    // if (!dh)
    // {
    // 	if (errno = ENOENT)
    // 	{
    // 		//If the directory is not found
    // 		perror("Directory doesn't exist");
    // 	}
    // 	else
    // 	{
    // 		//If the directory is not readable then throw error and exit
    // 		perror("Unable to read directory");
    // 	}
    // 	exit(EXIT_FAILURE);
    // }
    while ((dir_stuff = readdir(dir)) != NULL)
    {
        strcpy(names[count], dir_stuff->d_name);
        count++;
        if (!hide_loc && (dir_stuff->d_name[0] == '.'))
            continue;
        char addressing_element[buffer];
        strcpy(addressing_element, loc);
        strcat(addressing_element, dir_stuff->d_name);
        struct stat data;
        // if(errno = ENOENT))
        //  	{
        //  		//If the directory is not found
        //  		perror("Directory doesn't exist");
        //  	}
        //  	else
        //  	{
        //  		//If the directory is not readable then throw error and exit
        //  		perror("Unable to read directory");
        //  	}
        if (stat(addressing_element, &data) == -1)
        {
            printf("%s\n", addressing_element);
            perror("Error getting stat struct");
            continue;
        }
        total_blocks += data.st_blocks;
    }
    char temp[buffer];
    int i, j;
    for (i = 0; i < total - 1; i++)
    {
        for (j = i + 1; j < total; j++)
        {
            if (strcmp(names[i], names[j]) > 0)
            {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }

    if (details)
        printf("total %d\n", total_blocks / 2);
    for (int i = 0; i < total; i++)
    {
        char *curr_name = names[i];
        if (curr_name[0] == '.' && hide_loc == 0)
        {
            continue;
        }
        char addressing_element[buffer];
        strcpy(addressing_element, loc);
        strcat(addressing_element, curr_name);
        printing_details(addressing_element, curr_name, details);
    }
    closedir(dir);
    free(dir_stuff);
}
void ls_handler(char *tokens[], int number, const char *working_dir, const char *initial_dir)
{
    char loc[buffer];
    int hide_loc = 0, details = 0;
    int dir[number + 1];
    int dirs = 0;
    int i = 1;
    while (i < number)
    {
        if (tokens[i][0] == '-')
        {
            int j = 1;
            while (j < strlen(tokens[i]))
            {
                //     int op_a = 0, op_l = 0;
                // char *p = (char*)(token[1] + 1);
                // while(*p){
                // 	if(*p == 'a') op_a = 1;
                // 	else if(*p == 'l') op_l = 1;
                // 	else{
                // 		perror("Option not available");
                // 		exit(EXIT_FAILURE);
                // 	}
                // 	p++;
                // }
                if (tokens[i][j] == 'l')
                    details = 1;
                else if (tokens[i][j] == 'a')
                    hide_loc = 1;
                else
                {
                    printf("ls : invalid flag only l and a supported\n");
                    return;
                }
                j++;
            }
        }
        else
        {
            dir[dirs] = i;
            dirs++;
        }
        i++;
    }
    int detail = 1;
    if (dirs == 0)
    {
        detail = 0;
        tokens[number] = strdup(".");
        dir[dirs] = number;
        dirs++;
    }
    int j = 0;
    while (j < dirs)
    {
        //         char buf[512];
        // while((myfile = readdir(mydir)) != NULL)
        // {
        //     sprintf(buf, "%s/%s", argv[1], myfile->d_name);
        //     stat(buf, &mystat);
        int i = dir[j];
        absolute_relativer_addressing(loc, tokens[i], working_dir, initial_dir);
        struct stat stats_dir;
        if (stat(loc, &stats_dir) == 0)
        {
            if ((S_IFDIR & stats_dir.st_mode))
            {
                if (loc[strlen(loc) - 1] != '/')
                {
                    strcat(loc, "/");
                }
                ls_printing(loc, hide_loc, details, 0, tokens[i], detail);
            }
        }
        else if (S_IFREG & stats_dir.st_mode)
        {
            ls_printing(loc, hide_loc, details, 1, tokens[i], detail);
        }
        else
        {
            printf("ls : No such file or directory\n");
        }
        printf("\n");
        j++;
    }
}
