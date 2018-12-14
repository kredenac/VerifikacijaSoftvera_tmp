#include <iostream>
#include "nadezda_spadijer.h"
#include "nikola_rastko.h"

using namespace std;

int main()
{
    cout << "hello world" << endl;
    auto testCaseFinder = nadezda_spadijer();

    auto tests = testCaseFinder.getTestCases();

    auto redundantTestCaseChecker = nikola_rastko(tests);

    if (redundantTestCaseChecker.hasRedundant()){
        auto redundantTests = redundantTestCaseChecker.getRedundant();
        cout << "found redundant tests:" << redundantTests.size() << endl;
        for (auto test : redundantTests){
            cout << test.functionName << endl;
        }
    }
    else {
        cout << "no redundant tests" << endl;
    }

    cout << "bye" << endl;
    return 0;
}
