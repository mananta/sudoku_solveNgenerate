#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void dimac_creator(FILE *FP,int s[9][9],int a[9][9][9]);
void parser (FILE *out,FILE *final);

/*some global variables used throughout the entire program*/
char command[100];
int A[729];
int p=0;
char num[10],sat[10];
int sudoku[9][9];
int flag=1;


//this function randomly shuffles a given array with size n
void randomize(int a[],int n)
{
     for(int i=n-1;i>=0;i--)
     {	
	/*for every i we generate a random j between 0 and (n-1) and swap a[i] and a[j]*/
          int j=rand()%n;
          int temp=a[j];
          a[j]=a[i];
          a[i]=temp;
     }
    
}

/*creates the SAT encodings in dimacs representation */
void dimac_creator(FILE *FP,int s[9][9],int a[9][9][9])
{
	fprintf(FP,"c this is the SAT encoding in the DIMACS representation\np cnf 729 30000\n");
	 
	 
	 for (int i=0;i<9;i++)
	 {
		 for (int j=0;j<9;j++)
		 {	
			 /*constraint of input values */
			 if(s[i][j]!=0)
			 {
				 int k=s[i][j];
				 fprintf(FP,"%d 0\n",a[i][j][k]);
			 }
			 /*constraint that blank cells can receive at least one and at most one values */
			 else if(s[i][j]==0)
			 {
				 for (int k=1;k<=9;k++)
				 {
					 fprintf(FP,"%d ",a[i][j][k]);
				 }
				 fprintf(FP,"0\n");
				 
				 for (int k=1;k<=9;k++)
				 {
					 for (int l=k+1;l<=9;l++)
					 {
						fprintf(FP,"-%d -%d 0\n",a[i][j][k],a[i][j][l]);
						
					 }
				 }
			 }
		 }
	  }
	  
	  /*constraint of row repeatation*/
	  for (int k=1;k<=9;k++)
	  {
		  for (int i=0;i<9;i++)
		  {
			  for (int j1=0;j1<9;j1++)
				 {
					 for (int j2=j1+1;j2<9;j2++)
					 {
						fprintf(FP,"-%d -%d 0\n",a[i][j1][k],a[i][j2][k]);
						
					 }
				 }
		  }
	  }
	  
	  /*constraint of column repeatation*/
	  for (int k=1;k<=9;k++)
	  {
		  for (int j=0;j<9;j++)
		  {
			  for (int i1=0;i1<9;i1++)
				 {
					 for (int i2=i1+1;i2<9;i2++)
					 {
						fprintf(FP,"-%d -%d 0\n",a[i1][j][k],a[i2][j][k]);
						
					 }
				 }
		  }
	  }
	  
	  /*constraint of diagonal repeatation*/
	 for (int k=1;k<=9;k++)
	 {	
		 /*Principal diagonal*/
		 for (int i=0;i<9;i++)
		 {
			 for (int j=i+1;j<9;j++)
			 fprintf(FP,"-%d -%d 0\n",a[i][i][k],a[j][j][k]);
		 }
	  }
	
	  for (int k=1;k<=9;k++)
	  {
		 /*Off diagonal*/
		 for (int i=0;i<9;i++)
		 {
			 for (int j=i+1;j<9;j++)
			 fprintf(FP,"-%d -%d 0\n",a[i][8-i][k],a[j][8-j][k]);
		 }
	  }
	  
	   /*constraint of box repeatation */
	  for (int k=1;k<=9;k++)
	  {
		  for (int p=0;p<3;p++)
		  {
			  for (int q=0;q<3;q++)
			  {
				  for (int i=1;i<=9;i++)
				  {
					  for (int j=i+1;j<=9;j++)
					  {
						  int r1=(i-1)/3;
						  int c1=(i-1)%3;
						  int r2=(j-1)/3;
						  int c2=(j-1)%3;
						  fprintf(FP,"-%d -%d 0\n",a[3*p+r1][3*q+c1][k],a[3*p+r2][3*q+c2][k]);
						 
					  }
				  }
			  }
		  }
	  }
	  
	return; 
}

/*Parse the data from SAT solver output to print the solution SUDOKU+ in final.txt*/
void parser (FILE *out,FILE *final)
{
	fscanf(out,"%s",sat);
	if (strcmp(sat,"SAT")!=0)
	{
		flag=0;
		return;
	}
	p=0;
	   while(p<729)
	   {
		   fscanf(out,"%s",num);
		   A[p++]=atoi(num);
		}
	  
	  
	  
	  for (int i=0;i<9;i++)
	  {
		  for (int j=0;j<9;j++)
		  {
			  for(int l=81*i+9*j;l<81*i+9*j+9;l++)
			  {
				  if (A[l]>0)
				  {
					  sudoku[i][j]=A[l]-81*i-9*j;
					  break;
				  }
			  }
		  }
	  }
	  
	  for (int i=0;i<9;i++)
	  {
		  for (int j=0;j<9;j++)
		  {
			  fprintf(final,"%d ",sudoku[i][j]);
		  }
		  fprintf(final,"\n");
		  
	  }
	  
	  fprintf(final,"%s...............................\n",sat);
	  
	  
}

