//This is implementation of Mini-Max algorithm on Tic-Tac-Toe game using C/C++
//This code is not complete as I am working on it nowadays 

#include<iostream>
#include<stdio.h>
#include<stdlib.h>


typedef struct data_returned_from_minmax
{
	int value;
	int path;
}MOVE;

void Go(int n,int turn,int *board);	//takes the player to nth postion and records his symbol at that location
void UndoGo(int n,int *board);		// Undo the work done by Go 
int Posswin(char player,int *board); //returns 0 if no winning position is available with respect to the player being passed otherwise the position which  
int Static(int position,char player,int *board,char first_player);  //heuristic function returning value taking into consideration the player being passed
int * Movegen(int position, char player,int *board);  //generates all plausible moves for the player being passed from its current position
int DeepEnough(int depth,int depthlimit);
char Opposite(char player);
int Win(char player, int * board);

MOVE MinMax(int position,int depth,int depthlimit, int turn, char player, int *board, char player_who_played_first);

using namespace std;
int main()
{
	int depthlimit, mov_pos, board[10]={2,2,2,2,2,2,2,2,2,2}, turn=1, current, depth=0;
	MOVE my_mov;
    char option;
    cout<<"\nInput the depth Upto which processing is to be done:";
	cin>>depthlimit;
    cout<<"\nYou wanna play First or second(f/s):";
    cin>>option;
    if(option=='f')
    {
	do
	{
		cout<<"\nEnter your move position";
		cin>>mov_pos;
		if(turn==1)
			{
				if(mov_pos==1)
				current=4;
			else
				current=0;
			}

		Go(mov_pos-1,turn,board);
		cout<<"\nyou moved to position"<<mov_pos;
		if(Win('X',board))
		{
			cout<<"Human has won";
			for(int i=0;i<9;i++)
				cout<<"\n"<<board[i]<<"\t";
			sleep(5);
			exit(0);
		}
		turn++;
		my_mov=MinMax(current,depth,depthlimit,turn,'0',board,'H');
		Go(my_mov.path,turn,board);
		cout<<"\nComputer moved to position"<<(my_mov.path+1);
		if(Win('0',board))
		{
			cout<<"Computer has won";
			sleep(5);
			exit(0);
		}
		current=my_mov.path;
		turn++;
		depth++;
	}while(turn<=9);

    }
    else
    {
	current=0;
	do
	{
		my_mov=MinMax(current,depth,depthlimit,turn,'X',board,'C');
		Go(my_mov.path,turn,board);
		cout<<"\nComputer moved to position"<<(my_mov.path+1);
		if(Win('X',board))
		{
			cout<<"Computer has won";
			sleep(5);
			exit(0);
		}
		current=my_mov.path;
		turn++;
		depth++;
		cout<<"Enter your move position";
		cin>>mov_pos;
		Go(mov_pos-1,turn,board);
		cout<<"\nyou moved to position"<<mov_pos;
		if(Win('0',board))
		{
			cout<<"Human has won";
			for(int i=0;i<9;i++)
				cout<<"\n"<<board[i]<<"\t";
			sleep(5);
			exit(0);
		}
		turn++;

	}while(turn<=9);
    }
    sleep(5);
    return 0;
}


void Go(int n,int turn,int *board)
{
	if(turn%2==1) //odd turn
		board[n]=3;
	else
		board[n]=5;
}

void UndoGo(int n,int *board)
{
	board[n]=2;
}

int Posswin(char player, int *board)
{
	int i,j;
	if(player=='X')
	{
		for(i=0;i<7;i+=3)
		{
			if(board[i]*board[i+1]*board[i+2]==18)  // row wise checking
			{
				if(board[i]==2)
					return i;
				else if(board[i+1]==2)
					return i+1;
				else
					return i+2;
			}
		}

		for(i=0;i<3;i++)
		{
			if(board[i]*board[i+3]*board[i+6]==18) //column wise checking
			{
				if(board[i]==2)
					return i;
				else if(board[i+3]==2)
					return i+3;
				else
					return i+6;
			}

		}

		if(board[0]*board[4]*board[8]==18) //diagonal 1
		{
			if(board[0]==2)
					return 0;
			else if(board[4]==2)
					return 4;
			else
					return 8;
		}

		else if(board[2]*board[4]*board[6]==18)  //diagonal 2
		{
			if(board[2]==2)
					return 2;
			else if(board[4]==2)
					return 4;
			else
					return 6;
		}
		return 0;


	}


	else
	{
		for(i=0;i<7;i+=3)
		{
			if(board[i]*board[i+1]*board[i+2]==50)  // row wise checking
			{
				if(board[i]==2)
					return i;
				else if(board[i+1]==2)
					return i+1;
				else
					return i+2;
			}
		}

		for(i=0;i<3;i++)
		{
			if(board[i]*board[i+3]*board[i+6]==50) //column wise checking
			{
				if(board[i]==2)
					return i;
				else if(board[i+3]==2)
					return i+3;
				else
					return i+6;
			}

		}

		if(board[0]*board[4]*board[8]==50) //diagonal 1
		{
			if(board[0]==2)
					return 0;
			else if(board[4]==2)
					return 4;
			else
					return 8;
		}

		else if(board[2]*board[4]*board[6]==50)  //diagonal 2
		{
			if(board[2]==2)
					return 2;
			else if(board[4]==2)
					return 4;
			else
					return 6;
		}
		return 0;

	}
}

