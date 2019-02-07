#include "testcase.h"

void TestCase::Comment()
{
//    isRedundant = true;

    char comment_sh[50+fileName.length()];
    sprintf(comment_sh, "sed -i \"%d,%ds/.*/\\/\\/&/\" %s", beginLine, endLine, fileName.c_str());

    char comment_slot_sh[50+fileName.length()];
    sprintf(comment_slot_sh, "sed -i \"%d,%ds/.*/\\/\\/&/\" %s", slotLine, slotLine, fileName.c_str());
//    printf("%s\n", comment_sh);

    system(comment_sh);
}

void TestCase::unComment()
{
//    isRedundant = false;

    char uncomment_sh[50+fileName.length()];
    sprintf(uncomment_sh, "sed -i \"%d,%ds/^\\(\\s*\\/\\/\\)*//\" %s", beginLine, endLine, fileName.c_str());

    char uncomment_slot_sh[50+fileName.length()];
    sprintf(uncomment_slot_sh, "sed -i \"%d,%ds/^\\(\\s*\\/\\/\\)*//\" %s", slotLine, slotLine, fileName.c_str());

//    printf("%s\n", uncomment_sh);

    system(uncomment_sh);
}
