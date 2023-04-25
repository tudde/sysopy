#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int customer_cnt = 0;
int* last_served;

void handle_exit(){
    sem_unlink("barbers");
    sem_unlink("chairs");
    sem_unlink("waiting");
    shm_unlink("last_served");
    exit(-1);
}
void do_haircut(){
    int haircut_time = rand()%7+1;
    sleep(haircut_time);
    printf("Klient %d obsluzony\n", customer_cnt);
    
}


int main(int argc, char *argv[]){
    // argumenty: m (fryzjerzy), n (fotele), p (poczekalnia)
    if(argc<4){
        printf("Too few arguments.\n");
    }

    sem_t* barbers = sem_open("barbers", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR, atoi(argv[1]));
    sem_t* chairs = sem_open("chairs", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR, atoi(argv[2]));
    sem_t* waiting = sem_open("waiting", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR, atoi(argv[3]));
    
    int fd = shm_open("last_served", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
    ftruncate(fd, sizeof(int));
    int* last_served = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
    *last_served=0;

    signal(SIGINT,handle_exit);
    signal(SIGQUIT,handle_exit);

    int *val1 = malloc(sizeof(int));
    int *val2 = malloc(sizeof(int));
    int *val3 = malloc(sizeof(int));
    

    while(1){
        int sleep_time = (rand()%2+1);
        sleep(sleep_time);
        sem_getvalue(barbers, val1);
        sem_getvalue(chairs, val2);
        sem_getvalue(waiting, val3);
        printf("Fryzjerow: %d | Foteli: %d | Poczekalnia: %d\n",*val1,*val2,*val3);
        customer_cnt++;
        int pid = fork();
        if(pid == 0){
            printf("Klient %d przyszedl\n", customer_cnt);

   
            if(sem_trywait(barbers)!=-1){
                printf("Klient %d znalazl fryzjera\n", customer_cnt);

                if(sem_trywait(chairs)!=-1){
                    printf("Klient %d znalazl fotel\n", customer_cnt);
                    if(customer_cnt>*last_served){
                         *last_served=customer_cnt;
                    }
                    do_haircut();
                    sem_post(chairs);
                }
                else{
            
                    if(sem_trywait(waiting)!=-1){
                        printf("Klient %d trafil do poczekalni\n", customer_cnt);
                        while(customer_cnt<*last_served+1);

                        sem_wait(chairs);
                        sem_post(waiting);

                        printf("Klient %d znalazl fotel\n", customer_cnt);
                        if(customer_cnt>*last_served){
                            *last_served=customer_cnt;
                        }
                        do_haircut();
                        sem_post(chairs);



                    }
                    else{
                        printf("Klient %d nie znalazl miejsca w poczekalni i wyszedl\n", customer_cnt);
                        if(customer_cnt>*last_served){
                            *last_served=customer_cnt;
                        }
                    }
                    
                }
                sem_post(barbers);
            
            }
            else{
                printf("Klient %d nie znalazl fryzjera i wyszedl\n", customer_cnt);
                // if(customer_cnt>*last_served){
                //     *last_served=customer_cnt;
                // }
                
                
            }

            
        
            exit(0);

        }



    }

}
