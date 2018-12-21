#include "RedundantFinder.h"
#include <algorithm>
#include <iterator>

RedundantFinder::RedundantFinder(vector<TestCase> & tests) : tests(tests)
{
    isRedundant.resize(tests.size());
    fill(isRedundant.begin(), isRedundant.end(), false);
    checkTests();
}

void RedundantFinder::checkTests()
{
    double baseLine = getGcovLineCoverage();
    for (unsigned i=0; i<tests.size(); i++){

    }
}

double RedundantFinder::getGcovLineCoverage()
{

    return 0.;
}

bool RedundantFinder::checkIsRedundant(const TestCase &t)
{

}
