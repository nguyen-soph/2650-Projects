// Niki Manolis
// Project 1a
// MNS_PMN_2_1a.cpp : This file contains the 'main' function to run the mastermind game, create a secret code, and test guesses.


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "code.h"

using namespace std;


int main()
{
    // Create example guesses as given
    vector<int> guessCode_1 = { 5,0,3,2,6 };
    vector<int> guessCode_2 = { 2,1,2,2,2 };
    vector<int> guessCode_3 = { 1,3,3,4,5 };

    // Initialize these guesses as Code objects
    Code g1(guessCode_1);
    Code g2(guessCode_2);
    Code g3(guessCode_3);

    // Seeds the random number generator with the current time, converts to the correct type
    srand(static_cast<unsigned int>(time(nullptr)));

    // Sets the fixed n and m values as directed for part a
    Code secretCode(5, 10);

    secretCode.generateRandom();

    cout << "Secret Code: ";
    secretCode.printCode();
    
    // Print the results for guess 1
    cout << "\nGuess 1: ";
    g1.printCode();
    cout << "Correct digits in correct place: " << secretCode.checkCorrect(g1);
    cout << "\nCorrect digits in incorrect place: " << secretCode.checkIncorrect(g1);

    // Print the results for guess 2
    cout << "\nGuess 2: ";
    g2.printCode();
    cout << "Correct digits in correct place: " << secretCode.checkCorrect(g2);
    cout << "\nCorrect digits in incorrect place: " << secretCode.checkIncorrect(g2);

    // Print the results for guess 3
    cout << "\nGuess 3: ";
    g3.printCode();
    cout << "Correct digits in correct place: " << secretCode.checkCorrect(g3);
    cout << "\nCorrect digits in incorrect place: " << secretCode.checkIncorrect(g3);

    return 0;
    cout << "Press Enter to exit";
    cin.ignore();
    cin.get();
}

