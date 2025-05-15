//
//  code.cpp
//  2560-Project-1
//
//  Created by Sophia Nguyen on 5/15/25.
//

// code.cpp
#include "code.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Constructor: initializes length and range, and generates a random code
Code::Code(int length, int range)
    : _length(length), _range(range) {
    srand(static_cast<unsigned>(time(0)));
    InitializeRandom();
}

// Manually set the code with input vector, with length validation
void Code::SetCode(const vector<int>& input) {
    if (input.size() != _length) {
        cerr << "Error: Code must be of length " << _length << endl;
        return;
    }
    _code = input;
}

// Generate a random code of _length digits in range [0, _range - 1]
void Code::InitializeRandom() {
    _code.clear();
    for (int i = 0; i < _length; ++i) {
        _code.push_back(rand() % _range);
    }
}

// Return a copy of the internal code
vector<int> Code::GetCode() const {
    return _code;
}

// Count digits that are correct and in the correct position
int Code::CheckCorrect(const Code& guess) const {
    int correct = 0;
    for (int i = 0; i < _length; ++i) {
        if (_code[i] == guess._code[i]) {
            ++correct;
        }
    }
    return correct;
}

// Count digits that are correct but in the wrong position
int Code::CheckIncorrect(const Code& guess) const {
    vector<bool> codeUsed(_length, false);
    vector<bool> guessUsed(_length, false);
    int incorrect = 0;

    // Mark digits that are correct and in the correct position
    for (int i = 0; i < _length; ++i) {
        if (_code[i] == guess._code[i]) {
            codeUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    // Count correct digits in wrong positions
    for (int i = 0; i < _length; ++i) {
        if (guessUsed[i]) continue;
        for (int j = 0; j < _length; ++j) {
            if (!codeUsed[j] && guess._code[i] == _code[j]) {
                ++incorrect;
                codeUsed[j] = true;
                break;
            }
        }
    }

    return incorrect;
}

// Validate that code digits are in the correct range and length
bool Code::CheckValidInput() const {
    if (_code.size() != _length) return false;
    for (int digit : _code) {
        if (digit < 0 || digit >= _range) return false;
    }
    return true;
}

// Overload >> operator for inputting a code from user
istream& operator>>(istream& in, Code& c) {
    c._code.clear();
    int digit;
    for (int i = 0; i < c._length; ++i) {
        in >> digit;
        if (digit < 0 || digit >= c._range) {
            cerr << "Digit out of range. Please enter values between 0 and " << (c._range - 1) << ".\n";
            c._code.clear();
            break;
        }
        c._code.push_back(digit);
    }
    return in;
}

// Overload << operator for printing a code
ostream& operator<<(ostream& out, const Code& c) {
    for (int digit : c._code) {
        out << digit << " ";
    }
    return out;
}

// Overload == operator for comparing two codes
bool operator==(const Code& c1, const Code& c2) {
    return c1._code == c2._code;
}

// Overload = operator for copying a Code object
Code& Code::operator=(const Code& other) {
    if (this != &other) {
        _length = other._length;
        _range = other._range;
        _code = other._code;
    }
    return *this;
}

