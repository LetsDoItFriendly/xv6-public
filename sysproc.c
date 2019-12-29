#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "syscall.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "reenterantlock.h"

struct reenterantlock rtest;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_reenterantlocktest(void)
{
  acquirereenterantlock(&rtest);
  cprintf("lock 1 \n");
  printlock(&rtest);
  return 0; 
}

int
sys_reenterantunlock(void)
{
  releasereenterantlock(&rtest);
  cprintf("unlock 1 \n");
  printlock(&rtest);
  return 0; 
}


void
sys_reenterantlockinit(void)
{
  initreenterantlock(&rtest, "TestReenterantLock");
  cprintf("init \n");
  printlock(&rtest);
}

int sys_initBarrier(void){
  int num, barrierNum;
  argint(0, &num);
  argint(1, &barrierNum);
  return initBarr(num, barrierNum);
}

int sys_waitBarrier(void){
  int barrierNum;
  argint(0, &barrierNum);
  return waitBarr(barrierNum);
}
