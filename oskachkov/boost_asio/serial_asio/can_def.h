#ifndef CAN_DEF
#define CAN_DEF

#include <cstdint>
#include <iostream>
#include <iomanip>

#pragma pack(push, 1)

struct CAN{
    uint8_t idType;
    uint32_t id;
    uint8_t dlc;
    union {
        struct {
            uint8_t data0;
            uint8_t data1;
            uint8_t data2;
            uint8_t data3;
            uint8_t data4;
            uint8_t data5;
            uint8_t data6;
            uint8_t data7;
        };
        uint8_t data[8];
        uint64_t data64;
    };
    uint64_t timestamp;
    bool operator < (const CAN & c)const
    {
        return id < c.id;
    }
};

#pragma pack(pop)

std::ostream& operator << (std::ostream& stream, const CAN & cn)
{
    using namespace std;
    ios_base::fmtflags d = stream.flags();
    stream << "[" << hex << setw(8) << cn.id << "] " << setw(16) << cn.data64 << " : " << setw(16) << dec <<  cn.timestamp;
    stream.setf(d);
    return stream;
}

#endif // CAN_DEF

