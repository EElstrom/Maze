#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 15
#define COL 15

// multidimensional array for maze
int maze[ROW][COL];

void mazeProblem(void);
void printMaze(int maze[][COL]);

void generateMaze(int maze[][COL], 
				  int rowStart, 
				  int colStart, 
				  int rowEnd, 
				  int colEnd);
				  
int mazeTraverse(int maze[][COL], 
				 int row, 
				 int col, 
				 int p);
				 
int checkSolve(int maze[][COL], 
			   int row, 
			   int col);

void mazeProblem (void)
{

	// initialize maze in one block
	for (int i = 0; i < ROW; i++) 
	{
		for (int j = 0; j < COL; j++)
		{
			maze[i][j]='#';
		}
	}

	// create entry and exit randomly
	srand(time(NULL));
	int rowStart= 1 + rand()%(ROW-2);
	int colStart = 0;

	int rowEnd = 1 + rand()%(ROW-2);
	int colEnd = COL-1;
	
	// call maze generator with now defined parameters.
	generateMaze(maze, rowStart, colStart, rowEnd, colEnd);

	// utilize traversal function to check if maze is valid. Set printing parameter to 0.
	while(!mazeTraverse(maze, rowStart, colStart+1, 0))
		generateMaze(maze, rowStart, colStart, rowEnd, colEnd);
	
	// clear out the breadcrumbs and path markers left from checking validity
	for (int i=0; i<ROW; i++) 
	{
		for (int j = 0; j < COL; j++)
		{
			if (maze[i][j] == 'o' || maze[i][j]=='.')
			{
				maze[i][j]=' ';
			}
		}
	}

	// Maze is solvable, and mazeTraverse will return true. 
	// Printing parameter is set to 1 so that progress can be viewed.
	if (mazeTraverse(maze, rowStart, colStart+1, 1))
	{
		printMaze(maze);
		printf("\n\nSolved.\n");
	}
	// error message, just in case.
	else
		puts("\n\nThere shouldn't be an else.. something bad happened. Error!\n");    
}

// function to print maze
void printMaze(int maze[][COL]) 
{
	printf("\n\n");
	for (int i = 0; i < ROW; i++) 
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%c ", maze[i][j]);
		}
	printf("\n");
	}
}

// function to generate maze. 
void generateMaze(int maze[][COL], int rowStart, int colStart, int rowEnd, int colEnd)
{

	// flag entry and exits
	maze[rowStart][colStart] =  'X';
	maze[rowEnd][colEnd] = '!';
	// clear spaces directly leading from and to flags for better chances at maze validity.
	maze[rowStart][colStart+1]=' ';
	maze[rowEnd][colEnd-1]= ' ';

	// seed random element
	srand(time(NULL));

	// iterate over each element inside walls and randomly decide (of a 2/3 chance)
	// if the space will be cleared. 
	for (int i = 1; i < ROW-1; i++)
	{
		for (int j = 1; j < COL-1; j++)
		{
			int path = rand()%3;
			if(path > 0)
			{
				maze[i][j] = ' ';
			}
		else 
			continue;
		}
	}  
}

// Recursive traversal function
// parameter 'p' used to designate when the maze progress should be printed.
int mazeTraverse (int maze[][COL], int row, int col, int p)
{
	// each step except for the solution (flagged exit) returns 0; 
	// this check calls the solution function, which will return either true or false, 
	// which will be the only time this function also returns true.
	if (checkSolve(maze, row, col))
	{
		return 1;
	}
	
	// check for the walls or if the location has already been visited
	if (maze[row][col]=='#' || maze[row][col]=='.')
	{
		return 0;
	}
	
	// empty character space will be rewritten with a '.' flag
	if (maze[row][col]==' ')
	{
		maze[row][col]='.';
	}
	
	// for printing purposes
	if (p) 
	{
		printMaze(maze);
		// pressing enter to run each iteration
		char k;
		scanf("%c", &k);
	}
	
	// recursive element of function. Each statement calls the traversal function again, 
	// and will progress to the right, down, left, and then finally up. 
	// The recursiveness of this function will pop several stacks if it cannot turn in any 
	// direction without hitting a wall or '.', and then reset coordinates back to a prior junction.
	// by no means will it find the fastest solution, but it will find it.
	// when the value of the function returns true (by finding exit), all of the successful recursive 
	// calls will pop and return true, labeling each success with a 'o' to mark its solution path.
	if (mazeTraverse(maze, row, col+1, p) || 
		mazeTraverse(maze, row+1, col, p) ||
		(maze, row, col-1, p) ||
		mazeTraverse(maze, row-1, col, p) )
	{
		maze[row][col]='o';
		return 1;
	}
	return 0;
}

// function which returns true when traversal finds the eixt,
// which is flagged with it's own unique character.
int checkSolve (int maze[][COL], int row, int col)
{
	if (maze[row][col]=='!')
	{
		return 1;
	}
	return 0;
}


