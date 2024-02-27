#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "sem.h"

struct _s_semaphore{
    int cont;
    struct spinlock lock;
    int used;
};

struct _s_semaphore list[SEM_SIZE];

// Inicializa un array de semaforos.
int
sem_init(void)
{
    int success = false;
    int index = RESERVED;
    while(index<SEM_SIZE){
        list[index].used = false;
        initlock(&list[index].lock, "candado");
        index++;
    }
    if(index==SEM_SIZE)
        success = true;
    
    return success;
}

// Abre y/o inicializa el semáforo “sem” con un
// valor arbitrario “value”.
int
sem_open(void)
{
    int sem;
    int value;
    int opened = false;
    argint(0, &sem);
    argint(1, &value);
    if(list[sem].used==false){
        list[sem].cont = value;
        list[sem].used = true;
        opened = true;
    }
    return opened;
}

// Devuelve el primer semaforo libre para que sea abierto.
int 
sem_get(void)
{
    acquire(&list[RESERVED].lock);
    unsigned int freeIndex=0;
    for(int i=FIRSTFREE ; i<SEM_SIZE && freeIndex==0 ; i++){
        if(list[i].used==false)
            freeIndex=i;
    }
    release(&list[RESERVED].lock);
    return freeIndex;
}

// Libera el semáforo “sem”.
int
sem_close(void) 
{
	int sem , closed = false;
    argint(0, &sem);
    if(list[sem].used==true) {
        list[sem].used = false;
        closed=true;
    }
    return closed;
}

// Incrementa el semáforo ”sem” desbloqueando los procesos
// cuando su valor es 0.
int
sem_up(void)
{
	int sem ;
    argint(0, &sem);
    acquire(&list[sem].lock);
    int check_count = list[sem].cont;
    list[sem].cont++;
    wakeup(&list[sem]);
    release(&list[sem].lock);
    return (check_count < list[sem].cont);
}

// Decrementa el semáforo ”sem” bloqueando los procesos
// cuando su valor es 0. El valor del semaforo nunca puede ser menor a 0
int
sem_down(void)
{    
	int sem;
    argint(0, &sem);
    acquire(&list[sem].lock);
    while(list[sem].cont==0)
        sleep(&list[sem], &list[sem].lock);
    int check_count = list[sem].cont;
    list[sem].cont--;
    release(&list[sem].lock);
    return (check_count > list[sem].cont && list[sem].cont>=0);
}
