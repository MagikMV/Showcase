/* TestMaze.cpp
 *
 * CS 121 Bolden    //                      GCC 5.1.0                   //  Miguel Villanueva
 * October 2, 2019  //  Eluktronics P65_67HSHP // Intel Core i7-7700HQ  //  vill9577@vandals.uidaho.edu
 *
 * Program Description:
 *     Maze traversal using dynamic arrays and stacks. Where storage for the maze is dynamically allocated
 *     using arrays and the solution or path is found using stacks.
 */

#include <iostream>
#include <fstream>

#include "stack.cpp"

using namespace std;

bool visitedCell(int direction, int *&Array, int arraySize); // Checks if the cell is marked as visited

int main()
{
    cout << "TestMaze.cpp" << endl << endl;
    cout << "Miguel Villanueva" << endl;
    cout << "October 2, 2019" << endl << endl << endl;

    ifstream infile;
    infile.open("maze1.txt");

    int rowSize, columnSize; // Width and height specified in the first line of the included .txt file
    infile >> rowSize;
    infile >> columnSize;
    int mazeSize = rowSize * columnSize;

    char *maze = new char[mazeSize]; // Dynamic array that stores the maze
    int wrap = 0; // Variable that simulates the change row number of a 2D array

    //***PRINT AND STORE MAZE***//
    for(int i = 0; i < mazeSize; i++)
    {
        infile >> maze[i]; // Reads file into the dynamic array
        cout << maze[i];    // Prints maze as reference for user to compare to the solution
        wrap++;
        if(wrap == columnSize)
        {
            cout << endl;
            wrap = 0;
        }
    }

    //***FIND STARTING POSITION AND GOAL***
    int currentCell, exit; // Store positions
    for(int i = 0; i < mazeSize; i++)
    {
        if(maze[i] == 'S')
            currentCell = i;
        if(maze[i] == 'G')
            exit = i;
    }
    int north, east, south, west; // Direction of travel in the maze
    north = currentCell - columnSize; // Expression that refers to the cell above the current cell
    east = currentCell + 1; // Expression that refers to the cell that is right of the current cell
    south = currentCell + columnSize; // Expression that refers to the cell below the current cell
    west = currentCell - 1; // Expression that refers to the cell that is left of the current cell
    int visitedSize = 1; // Array size
    int *visited = new int[visitedSize]; // Dynamic array that stores positions of each cell that is visited
    visited[visitedSize - 1] = currentCell; // Stores the position at the start of the maze
    int *directionVisited = new int[mazeSize]; // Dynamic array that accounts for the direction that the maze is traversed
    int neighborsFoundSize = 1;
    int *neighborsFound = new int[neighborsFoundSize];
    Stack mazeStack; // Creates an object of the Stack class
    //***TRAVERSING THE MAZE***
    while(north != exit || east != exit || south != exit || west != exit)
    {
        north = currentCell - columnSize;           //                             //
        east = currentCell + 1;                     //  Updates positional values  //
        south = currentCell + columnSize;           //                             //
        west = currentCell - 1;                     //                             //
        // Top Left, cannot go west or north
        if(currentCell == 0)
        {
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Top Right, cannot go east or north
        else if(currentCell == columnSize - 1)
        {
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Bottom Left, cannot go west or south
        else if(currentCell == mazeSize - columnSize)
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Bottom Right, cannot go east or south
        else if(currentCell == mazeSize - 1)
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Left Edge, cannot go west
        else if(currentCell%columnSize == 0 && currentCell != 0 && currentCell != mazeSize - columnSize)
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Top Edge, cannot go north
        else if(currentCell < columnSize && currentCell > 0 && currentCell < columnSize - 1)
        {
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Right Edge, cannot go east
        else if(currentCell%columnSize == columnSize - 1 && currentCell != columnSize - 1 && currentCell != mazeSize - 1)
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Bottom Edge, cannot go south
        else if(currentCell < mazeSize && currentCell >= mazeSize - columnSize && currentCell != mazeSize - columnSize && currentCell != mazeSize - 1)
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // No Edge, ability to traverse to the north, east, west, and south if move is legal
        else
        {
            if(maze[north] == '.' && visitedCell(north, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(north);
                directionVisited[north] = 1;
                neighborsFound[neighborsFoundSize - 1] = north;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[south] == '.' && visitedCell(south, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(south);
                directionVisited[south] = 3;
                neighborsFound[neighborsFoundSize - 1] = south;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            if(maze[east] == '.' && visitedCell(east, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(east);
                directionVisited[east] = 2;
                neighborsFound[neighborsFoundSize - 1] = east;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
            // For maze1, program kapoots here, adds 44 which is already in the stack
            if(maze[west] == '.' && visitedCell(west, visited, visitedSize) != true && mazeStack.alreadyInStack(neighborsFound, neighborsFoundSize) != true)
            {
                mazeStack.push(west);
                directionVisited[west] = 4;
                neighborsFound[neighborsFoundSize - 1] = west;
                neighborsFoundSize = neighborsFoundSize + 1;
            }
        }
        // Nothing was pushed onto the stack && stack is empty, unsolvable maze
        if(mazeStack.isEmpty() == true) // problem could be here discovered 10/30/19
        {
            cout << endl << "The Maze Is Unsolvable" << endl;
            break;
        }
        mazeStack.printStack(); // Included to get some output since program falls through at some along run time
        cout << endl;
        currentCell = mazeStack.pop(); // Removes the next element in the stack and makes it the current cell
        visitedSize = visitedSize + 1; // Dynamic array size increase
        visited[visitedSize - 1] =  currentCell; // Records the position of the current cell
    }
    //***WAS THE MAZE SOLVED***
    north = currentCell - columnSize;           //                             //
    east = currentCell + 1;                     //  Updates positional values  //
    south = currentCell + columnSize;           //                             //
    west = currentCell - 1;                     //                             //
    if(north == exit || east == exit || south == exit || west == exit)
    {
        cout << endl << "Congratulations, You Did The Thing" << endl;
    }

    //***CHANGE CHARACTERS INSIDE OF MAZE FOR OUTPUT WITH AN OUTLINED PATH***
    for(int i = 0; i < mazeSize; i++)
    {
        int x = visited[i];
        maze[x] = directionVisited[x];
        if(directionVisited[x] == 1) // North
        {
            maze[x] = '^';
        }
        if(directionVisited[x] == 2) // East
        {
            maze[x] = '>';
        }
        if(directionVisited[x] == 3) // South
        {
            maze[x] = 'V';
        }
        if(directionVisited[x] == 4) // West
        {
            maze[x] = '<';
        }
    }

    //***PRINT OUT PATH OUTLINED MAZE***
    int wrap2 = 0;
    for(int i = 0; i < mazeSize; i++)
    {
        cout << maze[i];
        wrap2++;
        if(wrap2 == columnSize)
        {
            cout << endl;
            wrap2 = 0;
        }
    }
    delete []maze;               //                                     //
    delete []visited;            // Delete dynamically allocated memory //
    delete []directionVisited;   //                                     //

}

//***CHECK IF CELL IS MARKED AS VISITED***
bool visitedCell(int direction, int *&Array, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(Array[i] == direction)
        {
            return true; // Return true if position is already existent in visited array (i.e. if the position has been visited)
        }
    }
    return false;
}
