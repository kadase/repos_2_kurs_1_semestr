#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define SAFE(msg, call)\
if ((call) == -1)\
{\
    perror(msg);\
    exit(1);\
}\

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments");
        return 1;
    } 

    pid_t pid = fork();
    if (pid == 0)
    {
        if (strcmp(argv[1], "execlp") == 0)
        {
            SAFE("Error with execlp", (execlp("mkdir", "mkdir", "new_papka1", (char*)0)))
        }
        else if (strcmp(argv[1], "execvp") == 0)
        {
            char* arg[6] = {"grep", "grep", "t.txt", "hello", NULL};
            SAFE("Error with execvp", (execvp(*arg, arg)))
        }
        else if (strcmp(argv[1], "execl") == 0)
        {
            SAFE("Error with execl", (execl("hello", "hello", (char*)0)))
        }
        else
        {
            printf("Error. Unknown function, write another one");
        }
    }   
    else 
    {
        wait(NULL);
    }
    return 0;
}