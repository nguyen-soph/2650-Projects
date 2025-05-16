// Niki Manolis
// Project 1a
// code.cpp : This file contains the implementation of the code class
// and its member functions.


#include "code.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


// Constructor for the Code object. 
// Has 2 parameters n and m, for the length and range of a code, respectively.
// The code vector is resized to length n
Code::Code(int n, int m) 
{
	length = n;
	range = m;
	code.resize(n);
}

// Constructor that initializes the code directly from a given vector
// Parameter vectorGuess is a const reference to a integer vector containing the guessed code.
Code::Code(const vector<int>& vectorGuess)
{
	length = vectorGuess.size();
	range = 10;						// sets fixed value of 10, just for part a's assumptions
	code = vectorGuess;
}

// Generates the random secret code for a new game by assigning a random value to each digit.
// Takes in no arguments and does not return anything.
void Code::generateRandom()
{
	for (int i = 0; i < length; i++)
	{
		code[i] = rand() % range;	// sets random digits to be within range
	}
}

// Counts how many digits in guess match the secret code in the exact position. 
// Takes in the users guess as a parameter.
// Returns an integer value representing the number of digits in the correct postition.
int Code::checkCorrect(const Code& guess) const
{
	int correctDigits = 0;

	for (int i = 0; i < length; i++) 
	{
		if (code[i] == guess.code[i])	// if the digit in corresponding locations match, its counted
		{
			correctDigits++;			// adds 1 to the count
		}
	}
	return correctDigits;
}


// Counts digits in guess that match digits in code but are in the wrong position.
// Takes in the users guess as a parameter.
// Returns an integer value representing the number of correct digits in the wrong location.
int Code::checkIncorrect(const Code& guess) const
{
	int incorrectDigits = 0;

	vector <int> unmatchedCode;
	vector <int> unmatchedGuess;

	// Group the unmatched digits from both the secret code and the guess
	for (int i = 0; i < length; i++) 
	{
		if (code[i] != guess.code[i]) 
		{
			unmatchedCode.push_back(code[i]);
			unmatchedGuess.push_back(guess.code[i]);
		}
	}

	// In the unmatched guesses, check if it matches an unmatched code digit
	for (int i = 0; i < unmatchedGuess.size(); i++) 
	{
		for (int j = 0; j < unmatchedCode.size(); j++) 
		{
			if (unmatchedGuess[i] == unmatchedCode[j]) 
			{
				incorrectDigits++;
				unmatchedCode.erase(unmatchedCode.begin() + j);		// Remove matched digit to avoid recounting
				break;	
			}
		}
	}
	return incorrectDigits;
}


// Prints the code digits on a single line followed by a newline.
// No parameters, returns void.
void Code::printCode()  const
{
	for (int i = 0; i < length; i++) 
	{
		cout << code[i];
	}
	cout << endl;
}