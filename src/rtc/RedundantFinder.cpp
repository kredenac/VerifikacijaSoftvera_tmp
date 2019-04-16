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

RedundantFinder::RedundantFinder(vector<TestCase> & tests, string pathToProject, string executableName) : tests(tests),
    pathToProject(pathToProject), executableName(executableName)
{
    checkTests();
}

void RedundantFinder::checkTests()
{
    double baselineCov = getGcovLineCoverage();
    cout << "baseline coverage: " << baselineCov << endl;
    for (unsigned i=0; i<tests.size(); i++){
        checkIsRedundant(tests[i], baselineCov);
    }
}

bool RedundantFinder::hasRedundant()
{
    return any_of(tests.cbegin(), tests.cend(), [](const TestCase &test){return test.isRedundant;});
}

double RedundantFinder::getGcovLineCoverage()
{
    // build, run program, then get gcov line coverage
    string command = "python build_n_run.py " + pathToProject + " " + executableName;
    string result = GetStdoutFromCommand(command);

    if (result.find("error") != string::npos){
        cout << "error while calling python script" << endl;
        cout << "Error:" + result << endl;
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
        cout << t.functionName << " is redundant, coverage without it: "
             << currCov << endl;
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
