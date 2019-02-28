#ifndef TEST_FINDER_H
#define TEST_FINDER_H

#define _XOPEN_SOURCE 700
#include <iostream>
#include <vector>
#include <map>
#include <ftw.h>
#include "testcase.h"
#include "parser.hpp"

using namespace std;


// TODO by Nadezda and Spadijer
class TestFinder
{
public:
    TestFinder(string &path);

    // returns all test cases
    vector<TestCase> getTestCases() const;
private:
    string path;
    static vector<TestCase> testovi;
    static map<std::string, unsigned> testFunctionNames;
    static int nftwCallback(const char *fpath, const struct stat *sb, int typeFlag, struct FTW *ftwbuf);
    friend class yy::parser;
};

#endif // TEST_FINDER_H
