//c program to implement dining philosophers problem
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t c[5];
pthread_t p[5];

void *dine(void *args)
{
    int i=*(int *)args;
    printf("philosopher %d is hungry\n",i+1);
    if(i==4)
    {
        sem_wait(&c[(i+1)%5]);
        sem_wait(&c[i]);
    }
    else{
        sem_wait(&c[i]);
        sem_wait(&c[(i+1)%5]);
        
    }
    printf("philosopher %d is eating with chopsticks%d and %d\n",i+1,i,(i+1)%5);
    sleep(2);
    printf("philosopher %d released chopsticks an now thinking\n",i+1);
    sem_post(&c[i]);
    sem_post(&c[(i+1)%5]);
    return NULL;
}
int main()
{
    int i,id[5];
    for(i=0;i<5;i++)
    {
        sem_init(&c[i],0,1);
        id[i]=i;
    }
    for(int i=0;i<5;i++)
    {
        pthread_create(&p[i],NULL,dine,&id[i]);
    }
    for(int i=0;i<5;i++)
    {
        pthread_join(p[i],NULL);
        
    }
    for(int i=0;i<5;i++)
    {
        sem_destroy(&c[i]);
    }
    return 0;
}
