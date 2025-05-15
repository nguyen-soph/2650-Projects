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
#include <filesystem>  // C++17 for full path resolution
#include "dictionary.h"
#include "grid.h"

namespace fs = std::filesystem;
using namespace std;

/*
 * findMatches:
 * Given a Dictionary and Grid, searches all possible starting positions, directions, and lengths
 * to find and print all dictionary words that appear in the grid.
 */
void findMatches(const Dictionary& dict, const Grid& grid) {
    vector<string> foundWords;
    string candidate;

    int maxLength = min(grid.numRows, grid.numCols);

    cout << "\n[INFO] Selected Grid:\n";
    grid.printGrid();
    cout << endl;

    cout << "[INFO] Beginning search..." << endl;

    for (int row = 0; row < grid.numRows; ++row) {
        for (int col = 0; col < grid.numCols; ++col) {
            for (int direction = 0; direction < 8; ++direction) {
                for (int len = maxLength; len >= 5; --len) {
                    candidate = grid.getWord(row, col, direction, len);
                    if (!dict.lookupWord(candidate).empty()) {
                        foundWords.push_back(candidate);
                    }
                }
            }
        }
    }

    cout << "[INFO] Search complete. " << foundWords.size() << " words found." << endl;

    // Determine output filename based on grid size
    string outputFilename;
    if (grid.numRows == 15 && grid.numCols == 15)
        outputFilename = "15x15s.txt";
    else if (grid.numRows == 30 && grid.numCols == 30)
        outputFilename = "30x30s.txt";
    else if (grid.numRows == 50 && grid.numCols == 50)
        outputFilename = "50x50s.txt";
    else
        outputFilename = "grid-results.txt";

    // Write results to file
    ofstream fout(outputFilename);
    for (size_t i = 0; i < foundWords.size(); ++i) {
        fout << foundWords[i];
        if (i < foundWords.size() - 1) fout << ", ";
    }
    fout << endl;
    fout.close();

    // Output full path of saved file
    fs::path resultPath = fs::current_path() / outputFilename;
    cout << "[INFO] Results saved to: " << resultPath << endl;
}

/*
 * search:
 * Prompts user to select a grid, loads Dictionary and Grid objects,
 * and calls findMatches() to find and output valid words.
 */
void search() {
    int gridChoice;
    string gridFilename;

    // Try opening dictionary file
    ifstream dictFile("Dictionary.txt");
    if (!dictFile) {
        cerr << "[ERROR] Dictionary.txt not found in: ";
        system("pwd");
        cerr << "[ERROR] Directory contents:\n";
        system("ls -l");
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
            cerr << "[ERROR] Invalid grid choice. Exiting.\n";
            exit(EXIT_FAILURE);
    }

    cout << "[INFO] Loading and sorting dictionary..." << endl;

    // Load and sort dictionary
    Dictionary dict;
    dict.readFromFile(dictFile);
    dict.selectionSort();

    // Optionally save sorted dictionary
    ofstream sortedOut("dictionary-sorted.txt");
    sortedOut << dict;
    sortedOut.close();

    cout << "[INFO] Dictionary sorted and saved to dictionary-sorted.txt" << endl;
    cout << "[INFO] Loading grid and starting match search..." << endl;

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

