/*************************************
Luke Darrow 11349190
CptS 460 pv.c
pg 182 of book
*************************************/

typedef struct semaphore{
    int value;
    PROC *queue;
}SEMAPHORE;

extern int int_off(), int_on();

int P(SEMAPHORE *s)
{
    int sr;

    sr = int_off(); //interrupt off

    s->value--;

    if (s->value < 0){
       running->status = BLOCK;
       enqueue(&(s->queue), running);
       tswitch(); //switch proccess
       int_on(sr);
    }
    else{
       int_on(sr);
    }
}

int V(SEMAPHORE *s)
{
    int sr;
    PROC *p;
    sr = int_off(); //interrupt off

    s->value++;

    if (s->value<=0){
        p = dequeue(&(s->queue));
        p->status=READY;
        enqueue(&readyQueue, p);
    }

    int_on(sr);
}
