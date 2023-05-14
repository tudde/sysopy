#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t elves_mutex;
pthread_cond_t elves_cond;
pthread_mutex_t reindeer_mutex;
pthread_cond_t reindeer_cond;
pthread_mutex_t wakes_mutex;
pthread_cond_t wakes_cond;

int should_wake = 0;
int elves_waiting = 0;
int reindeer_waiting = 0;
int times_delivered = 0;
int* elves_waiting_IDs;
int* elf_IDs;
int* reindeer_IDs;


void* reindeer_f(void* arg){
    int reindeerID = *(int*)arg;

    while(times_delivered<3){
        usleep((rand()%5000+5000)*1000);
        pthread_mutex_lock(&reindeer_mutex);
        reindeer_waiting++;
        if(reindeer_waiting==9){
            pthread_mutex_lock(&wakes_mutex);
            printf("Renifer: wybudzam Mikołaja, ID %d\n",reindeerID);
            should_wake=1;
            //wait until santa finishes delivering
            pthread_cond_broadcast(&wakes_cond);
            pthread_mutex_unlock(&wakes_mutex);
        }
        else{
            printf("Renifer: czeka %d reniferów na Mikołaja, ID %d\n", reindeer_waiting, reindeerID);
        }
        pthread_cond_wait(&reindeer_cond,&reindeer_mutex);
        pthread_mutex_unlock(&reindeer_mutex);        
    }
    return NULL;
}

void* elf_f(void* arg){
    int elfID = *(int*)arg;
    
    while(times_delivered<3){
        usleep((rand()%3000+2000)*1000);

        pthread_mutex_lock(&elves_mutex);
        if(elves_waiting<3){ 
            //waits for santa
            elves_waiting_IDs[elves_waiting]=elfID;
            elves_waiting++;
            if(elves_waiting==3){
                pthread_mutex_lock(&wakes_mutex);
                printf("Elf: wybudzam Mikołaja, ID %d\n", elfID);
                should_wake=1;
                pthread_cond_broadcast(&wakes_cond);
                pthread_mutex_unlock(&wakes_mutex);
            }else{
                printf("Elf: czeka %d elfów na Mikołaja, ID %d\n", elves_waiting, elfID);
            }
            //wait until santa finishes helping
            pthread_cond_wait(&elves_cond,&elves_mutex);
            //printf("Elf: Mikołaj rozwiązuje problem, ID %d\n", elfID);
        }
        else{ 
            //deals with the problem themself
            printf("Elf: samodzielnie rozwiązuję swój problem, ID %d\n", elfID);
        }
        pthread_mutex_unlock(&elves_mutex);
    }
    return NULL;
}

void* santa_f(void* arg){
    while(times_delivered<3){

        //wait until something sends wake up signal
        pthread_mutex_lock(&wakes_mutex);
        while(should_wake==0){
            pthread_cond_wait(&wakes_cond,&wakes_mutex);
        }
        printf("Mikołaj: budzę się\n");
        should_wake=0;
        pthread_mutex_unlock(&wakes_mutex);

        //check elves
        pthread_mutex_lock(&elves_mutex);
        if(elves_waiting==3){
            printf("Mikołaj: rozwiązuje problemy elfów %d %d %d\n",elves_waiting_IDs[0],elves_waiting_IDs[1],elves_waiting_IDs[2]);
            usleep((rand()%1000+1000)*1000);
            elves_waiting=0;
            pthread_cond_broadcast(&elves_cond);
        }
        pthread_mutex_unlock(&elves_mutex);

        //check reindeer
        pthread_mutex_lock(&reindeer_mutex);
        if(reindeer_waiting==9){
            printf("Mikołaj: dostarczam zabawki\n");
            usleep((rand()%2000+2000)*1000);
            reindeer_waiting=0;
            times_delivered++;
            pthread_cond_broadcast(&reindeer_cond);
        }
        pthread_mutex_unlock(&reindeer_mutex);

        printf("Mikołaj: zasypiam\n");
    }

    //free potentially reamining elves and reindeer after ending
    pthread_cond_broadcast(&elves_cond);
    pthread_cond_broadcast(&reindeer_cond);
    return NULL;
}


int main(int argc, char *argv[]){

    pthread_mutex_init(&elves_mutex,NULL);
    pthread_mutex_init(&reindeer_mutex,NULL);
    pthread_mutex_init(&wakes_mutex,NULL);
    pthread_cond_init(&wakes_cond,NULL);
    pthread_cond_init(&elves_cond,NULL);
    pthread_cond_init(&reindeer_cond,NULL);

    pthread_t santa;
    pthread_t elves[10];
    pthread_t reindeer[9];

    
    reindeer_IDs = malloc(9*sizeof(int));
    elf_IDs = malloc(10*sizeof(int));
    elves_waiting_IDs=malloc(3*sizeof(int));


    pthread_create(&santa, NULL, santa_f, NULL);
    for(int i=0;i<10;i++){
        elf_IDs[i]=i;
        pthread_create(&elves[i], NULL, elf_f, &elf_IDs[i]);
    }
    for(int i=0;i<9;i++){
        reindeer_IDs[i]=i;
        pthread_create(&reindeer[i], NULL, reindeer_f, &reindeer_IDs[i]);
    }


    pthread_join(santa,NULL);
    for(int i=0;i<10;i++){
        pthread_join(elves[i],NULL);
    }
    for(int i=0;i<9;i++){
        pthread_join(reindeer[i],NULL);
    }
    

    free(reindeer_IDs);
    free(elf_IDs);
    free(elves_waiting_IDs);
    pthread_mutex_destroy(&elves_mutex);
    pthread_mutex_destroy(&reindeer_mutex);
    pthread_mutex_destroy(&wakes_mutex);
    pthread_cond_destroy(&wakes_cond);
    pthread_cond_destroy(&elves_cond);
    pthread_cond_destroy(&reindeer_cond);
}
