/* gopher.cpp
 *
 * Miguel Villanuva
 * CSAC
 * 
 * EDIT: fixed (line 83)
 * Has a bug, can win the game by choosing the same spot
 * over and over
 */

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

const int ROW = 2;
const int COL = 2;
int numGophers = 3;
int numMoves = 0;
int numMovesToWin = (ROW*COL) - numGophers;
bool youLost = false;

void printArray(int a[ROW][COL])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            cout << a[i][j] << " ";
        }
	cout << endl;
    }
}

void printArray(char a[ROW][COL])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void compute(int a[ROW][COL], int board[ROW][COL])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(a[i][j] == 1)
	        {
		        board[i][j] = 9;
		        continue;
	        }
	    
	        // Check all around
	        if(i - 1 >= 0 && a[i-1][j] == 1) 			        // Up
		        board[i][j] += 1;
	        if(i - 1 >= 0 && j + 1 < ROW && a[i-1][j+1] == 1) 	// Up Right
		        board[i][j] += 1;
	        if(j + 1 < COL && a[i][j+1] == 1) 			        // Right
                board[i][j] += 1;
	        if(i + 1 < ROW && j + 1 < COL && a[i+1][j+1] == 1) 	// Down Right
                board[i][j] += 1;
	        if(i + 1 < ROW && a[i+1][j] == 1) 			        // Down
                board[i][j] += 1;
	        if(i + 1 < ROW && j - 1 >= 0 && a[i+1][j-1] == 1) 	// Down Left
                board[i][j] += 1;
	        if(j - 1 >= 0 && a[i][j-1] == 1)			        // Left
                board[i][j] += 1;
	        if(i - 1 >= 0 && j - 1 >=0 && a[i-1][j-1] == 1)   	// Up Left
                board[i][j] += 1;
        }
    }
}

// This is segfaulting because it keeps checking the same spaces
void reveal(int x, int y, int board[ROW][COL], char game[ROW][COL])
{
    if(game[x][y] == '+')
	    numMoves++;

    if(board[x][y] == 0)
    {
	    game[x][y] = '0';
	    // Check all around
        if(x - 1 >= 0 && game[x-1][y] == '+')                    // Up
            reveal(x-1, y, board, game);
        if(x - 1 >= 0 && y + 1 < ROW && game[x-1][y+1] == '+')   // Up Right
            reveal(x-1, y+1, board, game);
        if(y + 1 < COL && game[x][y+1])		                     // Right
            reveal(x, y+1, board, game);
        if(x + 1 < ROW && y + 1 < COL && game[x+1][y+1] == '+')  // Down Right
            reveal(x+1, y+1, board, game);
        if(x + 1 < ROW && game[x+1][y] == '+')                   // Down
            reveal(x+1, y, board, game);
        if(x + 1 < ROW && y - 1 >= 0 && game[x+1][y-1] == '+')   // Down Left
            reveal(x+1, y-1, board, game);
        if(y - 1 >= 0 && game[x][y-1] == '+')                    // Left
            reveal(x, y-1, board, game);
        if(x - 1 >= 0 && y - 1 >=0 && game[x-1][y-1] == '+')     // Up Left
            reveal(x-1, y-1, board, game);
    }
    else
    {
	    game[x][y] = '0' + board[x][y];
	    if(game[x][y] == '9')
	    {
	        game[x][y] = 'G';
	        youLost = true;
	        cout << "You lose" << endl;
	    }
    }
}

int main()
{
    srand(time(NULL));
    int array[ROW][COL], board[ROW][COL];
    char game[ROW][COL];

    // Zero out every 2D array
    for(int i = 0; i < ROW; i++)
    {
	for(int j = 0; j < COL; j++)
	{
	    array[i][j] = 0;
	    board[i][j] = 0;
	    game[i][j] = '+';
	}
    }

    // Spawn gophers
    int i = 0;
    while(i < numGophers)
    {
	    int r = rand() % ROW;
	    int c = rand() % COL;
	    if(array[r][c] == 0)
	    {
	        array[r][c] = 1;
	        i++;
	    }
    }

    printArray(array);
    cout << endl;
    compute(array, board);
    printArray(board);
    cout << endl;

    cout << "Welcome to the game of gophers" << endl;
    printArray(game);

    while(numMoves != numMovesToWin && !youLost)
    {
	    int x, y;
	    cout << "Enter the thing" << endl;
	    cin >> x;
	    cin >> y;
	    reveal(x, y, board, game);
	    printArray(game);
    }

    if(!youLost)
	    cout << "You de winna" << endl;

    /*int x, y;
    cout << "Enter coordinates" << endl;
    cin >> x;
    cin >> y;
    reveal(x, y, board, game);
    */
    //int n = 4;
    //char c = '+';
    //c = '0' + n;
    //cout << c << endl;
    //cout << endl;
    //printArray(game);
    return 0;
}


