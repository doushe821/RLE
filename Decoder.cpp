#include <stdlib.h>
#include "rle.h"
#include "dynamicMemorySupport.h"
#include <stdio.h>
#include <assert.h>

struct encoderOutput decode (const char* coded, int stringSize)
{
    struct dynamicMemoryTracker dMemTracker =
    {
        initialCallocMem,
        0,
        0,
        MemReallocCoefficient,
        NULL
    };

    struct encoderOutput output = {};
    dMemTracker.ptr = (char*) calloc(dMemTracker.initialAllocation, sizeof(char));
    dMemTracker.allocated = dMemTracker.initialAllocation;
    if(!dMemTracker.ptr)
    {
        output.errorFlag = NO_ACCESSIBLE_MEMORY;
        return output;
    }

    int length = 0;
    for(int k = 0; k < stringSize; k+=2)
    {
        for(int m = 0; m < coded[k]; m++)
        { 
            if(length >= (int) dMemTracker.allocated)
            {
                char* newptrD = (char*) realloc(dMemTracker.ptr, dMemTracker.allocated*sizeof(char)*dMemTracker.reallocCoef);
                if(newptrD == NULL)
                {
                    assert(0 && "no mem");   //TODO - replace (was a temporal solution)
                    output.errorFlag = NO_ACCESSIBLE_MEMORY;
                    return output;
                }
                dMemTracker.allocated *= dMemTracker.reallocCoef;
            }   
            dMemTracker.ptr[length++] = coded[k+1];
            dMemTracker.used += 1;
        }
        //fprintf(stderr, "Memory allocated: %zu\n", dMemTracker.allocated);
        //fprintf(stderr, "Memory used: %zu\n", dMemTracker.used);
    } 
    printf("%s\n", dMemTracker.ptr);
    output.line = dMemTracker.ptr;
    output.lineLength = length;
    return output;
}

