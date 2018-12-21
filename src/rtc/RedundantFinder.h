#ifndef REDUNDANT_FINDER_H
#define REDUNDANT_FINDER_H
#include "TestFinder.h"
#include <iostream>

// TODO by Nikola and Rastko
// take in test cases and generate
// gcov stats to decide if some
// test should be removed
class RedundantFinder
{
public:
    RedundantFinder(vector<TestCase> & tests);

    bool hasRedundant()
    {
        return false;
    }

    vector<TestCase> getRedundant(){
        return vector<TestCase>();
    }
private:
    double getGcovLineCoverage();
    void checkTests();
    bool checkIsRedundant(const TestCase &t);
    vector<bool> isRedundant;
    vector<TestCase> tests;
};

#endif // REDUNDANT_FINDER_H
