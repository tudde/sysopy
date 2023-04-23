#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>

typedef struct sembuf sembuf;
int sem_set;
int customer_cnt = 0;
int shm_id;
int* last_served;

void handle_exit(){
    shmdt(last_served);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_set,0,IPC_RMID);
    exit(-1);
}
void do_haircut(){
    int haircut_time = rand()%7+1;
    sleep(haircut_time);
    printf("Klient %d obsluzony\n", customer_cnt);
    
}
void free_sem(int n){
    sembuf op[1];
    op[0].sem_op = 1;
    op[0].sem_num = n;
    semop(sem_set,op,1);
}




int main(int argc, char *argv[]){
    // argumenty: m (fryzjerzy), n (fotele), p (poczekalnia)
    if(argc<4){
        printf("Too few arguments.\n");
    }

    key_t sem_key = ftok(getenv("HOME"),1);
    key_t shm_key = ftok(getenv("HOME"),1);
    sem_set = semget(sem_key,3,IPC_CREAT | 0666);
    shm_id = shmget(shm_key, sizeof(int), IPC_CREAT | 0666);

    signal(SIGINT,handle_exit);
    signal(SIGQUIT,handle_exit);

    semctl(sem_set, 0, SETVAL, atoi(argv[1]));
    semctl(sem_set, 1, SETVAL, atoi(argv[2]));
    semctl(sem_set, 2, SETVAL, atoi(argv[3]));


    //id ostatniego klienta, ktorego zaczeto strzyc albo sobie poszedl
    last_served = (int*) shmat(shm_id, NULL,0);
    *last_served = 0;
    

    sembuf curop[1];

    while(1){
        int sleep_time = (rand()%2+1);
        sleep(sleep_time);
        int val1=semctl(sem_set, 0, GETVAL);
        int val2=semctl(sem_set, 1, GETVAL);
        int val3=semctl(sem_set, 2, GETVAL);
        printf("Fryzjerow: %d | Foteli: %d | Poczekalnia: %d\n",val1,val2,val3);
        customer_cnt++;
        int pid = fork();
        if(pid == 0){
            printf("Klient %d przyszedl\n", customer_cnt);
            
            curop[0].sem_op = -1;
            curop[0].sem_num = 0;
            curop[0].sem_flg = IPC_NOWAIT;

            
            if(semop(sem_set,curop,1)!=-1){
                printf("Klient %d znalazl fryzjera\n", customer_cnt);

                curop[0].sem_num = 1;
                if(semop(sem_set,curop,1)!=-1){
                    printf("Klient %d znalazl fotel\n", customer_cnt);
                    if(customer_cnt>*last_served){
                        *last_served=customer_cnt;
                    }
                    do_haircut();
                    free_sem(1);
                }
                else{
                    curop[0].sem_num = 2;
                    if(semop(sem_set,curop,1)!=-1){
                        printf("Klient %d trafil do poczekalni\n", customer_cnt);
                        while(customer_cnt<*last_served+1);

                        curop[0].sem_num=1;
                        curop[0].sem_flg=0;
                        curop[0].sem_op=-1;

                        semop(sem_set,curop,1);
                        free_sem(2);

                        printf("Klient %d znalazl fotel\n", customer_cnt);
                        if(customer_cnt>*last_served){
                            *last_served=customer_cnt;
                        }
                        do_haircut();
                        free_sem(1);



                    }
                    else{
                        printf("Klient %d nie znalazl miejsca w poczekalni i wyszedl\n", customer_cnt);
                        if(customer_cnt>*last_served){
                            *last_served=customer_cnt;
                        }
                    }
                    
                }
                free_sem(0);
            
            }
            else{
                printf("Klient %d nie znalazl fryzjera i wyszedl\n", customer_cnt);
                if(customer_cnt>*last_served){
                    *last_served=customer_cnt;
                }
                
                
            }

            
        
            exit(0);

        }



    }

}