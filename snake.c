//This is the classic snake game implemented in C made for 16-bit windows environment. A,W,S,D buttons are used to control the snake and food appears at random location
//Your score increases as you eat more and more food, and snake dies as it touches the boundary
// This doesn't use C graphics

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>


void printBase(void);
void printfood(void);
void print_newFood(void);
void printSnake(void);
void printModSnake1(void);
void printModSnake2(void);
int c,d,lev=1,scr=1,i=2;
static int pos[100][2];
char key;



int main()
{
 clrscr();
 print_newFood();
 gotoxy(2,9);
 printf("**\b");
 pos[0][0]=3; //initialising the value of coordinates of head of snake
 pos[0][1]=9;
 pos[1][0]=2; //initialising the value of coordinates of 2nd star of snake
 pos[1][1]=9;
 while(1)
   {
     delay(100);
     if(kbhit())
     {
	key=getch();
	if((key=='w')&&(pos[0][1]==pos[1][1])) //if snake is horizontal
	 {
	  printModSnake1();
	  pos[0][1]--;                         //row of head becomes oneless
	  if(pos[0][1]==1)
	  break;
	  clrscr();
	  printModSnake2();
	 }

	 else if((key=='s')&&(pos[0][1]==pos[1][1]))   //snake horizontal
	 {
	  printModSnake1();
	  pos[0][1]++;                        //row of head becomes one plus
	  if(pos[0][1]==20)
	  break;
	  clrscr();
	  printModSnake2();
	 }

	 else if((key=='d')&&(pos[0][0]==pos[1][0]))  //snake vertical
	 {
	  printModSnake1();
	  pos[0][0]++;                       //colmn of head becomes one plus
	  if(pos[0][0]==65)
	  break;
	  clrscr();
	  printModSnake2();
	 }

	 else if((key=='a')&&(pos[0][0]==pos[1][0]))  //snake vertical
	 {
	  printModSnake1();
	  pos[0][0]--;                  //colmn of head becomes one less
	  if(pos[0][0]==1)
	  break;
	  clrscr();
	  printModSnake2();
	 }
     }
     if(!kbhit())
     {
       if((pos[0][0]==1)||(pos[0][0]==65)||(pos[0][1]==1)||(pos[0][1]==20))
       break;
       clrscr();
       printSnake();
     }
  }
  gotoxy(70,11);
  printf("END OF GAME");
  getch();
  delay(500);
  return 0;
}


void printBase(void) //function to print base n score/level
{
int a,b;
clrscr();        //printing of base and score/level
for(a=0;a<20;a++)
{
  for(b=0;b<65;b++)
    {
    if(a==0||a==19)
    printf("!");
    else
      {
      if(b==0||b==64)
      printf("!");
      else
      printf(" ");
      }
    }
  printf("\n");
}
gotoxy(69,3);
printf("Level: %d",lev);
gotoxy(69,5);
printf("Score: %d",scr);
}

void printfood(void)
{
gotoxy(c,d);
printf("$");
}

void print_newFood(void)  //printing of new food starts here
{
/*if((scr/5==0)&&(scr!=0))
lev++,scr++;
else
scr++; */
printBase();
randomize();
c=random(60);
d=random(17);
d=d+3;
c=c+3;
gotoxy(c,d);
printf("$");
}

void printSnake(void)
{
int count;
printBase();
printfood();
if(pos[0][0]==c&&pos[0][1]==d)      //coordinates of head become equal to coordinates of food
  {
    scr++;
    i++;
    print_newFood();
  }

if((pos[0][0]==pos[1][0])&&(pos[0][1]>pos[1][1]))//vertical and head downward
{
  for(count=i-1;count>0;count--)
   {
    pos[count][0]=pos[count-1][0];
    pos[count][1]=pos[count-1][1];
   }
pos[0][1]++;
}

else if((pos[0][0]==pos[1][0])&&(pos[1][1]>pos[0][1]))//vert n head upward
{
for(count=i-1;count>0;count--)
 {
  pos[count][0]=pos[count-1][0];
  pos[count][1]=pos[count-1][1];
 }
pos[0][1]--;
}

else if((pos[0][1]==pos[1][1])&&(pos[0][0]>pos[1][0]))//horizontal n head RT
{
for(count=i-1;count>0;count--)
 {
  pos[count][0]=pos[count-1][0];
  pos[count][1]=pos[count-1][1];
 }
pos[0][0]++;
}

else if((pos[0][1]==pos[1][1])&&(pos[1][0]>pos[0][0]))//horizontal n head LFT
{
for(count=i-1;count>0;count--)
 {
  pos[count][0]=pos[count-1][0];
  pos[count][1]=pos[count-1][1];
 }
pos[0][0]--;
}

for(count=0;count<i;count++)
{
gotoxy(pos[count][0],pos[count][1]);
printf("*");
}
}


void printModSnake1(void)
{
int count;
printBase();
printfood();
if(pos[0][0]==c&&pos[0][1]==d)      //coordinates of head become equal to coordinates of food
  {
    scr++;
    i++;
    print_newFood();
  }
for(count=i-1;count>0;count--)
 {
  pos[count][0]=pos[count-1][0];
  pos[count][1]=pos[count-1][1];
 }
}

void printModSnake2(void)
{
int count;
for(count=0;count<i;count++)
    {
     gotoxy(pos[count][0],pos[count][1]);
     printf("*");
    }
}

