// Niki Manolis
// Project 1a
// code.h : This file contains the declaration of the code class to model
// a secret code for the mastermind game.


#ifndef CODE_H
#define CODE_H
#include <vector>

using namespace std;

class Code
{
public:

	// Constructor: initializes the code length and digit range.
	// Parameter n is the length of the code, and m is the range of each digit (0 to m-1)
	// Values n and m are assumed to be negative

	Code(int n = 0, int m = 0);

	// Constructor2: initializes the code directly from a given vector.
	// Parameter vectorGuess is a const reference to a integer vector containing the guessed code.
	
	Code(const vector<int>& vectorGuess);

	// Generates a new random code based on length and range.
	// No parameters, returns nothing.
	
	void generateRandom();

	// Returns the number of digits that are matches and in the correct position when compared with the guess.
	// Parameter guess is a const reference to another Code object to compare against.
	
	int checkCorrect(const Code& guess) const;

	// Returns the number of digits that match another digit in the guess, but is in the wrong position.
	// Parameter guess is a const reference to another Code object to compare against.
	
	int checkIncorrect(const Code& guess) const;

	// Prints the digits within a code object.
	
	void printCode() const;

private:

	int length;			// number of digits in the code
	int	range;			// range of digit values
	vector<int> code;	// vector to store code digits
};

#endif