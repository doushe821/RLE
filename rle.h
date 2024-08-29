#ifndef RUN_LENGTH_ENCODER_INCLUDED
#define RUN_LENGTH_ENCODER_INCLUDED

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
    char currentChar;
    int outputLineIndex;
};

struct encoderOutput encode (const char* uncoded, int stringSize);
struct encoderOutput decode (const char* coded, int stringSize);

#endif