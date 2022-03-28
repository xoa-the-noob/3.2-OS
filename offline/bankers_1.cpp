#include <iostream>
using namespace std;
int main()
{
    int r,p;
    printf("Enter total no of process:");
    scanf("%d",&p);
    printf("Enter total no of resources:");
    scanf("%d",&r);
    int allocated[p][r],need[p][r],maxm[p][r],total[r],available[r];
    printf("Enter total resources array:");
    for(int i = 0; i< r; i++)
    {
        scanf("%d",&total[i]);
    }
    printf("Input the allocated array:\n");
    for(int i = 0; i < p; i++)
    {
        for(int j=0; j < r; j++)
        {
            scanf("%d",&allocated[i][j]);
        }
    }
    printf("Input the maximum array:\n");
    for(int i = 0; i < p; i++)
    {
        for(int j=0; j < r; j++)
        {
            scanf("%d",&maxm[i][j]);
        }
    }

    printf("\nThe need array :\n");
    for(int i = 0; i < p; i++)
    {
        for(int j=0; j < r; j++)
        {
            need[i][j] = maxm[i][j] - allocated[i][j];
            printf("  %d  ",need[i][j]);
        }
        printf("\n");
    }
    int temp[100] = {0};
    for (int i = 0; i < p; i++)
	{
        for (int j = 0; j < r; j++)
		{
            temp[j] += allocated[i][j];
        }
    }

    for (int i = 0; i < r; i++)
	{
        available[i] = total[i] - temp[i];
	}
    printf("\nThe available array:\n");
    for(int i = 0; i<r ;i++)
    {
        printf("  %d  ",available[i]);
    }

    int done[p] = {0},no=0,print[p];
    for(int i = 0 ; i < p ; i++)
    {
        for(int j = 0 ; j < p ; j++)
        {
            if(done[j] == 0)
            {
                int work = 0;
                for(int k = 0 ; k < r ; k++)
                {
                    if( need[j][k] > available[k] )
                    {
                        work = 1;
                        break;
                    }
                }
                if(work == 0)
                {
                    printf("\n");
                    print[no++] = j+1;
                    for(int x = 0 ; x < r ; x++)
                    {
                        available[x] += allocated[j][x];
                        printf("  %d  ",available[x]);
                    }
                    done[j] = 1;


                }
            }
        }
    }
    printf("Process:");
    for(int i=0; i<p ; i++)
    {
        printf("  P%d -->  ",print[i]);
    }

return 0;
}

/*
0
1
0
2
0
0
3
0
2
2
1
1
0
0
2
*/

/*
7
5
3
3
2
2
9
0
2
2
2
2
4
3
3
*/
