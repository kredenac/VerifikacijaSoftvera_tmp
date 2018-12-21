#include "RedundantFinder.h"
#include <algorithm>
#include <iterator>

RedundantFinder::RedundantFinder(vector<TestCase> & tests) : tests(tests)
{
    checkTests();
}

void RedundantFinder::checkTests()
{
    double baselineCov = getGcovLineCoverage();
    for (unsigned i=0; i<tests.size(); i++){
        checkIsRedundant(tests[i], baselineCov);
    }
}

double RedundantFinder::getGcovLineCoverage()
{
    // build, run program, then get gcov line coverage
    // TODO call rale script
    system("myfile.sh"); // myfile.sh should be chmod +x
    return 0.;
}

void RedundantFinder::checkIsRedundant(TestCase &t, double baseline)
{
    t.Comment();
    double currCov = getGcovLineCoverage();
    if (currCov >= baseline){
        t.isRedundant = true;
    }
    t.unComment();
}

vector<TestCase> RedundantFinder::getRedundant()
{
    auto red = vector<TestCase>();

    for_each(tests.begin(), tests.end(), [&](TestCase &t) {
        if (t.isRedundant) red.push_back(t);
    });

    return red;
}
