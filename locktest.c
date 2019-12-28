#include "types.h"
#include "stat.h"
#include "fcntl.h" 
#include "user.h" 
#include "spinlock.h"
#include "sleeplock.h"
#include "reenterantlock.h"

int main(int argc, char *argv[]) 
{
	int pid;
	reenterantlockinit();
	pid = fork();
	reenterantlocktest();
	if (pid < 0)
	{
		printf(1, "%s\n", "fork error");
	}
	else if(pid > 0){
		wait();
	}
	exit();
}