// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Project 3a
// board.h : This file contains the declaration of the board class and its member functions.

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "d_matrix.h"
#include "d_except.h"
#include "cell.h"

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

extern int numSolutions;

class board
// Stores the entire Sudoku board
{
public:
    board(int);
    void clear();
    void initialize(ifstream &fin);
    void print();
    
    bool isBlank(int i, int j);
    int getCellValue(int i, int j);
    void setCell(int a, int b, int val);
    void clearCell(int a, int b);
    
    bool isSolved();
    void setConflicts(int row, int col);
    void updateConflicts();
    void printConflicts();
    
    friend ostream& operator<<(ostream& ostr, board& b);
    friend ostream &operator<<(ostream &ostr, vector<int> &v);
    int getSquareMin(int x);
      
private:
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    matrix<cell> value;
};

#endif
