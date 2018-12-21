#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>

using namespace std;

// represents an instance of a test case by storing
// filename, function name, beginning line and ending line
class TestCase {

public:
    TestCase(string funName, string filName, unsigned slotL, unsigned beginL, unsigned endL)
        : isCommented(false), functionName(funName), fileName(filName), slotLine(slotL), beginLine(beginL), endLine(endL)
    {

    }

    void Comment()
    {
        isCommented = true;
        // TODO call rale script
        system("myfile.sh"); // myfile.sh should be chmod +x
    }

    void unComment()
    {
        isCommented = false;
        // TODO call rale script
        system("myfile.sh"); // myfile.sh should be chmod +x
    }


public:
    bool isCommented;
    string functionName;
    string fileName;
    unsigned slotLine;
    unsigned beginLine;
    unsigned endLine;

};


#endif // TESTCASE_H
