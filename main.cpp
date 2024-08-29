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
    UnitTest();
}

void freeDynamicMemory(dynamicMemoryTracker tracker)
{
    free(tracker.ptr);
}

