#include "TestFinder.h"
#include <fstream>
#include "lexer.h"
#include "parser.hpp"

//const unsigned MAX_LINE = 512U;

vector<TestCase> TestFinder::testovi;
map<string, unsigned> TestFinder::testFunctionNames;

TestFinder::TestFinder(string &path) : path(path)
{

}

int TestFinder::nftwCallback(const char *fpath, const struct stat *, int tflag, struct FTW *)
{
    if (tflag != FTW_F)
        return 0;
    string path = fpath;
    auto tacka = path.find_last_of('.');
    if (tacka == string::npos)
        return 0;
    if (path.substr(tacka) != ".cpp") // && path.substr(tacka) != ".h"
        return 0;
    //std::cout << path << std::endl;
    ifstream f(path);
    if (!f.is_open())
        return -1;
    testFunctionNames.clear();
    /* PRIMITIVNI PARSER; ZAMENJEN JE PARSEROM DOBIJENIM LEX-OM I YACC-OM
    char line[MAX_LINE];
    unsigned lineNum = 0U;
    bool x = false;
    while (!f.eof())
    {
        f.getline(line, MAX_LINE);
        string LINE = line;
        ++lineNum;
        if (LINE.find("#include <QtTest>") != string::npos)
            x = true;
        if (LINE.find("private Q_SLOTS:") != string::npos && x)
        {
            //FIXME bug here, does not handle newlines
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
                testFunctionNames.insert(make_pair(functionName, lineNum));
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
    }*/
    yy::Lexer lexer;
    lexer.switch_streams(f, std::cout);
    yy::parser parser(lexer, path);
    return parser.parse();
}

vector<TestCase> TestFinder::getTestCases() const
{
    testovi.clear();
    nftw(path.c_str(), nftwCallback, 3, 0);
    return testovi;
}
