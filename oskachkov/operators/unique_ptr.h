#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include "weak_ptr.h"

template<typename T>
class UniquePtr: public WeakPtr<T>
{
public:
    UniquePtr(T * ptr):
        WeakPtr(new T*(ptr))
    {
    }
    UniquePtr(const UniquePtr & o) = delete;
    UniquePtr& operator=(const UniquePtr & o) = delete;

    ~UniquePtr()
    {
        free();
    }

    void free()
    {
        if ( m_Ptr && *m_Ptr ){
            delete *m_Ptr;
            *m_Ptr = 0;
        }
    }
};

#endif // UNIQUE_PTR

