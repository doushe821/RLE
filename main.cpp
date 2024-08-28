#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// TODO: в отдельный файл
enum errors
{
    NO_ACCESSIBLE_MEMORY = 1
};

struct encoderOutput
{
    char* line;
    int lineLength;
    enum errors errorFlag;
};

struct dynamicMemoryTracker 
{
    int allocated;
    int used;
    int reallocCoef
    };

struct testData
{
    const char* line;
    const char* refLine;
};

const int initialCallocMemory = 1024;

struct encoderOutput encode (const char* uncoded, int stringSize);
struct encoderOutput decode (char* coded);
int UnitTest(struct testData test);
int digits(int a);

int main()
{
    struct testData test1 =
    {
        "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq sssssssssssssssss 32",
        "\057q\001 \017s\001 \0013 \0012"
    };

    UnitTest(test1);
}

struct encoderOutput encode (const char* uncoded, int stringSize)
{

    encoderOutput output = {};
    char* codedLine = (char*) calloc(initialCallocMemory, sizeof(char)); // FIXME
    if(!codedLine)
    {
        output.errorFlag = NO_ACCESSIBLE_MEMORY;
        return output;
    }

    int n = 0;
    for(int k = 0; k < stringSize; k++)
    { 
        char rCount = 1;
        char curChar = 0;
        curChar = uncoded[k];
        while(uncoded[k] == uncoded [k+1]) 
        {
            rCount++;
            k++;
        }
        codedLine[n++] = rCount;
        codedLine[n++] = curChar;
        char* newptr = (char*) realloc(codedLine, 2*sizeof(char));
        if (newptr == NULL)
        {
            output.errorFlag = NO_ACCESSIBLE_MEMORY;
            return output;
        }
    }
    printf("codedLine: %s\n\n", codedLine);
    output.line = codedLine;
    return output;
}

int digits(int a)
{
    int tenPower = 10;
    if(a < tenPower)
        return 1;

    int c = 1;
    while(a >= tenPower)
    {
        c++;
        tenPower *= tenPower;
    }

    return c;  
}

int UnitTest(struct testData test)
{
    int ErrorsNum = 0;
    if(strcmp(encode(test.line, 78).line, test.refLine) != 0)
    {
        printf("errir");
        return 1;
    }
    else
        printf("all good");
    return ErrorsNum;
}