
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double calculateDistance(int row, int col, int goalRow, int goalCol)
{
    return sqrt(
        (row - goalRow) * (row - goalRow) +
        (col - goalCol) * (col - goalCol)
    );
}

int main()
{
    // The assignment requires a fixed 20x20 grid.
    int grid[20][20];

    // Start and goal positions follow the coordinate system defined in the assignment.
    int startRow = 0;
    int startCol = 0;

    int goalRow = 19;
    int goalCol = 19;

    // A cell must have a lower movement cost to replace its current path.
    int gCost[20][20];

    // Parent coordinates are needed because the final path is reconstructed backwards.
    int parentRow[20][20];
    int parentCol[20][20];

    // Prevents processing the same cell more than once.
    bool closedList[20][20];

    // Keep discovered cells separate from processed cells until they are selected for expansion.
    bool openList[20][20];

    // Preserve discovery order to resolve equal-cost choices deterministically.
    int discoveryOrder[20][20];
    int discoveryCounter = 0;

    // Initialize all helper arrays.
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            gCost[i][j] = 999999;
            parentRow[i][j] = -1;
            parentCol[i][j] = -1;
            closedList[i][j] = false;
            openList[i][j] = false;
            discoveryOrder[i][j] = -1;
        }
    }

    gCost[startRow][startCol] = 0;
    openList[startRow][startCol] = true;
    discoveryOrder[startRow][startCol] = discoveryCounter++;

    int currentRow = -1;
    int currentCol = -1;
    double bestF;
    int bestDiscoveryOrder;

    ifstream file("grid.txt");

    if (!file.is_open())
    {
        cout << "Cannot open grid.txt." << endl;
        return 1;
    }

    // Keep the map in memory so its cells can be accessed during pathfinding.
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            file >> grid[19 - i][j];
        }
    }

    file.close();

    while (true)
    {
        currentRow = -1;
        currentCol = -1;
        bestF = 999999;
        bestDiscoveryOrder = -1;

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (openList[i][j])
                {
                    double f = gCost[i][j] + calculateDistance(i, j, goalRow, goalCol);

                    if (f < bestF || (f == bestF && discoveryOrder[i][j] > bestDiscoveryOrder))
                    {
                        bestF = f;
                        bestDiscoveryOrder = discoveryOrder[i][j];
                        currentRow = i;
                        currentCol = j;
                    }
                }
            }
        }

        if (currentRow == -1)
        {
            break;
        }

        openList[currentRow][currentCol] = false;
        closedList[currentRow][currentCol] = true;

        if (currentRow + 1 < 20) // UP movement
        {
            int neighborRow = currentRow + 1;
            int neighborCol = currentCol;

            if (grid[neighborRow][neighborCol] != 5 &&
                !closedList[neighborRow][neighborCol])
            {
                int newG = gCost[currentRow][currentCol] + 1;

                if (newG < gCost[neighborRow][neighborCol])
                {
                    gCost[neighborRow][neighborCol] = newG;
                    parentRow[neighborRow][neighborCol] = currentRow;
                    parentCol[neighborRow][neighborCol] = currentCol;

                    if (!openList[neighborRow][neighborCol]) // if neighbor is not in the open list
                    {
                        openList[neighborRow][neighborCol] = true;
                        discoveryOrder[neighborRow][neighborCol] = discoveryCounter++;
                    }
                }
            }
        }

        if (currentRow - 1 >= 0) // DOWN movement
        {
            int neighborRow = currentRow - 1;
            int neighborCol = currentCol;

            if (grid[neighborRow][neighborCol] != 5 &&
                !closedList[neighborRow][neighborCol])
            {
                int newG = gCost[currentRow][currentCol] + 1;

                if (newG < gCost[neighborRow][neighborCol])
                {
                    gCost[neighborRow][neighborCol] = newG;
                    parentRow[neighborRow][neighborCol] = currentRow;
                    parentCol[neighborRow][neighborCol] = currentCol;

                    if (!openList[neighborRow][neighborCol])
                    {
                        openList[neighborRow][neighborCol] = true;
                        discoveryOrder[neighborRow][neighborCol] = discoveryCounter++;
                    }
                }
            }
        }
        if(currentCol-1 >= 0) // LEFT movement
        {
            int neighborRow = currentRow;
            int neighborCol = currentCol - 1;

            if (grid[neighborRow][neighborCol] != 5 &&
                !closedList[neighborRow][neighborCol])
            {
                int newG = gCost[currentRow][currentCol] +1;

                if(newG < gCost[neighborRow][neighborCol])
                {
                    gCost[neighborRow][neighborCol] = newG;
                    parentRow[neighborRow][neighborCol] = currentRow;
                    parentCol[neighborRow][neighborCol] = currentCol;

                    if (!openList[neighborRow][neighborCol])
                    {
                        openList[neighborRow][neighborCol] = true;
                        discoveryOrder[neighborRow][neighborCol] = discoveryCounter++;
                    }
                }
            }
        }
        if(currentCol+1 < 20) // RIGHT movement
        {
            int neighborRow = currentRow;
            int neighborCol = currentCol + 1;

            if (grid[neighborRow][neighborCol] != 5 &&
                !closedList[neighborRow][neighborCol])
            {
                int newG = gCost[currentRow][currentCol] +1;

                if(newG < gCost[neighborRow][neighborCol])
                {
                    gCost[neighborRow][neighborCol] = newG;
                    parentRow[neighborRow][neighborCol] = currentRow;
                    parentCol[neighborRow][neighborCol] = currentCol;

                    if (!openList[neighborRow][neighborCol])
                    {
                        openList[neighborRow][neighborCol] = true;
                        discoveryOrder[neighborRow][neighborCol] = discoveryCounter++;
                    }
                }
            }
        }
    }

    // Display the loaded map to verify the input before running A*.
    for (int i = 19; i >= 0; i--)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << grid[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}
