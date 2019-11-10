#include "logger.h"
#include <cstdint>
#include <cstdarg>
#include <cstdio>

Logger::Logger()
{

}

void Logger::write(const char *msg, ...)
{
    va_list argptr;
    va_start (argptr, msg);
    vprintf(msg, argptr);
    printf("|\n");
    va_end(argptr);
}

