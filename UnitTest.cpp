#include <string.h>
#include "UnitTest.h"
#include "rle.h"
#include "dynamicMemorySupport.h"

bool RunTest(struct testData test)
{
    if(strcmp(encode(test.line, test.lineLength).line, test.refLine) != 0)
        return false;
    else
        return true;
}