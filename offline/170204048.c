#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
sem_t mutex,db,exclusivelock,writermutex;
pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];
int readercount = 0;
int writercount = 0;


int MAXSIZE = 10;
int stack[10];
int top = -1;
int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}

int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   int data;

   if(!isempty()) {
      data = stack[top];
      top = top - 1;
      return data;
   } else {
      //printf("Could not retrieve data, Stack is empty.\n");
      return -1;
   }
}

int push(int data) {

   if(!isfull()) {
      top = top + 1;
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}



void *reader(void* param)
{
    printf("Reader %d : waiting\n",*((int *)param));
    sem_wait(&mutex);
    readercount++;
    if(readercount==1)
        sem_wait(&db);
    sem_post(&mutex);
    //printf("Reading %d\n",pop());
    //usleep(3);
    printf("Reader %d : Reading %d\n",*((int *)param),pop());
    sem_wait(&mutex);
    readercount--;
    if(readercount==0)
    {
        sem_post(&db);
    }
    sem_post(&mutex);
    printf("Reader %d : Leaves\n",*((int *)param));
    return NULL;
}

void *writer(void* param)
{
    printf("Writer %d : Waiting\n",*((int *)param));
    sem_wait(&writermutex);
    writercount++;
    if(writercount==1)
    {
        sem_wait(&db);
    }
    sem_post(&writermutex);
    sem_wait(&exclusivelock);

    int n;
    scanf("%d",&n);
    push(n);
    printf("Writer %d : Writing data %d in buffer\n",*((int *)param),n);

    sem_post(&exclusivelock);
    sem_wait(&writermutex);
    writercount--;
    sem_post(&writermutex);
    if(writercount==0)
    {
        sem_post(&db);
    }
    printf("Writer %d : Leaves\n",*((int *)param));
    return NULL;
}

int main()
{
    int n2,i;
    printf("Enter the number of readers:");
    scanf("%d",&n2);
    printf("\n");
    int n1[n2];
    sem_init(&mutex,0,1);
    sem_init(&db,0,1);
    sem_init(&exclusivelock,0,1);
    sem_init(&writermutex,0,1);
    //int a[5] = {1,2,3,4,5};
    int a[n2];
    for(i=0;i<n2;i++)
    {
        a[i] = i+1;
    }
    for(i=0;i<n2;i++)
    {
        pthread_create(&writerthreads[i],NULL,reader,(void *)&a[i]);
        pthread_create(&readerthreads[i],NULL,writer,(void *)&a[i]);
    }
    for(i=0;i<n2;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&db);
    sem_destroy(&writermutex);
    sem_destroy(&exclusivelock);
}
