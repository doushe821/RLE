#include "rle.h"
#include <stdlib.h>
#include "dynamicMemorySupport.h"

struct encoderOutput encode (const char* uncoded, int stringSize)
{

    struct dynamicMemoryTracker eMemTracker =
    {
        initialCallocMem,
        0,
        0,
        MemReallocCoefficient,
        NULL
    };

    encoderOutput output = {};
    eMemTracker.ptr = (char*) calloc(eMemTracker.initialAllocation, sizeof(char)); 
    eMemTracker.allocated = eMemTracker.initialAllocation;
    if(!eMemTracker.ptr)
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
            {
                k++;
                break;
            }
            track.repeatCounter++;
            k++;
        }
        eMemTracker.ptr[track.outputLineIndex++] = track.repeatCounter;
        eMemTracker.ptr[track.outputLineIndex++] = track.currentChar;
        eMemTracker.used += 2;
        if(eMemTracker.used == eMemTracker.allocated)
        {
            char* newptrE = (char*) realloc(eMemTracker.ptr, eMemTracker.allocated*sizeof(char)*eMemTracker.reallocCoef);
            if (newptrE == NULL)
            {
                output.errorFlag = NO_ACCESSIBLE_MEMORY;
                return output;
            }
            eMemTracker.allocated *= eMemTracker.reallocCoef;
        }
    }
    output.line = eMemTracker.ptr;
    output.lineLength = track.outputLineIndex;
    return output;
}