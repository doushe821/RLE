#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// TODO: в отдельный файл

const size_t initialCallocMem = 4;
const int MemReallocCoefficient  = 2;

enum error
{
    NO_ERRORS = 0,
    NO_ACCESSIBLE_MEMORY
};

struct encoderOutput
{
    char* line;
    int lineLength;
    enum error errorFlag;
};

struct dynamicMemoryTracker 
{
    size_t initialAllocation;
    size_t allocated;
    size_t used;
    int reallocCoef;
    char* ptr;
};

struct encoderTracker
{
    char repeatCounter;
    char currentChar;
    int outputLineIndex;
};

struct testData
{
    const char* line;
    const int lineLength;
    const char* refLine;
};

struct encoderOutput encode (const char* uncoded, int stringSize);
struct encoderOutput decode (char* coded);
bool UnitTest(struct testData test);
int digits(int a);
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
    if(UnitTest(test1))
        printf("\nAll good");
    else
        printf("\nGot an error");
}

struct encoderOutput encode (const char* uncoded, int stringSize)
{
    struct dynamicMemoryTracker encodeMemoryTracker = 
    {
        0,
        0,
        MemReallocCoefficient,
        initialCallocMem,
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
    printf("%s", encodeMemoryTracker.ptr);
    output.line = encodeMemoryTracker.ptr;
    output.lineLength = track.outputLineIndex;
    return output;
}

struct encoderOutput decode (const char* coded, int stringSize)
{
    struct dynamicMemoryTracker decodeMemoryTracker
    {
        0,
        0,
        MemReallocCoefficient,
        initialCallocMem,
        NULL
    };


}

bool UnitTest(struct testData test)
{
    if(strcmp(encode(test.line, test.lineLength).line, test.refLine) != 0)
        return false;
    else
        return true;
}

void freeDynamicMemory(dynamicMemoryTracker tracker)
{
    free(tracker.ptr);
}

