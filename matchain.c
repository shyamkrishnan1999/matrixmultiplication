#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<float.h>

// Defining a new data type matrix to store the matrices
typedef struct 
{
	int Elements[100][100];
} matrix;

//Function declarations
void generateFiles(int);
void generateSize(int);
matrix readFile(int,int,char *);
double matmultiplication(int arr[],int);
double Optimisedmatmultiplication(int arr[],int,int);

//main function
void main(int argc,char **argv)
{
	

	//Variables used
	int r[20],length=0;
	double optimal1,optimal2;
	double time_taken;
	matrix mat[20];
	clock_t start,end;
	char name[10]="mat1.txt";
	char c,str[100];

	//Generating files for storing matrices and their sizes
	generateFiles(atoi(argv[1]));
	generateSize(atoi(argv[1]));

	FILE *size=fopen("size.txt","r");

	//Reading size from size.txt
	while(!feof(size))
	{	
		fgets(str,100,size);
		r[length]=atoi(str);
		length++;
	}


	//Reading matrices from file
	for(int i=0;i<length-1;i++)
	{
		mat[i]=readFile(r[i],r[i+1],name);
		c=(i+1)+'0';
		name[3]=c;
	}




	//Calling function and calculating the time taken
	start=clock();
	optimal1=matmultiplication(r,length-1);
	end=clock();
	time_taken=((double)end-start)/CLOCKS_PER_SEC;

	start=clock();
	optimal2=Optimisedmatmultiplication(r,0,length-2);
	end=clock();
	time_taken=((double)end-start)/CLOCKS_PER_SEC;

	//printing out results
	printf("Normal matrix chain Multiplication:\n");
	printf("Optimal multiplications:%lf\n",optimal1);
	printf("Time taken(in seconds):%lf",time_taken);

	printf("\n\n\n");
	printf("Optimised matrix chain Multiplication:\n");
	printf("Optimal multiplications:%lf\n",optimal2);
	printf("Time taken(in seconds):%lf",time_taken);





}

//Function for generating matrices
void generateFiles(int size)
{
	srand(time(0));
	char name[10]="mat1.txt";
	char c;

	for(int i=1;i<size;i++)
	{
		FILE * myfile;
		myfile=fopen(name,"w+");
		

		for(int j=0;j<10000;j++)
		{
			
			fprintf(myfile,"%d\n",rand()%20);
		}

		fclose(myfile);
		c=(i+1)+'0';
		name[3]=c;
		
	}
}


//Function to generate size.txt
void generateSize(int size)
{
	srand(time(0));
	char name[10]="size.txt";
	FILE *myfile;
	myfile=fopen(name,"w+");

	for(int j=0;j<size;j++)
		{
			
			fprintf(myfile,"%d\n",rand()%100);
		}
	

	fclose(myfile);
}

//Function for reading matrices from file 
matrix readFile(int row,int column,char *name)
{
	matrix mat;
	FILE *myfile;
	char line[100];
	myfile=fopen(name,"r");

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			
			fgets(line,100,myfile); 
            mat.Elements[i][j]=atoi(line);
					
		}
	}
	fclose(myfile);
	return mat;

}

//matrix chain multiplication
 double matmultiplication(int arr[],int n)
{
	double m[20][20],temp;
	 int j;

	for(int i=0;i<n;i++)
		m[i][i]=0;

	for(int l=0;l<n-1;l++)
	{
		for(int i=0;i<n-l;i++)
		{
			j=l+i;
			double min_val=m[i][i]+m[i+1][j]+(arr[i-1]*arr[i]*arr[j]);

			for(int k=i+1;k<j;k++)
			{
				temp=m[i][k]+m[k+1][j]+(arr[i-1]*arr[k]*arr[j]);

                if(temp<min_val)
			   		min_val=temp;
			}

			m[i][j]=min_val;

		}
	}

	return m[0][n-2];
	
}

double Optimisedmatmultiplication(int arr[],int i,int j)
{

	double m[20][20],temp;
	
	if(j<i+1)
		return 0;
	
	double min_val=DBL_MAX;

	if(m[i][j]==0)
	{

		for(int k=i+1;k<j;k++)
		{
			temp=Optimisedmatmultiplication(arr,i,k);
			temp+=Optimisedmatmultiplication(arr,k,j);
			temp+=arr[i]*arr[k]*arr[j];

			if(temp<min_val)
				min_val=temp;
		}

		m[i][j]=min_val;
	}

	return m[i][j-1];

}

