// EECE 2560 - Fundamentals of Engineering Algorithms
// Project: Word Search Solver
// dictionary.h
// 2560-Project-2
//
// Niki Manolis, Sophia Nguyen, Maria Clara Porto
// Description: Implements a dictionary class to read, sort, and search words for use in a word search solver.
// Created by Sophia Nguyen on 5/26/25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Dictionary {
public:
    Dictionary();

    // Reads all words from a given dictionary file stream
    void readFromFile(ifstream& fin);

    // Sorts the internal word list using selection sort
    void selectionSort();

    // Performs binary search on the sorted dictionary for a word
    string lookupWord(const string& word) const;

    // Overloaded output operator to print dictionary contents
    friend ostream& operator<<(ostream& ostr, const Dictionary& dict);

private:
    vector<string> wordList; // Internal storage for all words
};

// Constructor
Dictionary::Dictionary() {}

// Reads dictionary words from input file stream
void Dictionary::readFromFile(ifstream& fin) {
    string line;

    if (!fin) {
        cerr << "Error: Dictionary file not found." << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(fin, line)) {
        if (!line.empty()) {
            if (isupper(line[0]))
                line[0] = tolower(line[0]); // Lowercase first char
            wordList.push_back(line.substr(0, line.find_last_not_of(" \r\n") + 1)); // Trim trailing whitespace
        }
    }

    fin.close();
}

// Sorts the dictionary words using selection sort
void Dictionary::selectionSort() {
    for (size_t i = 0; i < wordList.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < wordList.size(); ++j) {
            if (wordList[j] < wordList[minIndex]) {
                minIndex = j;
            }
        }
        swap(wordList[i], wordList[minIndex]);
    }

    cout << "Selection sort completed." << endl;

    // Optional: write sorted list to file
    ofstream fout("sorted_dict.txt");
    for (const string& word : wordList) {
        fout << word << '\n';
    }
    fout.close();
}

// Binary search for word in sorted dictionary
string Dictionary::lookupWord(const string& word) const{
    int low = 0;
    int high = static_cast<int>(wordList.size()) - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        const string& midWord = wordList[mid];

        if (midWord == word) {
            return word;
        } else if (midWord > word) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ""; // Not found
}

// Overloaded output operator
ostream& operator<<(ostream& ostr, const Dictionary& dict) {
    for (const string& word : dict.wordList) {
        ostr << word << endl;
    }
    return ostr;
}

#endif
