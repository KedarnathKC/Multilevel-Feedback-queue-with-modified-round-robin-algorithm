#include<stdio.h>
#include<math.h>
#include<stdbool.h>
int front1=0,rear1=-1,current=-2,r=0,front2=0,rear2=-1,front3=0,rear3=-1;
typedef struct
{
      int pid,q3t;
      bool f,exe;
      float bt,at,tt,wt,max_t;
}process_structure;
int enque1(int n,int ele,int que1[n])
{
    int k;
    que1[++rear1]=ele;
}
int deque1(int n,int que1[n])
{
    if(rear1==-1)
    {
        return 1;
    }
    else
    {
        int k;
        for(k=1;k<=rear1;k++)
        {
            que1[k-1]=que1[k];
        }
        rear1--;
        return 0;
    }
}
int enque2(int n,float ele ,int que2[n])
{
    int k;
    que2[++rear2]=ele;
}
int deque2(int n,int que2[n])
{
    if(rear2==-1)
    {
        return 1;
    }
    else
    {
        int k;
        for(k=1;k<=rear2;k++)
        {
            que2[k-1]=que2[k];
        }
        rear2--;
        return 0;
    }
}
int enque3(int n,int ele,int que3[n])
{
    int k;
    que3[++rear3]=ele;
}
int deque3(int n,int que3[n])
{
    if(rear3==-1)
    {
        return 1;
    }
    else
    {
        int k;
        for(k=1;k<=rear3;k++)
        {
            que3[k-1]=que3[k];
        }
        rear3--;
        return 0;
    }
}
void delete3(int n,int id,int que3[n])
{
    int k,j;
    for(j=front3;j<=rear3;j++)
    {
        if(que3[j]==id)
        {
            for(k=j+1;k<=rear3;k++)
            {
                que3[k-1]=que3[k];
            }
            rear3--;
            break;
        }
    }
}
float quantum(int id,int n,float bt1[n],int que[n],int front,int rear )
{
    float sum=0,ans,check;
    int k;
    if(id==2)
    {
        check=4;
    }
    else{
        check=6;
    }
    for(k=front;k<=rear;k++)
    {
        sum+=bt1[que[k]];
    }
    if(sum/4<check)
        return check;
    else
        return round(sum/4);
}

