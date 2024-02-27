#ifndef SEM_H
#define SEM_H

#define SEM_SIZE 64
#define RESERVED 0
#define FIRSTFREE 1
#define false 0
#define true 1
typedef struct _s_semaphore* semaphore;


int sem_open(void);

// Libera el semáforo “sem”.
int sem_close(void);

// Incrementa el semáforo ”sem” desbloqueando los procesos
// cuando su valor es 0.
int sem_up(void);

// Decrementa el semáforo ”sem” bloqueando los procesos
// cuando su valor es 0. El valor del semaforo nunca puede ser menor a 0

int sem_down(void);

int sem_get(void);

int sem_init(void);

#endif