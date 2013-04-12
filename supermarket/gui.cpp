// This program creates a GUI for for a supermarket where all the buttons except the alpha-numericals don't work to prevent invalid state of the software. 
// The product listing of the products of the supermarket is saved in a file called product_list.h
// This code works on 16-bit windows(dos) environment  

#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include"product_list.h"
#include<string.h>
#include<ctype.h>
#include<dos.h>

using namespace std;
int id_checker(char[]);
void error(int,int t2=1);
void line_clearer(int);
void search_clearer(int);
char id[10][6];
void search(char*);
int qnty_checker(char*);
int enter(char*,int,int);
int enter_num(char*,int,int);
void main()
{
 int i=0,nty2[50],j,k,t;
 char key=13,opt2='n',srch[10],nty[50][5],tmp;
 long sub_total[50];
 clrscr();
 cout<<"\n\nS.No\tProduct ID\tProduct Name\tPrice(Rs.)\tQnty\t  Amnt\n-------------------------------------------------------------------------------";
 while(1)
 {
 START:
 gotoxy(1,25);
 cout<<"Now press <ENTER> to add an entry, \"@\" to exit , or \"*\" to search";
 gotoxy(1,i+5);
 key=getch();
 gotoxy(1,25);
 cout<<"                                                                             ";
 gotoxy(1,i+5);
 START2:
 if(key=='*')
 {
  gotoxy(1,1);
  cout<<"                                                                             ";
  gotoxy(1,1);
  cout<<"Search: ";
  cin>>srch;
  gotoxy(20,1);
  cout<<":";
  search(srch);
  getch();
  gotoxy(1,1);
  cout<<"                                                                             ";
  gotoxy(1,i+5);
 }
 if(key=='@')
 break;
 if(key==13)
 {
  gotoxy(1,i+5);
  cout<<i+1;
  AGAIN:
  gotoxy(9,i+5);
  tmp=getch();
  if((tmp>=65&&tmp<=123)||(tmp>=48&&tmp<=57))
  {
   cout<<tmp;
   id[i][0]=tmp;
   t=enter(id[i],10,i+5);
   if(t==-1)
   goto AGAIN;
  }
  else
  {
   goto AGAIN;
  }
  j=id_checker(id[i]);
  if(j==-1)
   {
    error(1);
    line_clearer(i+5);
    key=getch();
    search_clearer(i+5);
    goto START2;
   }
  gotoxy(27,i+5);
  cout<<itemname[j];
  gotoxy(43,i+5);
  cout<<itemprice[j];
  INPUT:
  search_clearer(i+5);
  AGAIN2:
  gotoxy(59,i+5);
  tmp=getch();
  if(tmp>=48&&tmp<=57)
  {
   cout<<tmp;
   nty[i][0]=tmp;
   t=enter_num(nty[i],60,i+5);
   if(t==-1)
   goto AGAIN2;
  }
  else
  {
   goto AGAIN2;
  }
  nty2[i]=qnty_checker(nty[i]);
  if(nty2[i]<=0||nty2[i]>999)
  {
   error(2,i+5);
   goto INPUT;
  }
  gotoxy(69,i+5);
  sub_total[i]=itemprice[j]*nty2[i];
  cout<<sub_total[i]<<"\n";
  i++;
  }

}
 gotoxy(1,1);
 cout<<"\tDo you really want to exit [y(Y)/n(N)]  ";
 while(opt2!='y'||opt2!='n'||opt2!='N'||opt2!='Y')
 {
   opt2=getche();
   if(opt2=='y'||opt2=='Y')
   break;
   else
   {
    gotoxy(1,1);
    cout<<"                                                                             ";
    key=13;
    goto START;
   }
 }
 clrscr();
 cout<<"\n\tPrinting the bill....";
 getch();
}

int id_checker(char id[])
{
 int j;
 for(j=0;j<9;j++)
 {
  if(strcmpi(id,itemid[j])==0)
  return(j);
 }
 return(-1);
}

void error(int t,int t2)
{
 switch(t)
 {
  case 1:
  gotoxy(1,1);
  cout<<" Wrong id, PRESS: * to search; <ENTER> to enter id; @ to exit";
  break;
  case 2:
  gotoxy(1,1);
  cout<<"IIlegal input,Please enter a valid quantity";
  gotoxy(59,t2);
  cout<<"                       \n                                       ";
  gotoxy(59,t2);
  delay(1000);
 }
}

void line_clearer(int tmp)
{
 gotoxy(1,tmp);
 cout<<"                                                                             ";
 gotoxy(1,tmp);
}

void search_clearer(int tmp)
{
 gotoxy(1,1);
 cout<<"                                                                             ";
 gotoxy(1,tmp);
}

void search(char* item)
{
  int i,flag=0;
  for(i=0;i<10;i++)
   {
    if(strcmpi(item,itemid[i])==0)
    {
     cout<<"Item: "<<itemname[i]<<" Item Id: "<<itemid[i];
     flag=1;
     return;
    }
   }
 if(flag==0)
  {
   for(i=0;i<10;i++)
    {
     if(strcmpi(item,itemname[i])==0)
     {
      cout<<"Item: "<<itemname[i]<<" Item Id: "<<itemid[i];
      return;
     }
    }
  }
 cout<<"No match found";
}

int qnty_checker(char* qnty)
{
 for(int i=0;qnty[i]!='\0';i++)
 {
   if(isdigit(qnty[i])==0)
   return(-1);
 }
 int tmp=atoi(qnty);
 return(tmp);
}

int enter(char* res,int x,int y)
{
  int i=1;
  char tmp;
  while(1)
  {
   tmp=getch();
   if(tmp==13)
    {
      res[i]='\0';
      break;
    }
   else if((tmp>=65&&tmp<=123)||(tmp>=48&&tmp<=57))
    {
     cout<<tmp;
     x++;
     res[i]=tmp;
     i++;
    }
   else if(tmp==8)     // if back space pressed
    {
     x--;
     cout<<"\b ";
     gotoxy(x,y);
     i--;
     if(i==0)
     {
       return(-1);
     }
    }
   else
   {
    gotoxy(x,y);
    continue;
   }
  }
return(0);
}

int enter_num(char* res,int x,int y)
{
  int i=1;
  char tmp;
  while(1)
  {
   tmp=getch();
   if(tmp==13)
    {
      res[i]='\0';
      break;
    }
   else if(tmp>=48&&tmp<=57)
    {
     cout<<tmp;
     x++;
     res[i]=tmp;
     i++;
    }
   else if(tmp==8)     // if back space pressed
    {
     x--;
     cout<<"\b ";
     gotoxy(x,y);
     i--;
     if(i==0)
     {
       return(-1);
     }
    }
   else
   {
    gotoxy(x,y);
    continue;
   }
  }
return(0);
}

