#include "RedundantFinder.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <streambuf>


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
    std::ifstream t("../comm.txt");
    // read file into one string
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    t.close();
    if (str.find("error") != string::npos){
        cout << "error while calling python script" << endl;
    }
    double cov = atof(str.c_str());

    return cov;
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
