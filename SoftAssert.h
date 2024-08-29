#ifndef SOFT_ASSERT_INCLUDED
#define SOFT_ASSERT_INLCUDED

#include <stdio.h>

#ifdef NWHISPER
#define whisper
#else
#define whisper(condition, message) if(!condition) fprintf(fprintf, "%s", message)
#endif

#endif