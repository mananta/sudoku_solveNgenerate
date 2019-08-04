#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*some global variables used throughout the entire program*/
char command[100];
int A[729];
int p=0;
char num[10],sat[10];
int sudoku[9][9];
int flag=1;
int a[9][9][9];

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
	  
	  fprintf(final,"...............................\n");
	  
	  
}

int main()
{	
	int s[9][9];//we scan the input from sudoku_in.txt and store it in matrix s
	int i=0,j=0;
	char ch;
	int x=0;
	FILE *FP=fopen("sudoku_in.txt","r");
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
	
   for (int i=0;i<9;i++)
   for (int j=0;j<9;j++)
   for (int k=1;k<10;k++)
    a[i][j][k]=i*81+j*9+k;
	 /*a[i][j][k] stands for the proposition that (i,j)th cell receives number k*/
	 
	 
	 
	 
	 FP=fopen("dimac.txt","w");
	 //fprintf(FP,"c this is the SAT encoding in the DIMACS representation\np cnf 729 %d\n",y);
	 dimac_creator(FP,s,a);
	 fclose(FP);
	  
	  
	  
	  
	  
	  
	  
	/*prints the first solution*/
	  strcpy(command,"./MiniSat_v1.14_linux dimac.txt sat_output.txt");
	  system(command);
	  FILE *out=fopen("sat_output.txt","r");
	  FILE *final=fopen("final.txt","w");
	  parser(out,final);
	  fclose(out);
	  fclose(final);
	  
	  
	  
	  
	  
	  
	  
	  
	 /*other solutions; maximum 100 solution is generated; 
	 to generate all possible solutions substitute the for loop statement by "while(1)"
	 and to get only one solution comment out the entire section of for loop*/
	  for(int i=0;i<100;i++)
	  {	
		  /*basically we append the negation of already achieved solutions to obtain new solutions*/
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
	  FILE *out=fopen("sat_output.txt","r");
	  FILE *final=fopen("final.txt","a");
	  parser(out,final);
	  fclose(out);
	  fclose(final);
	  if (flag==0)
		break;
		 
	}
	  
}
