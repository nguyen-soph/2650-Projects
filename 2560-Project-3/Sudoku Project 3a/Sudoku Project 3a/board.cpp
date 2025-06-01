// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Project 3a
// board.cpp : This file contains the implementation of the board class and its member functions.

#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "d_matrix.h"
#include "d_except.h"
#include "cell.h"

int numSolutions = 0;

ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int val : v)
        os << val << ' ';
    return os;
}

board::board(int sqSize) : value(BoardSize, BoardSize)
// Board constructor
{
   clear();
}

void board::clear()
// Mark all possible values as legal for each board entry.
{
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            value[i][j].clearCell();
        }
    }
    numSolutions = 0;
}

void board::initialize(ifstream &fin)
// Reads a Sudoku board from the input file.
{
   char ch;
   clear();
   
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++)
        {
            fin >> ch;

            // If the read char is not Blank
            if (ch != '.') {
                setCell(i, j, ch - '0');   // Convert char to int
                value[i][j].givenInFile = true;
            }
        }
    }
}

bool board::isBlank(int i, int j)
// Returns true if cell is blank from the row and column of the cell.
{
    if (i < 0 || i >= BoardSize || j < 0 || j >= BoardSize) {
        throw rangeError("bad value in isBlank");
    }
    return value[i][j].getCellValue() == Blank;
}

int board::getCellValue(int i, int j)
// Returns current cell value from the row and column of the cell.
{
    if (i >= 0 && i < BoardSize && j >= 0 && j < BoardSize) {
        return value[i][j].getCellValue();
    }
    else {
        throw rangeError("bad value in getCellValue");
    }
}

void board::setCell(int i, int j, int val)
// Assigns val to cell.
{
    value[i][j].setCellValue(val);
}

void board::clearCell(int i, int j)
// Resets cell value to empty, and updates conflicts.
{
    value[i][j].clearCell();
    updateConflicts();
}

bool board::isSolved()
// Returns true if board is solved.
{
    updateConflicts();
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            if (isBlank(i, j)) {
                return false;
            }
        }
    }
    numSolutions++;
    return true;
}

void board::setConflicts(int row, int col)
// Updates conflicts based on the row and column of the cell.
{
    if (!isBlank(row, col))
        return;

    // Clear the current conflict list only (do NOT reset cell!)
    value[row][col].getConflicts().clear();

    // Check row
    for (int j = 0; j < BoardSize; j++) {
        if (j != col && !isBlank(row, j)) {
            value[row][col].addConflict(getCellValue(row, j));
        }
    }

    // Check column
    for (int i = 0; i < BoardSize; i++) {
        if (i != row && !isBlank(i, col)) {
            value[row][col].addConflict(getCellValue(i, col));
        }
    }

    // Check 3x3 square
    int startRow = getSquareMin(row);
    int startCol = getSquareMin(col);
    for (int i = startRow; i < startRow + SquareSize; i++) {
        for (int j = startCol; j < startCol + SquareSize; j++) {
            if ((i != row || j != col) && !isBlank(i, j)) {
                value[row][col].addConflict(getCellValue(i, j));
            }
        }
    }
}


void board::updateConflicts()
// Updates conflicts for all cells on the board.
{
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            setConflicts(i, j);
}

void board::printConflicts()
// Prints all conflicts for all cells on the board.
{
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            cout << "Cell [" << (i + 1) << "," << (j + 1) << "]    conflicts:  ";
            if (isBlank(i, j)) {
                cout << value[i][j].getConflicts() << endl;
            }
            else {
                cout << "Known value." << endl;
            }
        }
    }
}

int board::getSquareMin(int x)
// Returns the starting index that contains a given cell index x within a 3x3 square.
{
    if (x < 3) {
        return 0;
    }
    else if (x < 6) {
        return 3;
    }
    else {
        return 6;
    }
}

void board::print()
// Prints board.
{
    cout << *this;
}

ostream& operator<<(ostream& ostr, board& b)
// << operator function for easy printing of the board.
{
    for (int i = 0; i < BoardSize; i++) {
        // Print horizontal border between boxes
        if (i % SquareSize == 0) {
            ostr << " -";
            for (int j = 0; j < BoardSize; j++) {
                ostr << "---";
            }
            ostr << "-\n";
        }

        for (int j = 0; j < BoardSize; j++) {
            // Print vertical box borders
            if (j % SquareSize == 0) {
                ostr << "|";
            }

            if (!b.isBlank(i, j)) {
                ostr << " " << b.getCellValue(i, j) << " ";
            }
            else {
                ostr << " · ";
            }
        }

        ostr << "|\n";
    }

    // Final bottom border
    ostr << " -";
    for (int j = 0; j < BoardSize; j++)
        ostr << "---";
    ostr << "-\n";

    return ostr;
}

