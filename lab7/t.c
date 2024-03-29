/*************************************
Luke Darrow 11349190
CptS 460 Lab 4 t.c
*************************************/

#include "type.h"

PROC proc[NPROC], *running, *freeList, *readyQueue, *sleepList;
int procSize = sizeof(PROC);
int nproc = 0;

int color;

//moved this from vid.c to here so I can mess with it
int row, column; // logical row, col position
//moved out of time
u16 hour, min, sec;

int body();
char *pname[]={"Sun", "Mercury", "Venus", "Earth",  "Mars", "Jupiter", 
               "Saturn", "Uranus", "Neptune" };

PIPE pipe[NPIPE];	//NPIPE = 10
OFT oft[NOFT];		//NOFT = 20

#include "io.c"               //my io.c
#include "queue.c"            //my queue.c
#include "loader.c"           //my loader.c

#include "wait.c"             // YOUR wait.c   file
#include "kernel.c"           // YOUR kernel.c file
#include "int.c"              // YOUR int.c    file
#include "pipe.c"             //piping stuff

#include "vid.c"
#include "timer.c"

//initialize function
int init()
{
    PROC *p;
    int i;
    color = 0x0C;

    printf("init ....");
    //initialize all the procs
    for (i=0; i<NPROC; i++)
    {
        p = &proc[i];
        p->pid = i;
        p->status = FREE;
        p->priority = 0;
        strcpy(proc[i].name, pname[i]);
        p->inkmode = 1;
        p->next = &proc[i+1];
    }
    //all procs should be in freeList
    freeList = &proc[0];
    proc[NPROC-1].next = 0;
    readyQueue = sleepList = 0;

    //initialize all OFT and PIPE structures
    for(i = 0; i < NOFT; i++)
        oft[i].refCount = 0;
    for(i = 0; i < NPIPE; i++)
        pipe[i].busy = 0;

    //create P0 as running
    p = get_proc(&freeList);
    p->status = RUNNING;
    p->ppid   = 0;
    p->parent = p;
    running = p;
    nproc = 1;
    printf("done\n");
} 

//scheduler
int scheduler()
{
    if (running->status == RUNNING){
	running->status = READY;
        enqueue(&readyQueue, running);
    }
    running = dequeue(&readyQueue);
    running->status = RUNNING;
    color = (running->pid % 6) + 0x000A;
    //this is for task 2 lab 7
    //running->time = 5;
}

int int80h(), tinth();

int set_vector(u16 vector, u16 handler)
{
     put_word(handler, 0, vector<<2);
     put_word(0x1000,  0,(vector<<2) + 2);
}

//main function, execution starts here
main()
{
    int i = 0;
    vid_init();//initialize video

    printf("MTX starts in main()\n");
    init(); // initialize and create P0 as running
    set_vector(80, int80h);

    for(i = 0; i < 4; i++)
        kfork("/bin/u1");     // P0 kfork() P1

    //timer init
    lock();
    set_vector(8,tinth);
    timer_init();

    while(1)
    {
      printf("P0 running\n");
      if (nproc == 2 && proc[1].status != READY)
          printf("no runable process, system halts\n");
      while(!readyQueue);
      printf("P0 switch process\n");
      tswitch();         // P0 switch to run P1
   }
}

