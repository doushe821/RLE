#ifndef UNIT_TEST_INCLUDED
#define UNIT_TEST_INCLUDED

const int NUMBER_OF_TESTS = 3;

struct testData
{
    const char* line;
    const int lineLengthE;
    const char* refLine;
    const int lineLengthD;
};
const struct testData tests[NUMBER_OF_TESTS]= 
{
    {"1111111kkkkkkk", 14, "\0071\007k", 4},
    {"x5ljkj", 6, "\001x\0015\001l\001j\001k\001j", 12},
    {"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq sssssssssssssssss 32", 78, "\071q\001 \021s\001 \0013\0012", 12} 
};

enum testModes
{
    Encode = 0,
    Decode = 1
};


struct EnResult
{
    int errorCEncode;
    int testNumbersEn[NUMBER_OF_TESTS];
};

struct DeResult
{
    int errorCDecode;
    int testNumbersDe[NUMBER_OF_TESTS];

};

struct uTResult
{
    int errorCount;
    struct DeResult DRes;
    struct EnResult ERes;
};

void UnitTest();

#endif