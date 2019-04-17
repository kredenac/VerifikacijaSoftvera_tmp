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
    RedundantFinder(vector<TestCase> & tests, string pathToProject, string executableName, string pathToSource);

    bool hasRedundant();

    vector<TestCase> getRedundant();

private:
    void getGcovLineCoverage(double &cov1, double &cov2, double &cov3);
    void checkTests();
    void checkIsRedundant(TestCase &t, double baseline1, double baseline2, double baseline3);
    vector<TestCase> tests;
    string pathToProject;
    string executableName;
    string pathToSource;
};

#endif // REDUNDANT_FINDER_H
