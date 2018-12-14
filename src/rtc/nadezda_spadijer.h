#ifndef NADEZDA_SPADIJER_H
#define NADEZDA_SPADIJER_H
#include <iostream>
#include <vector>

using namespace std;

// represents an instance of a test case by storing
// filename, function name, beginning line and ending line
// NOTE: make this however you see that it best fits
// the chosen testing framework.
// We will be using instances of this class
// to temporarily remove certain functions from compilation
class TestCase {

public:
    TestCase(string funName, string filName, unsigned beginL, unsigned endL)
        :functionName(funName), fileName(filName), beginLine(beginL), endLine(endL)
    {

    }

public:
    string functionName;
    string fileName;
    unsigned beginLine;
    unsigned endLine;

};


// TODO by Nadezda and Spadijer
class nadezda_spadijer
{
public:
    nadezda_spadijer();

    // returns all test cases
    vector<TestCase> getTestCases();
};

#endif // NADEZDA_SPADIJER_H
