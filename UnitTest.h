#ifndef UNIT_TEST_INCLUDED
#define UNIT_TEST_INCLUDED

struct testData
{
    const char* line;
    const int lineLength;
    const char* refLine;
};

bool RunTest(struct testData test);

#endif