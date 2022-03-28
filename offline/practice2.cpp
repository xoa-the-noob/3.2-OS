#include <iostream>
using namespace std;
int main() {
   int arrrivalTime[] = {0,0,0,0};
   int n = sizeof arrrivalTime / sizeof arrrivalTime[0];
   int cpuTime[] = {6,8,7,3};
   int endTime[n-1],waitingTime[n];

   for (int step = 0; step < n - 1; ++step) {
    for (int i = 0; i < n - step - 1; ++i) {

      if (cpuTime[i] > cpuTime[i + 1]) {
        int temp1 = cpuTime[i];
        cpuTime[i] = cpuTime[i + 1];
        cpuTime[i + 1] = temp1;
      }
    }
  }
printf("\n CPU sorted time :");
for(int i=0;i<n;i++)
{
    printf(" %d ",cpuTime[i]);
}

   endTime[0] = cpuTime[0];
   //printf("%d",endTime[0]);
   for(int i = 0; i<n-1; i++)
   {
       endTime[i+1] = endTime[i] + cpuTime[i+1];
   }
   /*
   gannt chart*/
   printf("Gantt chart illustration:");
   for(int i = 0; i<=n-1; i++)
   {
       printf(" %d ---- ",endTime[i]);
   }
    waitingTime[0] = arrrivalTime[0];
   for(int i = 0; i<n-1; i++)
   {
       waitingTime[i+1] = endTime[i] - arrrivalTime[i+1];
   }
   printf("\nWaiting time array:");
   for(int i = 0; i<=n-1; i++)
   {
       printf(" %d ",waitingTime[i]);
   }

   //AWT
   double temp1=0;
   for(int i = 0; i<n ; i++)
   {
       temp1+= waitingTime[i];
   }
   double awt = temp1/n;
   printf("\nThe AWT is %0.2lf",awt);

   double temp2 = 0;
   for(int i = 0; i<n ; i++)
   {
       temp2+= cpuTime[i];
   }
   double act = temp2/n;
   printf("\nThe ACT is %0.2lf",act);
   printf("\nThe ATT is %0.2lf",awt+act);

      return 0;

}
