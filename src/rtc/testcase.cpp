#include "testcase.h"

void TestCase::Comment()
{
    isRedundant = true;
    // TODO call rale script
    system("myfile.sh"); // myfile.sh should be chmod +x
}

void TestCase::unComment()
{
    isRedundant = false;
    // TODO call rale script
    system("myfile.sh"); // myfile.sh should be chmod +x
}
