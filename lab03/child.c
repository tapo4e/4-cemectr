#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>  
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
int output=0;
int nanosleep(const struct timespec *req, struct timespec *rem);
static void sig(int);
struct  number{
    int first;
    int second;
};
struct counter{
    int first;
    int second;
    int third;
    int fourth;
} count;
    
int main(int argc,char* argv[]){
    signal(SIGUSR1,sig);
    signal(SIGUSR2,sig);
    char buffer[1024];
    int c=0;
   struct timespec tw = {0,125000000};
   struct timespec tr;
   while(1){
   c++;
    struct number d={rand()%2,rand()%2};
    if(nanosleep (&tw, &tr)==0){
        if(d.first==0 && d.second==0){
        count.first++;
        }
        else if(d.second==1 && d.first==0){
            count.second++;
        }
        else if(d.first==1 && d.second==0){
            count.third++;
        }
        else{
            count.fourth++;
        }
    }
    if(c==20){
        sprintf(buffer,"%s PID=%d {%d, %d, %d, %d}\n",argv[0],getpid(),count.first,count.second,count.third,count.fourth);
       count.first=0;
       count.second=0;
       count.third=0;
       count.fourth=0;
        char *ptr=buffer;
        if(output==0){
       while(*ptr!='\0' && fputc(*ptr++,stdout)!=EOF);
        }
       c=0;
    }
    
   }
    return 0;
} 
void sig(int signl){
    switch(signl){
    case SIGUSR1:{
output=1;
break;
    }
    case SIGUSR2:{
output=0;
break;
    }
    }
}