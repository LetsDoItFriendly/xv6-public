#include "types.h"
#include "stat.h"
#include "fcntl.h" 
#include "user.h" 
#include "spinlock.h"
#include "sleeplock.h"
#include "reenterantlock.h"

int main(int argc, char *argv[]) 
{
	reenterantlockinit();
	int t = reenterantlocktest();
	printf(1, "%d\n", t);
	exit();
}