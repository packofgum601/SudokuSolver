//header files
#include <iostream>

//Constants
#define SIZE 9

//print board function
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        // Print a horizontal divider every 3 rows (except the first row)
        if (i > 0 && i % 3 == 0) {
            std::cout << "------+-------+------" << std::endl;
        }
        for (int j = 0; j < SIZE; j++) {
            // Print a vertical divider every 3 columns (except the first column)
            if (j > 0 && j % 3 == 0) {
                std::cout << "| ";
            }
            // Print the cell value
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl; // Move to the next line after each row
    }
}

//isValid - checks if board is valid by checking if there is at least 17 given digits, since that is hwo many is needed for a unique solution
bool isValid(int board[SIZE][SIZE]) {
    int emptyCells = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyCells += 1;
            }
        }
    }

    if (emptyCells < 64) {
        return true;
    }
    else {
        return false;
    }

}

//isSafe - checks if number can be placed in cell
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    //check if number is already in row
    for (int n = 0; n < SIZE; n++) {
        if (board[row][n] == num) {
            return false;
        }
    }
    //check if number is already in column
    for (int m = 0; m < SIZE; m++) {
        if (board[m][col] == num) {
            return false;
        }
    }

    //check if number is already in 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

//sudokuSover - solves sudoku board with recursion
bool sudokuSolver(int board[SIZE][SIZE], int row, int col) {
    //check is board is valid
    if (isValid(board) == true) {
        //Base Case 1: if at the end of board, return true to avoid further backtracking
        if (row == SIZE - 1 && col == SIZE) {
            return true;
        }
        //Base Case 2: if at the end of a row, move to the next row
        if (col == SIZE) {
            row++;
            col = 0;
        }
        //Recursive Case 1:if current index already has a value, move to the next cell
        if (board[row][col] != 0) {
            return sudokuSolver(board, row, col + 1);
        }
        //Recursive Case 2: if current index does not have a value, fill it with a digit from 1-9
        for (int num = 1; num <= SIZE; num++) {
            //check if we can place num in the given index, then move to the next column
            if (isSafe(board, row, col, num) == true) {
                board[row][col] = num;
                //check the next column
                if (sudokuSolver(board, row, col + 1) == true) {
                    return true;
                }

                //backtrack: reset the cell
                board[row][col] = 0;
            }
        }


    }

    return false;
}

//main function -> creates the board and runs the solver, then outputs the solved board
int main()
{
    int board[SIZE][SIZE] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                   { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                   { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                   { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                   { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                   { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                   { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                   { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                   { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    if (sudokuSolver(board, 0, 0) == true) {
        std::cout << "Solved Board: \n";
        printBoard(board);
    }
    else {
        std::cout << "No Valid Solution Found";
    }
    return 0;
    
}


