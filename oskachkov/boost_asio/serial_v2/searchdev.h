#ifndef SEARCHDEV_H
#define SEARCHDEV_H

#include <string>
#include <cstdint>

#pragma pack(push, 1)
union Frame
{
    struct {
        uint32_t id;
        uint8_t dlc;
        uint8_t data[8];
    };
    uint8_t bytes[13];
};
#pragma pack(pop)

class SearchDev
{
public:
    static std::string findDevice();
};

#endif // SEARCHDEV_H
