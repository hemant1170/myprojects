//This program does assembly line scheduling problem solved using c/c++

#include<stdio.h>
#include<conio.h>
void ALS(int a[][11],int e_x[],int n,int t[][10],int l[][11]);
void path_print(int L,int l[][11],int n);
void main()
{
  int n,i;
  int a[2][11],e_x[4],t[2][10],l[2][11];
  printf("Enter the no. of stations in each assembly line:\n");
  scanf("%d",&n);
  printf("Enter the time of each station:\n");
  for(i=0;i<n;i++)
  {
    printf("Time at station a[1][%d]= ",i+1);
    scanf("%d",&a[0][i]);
    printf("Time at station a[2][%d]= ",i+1);
    scanf("%d",&a[1][i]);
  }
  printf("Enter the transfer time:\n");
  for(i=0;i<n-1;i++)
  {
    printf("Time of t[1][%d]= ",i+1);
    scanf("%d",&t[0][i]);
    printf("Time of t[2][%d]= ",i+1);
    scanf("%d",&t[1][i]);
  }
  printf("Enter the entry and exit time of assembly line1:\n");
  scanf("%d%d",&e_x[0],&e_x[2]);
  printf("Enter the entry and exit time of assembly line2:\n");
  scanf("%d%d",&e_x[1],&e_x[3]);
  ALS(a,e_x,n,t,l);
  getch();
}

void ALS(int a[][11],int e_x[],int n,int t[][10],int l[][11])
{
  int L,t1,t2,t3,j,f;
  t1=e_x[0]+a[0][0];
  t2=e_x[1]+a[1][0];
  l[0][0]=0;
  l[1][0]=1;
  for(j=1;j<n;j++)
  {
    t3=t1;
    if(t1+a[0][j]<=t2+t[1][j-1]+a[0][j])
    {
      t1=t1+a[0][j];
      l[0][j]=0;
    }
    else
    {
      t1=t2+t[1][j-1]+a[0][j];
      l[0][j]=1;
    }

    if(t2+a[1][j]<=t3+t[0][j-1]+a[1][j])
    {
      t2=t2+a[1][j];
      l[1][j]=1;
    }
    else
    {
      t2=t3+t[0][j-1]+a[1][j];
      l[1][j]=0;
    }
    printf("%d %d\n",t1,t2);
  }

  if(t1+e_x[2]<t2+e_x[3])
  {
    f=t1+e_x[2];
    L=0;
  }
  else
  {
    f=t2+e_x[3];
    L=1;
  }

  printf("\nTotal time taken by fastest path: %d\n",f);
  path_print(L,l,n);

}

void path_print(int L,int l[][11],int n)
{
  int i=L,j;
  printf("Line %d and station %d is exit\n",i+1,n);
  for(j=n-2;j>-1;j--)
  {
    i=l[i][j];
    printf("Line %d and station %d\n",i+1,j+1);
  }
}
