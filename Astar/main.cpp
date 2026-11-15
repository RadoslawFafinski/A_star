
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

    ifstream file("grid.txt");

    if (!file.is_open())
    {
        // Pathfinding cannot start without the input map.
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
