#ifndef REDUNDANT_FINDER_H
#define REDUNDANT_FINDER_H
#include "TestFinder.h"
#include <iostream>

// take in test cases and generate
// gcov stats to decide if some
// test should be removed
class RedundantFinder
{
public:
    RedundantFinder(vector<TestCase> & tests);

    bool hasRedundant();

    vector<TestCase> getRedundant();

private:
    double getGcovLineCoverage();
    void checkTests();
    void checkIsRedundant(TestCase &t, double baseline);
    vector<TestCase> tests;
};

#endif // REDUNDANT_FINDER_H
