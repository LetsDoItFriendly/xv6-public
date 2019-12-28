#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "reenterantlock.h"


void initreenterantlock(struct reenterantlock *lock, char* name)
{
  	initlock(&lock->lk, "reentrant lock");
	lock->locked = 0;
    lock->name = name;
    lock->pid = 0;
    lock->counter = 0;
}


void acquirereenterantlock(struct reenterantlock *lock)
{
  if (lock->counter > 0)
  {
	lock->counter++;
  }else{
	acquire(&lock->lk);
	while (lock->locked) {
		sleep(lock, &lock->lk);
	}
	lock->locked = 1;
	lock->pid = myproc()->pid;
	lock->counter++;
	release(&lock->lk);
  }
}

void releasereenterantlock(struct reenterantlock *lock)
{
	lock->counter--;
	if (lock->counter == 0)
	{
		acquire(&lock->lk);
		lock->locked = 0;
		lock->pid = 0;
		wakeup(lock);
		release(&lock->lk);
	}	
}


