#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>  
#include <stdlib.h>
#include <time.h> 
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>
int control=0;
char input[6];
void MyAlarm(int);
struct pid{
    pid_t pid;
    int number;
}process[99];
int main () {
    struct timespec tw = {5,0};
   struct timespec tr;
    int counter=0;
    process[counter].number=counter;
    char  buffer[3];
    while(true){
    int operator=0;
    char name[10]="child_";    
    signal(SIGALRM,MyAlarm);
    printf("%s",input);
    fgets(input,sizeof(input),stdin);
    for(int i=0;i<6;i++){
        if(input[i]=='\n'){
            input[i]='\0';
        }
    }
     if(strstr(input,"q")!=0){
        for(int i=0;i<99;i++){
        kill(process[i].pid,SIGKILL);
        }
        break;
    }
    if(strstr(input,"+")!=0){
        operator=1;
    }
    if(strstr(input,"-")!=0){
        operator=2;
    }
    if(strstr(input,"l")!=0){
        operator=3;
    }
     if(strstr(input,"k")!=0){
        operator=4;
    }
     if(strstr(input,"s")!=0){
        if(input[1]>=48)
        {
        int a =input[1]-48;
            if(input[2]>=48){
            a=a+input[2]-39;
            }
        kill(process[a].pid,SIGUSR1);
     }
     else{
        operator=5;
     }
    }
     if(strstr(input,"g")!=0){
        if(input[1]>=48)
        {
        int a =input[1]-48;
            if(input[2]>=48){
            a=a+input[2]-39;
            }
        kill(process[a].pid,SIGUSR2);
     }
     else{
        operator=6;
     }
    }
    if(strstr(input,"p")!=0){
        for(int i=0;i<counter;i++){
        kill(process[i].pid,SIGUSR1);
        }
        
        if(input[1]>=48)
        {
        int a =input[1]-48;
            if(input[2]>=48){
            a=a+input[2]-39;
            }
        kill(process[a].pid,SIGUSR2);
        alarm(5);
    }
    }
    switch(operator){
        case 1:{
         memset(buffer,0,3);
            sprintf(buffer,"%d",process[counter].number);
            strcat(name,buffer);
            char *args[]={name,(char*)0};
             process[counter].pid=fork();
            if(process[counter].pid==0){
                execve("./child",args,NULL);
                }
                  counter++;
                process[counter].number=counter;
                control=counter;
            break;
        }
        case 2:{
            if(counter==0){
                printf("Have't any child\n");
                break;
            }
           counter--;
             kill(process[counter].pid,SIGKILL);
            break;
        }
        case 3:{
            printf("Parent PID=%d\n",getpid());
            for(int i=0;i<counter;i++){
                printf("child_%d PID=%d\n",process[i].number,process[i].pid);
            }
            break;
        }
        case 4:{
        for(int i=0;i<counter;i++){
        if(kill(process[i].pid,SIGKILL)==0){
            printf("child_%d was delete\n",i);
        }
        }
        counter=0;
            break;
        }
        case 5:{
            if(counter==0){
                printf("Have't any child\n");
                break;
            }
              for(int i=0;i<counter;i++){
        kill(process[i].pid,SIGUSR1);
        }
            break;
        }
        case 6:{
            if(counter==0){
                printf("Have't any child\n");
                break;
            }
              for(int i=0;i<counter;i++){
        kill(process[i].pid,SIGUSR2);
        }
            break;
        }
    }
  memset(input,0,6);
    memset(name,0,10);
  
   }
exit(0);
}
void MyAlarm(int var){
    int s=var;
    for(int i=0;i<control;i++){
        kill(process[i].pid,SIGUSR2);
        }
}
