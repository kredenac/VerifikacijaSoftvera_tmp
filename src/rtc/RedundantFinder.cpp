#include "RedundantFinder.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

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

RedundantFinder::RedundantFinder(vector<TestCase> & tests, string pathToProject, string executableName, string pathToSource) : tests(tests),
    pathToProject(pathToProject), executableName(executableName), pathToSource(pathToSource)
{
    checkTests();
}

void RedundantFinder::checkTests()
{
    double baselineCov1,  baselineCov2, baselineCov3;
    getGcovLineCoverage(baselineCov1,  baselineCov2, baselineCov3);
    cout << "baseline coverage: " << baselineCov1 << " " <<  baselineCov2 << " " << baselineCov3 << endl;
    for (unsigned i=0; i<tests.size(); i++){
        checkIsRedundant(tests[i], baselineCov1,  baselineCov2, baselineCov3);
    }
}

bool RedundantFinder::hasRedundant()
{
    return any_of(tests.cbegin(), tests.cend(), [](const TestCase &test){return test.isRedundant;});
}

void RedundantFinder::getGcovLineCoverage(double &cov1, double &cov2, double &cov3)
{
    // build, run program, then get gcov line coverage
    string command = "python build_n_run.py " + pathToProject + " " + executableName + " " + pathToSource;
    string result = GetStdoutFromCommand(command);
    //cout << "python said:" + result << endl;
    if (result.find("error") != string::npos){
        cout << "error while calling python script" << endl;
        cout << "Error:" + result << endl;
    }
    std::stringstream ss(result);
    ss >> cov1 >> cov2 >> cov3;
}

void RedundantFinder::checkIsRedundant(TestCase &t, double baseline1, double baseline2, double baseline3)
{
    t.Comment();
    double currCov1, currCov2, currCov3;
    getGcovLineCoverage(currCov1, currCov2, currCov3);
    double baselineSum = baseline1 + baseline2 + baseline3;
    double currSum = currCov1 + currCov2 + currCov3;

    if (currSum == baselineSum){
        t.isRedundant = true;
        cout << t.functionName << " is redundant, coverage without it: "
             << currCov1 << ", " << currCov2 << ", " << currCov3  << endl;
    } else if (currSum > baselineSum){
        cout << "error, currcov > baseline" << endl;
    } else {
        cout << t.functionName << " is not redundant." << currCov1 <<
                ", " << currCov2 << ", " << currCov3  << endl;
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
