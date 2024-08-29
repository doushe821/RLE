#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "UnitTest.h"
#include "rle.h"
#include "dynamicMemorySupport.h"
// TODO: в отдельный файл



void freeDynamicMemory(dynamicMemoryTracker tracker);

int main()
{
    struct testData test1 =
    {
        "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq sssssssssssssssss 32",
        78,
        "\071q\001 \021s\001 \0013\0012"
    };

    printf("%s\n", test1.refLine);
    if(RunTest(test1))
        printf("\nAll good");
    else
        printf("\nGot an error");
}

void freeDynamicMemory(dynamicMemoryTracker tracker)
{
    free(tracker.ptr);
}

