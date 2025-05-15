//
//  code.h
//  2560-Project-1
//
//  Created by Sophia Nguyen on 5/15/25.
//
//
// Code Class prototypes

#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <vector>
using namespace std;

class Code {
public:
    // Constructor
    Code(int length, int range);

    // Set code manually
    void SetCode(const vector<int>& input);

    // Generate random secret code
    void InitializeRandom();

    // Get the stored code
    vector<int> GetCode() const;

    // Count correct digits in the correct place
    int CheckCorrect(const Code& guess) const;

    // Count correct digits in the wrong place
    int CheckIncorrect(const Code& guess) const;

    // Validate input values
    bool CheckValidInput() const;

    // Overloaded operators
    friend istream& operator>>(istream& in, Code& c);
    friend ostream& operator<<(ostream& out, const Code& c);
    friend bool operator==(const Code& c1, const Code& c2);
    Code& operator=(const Code& other);

private:
    vector<int> _code;
    int _length; // Code length, set by user
    int _range;  // Digit range [0, m-1], set by user
};

#endif // CODE_H

