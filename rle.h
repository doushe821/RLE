#ifndef RUN_LENGTH_ENCODER_INCLUDED
#define RUN_LENGTH_ENCODER_INCLUDED

const char MASK = 128;

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

struct encoderTracker
{
    char repeatCounter;
    char uniqueCounter;
    char currentChar;
    int outputLineIndex;
};

struct encoderOutput encode (const char* uncoded, int stringSize);
struct encoderOutput decode (const char* coded, int stringSize);

#endif