#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row1;
    int column1;
    int row2;
    int column2;
    int **Matrix1;
    int **Matrix2;
    int **result;
    int i;
    int j;
    printf("%s","Welcome to vector Matrix multiplication program! \n");
    printf("%s","To read dimensions and values from file press 1\n");
    printf("%s","To read dimensions and values from console press 2\n");
    int choose;
    scanf("%d",&choose);
    if(choose==1)
    {
        char fileName[100];
        printf("%s","Please Enter The File Name : ");
        getchar();
        gets(fileName);
        FILE*file=fopen(fileName,"r");
        if(!file)
        {
            printf("%s","file is not found");
            return 0;
        }
        else if(file)
        {
            fscanf(file,"%d",&row1);
            fscanf(file,"%d",&column1);
            Matrix1=(int**)malloc(row1*sizeof(int*));
            for( i=0;i<row1;i++)
            {
                Matrix1[i]=malloc(column1*sizeof(int));
            }
            for(i=0;i<row1;i++)
            {
                for(j=0;j<column1;j++)
                {
                    fscanf(file,"%d",&Matrix1[i][j]);
                }
            }
            fscanf(file,"%d",&row2);
            fscanf(file,"%d",&column2);
            Matrix2=(int**)malloc(row2*sizeof(int*));
            for( i=0;i<row2;i++)
            {
                Matrix2[i]=malloc(column2*sizeof(int));
            }
            for(i=0;i<row2;i++)
            {
                for(j=0;j<column2;j++)
                {
                    fscanf(file,"%d",&Matrix2[i][j]);
                }
            }

        }
        fclose(file);
    }
    else if(choose==2)
    {
        printf("%s","Please enter dimensions of the first matrix: ");
        scanf("%d",&row1);
        scanf("%d",&column1);
        printf("%s","Please enter its elements:\n");
        Matrix1=(int**)malloc(row1*sizeof(int*));
        for( i=0;i<row1;i++)
        {
            Matrix1[i]=malloc(column1*sizeof(int));
        }
        for(i=0;i<row1;i++)
        {
            for(j=0;j<column1;j++)
            {
                scanf("%d",&Matrix1[i][j]);
            }
        }
        printf("%s","Please enter dimensions of the second matrix: ");
        scanf("%d",&row2);
        scanf("%d",&column2);
        printf("%s","Please enter its elements:\n");
        Matrix2=(int**)malloc(row2*sizeof(int*));
        for( i=0;i<row2;i++)
        {
            Matrix2[i]=malloc(column2*sizeof(int));
        }
        for(i=0;i<row2;i++)
        {
            for(j=0;j<column2;j++)
            {
                scanf("%d",&Matrix2[i][j]);
            }
        }
    }
    else
    {
        return 0;
    }
    if(column1!=row2)
    {
        printf("%s","Can not Multiply Those Two Matrices");
        return 0;
    }
    else if(column1==row2)
    {
        result=(int**)malloc(row1*sizeof(int*));
        for(i=0;i<row1;i++)
        {
            result[i]=malloc(column2*sizeof(int));
        }
        int k;
        int c1=0,c2=0;
        int total=0;
        for(i=0;i<row1;i++)
        {
            for(j=0;j<column2;j++)
            {
                total=0;
                for(k=0;k<column1;k++)
                {
                    total+=Matrix1[i][k]*Matrix2[k][j];
                }
                result[i][j]=total;
            }
        }
        printf("%s","\nResult Matrix is(");
        printf("%d",row1);
        printf("%s","x");
        printf("%d",column2);
        printf("%s",")\n");
        for(i=0;i<row1;i++)
        {
            for(j=0;j<column2;j++)
            {
                printf("%d",result[i][j]);
                printf("%s"," ");
            }
            printf("%s","\n");
        }
        free(Matrix1);
        free(Matrix2);
        free(result);
    }
    return 0;
}
