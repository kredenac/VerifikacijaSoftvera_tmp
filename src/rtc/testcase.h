#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>

using namespace std;

// represents an instance of a test case by storing
// filename, function name, beginning line and ending line
class TestCase {

public:
    TestCase(string funName, string filName, unsigned slotL, unsigned beginL, unsigned endL)
        : isRedundant(false), functionName(funName), fileName(filName), slotLine(slotL), beginLine(beginL), endLine(endL)
    {

    }

    void Comment();
    void unComment();
    bool isRedundant;
    string functionName;
    string fileName;
    unsigned slotLine;
    unsigned beginLine;
    unsigned endLine;

};


#endif // TESTCASE_H