int main()
{	
	srand(time(0));
	int s[9][9];//we scan the input from final.txt and store it in matrix s
	int i=0,j=0;
	char ch;
	int x=0;
	//FILE *FP=fopen("sudoku_in.txt","r");
	FILE *FP=fopen("final.txt","r");
	while(i<9)
	{
		fscanf(FP,"%c",&ch);
		if(ch=='\n' || ch==' ')
			continue;
		else if(ch=='.')
			s[i][j]=0;
	    else
			{s[i][j]=ch-'0';
			x++;}
	    if(j==8)
	    {
			i++;j=0;
		}
		else
			j++;
	 }
	 fclose(FP);
	 
	 
	int a[9][9][9];
	 for (int i=0;i<9;i++)
   for (int j=0;j<9;j++)
   for (int k=1;k<10;k++)
    a[i][j][k]=i*81+j*9+k;
	 /*a[i][j][k] stands for the proposition that (i,j)th cell receives number k*/
	 
	 
	 
	 strcpy(command,"./MiniSat_v1.14_linux dimac.txt sat_output.txt");
	 int row,col,val;
	 
	 
	 /*strategy : To generate a sample sudoku+ problem we take a random solution (very easy to get it from the program designed for
	   the previous problem; we can use any random input and obtain a solution). Now at each step we pop up the value from a random 
	   cell and check whether the solution is unique or not. Obviously, the solution will be unique at first few popping operation. 
	   Whenever the solution becomes multiple we take that particular situation. Now, another operation starts. We start checking 
	   if it is possible to eliminate non-zero values randomly as much as possible to get a minimal solution and the algo works!!*/
	while (1)
	{
	   FP=fopen("dimac.txt","w");
	   dimac_creator(FP,s,a);
	   fclose(FP);
	   system(command);
	   
	   FILE *out=fopen("sat_output.txt","r");
	   FILE *final=fopen("final.txt","w");
	   parser(out,final);
	   fclose(out);
	   fclose(final);
	   FP=fopen("dimac.txt","a");
		  for (int i=0;i<9;i++)
		  {
			  for (int j=0;j<9;j++)
			  {
				  fprintf (FP,"-%d ",a[i][j][sudoku[i][j]]);
			  }
		  }
		  fprintf (FP,"0\n");
		  fclose(FP);
		 system(command);
		 char vital[10];
		 out=fopen("sat_output.txt","r");
		 fscanf (out,"%s",vital);
		 fclose(out);
		 if (strcmp(vital,"SAT")==0)
			//printf ("multiple solution!\n");
			{
				s[row][col]=val;
				break;
			}
		 else if (strcmp(vital,"UNSAT")==0)
			//~ printf ("unique solution!\n");
			//~ break;
			{	
				while(1)
				{
					row=rand()%9;
					col=rand()%9;
					val=s[row][col];
					if (val!=0)
					{
						s[row][col]=0;
						break;
					}
				}
				
			}
	 }
	 int arr[81];
	 for (int i=0;i<81;i++)
		arr[i]=i+1;
	randomize(arr,81);
	 for (int p=0;p<81;p++)
				{
					int i=(arr[p]-1)/9;
					int j=(arr[p]-1)%9;
					if (s[i][j]!=0)
						{	
							int v=s[i][j];
							s[i][j]=0;
							FP=fopen("dimac.txt","w");
							dimac_creator(FP,s,a);
							fclose(FP);
							system(command);
							
							FILE *out=fopen("sat_output.txt","r");
							FILE *final=fopen("final.txt","w");
							parser(out,final);
							fclose(out);
							fclose(final);
							
							FP=fopen("dimac.txt","a");
							for (int i=0;i<9;i++)
							{
								for (int j=0;j<9;j++)
								{
									fprintf (FP,"-%d ",a[i][j][sudoku[i][j]]);
								}
							}
							fprintf (FP,"0\n");
							fclose(FP);
							system(command);
		                    char vital_[10];
		                    out=fopen("sat_output.txt","r");
							fscanf (out,"%s",vital_);
							fclose(out);
							if (strcmp(vital_,"SAT")==0)
								s[i][j]=v;
						}
			 }
	 
	 /*the sample problem is printed in sample.txt in the required format*/
	FP=fopen("sample.txt","w");
	for (int i=0;i<9;i++)
	{
		for (int j=0;j<9;j++)
		{
			if (s[i][j]==0)
				fprintf (FP,". ");
			else
				fprintf (FP,"%d ",s[i][j]);
		}
		fprintf (FP,"\n");
	}
	fclose (FP);
}
