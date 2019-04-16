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

int main(int argc, char **argv)
{
    string pathToProject;
    string executableName;
    if (argc!=3){
        std::cout << "Example of use:\n./program path_to_test_pro test_executable_name" << std::endl;
        pathToProject = "/home/nikola/Desktop/redundant-test-cases/src/what_we_test/Root/Haming/string_distance_test/string_distance_test.pro";
        executableName = "tst_string_distance_test";
    } else {
        pathToProject = argv[1];
        executableName = argv[2];
    }

    chdir("../");
    std::cout << "pwd=" << GetCurrentWorkingDir() << std::endl;
    string path = pathToProject.substr(0, pathToProject.find_last_of('/') );
    auto testCaseFinder = TestFinder(path);

    auto tests = testCaseFinder.getTestCases();
    cout << "test.size = " << tests.size() << endl;
    auto redundantTestCaseChecker = RedundantFinder(tests, pathToProject, executableName);

    if (redundantTestCaseChecker.hasRedundant()){
        auto redundantTests = redundantTestCaseChecker.getRedundant();
        cout << "found redundant tests:" << redundantTests.size() << endl;
        for (auto test : redundantTests){
            cout << test.functionName << endl;
        }
    } else {
        cout << "no redundant tests" << endl;
    }

    cout << "bye" << endl;
    return 0;
}
