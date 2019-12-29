#include "types.h"
#include "user.h"


int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf(1, "enter num of childs please.\n");
        exit();
    }

    int childNums = atoi(argv[1]);

    int pid = getpid();
    printf(1, "parent pid : %d\n", pid);
    if(initBarrier(childNums+1, 0) == -1){
        printf(1, "Error in initializing barrier.\n");
        return -1;
    }
    printf(1, "barrier initialized to %d.\n", childNums + 1);
    
    int i;
    for(i = 0; i < childNums; i++)
    {
        if(pid > 0)
        {
            pid = fork();
            if(pid > 0)
            {
            }
            if(pid == 0 )
                break;
        }
    }
       
    for (i = 0; i < childNums + 1; i++){
        if(getpid() == 3+i){
            sleep((childNums-i+1) * 300);
            printf(1, "process with pid %d slept for %d\n", getpid(), (childNums-i+1) * 300);
        }
    }
    
    if(waitBarrier(0) == -1){
        printf(1, "Error in waiting for others.\n");
        return 1;
    };
    
    printf(1, "%d", getpid());

    if(pid == 0)
    {
        
    }
    else
    {
        int i;
        for(i = 0; i < childNums; i++)
            wait();
        printf(1, "Main user program finished.\n");
    }
  exit();
}