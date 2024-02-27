##Objetivos: 
    1. Implementar 4 syscalls: sem_open(), sem_up(), sem_down(),sem_close().
        Las syscalls irán en el archivo kernel/syscalls.c (también hay que toquetear algun otro archivo)
        
        int sem_open(int sem, int value) → Abre y/o inicializa el semáforo “sem” con un
        valor arbitrario “value”.

        int sem_close(int sem) → Libera el semáforo “sem”.

        int sem_up(int sem) → Incrementa el semáforo ”sem” desbloqueando los procesos
        cuando su valor es 0.

        int sem_down(int sem) → Decrementa el semáforo ”sem” bloqueando los procesos
        cuando su valor es 0. El valor del semaforo nunca puede ser menor a 0

    2. Implementar un programa de espacio de usuario “pingpong” que funcione de la
    “manera natural”.
        El programa estará en user/pingpong.c
