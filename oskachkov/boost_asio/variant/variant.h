#ifndef VARIANT
#define VARIANT

#include <cstdint>
#include <istream>
#include <ostream>
#include <deque>
#include <string>

namespace variant_internal
{

namespace SFINAE
{
template<class T, class U, class V>
struct has_ostream_shift
{
  template<class T1,
           class Reference = decltype(
             (*std::declval<std::ostream*>()) << (*std::declval<T*>())
           ),
           class = typename std::enable_if<
             !std::is_void<Reference>::value
           >::type>
  static U test(int);

  template<class>
  static V test(...);

  using type = decltype(test<T>(0));
};

template<class T, class U, class V>
struct has_istream_shift
{
  template<class T1,
           class Reference = decltype(
             (*std::declval<std::istream*>()) >> (*std::declval<T*>())
           ),
           class = typename std::enable_if<
             !std::is_void<Reference>::value
           >::type>
  static U test(int);

  template<class>
  static V test(...);

  using type = decltype(test<T>(0));
};

}

extern int TEMPLATE_COUNTER;

template<typename T>
struct ID_Ver
{
    static const int ID;
};

template<typename T>
const int ID_Ver<T>::ID = TEMPLATE_COUNTER++;

struct Body;

struct IOSWriter
{
    virtual std::ostream& ostreamWrite(std::ostream&, const Body &)const = 0;
};

struct IISReader
{
    virtual std::istream& istreamRead(std::istream&, Body &) = 0;
};

struct IVarianMemCtrl: IOSWriter, IISReader
{
    virtual void cloneFrom(const Body & from, Body * pOut) = 0;
    virtual void destroy(Body & x) = 0;
    virtual bool isBodyOK(const Body & other) const = 0;
};

struct NoOSWriter: IOSWriter
{
    std::ostream& ostreamWrite(std::ostream&, const Body &)const
    {
        throw std::bad_cast("Varian: no ostream operators");
    }
};

template<typename T>
struct OSWriter: IOSWriter
{
    std::ostream& ostreamWrite(std::ostream& s, const Body & b)const
    {
        T * ptr = (T*)b.buffer;
        return s << *ptr;
    }
};

struct NoISReader: IISReader
{
    std::istream& istreamRead(std::istream&, Body &)
    {
        throw std::bad_cast("Varian: no ostream operators");
    }
};

template<typename T>
struct ISReader: IISReader
{
    std::istream& istreamRead(std::istream& s, Body & b)
    {
        T * ptr = (T*)b.buffer;
        return s >> *ptr;
    }
};

struct Body
{
    uint8_t * buffer;
    size_t size;
    int id;
    IVarianMemCtrl * ctrl;
};

template<typename T>
class VarianMemCtrl: public IVarianMemCtrl
{
    IOSWriter * m_pWriter;
    IISReader * m_pReader;
protected:
    VarianMemCtrl(){}
    bool isBodyOK(const Body & other)const
    {
        return ID_Ver<T>::ID == other.id && other.size == sizeof(T);
    }

public:
    ~VarianMemCtrl(){ delete m_pWriter; delete m_pReader; }
    VarianMemCtrl(const VarianMemCtrl &) = delete;
    void operator=(const VarianMemCtrl &) = delete;

    static VarianMemCtrl * instance()
    {
        static VarianMemCtrl var;
        var.m_pWriter = new typename SFINAE::has_ostream_shift<T, OSWriter<T>, NoOSWriter>::type;
        var.m_pReader = new typename SFINAE::has_istream_shift<T, ISReader<T>, NoISReader>::type;
        return &var;
    }

    Body createNew(const T & other)
    {
        Body res;
        res.buffer = new uint8_t[sizeof(T)];
        res.id = ID_Ver<T>::ID;
        res.size = sizeof(T);
        new(res.buffer) T(other);
        res.ctrl = this;
        return res;
    }

    virtual void cloneFrom(const Body & from, Body * pOut)
    {
        if ( !isBodyOK(from) ){
            throw std::bad_cast("Varian: cast failed");
        }

        T * ptr = (T*)from.buffer;
        pOut->buffer = new uint8_t[sizeof(T)];
        pOut->size = sizeof(T);
        pOut->id = ID_Ver<T>::ID;
        pOut->ctrl = from.ctrl;
        new(pOut->buffer) T(*ptr);
    }

    virtual void destroy(Body & body)
    {
        if ( !isBodyOK(body) ){
            throw std::bad_cast("Varian: bad cast");
        }
        T * ptr = (T*)body.buffer;
        delete ptr;
        body.buffer = 0;
    }

    std::ostream& ostreamWrite(std::ostream& s, const Body & b)const
    {
        return m_pWriter->ostreamWrite(s, b);
    }

    std::istream& istreamRead(std::istream& s, Body & b)
    {
        return m_pReader->istreamRead(s, b);
    }
};

}

/**
 * @brief The Variant class - This class can incapsulate any type inside.
 */
class Variant
{
public:
    Variant();
    Variant(const Variant & o);
    ~Variant();
    Variant & operator=(const Variant & o);

    template <typename T> explicit Variant(const T & value)
    {
         m_Pimpl = variant_internal::VarianMemCtrl<T>::instance()->createNew(value);
    }

    template<typename T> Variant& operator=(const T & value)
    {
        if ( m_Pimpl.ctrl ){
            m_Pimpl.ctrl->destroy(m_Pimpl);
        }
        m_Pimpl = variant_internal::VarianMemCtrl<T>::instance()->createNew(value);
        return *this;
    }

    template<typename T> const T& castTo()const
    {
        if ( variant_internal::ID_Ver<T>::ID != m_Pimpl.id ){
            throw std::bad_cast("Varian: cast failed");
        }
        return *((T*)m_Pimpl.buffer);
    }

    template<typename T> T& castTo()
    {
        if ( variant_internal::ID_Ver<T>::ID != m_Pimpl.id ){
            throw std::bad_cast("Varian: cast failed");
        }
        return *((T*)m_Pimpl.buffer);
    }

    template<typename T>
    bool typeIs()const
    {
        return m_Pimpl.id == variant_internal::ID_Ver<T>::ID;
    }

    std::ostream& ostreamWrite(std::ostream& s)const;
    std::istream& istreamRead(std::istream& s);
    bool isNull() const;
    bool isObject() const;
    bool isArray() const;
    bool isNumber() const;

private:
    variant_internal::Body m_Pimpl;
};

struct Field
{
    std::string name;
    Variant value;
};

typedef std::deque<Field> VariantObject;
typedef std::deque<Variant> VariantArray;

std::ostream& operator << (std::ostream& s, const Variant & v);
std::istream& operator >> (std::istream& s, Variant & v);

#endif // VARIANT


