// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Project 3a
// cell.cpp : This file contains the implementation of the cell class and its member functions.

#include "cell.h"
#include <algorithm>

cell::cell() {}

cell::cell(int val) {
    cellValue = val;
}

int cell::getCellValue() {
    return cellValue;
}

void cell::setCellValue(int val) {
    cellValue = val;
}

void cell::clearCell() {
    cellValue = -1;
    givenInFile = false;
    cellPossibleNumbers.clear();
    cellConflicts.clear();
}

void cell::addConflict(int a) {
    if (a != -1 && find(cellConflicts.begin(), cellConflicts.end(), a) == cellConflicts.end()) {
        cellConflicts.push_back(a);
    }
}

vector<int> cell::getConflicts() {
    return cellConflicts;
}

ostream& operator<<(ostream& ostr, const cell& c) {
    ostr << c.cellValue;
    return ostr;
} 
