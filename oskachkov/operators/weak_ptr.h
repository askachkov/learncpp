#ifndef WEAK_PTR
#define WEAK_PTR

template<typename T>
class WeakPtr
{
protected:
    T ** m_Ptr;
    T *  m_pCursor;
    union {
        int & m_RefCounter;
        int * m_pRefCounter;
    };

    void free()
    {
        if ( --m_RefCounter == 0 ){
            delete m_pRefCounter;
            delete m_Ptr;
        }
    }

public:
    WeakPtr(T ** pptr = 0, int * pCounter = new int(1)):
        m_Ptr(pptr),
        m_pCursor(pptr?*pptr:0),
        m_pRefCounter(pCounter)
    {
    }


    WeakPtr(const WeakPtr & o):
        m_Ptr(o.m_Ptr),
        m_pCursor(o.m_pCursor),
        m_pRefCounter(o.m_pRefCounter)
    {
        m_RefCounter++;
    }

    WeakPtr& operator=(const WeakPtr & o)
    {
        free();
        m_Ptr = o.m_Ptr;
        m_pCursor = o.m_pCursor;
        m_pRefCounter = o.m_pRefCounter;
        m_RefCounter++;
        return *this;
    }

    ~WeakPtr()
    {
        free();
    }

    T* operator->()
    {
        return m_pCursor;
    }
    const T* operator->()const
    {
        return m_pCursor;
    }
    T& operator*()
    {
        return *m_pCursor;
    }
    const T& operator*()const
    {
        return *m_pCursor;
    }

    WeakPtr operator++()
    {
        m_pCursor++;
        return *this;
    }

    WeakPtr operator++(int)
    {
        WeakPtr res = *this;
        m_pCursor++;
        return res;
    }

    WeakPtr operator--()
    {
        m_pCursor--;
        return *this;
    }

    WeakPtr operator--(int)
    {
        WeakPtr res = *this;
        m_pCursor--;
        return res;
    }

    operator bool()const
    {
        return m_Ptr && *m_Ptr;
    }

    template <class U>
    operator U*()const
    {
        if ( m_Ptr && *m_Ptr )
            return (U*)*m_Ptr;
        return 0;
    }

    T * data()const
    {
        if ( m_Ptr && *m_Ptr )
            return *m_Ptr;
        return 0;
    }
};

#endif // WEAK_PTR

