#include<stdio.h>
int n,tq,time = 0;
int queue[100] = {0} , front = 0; rear = 0;

struct data
{
    int p;
    int at;
    int bt1;
    int bt;
    int wt;
    int tat;
}t;

int main()
{

    float avg1 = 0, avg2 = 0;
    printf("Enter total no of processes :");
    scanf("%d",&n);
    struct data aa[n];
    int i;
    for(i = 0; i<n ; i++)
    {
        printf("Enter arrival and burst time of p[%d]",i+1);
        aa[i].p = i+1;
        scanf("%d %d",&aa[i].at,&aa[i].bt);
        aa[i].bt1 = aa[i].bt;
    }
    printf("Enter time quantum:");
    scanf("%d",&tq);

    sort(aa);
    round_robin(aa);

    printf("\n\tProcessID\tWaiting Time\tTurnaround Time:");
    for(i = 0; i< n; i++)
    {
        printf("\n\t  [%d]\t        [%d]\t             [%d]",aa[i].p,aa[i].wt,aa[i].tat);
        avg1 += aa[i].wt;
        avg2 += aa[i].tat;
    }
    printf("\n Average Waiting Time: %f",avg1/n);
    printf("\n Average Turnaround Time: %f",avg2/n);
    return 0;
}

void sort(struct data a[])
{
    int i,j;
    for(i=0 ; i<n ; i++)
    {
        for(j= 0 ; j<n ; j++)
        {
            if(a[j].at>a[j+1].at)
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void round_robin(struct data a[])
{
    int i=1,j=0,x;
    x = n;
    printf("%d",a[0].at);
    while(x!=0)
    {
        j = select(j);
        if(a[j].bt <= tq && a[j].bt>0)
        {
            time = time + a[j].bt;
            a[j].bt = 0;
            printf("--->P%d--->%d",a[j].p , time);
        }
        else if(a[j].bt>0)
        {
            a[j].bt = a[j].bt - tq;
            time = time + tq;
            printf("--->P%d--->%d",a[j].p , time);
        }
        while(a[i].at<= time && i<n){
            push(i);
            i++;
        }
        if(a[j].bt == 0){
            x--;
            a[j].wt = time - a[j].at - a[j].bt1;
            a[j].tat = a[j].wt + a[j].bt1;
        }
        else{
            push(j);
        }
    }
}

int select(int j){
if(time == 0)
    return j;
else
{
    j = pop();
    return j;
}
}
int pop()
{
    int x;
    x = queue[front++];
    return x;
}
void push(int q)
{
  queue[rear++]=q;
}


