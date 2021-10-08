#include<stdio.h>
#include<stdlib.h>

struct row
{
    	int i;
    	int j;
	int r;
    	struct row* link;
}*head1 = NULL, *head2 = NULL;

void push(int, int);
void popstore(struct row*);
int checkpop(int, int);
struct row* pop();
struct row* move();
int check(int, int);
void solveMaze(int maze[10][10]);
void printSolution(int maze[10][10]);
int sol[10][10];

int main()
{   
    	int maze1[10][10] =  {{1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
 					         {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
			                 {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
			                 {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
			                 {1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
			                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			                 {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
			                 {0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
			                 {0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
			                 {0, 0, 0, 1, 1, 1, 1, 1, 0, 1}};
 	
   	    int maze2[10][10] = {{1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		       	            {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		       	            {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
		                    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		                    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		                    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		                    {0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
		                    {0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		                    {0, 0, 0, 1, 1, 1, 1, 1, 0, 1}};
	int i, j;
	for(i=0; i<10; i++)
		for(j=0; j<10; j++)
			sol[i][j] = 0;
    //solveMaze(maze1);
    //printSolution(maze1);
	solveMaze(maze2);
	printSolution(maze2);
	return 0;
}

//Push elements into the stack
void push(int i, int j)
{
    	struct row *n,*h,*t;
    	n = malloc(sizeof(struct row));
    	n->i = i;
    	n->j = j;
    	n->link = NULL;
    	
	if(head1 == NULL)
        	head1 = n; 
    	
	else
        {   
            	t = head1;
            	n->link = t;
            	head1 = n;
        }
} 

//Stores elements popped from the stack in a Linked List
void popstore(struct row* n)
{
	struct row *t;
	n->link = NULL;
	    
	if(head2 == NULL)
		head2=n;
    	else
    	{
        	t = head2;
        	n->link = t;
        	head2 = n; 
     	}
}

//Checks if i, j have already been popped from the stack
int checkpop(int i, int j)
{
    	struct row* t;
    	t = head2;
    	if(t == NULL)
		return 1;
    	else
	{
		while(t != NULL)
    		{   
        		if(((t->i) == i) && ((t->j) == j))
				return 0;
        
        		t = t->link;
    		}
	}
	return 1;
}  

//Pops elements from the stack
struct row* pop()
{
    	struct row *t;
    	t = head1;
    	head1 = head1->link;
    	return t;
}

//Checks if i, j have already been pushed into stack 1
int check(int i,int j)
{
	struct row* t;
    	t = head1;
    	if(i == 0 && j == 0)
		return 0;
    	else
	{
		while(t!=NULL)
    		{   
			if(((t->i) == i) && ((t->j) == j))
				return 0;
     
		        t=t->link;
    		}
	}
	return 1;
}  

//Checks the Right, Down, Left, Up conditions and changes value of stack, maze[i][j] and sol[i][j] accordingly
void solveMaze(int maze[10][10])
{
	struct row *t;	
	int i = 0, j = 0;
	t = malloc(sizeof(struct row));
	t->r = 0;
	t->i = 0; 
	t->j = 0;
	while(i<10 && j<10)
    	{   	
		if(head1 == NULL)
			push(i,j);
        	else
		{
		        i = head1->i;
			j = head1->j;
			//Right
			if(maze[i][j+1] != 0 && check(i,(j+1)) && checkpop(i,(j+1)) && j<9)
            		{
				maze[i][j]++;
				sol[i][j]++;	
				j++;
				push(i,j);
			}
			//Down
            		else if(maze[i+1][j] != 0 && check((i+1),j) && checkpop((i+1),j) && i<9)
                        {
				maze[i][j]++;
				sol[i][j]++;				
				i++;
				push(i,j);
			}
			//Left
            		else if(maze[i][j-1] != 0 && check(i,(j-1)) && checkpop(i,(j-1))  && j>0)
            		{
				maze[i][j]++;
				sol[i][j]++;				
				j--;
				push(i,j);
			}
			//Up
		        else if(maze[i-1][j] != 0 && check((i-1),j) && checkpop((i-1),j)  && i>0)
            		{
				maze[i][j]++;
				sol[i][j]++;				
				i--;
				push(i,j);
			}
			//BackTracking
            		else
			{
				maze[i][j]++;
				sol[i][j]++;
				popstore(pop());
			}
			if(i == 9 && j == 9)
			{
				maze[i][j] = 1;	
				sol[i][j] = 1;			
				printf("\nSolution path for Maze is:\n--------------------------\n");
				break;
			}
            		if(i == 0 && j == 0)
			{
				printf("\nSolution doesn't exist...");
        			printf("\nPath till reaching a dead end was:\n----------------------------------\n");
				break;
			}
            		t = head1->link;
            		if(t == NULL)
            		{ 
				t = malloc(sizeof(struct row));
				t->i=0; 
				t->j=0; 
			}
            	}
	}   
}

//Prints the effective path traversed by mouse in linked list and matrix form
void printSolution(int maze[10][10])
{
	struct row *t;
	int i = 0, j = 0;	
	t = head1;
    	while(t != NULL)
    	{ 
		printf(" <- (%d,%d) ",(t->i),(t->j));
      		t = t->link;  
	}
	printf("\n");
	printf("\nThe Path traversed:\n");
      	for(i = 0; i < 10;i++)
      	{
        	for(j=0;j<10;j++)
		{
			printf(" %d  ",sol[i][j]);
		}
        	printf("\n");
      	}
}