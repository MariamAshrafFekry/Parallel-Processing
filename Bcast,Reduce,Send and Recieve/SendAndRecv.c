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
		end=Length+remainder;
		for(i=start;i<=end;i++)
		{
			result*=i;
		}
	printf("the rank = %d  calculate partial factorial from %d to %d = %d\n",rank,start,end,result);
		for(i=1;i<numOfProcesses;i++)
		{
			start=i*Length+remainder+1;
			MPI_Send(&start,1,MPI_INT,i,0,MPI_COMM_WORLD);
			MPI_Send(&Length,1,MPI_INT,i,0,MPI_COMM_WORLD);

		}
		for(i=1;i<numOfProcesses;i++)
		{
			MPI_Recv(&subFactorial,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			result*=subFactorial;
		}
	        printf("After reduction rank %d will have factorial(%d) = %d\n",rank,n,result);
		
	}
	else if(rank!=0)
	{
		MPI_Recv(&start,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&Length,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		if(Length<=0)
		{
			printf("Rank = %d NO Calculation For Factorial\n",rank);
		}
		else
		{
			end=Length+start-1;
			for(i=start;i<=end;i++)
			{
				subFactorial*=i;
			}
printf("the rank = %d  calculate partial factorial from %d to %d = %d\n",rank,start,end,subFactorial);
		}
		MPI_Send(&subFactorial,1,MPI_INT,0,0,MPI_COMM_WORLD);

	}
	MPI_Finalize();
	return 0;
}
