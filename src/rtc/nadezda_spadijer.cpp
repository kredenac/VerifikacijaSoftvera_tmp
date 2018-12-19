#include "nadezda_spadijer.h"
#include <fstream>
#include <utility>

const unsigned MAX_LINE = 512U;

vector<TestCase> nadezda_spadijer::testovi;

nadezda_spadijer::nadezda_spadijer()
{

}

int nadezda_spadijer::function(const char *fpath, const struct stat *, int, struct FTW *)
{
    string path = fpath;
    if (path.find(".h") == string::npos && path.find(".cpp") == string::npos)
        return 0;
    ifstream f(fpath);
    if (!f.is_open())
        return -1;
    vector< pair<string, unsigned> > testFunctionNames;
    char line[MAX_LINE];
    unsigned lineNum = 0U;
    while (!f.eof())
    {
        f.getline(line, MAX_LINE);
        string LINE = line;
        ++lineNum;
        if (LINE.find("private slots:") != string::npos)
        {
            while (!f.eof())
            {
                f.getline(line, MAX_LINE);
                LINE = line;
                ++lineNum;
                if (LINE.find("};") != string::npos)
                    break;
                auto space = LINE.find("void ") + 5;
                auto zagrada = LINE.find("(");
                string functionName = LINE.substr(space, zagrada - space);
                testFunctionNames.push_back(make_pair(functionName, lineNum));
            }
        }
        if (!testFunctionNames.empty())
        {
            for (auto i = testFunctionNames.cbegin(); i != testFunctionNames.cend(); ++i)
            {
                if (LINE.find(i->first.c_str()) != string::npos)
                {
                    unsigned beginL = lineNum;
                    unsigned endL;
                    unsigned zagrada = 0U;
                    do
                    {
                        if (LINE.find("{") != string::npos)
                            ++zagrada;
                        if (LINE.find("}") != string::npos)
                        {
                            --zagrada;
                            if (zagrada == 0U)
                                break;
                        }
                        f.getline(line, MAX_LINE);
                        LINE = line;
                        ++lineNum;
                    }
                    while (!f.eof());
                    endL = lineNum;
                    TestCase testCase(i->first, path, i->second, beginL, endL);
                    testovi.push_back(testCase);
                    break;
                }
            }
        }
    }
    return 0;
}

vector<TestCase> nadezda_spadijer::getTestCases() const
{
    testovi.clear();
    nftw(".", function, 3, 0);
    //TODO: srediti da preskace direktorijume kao fajlove
    return testovi;
}
