#ifndef NADEZDA_SPADIJER_H
#define NADEZDA_SPADIJER_H

#define _XOPEN_SOURCE 700
#include <iostream>
#include <vector>
#include <ftw.h>

using namespace std;

// represents an instance of a test case by storing
// filename, function name, beginning line and ending line
// NOTE: make this however you see that it best fits
// the chosen testing framework.
// We will be using instances of this class
// to temporarily remove certain functions from compilation
class TestCase {

public:
    TestCase(string funName, string filName, unsigned slotL, unsigned beginL, unsigned endL)
        :functionName(funName), fileName(filName), slotLine(slotL), beginLine(beginL), endLine(endL)
    {

    }

public:
    string functionName;
    string fileName;
    unsigned slotLine;
    unsigned beginLine;
    unsigned endLine;

};


// TODO by Nadezda and Spadijer
class nadezda_spadijer
{
    static vector<TestCase> testovi;
    static int function(const char *fpath, const struct stat *sb, int typeFlag, struct FTW *ftwbuf);
public:
    nadezda_spadijer();

    // returns all test cases
    vector<TestCase> getTestCases() const;
};

#endif // NADEZDA_SPADIJER_H
