#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t pid;
    printf("Main Process ID : %d\n\n",(int)getpid());
    pid = fork();//fork0

    if (pid == 0)
    {
        printf("Fork 1. I'm the child %d, my parent is %d.\n",(int)getpid(),(int)getppid());
        pid = fork();//fork4
        if (pid > 0)
            wait(NULL);
        else if (pid == 0)
        {
            printf("Fork 4. I'm the child %d, my parent is %d.\n",(int)getpid(),(int)getppid());
            pid = fork();//fork5
            if (pid > 0)
                wait(NULL);
            else if (pid == 0)
                printf("Fork 5. I'm the child %d, my parent is %d.\n",(int)getpid(),(int)getppid());
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        pid = fork();//fork2
        if (pid > 0)
            wait(NULL);
        else if (pid == 0)
            printf("Fork 2. I'm the child %d, my parent is %d.\n",(int)getpid(),(int)getppid());

        pid = fork();//fork3
        if (pid > 0)
            wait(NULL);
        else if (pid == 0)
            printf("Fork 3. I'm the child %d, my parent is %d.\n",(int)getpid(),(int)getppid());
    }
    else//fork() < 0
    {
        printf("error.\n");
    }

    return 0;
}
