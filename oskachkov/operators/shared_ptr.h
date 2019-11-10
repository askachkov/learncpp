#ifndef SHARED_PTR
#define SHARED_PTR

#include "weak_ptr.h"

template<typename T>
class SharedPtr: public WeakPtr<T>
{
    union {
        int & m_ShRefCounter;
        int * m_pShRefCounter;
    };

    bool m_IsArray;

public:
    SharedPtr(T * ptr = 0, bool isArray = false):
        WeakPtr(new T*(ptr), new int(1)),
        m_pShRefCounter(new int(1)),
        m_IsArray(isArray)
    {
    }

    SharedPtr(const SharedPtr & o):
        WeakPtr(o),
        m_pShRefCounter(o.m_pShRefCounter),
        m_IsArray(o.m_IsArray)
    {
        m_ShRefCounter++;
    }

    SharedPtr& operator=(const SharedPtr & o)
    {
        free();
        WeakPtr::operator =(o);
        m_pShRefCounter = o.m_pShRefCounter;
        m_ShRefCounter++;
        m_IsArray = o.m_IsArray;
        return *this;
    }

    ~SharedPtr()
    {
        free();
    }

    void free()
    {
        if ( m_Ptr && *m_Ptr && --m_ShRefCounter == 0 ){
            delete m_pShRefCounter;
            if ( m_IsArray ){
                delete[] *m_Ptr;
            }else{
                delete *m_Ptr;
            }
            *m_Ptr = 0;
        }
    }
};

#endif // SHARED_PTR

