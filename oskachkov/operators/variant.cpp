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
