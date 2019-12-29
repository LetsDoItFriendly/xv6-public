#include "types.h"
#include "stat.h"
#include "fcntl.h" 
#include "user.h" 
#include "spinlock.h"
#include "sleeplock.h"
#include "reenterantlock.h"

int g(int num){
	reenterantlocktest();
	if (num == 1){
		reenterantunlock();
		return 1;
	}
	int a = num * g(num - 1);
	reenterantunlock();
	return a;
}

int main(int argc, char *argv[]) 
{
	// int pid;
	reenterantlockinit();
	printf(1, "%d\n", g(4));
	// pid = fork();
	// // reenterantlocktest();
	// if (pid < 0)
	// {
	// 	printf(1, "%s\n", "fork error");
	// }
	// else if(pid > 0){
	// 	wait();
	// }
	exit();
}

