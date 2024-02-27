#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>


static void ping(){
printf("Ping\n");
}

static void pong(){
printf("\tPong\n");
}

int main(int argc, char *argv[]){
    int cant = 0; // para causar error
    
    //checkeo de errores en la cantidad de argumentos de entrada de pingpong //
    if(argv[1] == NULL){
        printf("ERROR: pingpong no tiene argumentos\n");
    }
    else{
        cant = atoi(argv[1]);
    }

    //checkeo de error en la cantidad de iteraciones de pingpong //
    if(cant <= 0){
        printf("ERROR: valor de pingpong debe ser mayor que 0\n");
    }
    else{
        int sem_ping = sem_get();
	sem_open(sem_ping,1);
        int sem_pong = sem_get();
	sem_open(sem_pong,0);
        if(sem_ping==0 || sem_pong==0){
                exit(-1);
        }
        int rc = fork();
        for (int i = 0; i < cant; ++i){   
            if(rc<0){
                exit(-1);
            }

            if(rc==0){
                sem_down(sem_ping);
                ping();
                sem_up(sem_pong);
            }
            if(rc>0){
                sem_down(sem_pong);
                pong();
                sem_up(sem_ping);
            }
        }
        sem_close(sem_ping);
        sem_close(sem_pong);
    }
    return 0;
}
