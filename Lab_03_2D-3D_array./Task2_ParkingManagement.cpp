#include <iostream>
using namespace std;

int main() {
    const int ROWS = 4;
    const int COLS = 5;

    
    int parking[ROWS][COLS] = {
        {1, 0, 1, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1}
    };

    
    cout << "----- Parking Layout -----\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            cout << parking[i][j] << " ";
        cout << "\n";
    }

    
    int occupied = 0, empty = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;

    cout << "\nTotal occupied spaces: " << occupied << "\n";
    cout << "Total empty spaces: " << empty << "\n";

    
    int row, col;
    cout << "\nEnter row (0-" << ROWS - 1 << ") and column (0-" << COLS - 1 << "): ";
    cin >> row >> col;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (parking[row][col] == 1)
            cout << "Space (" << row << ", " << col << ") is OCCUPIED.\n";
        else
            cout << "Space (" << row << ", " << col << ") is AVAILABLE.\n";
    } else {
        cout << "Invalid row or column.\n";
    }

    
    cout << "\nTotal parking capacity: " << (ROWS * COLS) << "\n";
    cout << "Current occupancy: " << occupied << "\n";

    return 0;
}
