// EECE 2560 - Fundamentals of Engineering Algorithms
// Project: Word Search Solver
// MNS_PMN_2_2a.cpp
// 2560-Project-2
//
// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Description: Main file to compile. Reads in a grid and dictionary, performs word search, and prints
// all match in dictionary words found in the grid.
// Created by Sophia Nguyen on 5/26/25.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dictionary.h"
#include "grid.h"

using namespace std;

/*
 * findMatches:
 * Given a Dictionary and Grid, searches all possible starting positions, directions, and lengths
 * to find and print all dictionary words that appear in the grid.
 */
void findMatches(const Dictionary& dict, const Grid& grid) {
    vector<string> foundWords;
    string candidate, match;

    int maxLength = min(grid.numRows, grid.numCols);

    cout << "\nSelected Grid:\n";
    grid.printGrid();
    cout << endl;

    for (int row = 0; row < grid.numRows; ++row) {
        for (int col = 0; col < grid.numCols; ++col) {
            for (int direction = 0; direction < 8; ++direction) {
                for (int len = maxLength; len >= 5; --len) {
                    candidate = grid.getWord(row, col, direction, len);
                    match = dict.lookupWord(candidate);
                    if (!match.empty()) {
                        foundWords.push_back(match);
                    }
                }
            }
        }
    }

    // Output found words
    cout << "\nWords found in the grid:\n";
    for (size_t i = 0; i < foundWords.size(); ++i) {
        cout << foundWords[i];
        if (i < foundWords.size() - 1) cout << ", ";
    }
    cout << endl;

    // Save results to appropriate file
    string outputFilename;
    if (grid.numRows == 15 && grid.numCols == 15)
        outputFilename = "15x15s.txt";
    else if (grid.numRows == 30 && grid.numCols == 30)
        outputFilename = "30x30s.txt";
    else if (grid.numRows == 50 && grid.numCols == 50)
        outputFilename = "50x50s.txt";
    else
        outputFilename = "grid-results.txt";

    ofstream fout(outputFilename);
    for (size_t i = 0; i < foundWords.size(); ++i) {
        fout << foundWords[i];
        if (i < foundWords.size() - 1) fout << ", ";
    }
    fout << endl;
    fout.close();

    cout << "Results saved to: " << outputFilename << endl;
}

/*
 * search:
 * Prompts user to select a grid, loads Dictionary and Grid objects,
 * and calls findMatches() to find and output valid words.
 */
void search() {
    int gridChoice;
    string gridFilename;
    ifstream dictFile("Dictionary.txt");

    if (!dictFile) {
        cerr << "Dictionary.txt not found in: ";
        system("pwd");  // prints current directory
        cerr << "Contents:\n";
        system("ls -l"); // lists all files
        exit(EXIT_FAILURE);
    }

    if (!dictFile) {
        cerr << "Error: Could not open Dictionary.txt\n";
        exit(EXIT_FAILURE);
    }

    cout << "Choose a grid to search:\n";
    cout << " (1) input15.txt\n";
    cout << " (2) input30.txt\n";
    cout << " (3) input50.txt\n";
    cout << "Enter choice (1-3): ";
    cin >> gridChoice;

    switch (gridChoice) {
        case 1:
            gridFilename = "input15.txt";
            break;
        case 2:
            gridFilename = "input30.txt";
            break;
        case 3:
            gridFilename = "input50.txt";
            break;
        default:
            cerr << "Invalid choice. Exiting.\n";
            exit(EXIT_FAILURE);
    }

    // Load and sort dictionary
    Dictionary dict;
    dict.readFromFile(dictFile);
    dict.selectionSort();

    ofstream sortedOut("dictionary-sorted.txt");
    sortedOut << dict;
    sortedOut.close();

    // Load grid and find matches
    Grid grid(gridFilename);
    findMatches(dict, grid);
}

/*
 * main:
 * Program entry point. Starts search process.
 */
int main() {
    search();
    return 0;
}

