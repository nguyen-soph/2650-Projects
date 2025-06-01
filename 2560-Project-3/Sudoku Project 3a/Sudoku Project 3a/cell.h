// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Project 3a
// cell.h : This file contains the declaration of the cell class and its member functions.

#ifndef CELL_H
#define CELL_H

#include <vector>
#include <iostream>
using namespace std;

class cell {
public:
    cell();
    cell(int val);

    int getCellValue();
    void setCellValue(int val);

    void clearCell();
    void addConflict(int a);
    vector<int> getConflicts();

    friend ostream& operator<<(ostream& ostr, const cell& c);

    bool givenInFile = false;

private:
    int cellValue;
    vector<int> cellConflicts;
    vector<int> cellPossibleNumbers;
};

#endif

