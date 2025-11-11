#include "segdef.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



void init(int *semid_ptr,int *shmid_ptr)
{
    int semid;
    semid = semget(cle, 3, 0);

    if (semid == -1)
    {
        printf("semget error");
        
    }
    int shmid;
    shmid = shmget(cle, segsize, 0);

    if (shmid == -1)
    {
        printf("shmget error");

    }
    init_rand();
    *semid_ptr=semid;
    *shmid_ptr=shmid;

}


void make_request(int shmid, int req,int semid,int fork){
    acq_sem(semid,seg_dispo);
    segment* seg=(segment*) shmat(shmid,0,0);
    
    seg->pid=getpid();
    seg->req=req;
    long sum=0.0;
    for(int i =0;i<maxval;i++){
        long temp=getrand();
        seg->tab[i]=temp;
        sum+=temp;
    }
    sum=sum/((long)maxval);
    acq_sem(semid,seg_init);
    wait_sem(semid,res_ok);

    long tempresult= seg->result;

    lib_sem(semid,seg_init);
    lib_sem(semid,seg_dispo);
    
    shmdt(seg);
        if(tempresult!=sum){
        printf("error on request %d of fork %d \n",req,fork);
    }
}

int main(void)
{
    int semid;
    int shmid;
    int MaxFork=100;
    int MaxRequest=50;
    pid_t pid;
    init(&semid,&shmid);
    for(int i=0;i<MaxFork;i++){
        pid = fork();
        if(pid==-1){
            perror("fork");
        }
        if(pid==0){
            init_rand();
            for(int j=0;j<MaxRequest;j++){
            make_request(shmid,j,semid,i);
        }
        exit(EXIT_SUCCESS);
        };
    }

    int status;
    while (wait(&status)>0){}
    printf("\n finished \n");
    exit(EXIT_SUCCESS);
}