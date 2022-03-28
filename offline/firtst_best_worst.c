#include<stdio.h>
int p_size,b_size;
int main()
{
    printf("Enter process and block size:");
    scanf("%d %d",&p_size,&b_size);
    int i,j,p[p_size],b[b_size];

    printf("Enter process sizes:");
    for(i=0;i<p_size;i++)
    {
        scanf("%d",&p[i]);
    }

    printf("Enter block sizes:");
    for(i=0;i<b_size;i++)
    {
        scanf("%d",&b[i]);
    }

    int choice;
	printf("Enter 1 for first fit,2 for worst fit");
	scanf("%d",&choice);
	if(choice==1){first_fit();}
	else if(choice==2){worst_fit();}

    //first_fit(p,b);
    //worst_fit(p,b);

    return 0;
}
void first_fit(int p[],int b[])
{
    int i,j;
    for(i=0;i<p_size;i++)
    {
        for(j=0;j<b_size;j++)
        {
                if(b[j]>=p[i])
            {
                b[j]-=p[i];
                printf("\nProcess %d -->  Block %d",i+1,j+1);
                break;
            }

        }
    }

    int sum=0;
    for(i=0;i<b_size;i++)
    {
        sum+=b[i];
    }
    printf("\nExternal fragmentation is %d",sum);
}

int getMax(int b[]){
    int i,j;
    int max=0;
    for(j=0;j<b_size;j++)
    {
            if(b[j]>=max)
            {
                max = b[j];
            }
    }
    printf("The max is %d",max);
    return max;
}

void worst_fit(int p[],int b[])
{
    int i,j;
    int max;
    int flag=1;
    for(i=0;i<p_size;i++)
    {
        max = getMax(b);
        for(j=0;j<b_size;j++)
        {
          if(flag==1)
          {
                if(b[j]==max){
            if(b[j]>=p[i])
            {
                b[j]-=p[i];
            printf("\nProcess %d -->  Block %d",i+1,j+1);
            break;
            }
            else{flag=0;}
        }
          }
        }
    }

    int sum=0;
    for(i=0;i<b_size;i++)
    {
        sum+=b[i];
    }
    printf("\nExternal fragmentation is %d",sum);
}
/*
100 10 35 15 23 6 25 55 88 40
50 200 70 115 15
*/
