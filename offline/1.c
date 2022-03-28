#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 10
#define BufferSize 1

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
int resource = 0;
int e = BufferSize;
int f = 0;
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
        resource++;
        item = resource;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("Producer %d: Inserting data %d\n", *((int *)pno),item);
        f++;
        e--;

        printf("Full = %d ,  Empty = %d \n",f,e);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

}
void *consumer(void *cno)
{
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = resource;
        resource--;
        f--;
        e++;
        printf("Consumer %d: Remove Item %d Resource value after removing: %d \n",*((int *)cno),item,resource);
        printf("Full = %d ,  Empty = %d \n",f,e);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

}

int main()
{
    pthread_t pro[MaxItems],con[MaxItems];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[MaxItems];
    for(int i = 0 ; i < MaxItems ; i++)
    {
        a[i] = i+1;
    }

    printf("\n Initially the resource value is %d\n",resource);

    for(int i = 0; i < MaxItems; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < MaxItems; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < MaxItems; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < MaxItems; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\n Finally the resource value is %d",resource);

    return 0;

}

