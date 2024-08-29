#ifndef DYNAMIC_MEMORY__SUPPORT_INCLUDED
#define DYNAMIC_MEMORY__SUPPORT_INCLUDED

const size_t initialCallocMem = 128;
const int MemReallocCoefficient  = 2;

struct dynamicMemoryTracker 
{
    size_t initialAllocation;
    size_t allocated;
    size_t used;
    int reallocCoef;
    char* ptr;
};
#endif