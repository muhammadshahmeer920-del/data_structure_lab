#include <iostream>
using namespace std;

int main() {
    const int SIZE = 3;

    int matrixA[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int matrixB[SIZE][SIZE] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int sumMatrix[SIZE][SIZE];

    
    cout << "Matrix A:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << matrixA[i][j] << " ";
        cout << "\n";
    }

    
    cout << "\nMatrix B:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << matrixB[i][j] << " ";
        cout << "\n";
    }

    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            sumMatrix[i][j] = matrixA[i][j] + matrixB[i][j];

    
    cout << "\nSum of Matrix A and B:\n\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << sumMatrix[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
