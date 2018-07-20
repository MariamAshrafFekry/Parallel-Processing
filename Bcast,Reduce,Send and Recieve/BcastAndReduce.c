#include<stdio.h>
#include<mpi.h>
int main(int argc,char*argv[])
{
	int rank,numOfProcesses,start=1,end=1;
	int result=1,subFactorial=1;
	int n,Length,remainder=0,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numOfProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0)
	{
		printf("Enter Number to Calculate its Factorial\n");
		scanf("%d",&n);	
		Length=n/numOfProcesses;
		remainder=n%numOfProcesses;
	}
	MPI_Bcast(&Length,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&remainder,1,MPI_INT,0,MPI_COMM_WORLD);
	subFactorial=1;
	if(rank==0)
	{
		start=1;
		end=Length+remainder;
		for(i=start;i<=end;i++)
		{
			subFactorial*=i;
		}
       printf("the rank = %d  calculate partial factorial from %d to %d = %d\n",rank,start,end,subFactorial);
		MPI_Reduce(&subFactorial,&result,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
	}
	else if(Length<=0&&rank>0)
	{
		printf("Rank = %d NO Calculation For Factorial\n",rank);
		MPI_Reduce(&subFactorial,&result,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
	}
	else if(Length>0&&rank>0)
	{
		start=rank*Length+remainder+1;
		end=Length+start-1;
		for(i=start;i<=end;i++)
		{
			subFactorial*=i;
		}
	printf("the rank = %d  calculate partial factorial from %d to %d = %d \n",rank,start,end,subFactorial);
	MPI_Reduce(&subFactorial,&result,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
        }


	if(rank==0)
	{
		printf("After reduction rank %d will have factorial(%d) = %d \n",rank,n,result);
	}
	MPI_Finalize();
	return 0;
}
