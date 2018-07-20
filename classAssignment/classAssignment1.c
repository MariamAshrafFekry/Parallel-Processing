#include<stdio.h>
#include<string.h>
#include<math.h>
#include<mpi.h>
typedef enum { false, true } bool;
int Cofficient[101];
int Power[101];
int indx ;

double min(double x,double y)
{
	if(x<y)
	   return x;
	else
	   return y;
}
double absDifference(double x,double y)
{
	if(x>y)
	   return x-y;
	else
	   return y-x;
}
bool isDigit(char x) {
	if (x >= '0' && x <= '9')
		return true;
	else
		return false;
}
bool isSign(char x) {
	if (x == '+' || x == '-' || x == '^')
		return true;
	else
		return false;
}
int strLen(char *arr) {
	int i = 0;
	while (arr[i] != '\0') {
		i++;
	}
	return i;
}
void Shift(char *arr, int start, int interval, int size, char sign) {
	int i;
	char arr2[101];
	int c = 0;
	arr[start] = sign;
	for (i = 0; i <= start; i++)
	{
		arr2[c] = arr[i]; c++;
	}
	for (i = interval; i < size; i++)
	{
		arr2[c] = arr[i]; c++;
	}
	memset(arr, (char)0, size);
	memmove(arr, arr2, c);
}

void convertCharArray(char *arr, int size) {
	if (arr[size - 1] != '+'&&arr[size-1]!='-')
	{
		size += 1;
		arr[size - 1] = '+';
	}
	int c = 0, p = 0;
	char arrC[100], arrP[100];
	int cVal=1, pVal=1;
	memset(arrC, (char)0,100);
	memset(arrP, (char)0, 100);
	if (isDigit(arr[0]) == true)
	{
		cVal=1;
		arrC[c] = arr[0];
		c++;
	}
	else if (arr[0] == 'X')
	{
		arrC[c] = '0'+1;
		cVal = 1;
		c++;
	}
	else if (arr[0] == '-')
	{
		cVal = -1;
		arrC[c] = '0' + 1;
	}
	int i = 1;
	while (i < size)
	{
		if (isDigit(arr[i]) == true)
		{
			arrC[c] = arr[i];
			c++;
			i++;
		}
		else if ((arr[i] == '+'||arr[i]=='-'))
		{
			if (arr[i - 1] == 'X')
			{
				pVal = 1;
				arrP[p] = '0' + 1;
			}
			Cofficient[indx] = cVal*atoi(arrC);
			Power[indx] = pVal*atoi(arrP);
			memset(arrC, (char)0, c);
			memset(arrP, (char)0, p);
			c = 0;
			p = 0;
			cVal = 1;
			pVal = 0;
			indx++;
			if (arr[i] == '-')
			{
				cVal = -1;
				arrC[c] = '0' + 1;
			}
			else if (arr[i] == '+')
			{
				cVal = 1;
				arrC[c] = '0' + 1;
			}
			i++;
		}
		else if (arr[i] == '^'&&arr[i - 1] == 'X')
		{
			i++;
			pVal = 1;
			arrP[p] = '0' + 1;
			if (arr[i] == '-')
			{
				pVal = -1;
				i++;
			}
		    if (isDigit(arr[i]) == true)
			{
				while (isDigit(arr[i]) == true)
				{
					arrP[p] = arr[i];
					i++;
					p++;
				}
			}
		}
		else
		{
			i++;
		}
	}
}

