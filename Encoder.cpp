#include "rle.h"
#include <stdlib.h>
#include "dynamicMemorySupport.h"

struct encoderOutput encode (const char* uncoded, int stringSize)
{
    struct dynamicMemoryTracker encodeMemoryTracker =
    {
        initialCallocMem,
        0,
        0,
        MemReallocCoefficient,
        NULL
    };

    encoderOutput output = {};
    encodeMemoryTracker.ptr = (char*) calloc(encodeMemoryTracker.initialAllocation, sizeof(char)); 
    encodeMemoryTracker.allocated = encodeMemoryTracker.initialAllocation;
    if(!encodeMemoryTracker.ptr)
    {
        output.errorFlag = NO_ACCESSIBLE_MEMORY;
        return output;
    }

    struct encoderTracker track =
    {1, 0, 0};

    for(int k = 0; k < stringSize; k++)
    { 
        track.repeatCounter = 1;
        track.currentChar = uncoded[k];
        while(uncoded[k] == uncoded [k+1]) 
        {
            if(track.repeatCounter == CHAR_MAX)
                break;
            track.repeatCounter++;
            k++;
        }
        encodeMemoryTracker.ptr[track.outputLineIndex++] = track.repeatCounter;
        encodeMemoryTracker.ptr[track.outputLineIndex++] = track.currentChar;
        encodeMemoryTracker.used += 2;
        if(encodeMemoryTracker.used == encodeMemoryTracker.allocated)
        {
            char* newptr = (char*) realloc(encodeMemoryTracker.ptr, encodeMemoryTracker.allocated*sizeof(char)*encodeMemoryTracker.reallocCoef);
            if (newptr == NULL)
            {
                output.errorFlag = NO_ACCESSIBLE_MEMORY;
                return output;
            }
            encodeMemoryTracker.allocated *= encodeMemoryTracker.reallocCoef;
        }
    }
    output.line = encodeMemoryTracker.ptr;
    output.lineLength = track.outputLineIndex;
    return output;
}