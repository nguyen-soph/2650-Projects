// EECE 2560 - Fundamentals of Engineering Algorithms
// Project: Word Search Solver
// grid.h
// 2560-Project-2
//
// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Description: Class for reading and accessing word search grids with wraparound behavior.
// Created by Sophia Nguyen on 5/26/25.
//


#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "d_matrix.h"
using namespace std;

class Grid {
public:
    // Constructor: reads grid from input file
    Grid(const string& filename);

    // Returns word starting at (row, col) moving in direction dir for length len
    string getWord(int startRow, int startCol, int direction, int length) const;

    // Print the grid (for testing)
    void printGrid() const;

    int numRows;  // Number of rows in the grid
    int numCols;  // Number of columns in the grid

private:
    matrix<string> letterGrid;  // Matrix to store letters
};

// Constructor: builds grid from file
Grid::Grid(const string& filename) {
    ifstream fin(filename.c_str());
    if (!fin) {
        cerr << "Error: Could not open grid file." << endl;
        exit(EXIT_FAILURE);
    }

    // Read first line: grid dimensions
    string rowStr, colStr;
    getline(fin, rowStr, ' ');
    getline(fin, colStr);
    numRows = stoi(rowStr);
    numCols = stoi(colStr);

    // Resize the matrix
    letterGrid.resize(numRows, numCols);

    // Fill the matrix with letters
    string letter;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols - 1; ++c) {
            getline(fin, letter, ' ');
            letterGrid[r][c] = letter;
        }
        getline(fin, letter);  // Read final letter in the row (no trailing space)
        letterGrid[r][numCols - 1] = letter;
    }

    fin.close();
}

// Get word from (startRow, startCol) in direction `direction` with length `length`
// Directions are encoded as follows:
//  7   0   1
//  6   X   2
//  5   4   3
string Grid::getWord(int startRow, int startCol, int direction, int length) const {
    string word;
    int currentRow, currentCol;

    for (int i = 0; i < length; ++i) {
        switch (direction) {
            case 0: // Up
                currentRow = (startRow - i + numRows) % numRows;
                currentCol = startCol;
                break;
            case 1: // Up-Right
                currentRow = (startRow - i + numRows) % numRows;
                currentCol = (startCol + i) % numCols;
                break;
            case 2: // Right
                currentRow = startRow;
                currentCol = (startCol + i) % numCols;
                break;
            case 3: // Down-Right
                currentRow = (startRow + i) % numRows;
                currentCol = (startCol + i) % numCols;
                break;
            case 4: // Down
                currentRow = (startRow + i) % numRows;
                currentCol = startCol;
                break;
            case 5: // Down-Left
                currentRow = (startRow + i) % numRows;
                currentCol = (startCol - i + numCols) % numCols;
                break;
            case 6: // Left
                currentRow = startRow;
                currentCol = (startCol - i + numCols) % numCols;
                break;
            case 7: // Up-Left
                currentRow = (startRow - i + numRows) % numRows;
                currentCol = (startCol - i + numCols) % numCols;
                break;
            default:
                return ""; // Invalid direction
        }
        word += letterGrid[currentRow][currentCol];
    }

    return word;
}

// Print the contents of the grid
void Grid::printGrid() const {
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            cout << letterGrid[r][c] << " ";
        }
        cout << endl;
    }
}

#endif

