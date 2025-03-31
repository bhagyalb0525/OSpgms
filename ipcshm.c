//c program to implement producer consumer problem using shared memory
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#define SHM_KEY 1234
typedef struct
{
    int data;
    int flag;
}SharedMemory;

int main()
{
    int shmid=shmget(SHM_KEY,sizeof(SharedMemory),0666|IPC_CREAT);
    if(shmid==-1)
    {
        perror("shmget failed");
        exit(1);
        
    }
    SharedMemory *shm=(SharedMemory *)shmat(shmid,NULL,0);
    shm->flag=0;
    
    int pid=fork();
    if(pid<0)
    {
        printf("fork failed");
        exit(1);
    }
    else if(pid>0)
    {
        for(int i=0;i<5;i++)
        {
            while(shm->flag==1);
            
            shm->data=i+1;
            printf("producer produced %d\n",shm->data);
            shm->flag=1;
            sleep(1);
            
        }
    }
    else if(pid==0)
    {
        for(int i=0;i<5;i++)
        {
            while(shm->flag==0);
            
            printf("consumer consumed %d\n",shm->data);
            shm->flag=0;
            sleep(1);
        }
    }
    if(pid>0)
    {
        wait(NULL);
    }
    

}
