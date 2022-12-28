//Bash made by Vansh Marda
//2021101089
//IIIT H - CSE

#include "headers.h"
char temp[buffer];
void func1(char * path,char* file_name,char type_flag)
{
  DIR * d = opendir(path);
  if(d==NULL) return; 
  struct dirent * dir; 
  while ((dir = readdir(d)) != NULL)
    {
      if(dir-> d_type != DT_DIR){
      if(type_flag=='f' || type_flag=='0'){
            strcpy(temp,path);
            strcat(temp,"/");
            strcat(temp,dir->d_name);
            if(strcmp(file_name,"-1")==0){
                printf("%s", "\033[1m\033[36m");
                printf("%s\n", temp);
            }
            else if(strcmp(file_name,dir->d_name)==0){
                printf("%s", "\033[1m\033[36m");
                printf("%s\n", temp);
            }
      }
      }
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 )
      {
          if(type_flag=='d' || type_flag=='0'){
            strcpy(temp,path);
            strcat(temp,"/");
            strcat(temp,dir->d_name);
            if(strcmp(file_name,"-1")==0){
                printf("%s", "\033[1m\033[33m"); 
                printf("%s\n", temp);
            }
            else if(strcmp(file_name,dir->d_name)==0){
                printf("%s", "\033[1m\033[33m"); 
                printf("%s\n", temp);
            }
          }
        char d_path[255];
        sprintf(d_path, "%s/%s", path, dir->d_name);
        func1(d_path,file_name,type_flag);
      }
    }
    closedir(d); 
}

void final_target_directry(char* arr,char* arr2 , char* arr3){
    if(strcmp(arr,"~")!=0 && strcmp(arr,"..")!=0){
        return ;
    }
    if(strcmp(arr,"~")==0){
        strcpy(arr,arr3);
        return;
    }
    else{
        char temp[100];
        int index=-1;
        int n = strlen(arr2);
        for(int i=n-2;i>=0;i--){
            if(arr2[i]=='/'){
                index=i;
                break;
            }
        }
        int i=0;
        for(i=0;i<index;i++){
            temp[i]=arr2[i];
        }
        temp[i]='\0';
        strcpy(arr,temp);
        return;
    }
}

void discover_handler(char *tok[], int num, char *workingDirectory, char *initialDirector)
{
    //discover <target_dir> <type_flags> <file_name>
    char address[buffer];
    strcpy(address,"./");
    char target_dir_temp[100];
    char file_name[100];    // int count =0;
    char target_dir[100];
    int flag=0;
    //target directory
    if(num==1){
        strcpy(target_dir,".");
    }
    else{
        if(strcmp(tok[1],"-d")!=0 && strcmp(tok[1],"-f")!=0 && tok[1][0]!='"'){
            strcpy(target_dir_temp,tok[1]);
        }
        else{
            strcpy(target_dir_temp,".");
        }

        final_target_directry(target_dir_temp,workingDirectory,initialDirector);
        strcpy(target_dir,target_dir_temp);
        //for file_name
        for(int i=1;i<num;i++){
            if(tok[i][0]=='"'){
                strcpy(file_name,tok[i]);
                flag=1;
                break;
            }
        }
    }
    if(flag==0){
        strcpy(file_name,"-1");
    }
    else{
        int n=strlen(file_name);
        char temp[n-1];
        for(int i=1;i<n-1;i++){
            temp[i-1]=file_name[i];
        }
        temp[n-2]='\0';
        strcpy(file_name,temp);
    }
    //printf("%s %s",target_dir,file_name);
    int count =0;
    char type_flag;
    for(int i=0;i<num;i++){
        if(strcmp(tok[i],"-d")==0 || strcmp(tok[i],"-f")==0){
            count++;
            type_flag=tok[i][1];
        }
    }
    if(count==2 || count==0){
        type_flag='0';
    }
    func1(target_dir,file_name,type_flag);
}