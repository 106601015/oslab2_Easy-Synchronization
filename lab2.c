#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/* Hint
 * sem_init();
 * sem_destroy();
 * sem_wait();
 * sem_post();
 * pthread_mutex_lock();
 * pthread_mutex_unlock();
 */

#define LEVEL 3
#define LOOP 5

static int answer = 0;
//static int t1=0,t2=0,t3=0;
sem_t bs1, bs2, bs3;

void *Task(void* arg)
{
    for (int j = 0; j < LEVEL; j++) {
        sem_wait(&bs1);////stop util bs1>0
    	for (int i = 0; i < LOOP; i++) {
            answer++;
            printf("Task0, ans : %d\n", answer);
	}
	sem_post(&bs2);////next is task1, so bs2+=1

	//sem_getvalue(&bs1, &t1);
        //sem_getvalue(&bs2, &t2);
        //sem_getvalue(&bs3, &t3);
        //printf("t1:%d t2:%d t3:%d\n",t1,t2,t3);
    }   
    pthread_exit(0);
}

void *Task1(void* arg)
{
    for (int j = 0; j < LEVEL; j++) {
        sem_wait(&bs2);////stop util bs2>0
        for (int i = 0; i < LOOP; i++) {
            answer++;
            printf("Task1, ans : %d\n", answer);
        }
	sem_post(&bs3);////next is task2, so bs3+=1
	//sem_getvalue(&bs1, &t1);
        //sem_getvalue(&bs2, &t2);
        //sem_getvalue(&bs3, &t3);
        //printf("t1:%d t2:%d t3:%d\n",t1,t2,t3);
    }   
    pthread_exit(0);
}

void *Task2(void* arg)
{
    for (int j = 0; j < LEVEL; j++) {
        sem_wait(&bs3);////stop util bs3>0
	for (int i = 0; i < LOOP; i++) {
            answer++;
            printf("Task2, ans : %d\n", answer);
        }
	sem_post(&bs1);////next is task, so bs1+=1
	//sem_getvalue(&bs1, &t1);
	//sem_getvalue(&bs2, &t2);
	//sem_getvalue(&bs3, &t3);
        //printf("t1:%d t2:%d t3:%d\n",t1,t2,t3);
    }   
    pthread_exit(0);
}


int main()
{
    pthread_t t1; 
    pthread_t t2; 
    pthread_t t3; 

    //init three sem with 0,1,0, then os will run t2 first
    sem_init(&bs1, 0, 0);
    sem_init(&bs2, 0, 1);
    sem_init(&bs3, 0, 0);

    pthread_create(&t1, NULL, Task, NULL);
    pthread_create(&t2, NULL, Task1, NULL);
    pthread_create(&t3, NULL, Task2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