main()
{
    int n,clock,i,j;
    printf("enter the number of processes: ");
    scanf("%d",&n);
    int que1[n],que2[n],que3[n];
    float tet=0;
    float bt1[n],et[n],avgtt=0,avgwt=0;
    process_structure process[n],temp;
    for(i=0;i<n;i++)
    {
        process[i].pid=i;
        printf("PID : %d\n",i+1);
        printf("Arrival Time:\t");
        scanf("%f", &process[i].at);
        printf("Burst Time:\t");
        scanf("%f", &process[i].bt);
        bt1[i]=process[i].bt;
        process[i].f=false;
        process[i].exe=false;
        process[i].q3t=-1;
        process[i].max_t=-1;
        printf("\n");
    }
    for(j=1;j<n;j++)//sorting the process according to arrival time
    {
        int key=process[j].at;
        temp=process[j];
        i=j-1;
        while(i>=0 && process[i].at>key)
        {
            process[i+1]=process[i];
            i=i-1;
        }
        process[i+1]=temp;
    }
    tet=tet+process[0].at;
    for( i= 0 ;i< n; i++ )//finding total execution time
    {
    	if( tet>= process[i].at )
    	{
    		tet= tet+process[i].bt;
    	}
    	else
    	{
    		int diff = (process[i].at- tet);
    		tet= tet+ diff + process[i].bt;
    	}

    }
    int Ghant1[(int)tet],Ghant2[(int)tet],Ghant3[(int)tet]; //Ghant Chart
	for( i= 0; i<tet; i++ )//Because initially all ghant charts are empty
	{
		Ghant1[i]=-1;
		Ghant2[i]=-1;
		Ghant3[i]=-1;
	}
    int cpu_state=0,qu1=2,qu2=4,qu3=6,cq1=0,cq2=0,cq3=0;
    for(clock=0;clock<tet;clock++)
    {
        for(i=0;i<n;i++)
        {
            if(clock==process[i].at)
            {
                enque1(n, process[i].pid,que1);
            }
            if((clock-process[i].q3t)>process[i].max_t*2 && process[i].q3t>-1 && !process[i].exe && process[i].max_t>-1)
            {
                enque1(n,process[i].pid,que1);
                delete3(n,process[i].pid,que3);
                process[i].q3t=-1;
                process[i].max_t=-1;
            }


        }
        if(cpu_state==0)
        {
            if(rear1!=-1)
            {
                current=que1[front1];
                cpu_state=1;
                cq1=1;
                qu1=2;
                deque1(n,que1);
            }
            else if(rear1==-1 && rear2!=-1)
            {
                current=que2[front2];
                cpu_state=1;
                cq2=1;
                qu2=quantum( 2,n,bt1, que2, front2, rear2 );
                deque2(n,que2);
            }
            else if(rear1==-1 && rear2==-1 && rear3!=-1)
            {
                current=que3[front3];
                cpu_state=1;
                cq3=1;
                qu3=quantum(3,n,bt1,que3,front3,rear3);
                deque3(n,que3);
            }
        }
        else if(cpu_state==1)
        {
            if(cq2==1 && rear1!=-1)
            {
                enque2(n,current,que2);
                current=que1[front1];
                deque1(n,que1);
                qu1=2;
                cq2=0;
                cq3=0;
                cq1=1;
            }
            else if(cq3==1 && rear1!=-1)
            {
                enque3(n,current,que3);
                current=que1[front1];
                deque1(n,que1);
                qu1=2;
                cq3=0;
                cq2=0;
                cq1=1;
            }
            else if(cq3==1 && rear1==-1 && rear2!=-1)
            {
                enque3(n,current,que3);
                current=que2[front2];
                deque2(n,que2);
                qu2=quantum( 2,n,bt1, que2, front2, rear2 );
                cq3=0;
                cq2=1;
            }
        }
        if(current!=-2)
        {
            bt1[current]--;
            if(cq1==1)
            {
                Ghant1[clock]=current;
                qu1--;
                if(bt1[current]==0)
                {
                    process[i].f=true;
                    et[current]=clock;
                    cpu_state=0;
                    qu1=2;
                    current=-2;
                    cq1=0;
                }
                else if(qu1==0)
                {
                    enque2(n,current,que2);
                    current=-2;
                    cpu_state=0;
                    cq1=0;
                    cq2=0;
                    qu1=2;
                }
            }
            else if(cq2==1)
            {
                Ghant2[clock]=current;
                qu2--;
                if(bt1[current]==0)
                {
                    process[i].f=true;
                    et[current]=clock;

                    cpu_state=0;
                    qu2=quantum( 2,n,bt1, que2, front2, rear2 );
                    qu1=2;
                    current=-2;
                    cq2=0;
                }
                else if(qu2==0)
                {
                    enque3(n,current,que3);
                    process[current].max_t=bt1[current];
                    process[current].q3t=clock;
                    current=-2;
                    cpu_state=0;
                    cq1=0;
                    cq2=0;
                    cq3=0;
                    qu2=quantum(2, n,bt1, que2, front2, rear2 );

                }
            }

            else if(cq3==1)
            {
                process[current].exe=true;
                Ghant3[clock]=current;
                qu3--;
                if(bt1[current]==0)
                {
                    et[current]=clock;
                    process[i].f=true;
                    cpu_state=0;
                    qu3=quantum( 3,n,bt1, que2, front2, rear2 );
                    qu1=2;
                    current=-2;
                    cq3=0;
                }
                else if(qu3==0)
                {
                    enque3(n,current,que3);
                    process[current].exe=false;
                    current=-2;
                    cpu_state=0;
                    cq1=0;
                    cq2=0;
                    cq3=0;
                    qu3=quantum( 3,n,bt1, que2, front2, rear2 );

                }
            }
        }
    }

    //turnaround and waittime

    for(i=0;i<n;i++)
    {
        int pos;
        pos=process[i].pid;
        process[i].tt=et[pos]-process[i].at;
        process[i].wt=process[i].tt-process[i].bt;
        avgtt+=process[i].tt;
        avgwt+=process[i].wt;
    }

    printf("Time in seconds     :\n");
	for(i=0;i<tet;i++){//Time in seconds
		if (i<10)
			printf(" %d ",i);
		else
			printf("%d ",i);
	}
	printf("\n");

    for(i=0;i<tet;i++)
    {
        printf(" %d ",Ghant1[i]+1);
    }

    printf("\n");
    for(i=0;i<tet;i++)
    {
        printf(" %d ",Ghant2[i]+1);

    }printf("\n");
    for(i=0;i<tet;i++)
    {
        printf(" %d ",Ghant3[i]+1);
    }
    printf("\n");

    printf("\n\n");
    printf("PID     | Arrival_Time  | Burst_Time    | Turnaround_Time       | Wait_time\n");
    printf("________|_______________|_______________|_______________________|________________\n");
    for(i=0;i<n;i++)
    {
        printf("%d \t| %f \t| %f \t| %f \t\t| %f\n",process[i].pid+1,process[i].at,process[i].bt,process[i].tt,process[i].wt);
    }
    printf("________|_______________|_______________|_______________________|________________\n");
    printf("                    Average :           |       %f       |      %f          ",avgtt/n,avgwt/n);

    printf("\n\n");
}




