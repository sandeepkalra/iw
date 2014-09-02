#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int *stack=0;
int head = 0;

void Init(int sz){
    stack = (int*) malloc(sizeof(int)*sz);
}
void Destroy() {
    if(stack) free(stack); 
    stack = 0;
}

int push (int a) {
    stack[head++] = a;
    return a;
}

int pop() {
    head --;
    return  stack [ head -1 ]; 
}

int inc(int x, int d)
{
    int i=0;
    for(i=0;i<x;++i) 
		stack[i]+=d;
    return stack[head-1];
}

#define MAX_LEN (2000)
#define CMD_PUSH (1)
#define CMD_POP (2)
#define CMD_INC (3)
#define CMD_INVALID (-1)
#define STRLEN_PUSH (4)
#define STRLEN_POP (3)
#define STRLEN_INC  (3)

int main() {
    char string[MAX_LEN] = { };
    int max_depth=0;
    scanf("%d",&max_depth);
    
    Init(max_depth); 
    while(1)
    {
       
        int cmd = CMD_INVALID;
        int arg1 = 0;
        int arg2 = 0;
        char *p = string;
        
        memset(string,0,MAX_LEN);
        
        scanf(" %[^\t\n]",string);
        if(strncmp(p,"push",STRLEN_PUSH) == 0) {cmd=CMD_PUSH; p+=STRLEN_PUSH; p++;}
        else if(strncmp(p,"pop",STRLEN_POP)==0) {cmd = CMD_POP;}
        else if(strncmp(p,"inc",STRLEN_INC)==0) { cmd = CMD_INC;p+=STRLEN_INC; p++;}
        else  break;
        
        /* Parse the arguments in case of push and inc operations */
        if(cmd == CMD_PUSH) {
            arg1 = atoi(p);
        } 
        else if(cmd == CMD_INC)
        {
            char *first;
            char *second;
            first = strtok_r(p," ",&second);
            arg1 = atoi(first);
            arg2 = atoi(second);
        }
        
        if(cmd==CMD_POP) printf("%d\n",pop());
        else if (cmd == CMD_PUSH) printf("%d\n", push(arg1));
        else if (cmd == CMD_INC) printf("%d\n", inc(arg1, arg2));
        
        fflush(stdout);
    }//while
    
    Destroy();
    return 0;
}