bool validateInput(char *arr, int count) {
	if (arr[0] != 'X' && ((arr[0] == '^') || arr[0] == '+')){
		return false;
	}
	if (arr[0] == 'X' && (isDigit(arr[1]) == true))
	{
		return false;
	}
	if (count == 1 && arr[0] == 'X')
	{
		convertCharArray(arr, 1);
		return true;
	}
	int i = 1;
	while (i < count) {
		if (i >= count - 1 || arr[i] == '\0')
		{
				convertCharArray(arr, strLen(arr));
				return true;
		}
		if (isDigit(arr[i - 1]) == true && arr[i] == '^'
			&& isDigit(arr[i + 1]) == true) {
			return false;
		}
		else if (arr[i] != 'X' && isDigit(arr[i]) == false
			&& isSign(arr[i]) == false && i<count) {
			return false;
		}
		else if ((arr[i] == '^' && arr[i + 1] == '+')
			|| (isSign(arr[i]) == true && arr[i + 1] == '^')) {
			return false;
		}
		else if (arr[i] == 'X' && (isDigit(arr[i + 1]) == true))
		{
			return false;
		}
		else if (arr[i] == '^'&&arr[i + 1] == 'X')
		{
			return false;
		}
		
		else if (isSign(arr[i])) {
			int tmp = i;
			int c1 = 0, c2 = 0, c3 = 0;
			while (isSign(arr[i])) {
				if (arr[i] == '+')
					c1++;
				else if (arr[i] == '-')
					c2++;
				else if (arr[i] == '^')
					c3++;
				else { c1 = 0, c2 = 0, c3 = 0; }
				i++;
			}
			if (c3 > 1) {
				return false;
			}
			else if ((c2 >= 1&&c1>0)||(c2>1&&c2==0)) {
				if (c2 % 2 == 0) {
					Shift(arr, tmp,i, strLen(arr), '+');
				}
				else if (c2 % 2 != 0) {
					Shift(arr, tmp,i, strLen(arr), '-');
				}
			}
			else if (c1 > 1) {
				Shift(arr, tmp,i, strLen(arr), '+');
			}
		}
		i++;
	}
	convertCharArray(arr, strLen(arr));
	return true;
}
double f(double x) {
	int i = 0;
	double sum = 0;
	for (i = 0; i < indx; i++) {
		sum += Cofficient[i] * pow(x,Power[i]);
	}
	return sum;
}
int main(int argc,char*argv[])
{
	int rank,j,size;
	int rectanglesNum;
	double start,end,i;
        double sum=0,rectArea=0,triArea=0,total=0,e=0,s=0,x=0,y=0;
	double deltaX=0;
        char arr[101];
        MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0)
	{
		printf("%s", "Enter The Equation with maximum 100 character : ");
		scanf("%s",arr);
		printf("%s","Enter Start : ");
		scanf("%lf",&start);
		printf("%s","Enter End : ");
		scanf("%lf",&end);
		printf("%s","Enter Number of slices : ");
		scanf("%d",&rectanglesNum);
		deltaX=(end-start)*1.0/rectanglesNum;
		for(j=1;j<size;j++)
		{
			s=start+j*1.0*(end-start)/size;
			e=start+(j+1)*1.0*(end-start)/size;
			MPI_Send(&s,1,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
			MPI_Send(&e,1,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
			MPI_Send(&deltaX,1,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
			MPI_Send(arr,101,MPI_CHAR,j,0,MPI_COMM_WORLD);
		}
               validateInput(arr,strLen(arr));
		s=start*1.0;
		e=start+(end-start)*1.0/size;
		for(i=s;i<e;i+=deltaX)
		{	
			x=f(i+deltaX);
			y=f(i);
			triArea=0.5*deltaX*absDifference(x,y);
			rectArea=deltaX*min(x,y);
			sum+=(triArea+rectArea);
		}
		printf("The Rank = %d \t The Total Area = %f\n",rank,sum);
      		for(j=1;j<size;j++)
		{
			MPI_Recv(&total,1,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			sum+=total;
		}
		printf("The Total Area = %f\n",sum);

	}
	else if(rank!=0)
	{
		MPI_Recv(&s,1,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&e,1,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&deltaX,1,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(arr,101,MPI_CHAR,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		validateInput(arr,strLen(arr));
		for(i=s;i<e;i+=deltaX)
		{	
			x=f(i+deltaX);
			y=f(i);
			triArea=0.5*deltaX*absDifference(x,y);
			rectArea=deltaX*min(x,y);
			sum+=(triArea+rectArea);
		}
		printf("The Rank = %d \t The Total Area = %f\n",rank,sum);
		MPI_Send(&sum,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
