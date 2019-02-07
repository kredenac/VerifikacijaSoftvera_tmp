#include "RedundantFinder.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <streambuf>

string GetStdoutFromCommand(string cmd)
{
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)){
            if (fgets(buffer, max_buffer, stream) != NULL) {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    return data;
}

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
    string command = "python build_n_run.py";
    string result = GetStdoutFromCommand(command);
    cout << result << endl; // just for debugging
    if (result.find("error") != string::npos){
        cout << "error while calling python script" << endl;
    }
    double cov = atof(result.c_str());

    return cov;
}

void RedundantFinder::checkIsRedundant(TestCase &t, double baseline)
{
    t.Comment();
    double currCov = getGcovLineCoverage();
    if (currCov == baseline){
        t.isRedundant = true;
    } else if (currCov > baseline){
        cout << "error, currcov > baseline" << endl;
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
