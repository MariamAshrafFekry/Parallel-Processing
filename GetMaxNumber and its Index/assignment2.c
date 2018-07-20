#include<stdio.h>
#include<string.h>
#include<mpi.h>
int main(int argc,char*argv[])
{	
	int numOfProcesses;
	int rank;
        int arr[10001],max=0,indx=0;
	int lengthOfArray=0,lengthSubArray=0,remainder=0,i=0,maxValue=0,valueIndex=0,s=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numOfProcesses);
	if(rank==0)
	{
		printf("Hello from master process.\nNumber of slave processes is 4\n");
		printf("Please enter size of array...\n");
		scanf("%d",&lengthOfArray);
		printf("\nPlease enter array elements ...\n");
		for(i=0;i<lengthOfArray;i++)
		{
			scanf("%d",&arr[i]);
		}
		lengthSubArray=lengthOfArray/numOfProcesses;
		remainder=lengthOfArray%numOfProcesses;
		for(i=1;i<numOfProcesses;i++)
		{
			s=i*lengthSubArray+remainder;
			MPI_Send(&lengthSubArray,1,MPI_INT,i,0,MPI_COMM_WORLD);
			MPI_Send(&(arr[s]),10001,MPI_INT,i,0,MPI_COMM_WORLD);
		}

		max=arr[0];
		indx=0;
		for(i=1;i<(lengthSubArray+remainder);i++)	
		{
			if(arr[i]>max)
			{
				max=arr[i];
				indx=i;
                	}
		}
	printf("Hello from slave#%d Max number in my portion is %d and index is %d.\n",rank+1,max,indx);
		
		for(i=1;i<numOfProcesses;i++)
		{
			MPI_Recv(&maxValue,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&valueIndex,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&s,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(maxValue>max)
			{
				max=maxValue;
				indx=s*lengthSubArray+remainder+valueIndex;
			}
		}
                printf("Master process announces: max number is %d and its index is %d.\n",max,indx);	
	}
	else if(rank!=0)
	{
		MPI_Recv(&lengthSubArray,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&(arr),10001,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		max=arr[0];
		indx=0;
		for(i=1;i<lengthSubArray;i++)
		{
			if(arr[i]>max)
			{
				max=arr[i];
				indx=i;
			}
		}
	printf("Hello from slave#%d Max number in my portion is %d and index is %d.\n",rank+1,max,indx);
		MPI_Send(&max,1,MPI_INT,0,0,MPI_COMM_WORLD);
		MPI_Send(&indx,1,MPI_INT,0,0,MPI_COMM_WORLD);
		MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
