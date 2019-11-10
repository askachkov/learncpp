#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "variant.h"
#include <string>
#include <list>
#include <cstdint>
#include <type_traits>

#define SERIALIZE_BASIC(TYPE) Variant serialize(TYPE data);
#define SERIALIZE_BASIC_IMPL(TYPE)                  \
    Variant serialize(TYPE data)  \
    {                                               \
        return Variant(data);                       \
    }

#define SERIALIZE_REF(TYPE) template <> Variant serialize<TYPE>(const TYPE & data);
#define SERIALIZE_REF_IMPL(TYPE)                            \
    template <> Variant serialize<TYPE>(const TYPE & data)  \
    {                                                       \
        return Variant(data);                               \
    }

template <typename T> Variant serialize(const T & data);
template <typename T, size_t size> Variant serializeArray(const T(&arr)[size])
{
    VariantArray res;
    for ( size_t i = 0; i < size; ++i ){
        res.push_back(serialize(arr[i]));
    }
    return Variant(res);
}

SERIALIZE_BASIC(uint8_t)
SERIALIZE_BASIC(uint16_t)
SERIALIZE_BASIC(uint32_t)
SERIALIZE_BASIC(uint64_t)
SERIALIZE_BASIC(int8_t)
SERIALIZE_BASIC(int16_t)
SERIALIZE_BASIC(int32_t)
SERIALIZE_BASIC(int64_t)
SERIALIZE_BASIC(bool)
SERIALIZE_BASIC(float)
SERIALIZE_BASIC(double)
SERIALIZE_REF(std::string)

#endif // SERIALIZER_H
