// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Project 3a
// MNS_PMN_3_3a.cpp This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "d_matrix.h"
#include "d_except.h"
#include "board.h"
using namespace std;

int main() {
    ifstream fin;
    string fileName;

    // Prompt until a valid file is opened
    while (true) {
        cout << "Enter the name of the Sudoku text file (ex. sudoku.txt): ";
        getline(cin, fileName);
        fin.open(fileName.c_str());

        if (fin) {
            cout << "File opened successfully.\n";
            break;
        } else {
            cerr << "Cannot open \"" << fileName << "\". Please try again.\n";
            fin.clear(); // Clear error state
        }
    }

    try {
        board b1(SquareSize);
        
        while (fin && fin.peek() != 'Z') {
            cout << "\n=== Board ===\n";

            // Read board and display
            b1.initialize(fin);
            b1.updateConflicts(); 
            b1.print();
            b1.printConflicts();

            // Track digits in rows, columns, and squares
            matrix<bool> rowUsed(BoardSize, BoardSize + 1, false);
            matrix<bool> colUsed(BoardSize, BoardSize + 1, false);
            matrix<bool> squareUsed(BoardSize, BoardSize + 1, false);
            
            // Scan and fill usage trackers
            for (int i = 0; i < BoardSize; i++) {
                for (int j = 0; j < BoardSize; j++) {
                    int val = b1.getCellValue(i, j);
                    if (val != Blank) {
                        int squareIndex = (i / SquareSize) * SquareSize + (j / SquareSize);
                        rowUsed[i][val] = true;
                        colUsed[j][val] = true;
                        squareUsed[squareIndex][val] = true;
                    }
                }
            }

            // Check if board is solved
            if (b1.isSolved())
                cout << "Board is solved!\n";
            else
                cout << "Board is not yet solved.\n";
        }
    }
    catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        return 1;
    }

    return 0;
}
