#include <iostream>
#include "TestFinder.h"
#include "RedundantFinder.h"

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  string current_working_dir(buff);
  return current_working_dir;
}

int main()
{
    chdir("../");
    std::cout << "pwd=" << GetCurrentWorkingDir() << std::endl;
    string path = "what_we_test/Root/string_distance_test";
    auto testCaseFinder = TestFinder(path);

    auto tests = testCaseFinder.getTestCases();
    cout << "test.size = " << tests.size() << endl;
    auto redundantTestCaseChecker = RedundantFinder(tests);

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
