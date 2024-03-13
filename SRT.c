#include<stdio.h>
#include<stdbool.h>
#define INT_MAX 2147483647

struct Process{
    int pid;
    int art;
    int bt;
};

void findWaitingTime(struct Process proc[],int n,int wt[])
{
    int rt[n];
    for(int i=0;i<n;i++)
    {
        rt[i]=proc[i].bt;
    }
    int complete=0,t=0,minm=INT_MAX;
    int shortest=0,finish_time;
    bool check=false;
    
    while(complete!=n)
    {
        for(int j=0;j<n;j++)
    {
        if((proc[j].art<=t)&&(rt[j]>0&&rt[j]<minm))
        {
            minm=rt[j];
            shortest=j;
            check=true;
        }
    }
    if(check==false)
    {
        t++;
        continue;
    }
    rt[shortest]--;
    minm=rt[shortest];
    if(minm==0){
        minm=INT_MAX;
    }
    if(rt[shortest]==0)
    {
        complete++;
        check=false;
        finish_time=t+1;
        wt[shortest]=finish_time-proc[shortest].bt-proc[shortest].art;
        if(wt[shortest]<0)
        {
            wt[shortest]=0;
        }
    }
    t++;
    }
    
}

void findTurnAroundTime(struct Process proc[],int n,int wt[],int tat[])
{
    for(int i=0;i<n;i++)
    {
        tat[i]=proc[i].bt+wt[i];
    }
}

void findAvgTime(struct Process proc[],int n)
{
    int wt[n],tat[n],total_wt=0,total_tat=0;
    
    findWaitingTime(proc,n,wt);
    findTurnAroundTime(proc,n,wt,tat);
    
    printf("Processes");
    printf("Burst Time");
    printf("Waiting Time");
    printf("Turnaround Time\n");
    for(int i=0;i<n;i++)
    {
        total_wt+=wt[i];
        total_tat+=tat[i];
        printf("%d\t",proc[i].pid);
        printf("%d\t",proc[i].bt);
        printf("%d\t",wt[i]);
        printf("%d\n",tat[i]);
    }
    printf("\n Average Waiting time=%f\n",(float)total_wt/(float)n);
    printf("Average Turnaround time=%f\n",(float)total_tat/(float)n);
}

int main()
{
    struct Process proc[]={{1,0,3},{2,2,6},{3,4,4},{4,6,5},{5,8,2}};
    int n = sizeof(proc)/sizeof(proc[0]);
    findAvgTime(proc,n);
    return 0;
}