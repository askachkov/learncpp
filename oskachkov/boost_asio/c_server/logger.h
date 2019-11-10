#ifndef LOGGER_H
#define LOGGER_H


class Logger
{
public:
    Logger();
    static void write(const char * msg, ...);
};

#endif // LOGGER_H
