#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "UnitTest.h"
#include "rle.h"
#include "dynamicMemorySupport.h"

static struct uTResult doTests(const struct testData* testsToDo);
static bool RunTest(struct testData test, enum testModes mode);

void UnitTest()
{
    struct uTResult resOut = doTests(tests);
    if(resOut.errorCount > 0)
    {
        printf("Total errors: %d\n\n", resOut.errorCount);
        if(resOut.ERes.errorCEncode > 0)
        {
            printf("Encoding errors: %d\n", resOut.ERes.errorCEncode);
            printf("Tests: ");
            for(int i = 0; i < resOut.ERes.errorCEncode; i++)
                printf("%d, ", resOut.ERes.testNumbersEn[i]+1);
            printf("\n\n");
        }

        if(resOut.DRes.errorCDecode > 0)
        {
            printf("Decoding errors: %d\n", resOut.DRes.errorCDecode);
            printf("Tests: ");
            for(int i = 0; i < resOut.DRes.errorCDecode; i++)
                printf("%d ", resOut.DRes.testNumbersDe[i]+1);
            printf("\n\n");
        }
    }

    else
    {
        printf("All good.");
    }

}

static struct uTResult doTests(const struct testData* testsToDo)
{
    struct uTResult results = {};
    for(int i = 0; i < NUMBER_OF_TESTS; i++)
    {
        if(RunTest(testsToDo[i], Encode) == false)
        {
            results.ERes.testNumbersEn[results.ERes.errorCEncode] = i;
            results.ERes.errorCEncode++;
        }
        if(RunTest(testsToDo[i], Decode) == false)
        {
            results.DRes.testNumbersDe[results.DRes.errorCDecode] = i;
            results.DRes.errorCDecode++;
        }
        results.errorCount = results.DRes.errorCDecode + results.ERes.errorCEncode;
    }
    return results;
}

static bool RunTest(const struct testData test, enum testModes mode)
{
    struct encoderOutput  testLine= {};
    if(mode == Encode)
    {
        testLine = encode(test.line, test.lineLengthE);
        if(strcmp(testLine.line, test.refLine) != 0)
        {
            free(testLine.line);
            return false;
        }
        else
        {
            free(testLine.line);
            return true;
        }
    }
    else
    {
        testLine = decode(test.refLine, test.lineLengthD);
        if(strcmp(testLine.line, test.line) != 0)
        {
            free(testLine.line);
            return false;
        }
        else
        {
            free(testLine.line);
            return true; 
        }  
    }
}