int DeepEnough(int depth,int depthlimit)
{
	if(depth>=depthlimit)
		return 1;
	else
		return 0;
}

char Opposite(char player)
{
    if(player=='X')
	{return '0'; }
    else if(player=='0')
	{return 'X'; }
}                                                               



int Static(int position,char player,int *board,char first_player)  //heuristic function returning value taking into consideration the player being passed
{
    int wp;//Winning Probability
    int mf;//mf:multiplying factor
    
    wp=Posswin(Opposite(player),board);
    
    if((player=='X'&&first_player=='C')||(player=='0'&&first_player=='H'))
    	 mf=1;
    if((player=='X'&&first_player=='H')||(player=='0'&&first_player=='C'))
     	mf=-1;
    if(wp==1)
    {
         return(50*mf);
    }
    else
    {
		if (position%2==0)
			return(1*mf);
        else if(position==5)
        	return(5*mf);
        else
            return(3*mf);
     
    }
}



int * Movegen(int position, char player,int *board)
{

    int *succ=new int[9];
    int count=0,i;
    for(i=0;i<9;i++)
    {
	succ[i]=-1;
    }
    for(i=0;i<9;i++)
    {
	if(board[i]==2)
	{
	    succ[count]=i;
	    count++;
	}
    }
    
    return(succ);
    sleep(5);
}

int Win(char player, int * board)
{
	int i,j;
	if(player=='X')
	{
		for(i=0;i<7;i+=3)
		{
			if(board[i]*board[i+1]*board[i+2]==27)  // row wise checking
			{
				return 1;
			}
		}

		for(i=0;i<3;i++)
		{
			if(board[i]*board[i+3]*board[i+6]==27) //column wise checking
			{
				return 1;
			}

		}

		if(board[0]*board[4]*board[8]==27) //diagonal 1
		{
			return 1;
		}

		else if(board[2]*board[4]*board[6]==18)  //diagonal 2
		{
			return 1;
		}
		return 0;


	}


	else
	{
		for(i=0;i<7;i+=3)
		{
			if(board[i]*board[i+1]*board[i+2]==125)  // row wise checking
			{
				return 1;
			}
		}

		for(i=0;i<3;i++)
		{
			if(board[i]*board[i+3]*board[i+6]==125) //column wise checking
			{
				return 1;
			}

		}

		if(board[0]*board[4]*board[8]==125) //diagonal 1
		{
			return 1;
		}

		else if(board[2]*board[4]*board[6]==125)  //diagonal 2
		{
			return 1;
		}
		return 0;

	}
}

MOVE MinMax(int position,int depth,int depthlimit,int turn, char player, int *board, char first_playing_player)
{
	int count=0, val=0, i, *succ=NULL, newvalue, pos, undo=0, bestscore=-1000;

	MOVE record,result;                                                //record= new MOVE[9-(depth+1)];  //only this number of new children can be generated at this depth

	
    if(DeepEnough(depth,depthlimit))
    {
	record.value=Static(position,player,board,first_playing_player);
	record.path=0;
	return(record);
    }




    
    else
    {
	succ=Movegen(position,player,board);
	for(i=0;i<9;i++)
	{
	    if(succ[i]!=-1)
	    count++;
	}
	if(count==0)
	{
		record.value=Static(position,player,board,first_playing_player);
		record.path=0;
		return(record);
	}
	else
	{
	    for(i=0;(i<9&&succ[i]!=-1);i++)
	    {
		printf("\n Succ[%d]=%d",i,succ[i]);
		Go(succ[i],turn,board);    ///changed*****
		turn++;
		record=MinMax(succ[i],depth+1,depthlimit,turn,Opposite(player),board,first_playing_player); //recursive call
		sleep(5);
		newvalue=-1*(record.value);    //negation of value
		if(newvalue>bestscore)
		{
		    cout<<"\nnewvalue :"<<newvalue;
		    UndoGo(succ[i],board);
		    turn--;                           //if better previous best value is attained the move made in the previous best cell is undone
		    bestscore=newvalue;
		    result.value=newvalue;
		    result.path=succ[i];
		}
		else
		{

		    UndoGo(succ[i],board);
		    turn--;
		}
		
	    }

	}
    }
    return(result);
}



  

	
	
	
           
