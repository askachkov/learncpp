#include "variant.h"

namespace variant_internal
{

int TEMPLATE_COUNTER = 0;

}

Variant::Variant()
{
    m_Pimpl.ctrl = 0;
    m_Pimpl.id = -1;
    m_Pimpl.size = 0;
}

Variant::Variant(const Variant &o)
{
    o.m_Pimpl.ctrl->cloneFrom(o.m_Pimpl, &m_Pimpl);
}

Variant::~Variant()
{
    if ( m_Pimpl.ctrl && !m_Pimpl.size != 0 ){
        m_Pimpl.ctrl->destroy(m_Pimpl);
    }
}

bool Variant::isNull() const
{
    return m_Pimpl.id == -1;
}

bool Variant::isObject() const
{
    return typeIs<VariantObject>();
}

bool Variant::isArray() const
{
    return typeIs<VariantArray>();
}

std::ostream &Variant::ostreamWrite(std::ostream &s) const
{
    if ( m_Pimpl.ctrl ){
        return m_Pimpl.ctrl->ostreamWrite(s, m_Pimpl);
    }
    throw std::bad_cast("Varian: null variant used for ostream");
}

std::istream &Variant::istreamRead(std::istream &s)
{
    if ( m_Pimpl.ctrl ){
        return m_Pimpl.ctrl->istreamRead(s, m_Pimpl);
    }
    throw std::bad_cast("Varian: null variant used for istream");
}

Variant &Variant::operator=(const Variant &o)
{
    if ( m_Pimpl.ctrl ){
        m_Pimpl.ctrl->destroy(m_Pimpl);
    }
    o.m_Pimpl.ctrl->cloneFrom(o.m_Pimpl, &m_Pimpl);
    return *this;
}

std::ostream &operator <<(std::ostream &s, const Variant &v)
{
    return v.ostreamWrite(s);
}

std::istream &operator >>(std::istream &s, Variant &v)
{
    return v.istreamRead(s);
}

bool Variant::isNumber() const
{
    return typeIs<uint8_t>() || typeIs<int8_t>() || typeIs<uint16_t>() || typeIs<int16_t>() || typeIs<uint32_t>() ||
           typeIs<int32_t>() || typeIs<uint64_t>() || typeIs<int64_t>() || typeIs<float>() || typeIs<double>();
}
