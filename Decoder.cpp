#include <stdlib.h>
#include <rle.h>

struct encoderOutput decode (const char* coded, int stringSize)
{
    struct dynamicMemoryTracker decodeMemoryTracker =
    {
        initialCallocMem,
        0,
        0,
        MemReallocCoefficient,
        NULL
    };

    int length = 0;
    decodeMemoryTracker.ptr = (char*) calloc(decodeMemoryTracker.initialAllocation, sizeof(char));
    for(int k = 0; k < stringSize/2; k+=2)
    {
        for(int m = 0; m <= coded[k]; m++)
        {
            
            while(coded[k] >= CHAR_MAX)
            {
                decodeMemoryTracker.ptr[length++] = coded[k+1];
                decodeMemoryTracker.used += 1;
                if(length >= decodeMemoryTracker.allocated)
                {
                    char* newptr = (char*) realloc(decodeMemoryTracker.ptr, decodeMemoryTracker.allocated*sizeof(char)*decodeMemoryTracker.reallocCoef);
                    decodeMemoryTracker.allocated *= decodeMemoryTracker.reallocCoef;
                }
            }
        }
    }

    struct encoderOutput output = {};
    output.line = decodeMemoryTracker.ptr;
    output.lineLength = length;
    return output;
}