// This is the program implementing Breadth First Search on graph using C.
// Maximum number of possible nodes in graph can be 10
// Pretty much general, can be extended to any number of nodes after some modifications
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct queue{		// Queue is the primary structure used in Breadth First Search 
	int node_no;		//number of that particular node
	int Data;		//data at that particular node
	struct queue * next;	//pointer to next node
}queue_node;

queue_node * front=NULL;	//front pointer to queue
queue_node * rear=NULL;		//rear pointer to queue

int BFS(int, int [], int [][10], int, int);		// function returning node number if match occurs at any node, otherwise returns -1

int main()
{
	int data[10], i, j, n;						// data - array of data in nodes, i,j - loop counters, n - number of nodes in graph
	int item, target;						// item - to be searched, target - node number returned by BFS function (contains solution)
	int start, adjacency_matrix[10][10];		  		// start - node number from where to start BFS, adjacency_matrix - adjacency matrix
	printf("Enter total number of nodes [Max possible =10, min =1]:\t");
	scanf("%d",&n);
	printf("Enter data at all nodes starting from node no. 0 uptill node no n\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&data[i]);
	}
	printf("Enter the adjacency matrix for %d nodes:\n" , n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&adjacency_matrix[i][j]);
		}
	}
	printf("Enter the item to be searched");
	scanf("%d",&item);
	printf("Enter the node no to be taken as starting node");
	scanf("%d",&start);

	target=BFS(n,data,adjacency_matrix,item,start);
	if(target==-1)
	{
		printf("\nitem not found ..... program will now terminate");  
	}
	else
	{
		printf("\nitem found at node number : %d", target);
	}
	getch();
	return 0;
}

int BFS(int n, int data[], int adjacency_matrix[][10], int item, int start)		// argument list --> n - number of nodes, data - array of data at nodes,
{											// adjacency_matrix - adjacency matrix of graph, item - to be searched, start - starting node
	int i, status[10], j, tmp;		
						// i,j - loop variable, status - array saving ready, waiting, processed states of nodes, tmp - temporary variable 
	queue_node * ptr;			// pointer to a node
	if(n==1)
	{
		if(item==data[0])
		{
			return 0;
		}
		else 
		return -1;
		
	}
	else
	{
		for(i=0;i<n;i++)
		{
			status[i]=1;
		}
		front=(queue_node *)malloc(sizeof(queue_node));
		rear=front;
		front->node_no=start;
		front->Data=data[start];
		front->next=NULL;
		status[start]=2;
		while(front!=NULL)
		{

		   tmp=front->node_no;
		    status[tmp]=3;
		    if(front->Data==item)
		    {
			    return tmp;
		    }
		    for(i=0;i<n;i++)
		    {
			    if((adjacency_matrix[tmp][i]!=0)&&tmp!=i)
			    {
				    if(status[i]==1)
				    {
					    ptr=(queue_node *)malloc(sizeof(queue_node));
					    ptr->node_no=i;
					    ptr->Data=data[i];
					    ptr->next=NULL;
					    status[i]=2;
      	  				
					    rear->next=ptr;
					    rear=rear->next;
				    }
			    }

		    }
		    ptr=front;
		    front=front->next;
		    free(ptr);
		 }
		
	}
	return -1;
}
