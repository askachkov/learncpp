#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <algorithm>

using namespace std;

bool writeToDev(char * ch, size_t sz)
{
    cout << "Flush:";
    cout.write(ch, sz);
    cout << endl;
    return (bool)cout;
}

size_t readFromDev(char * ch, size_t szMax)
{
    static int state = 3;
    if ( state-- ){
        size_t sz = min(size_t(16), szMax);
        memcpy(ch, " 123 123 123 123", sz );
        return sz;
    }
    return 0;
}

/**
 * @brief The CustomBuf class
 *
 * Input sequence (get):
 *      eback - Pointer to beginning of input sequence (protected member function )
 *      gptr - Pointer to current position of input sequence (protected member function )
 *      egptr - Pointer to end of input sequence (protected member function )
 *      gbump - Increase get pointer (protected member function
 *      setg - Set input sequence pointers (protected member function )
 *      underflow - Get character on underflow (protected virtual member function )
 *
 * Output sequence (put):
 *      pbase - Pointer to beginning of output sequence (protected member function )
 *      pptr - Pointer to current position of output sequence (protected member function )
 *      epptr - Pointer to end of output sequence (protected member function )
 *      pbump - Increase put pointer (protected member function )
 *      setp - Set output sequence pointers (protected member function )
 *      overflow - Put character on overflow (protected virtual member function )
 *
 * Buffer management and positioning:
 *      sync - Synchronize stream buffer (protected virtual member function )
 */


class CustomBuf : public streambuf
{
private:
    char in_buffer[17];

public:
    CustomBuf()
    {
        setp(in_buffer, in_buffer, in_buffer + 16);
        setg(in_buffer, in_buffer, in_buffer + 16);
        sync();
    }

protected:

    /* функции записи в поток: */
    virtual int overflow(int c) override {
        if (c != traits_type::eof()){
            *pptr() = c; //тут нам пригодился 1 "лишний" символ, убранный в конструкторе
            pbump(1); //смещаем указатель позиции буфера на реальный конец буфера
            if ( sync() == -1 ){
                return traits_type::eof();
            }
            return c;
        }
        return traits_type::eof();
    }

    virtual int underflow() override {
        if ( sync() == 0 ){
            return *gptr();
        }
        return traits_type::eof();
    }

    virtual int sync() override {
        if (pptr() != pbase()){
            ptrdiff_t sz = pptr() - pbase(); //вычисляем, сколько символов записано в буффер
            if (!writeToDev(pbase(), sz)){
                return -1;
            }
            setp(in_buffer, in_buffer, in_buffer + 16);
        }
        if ( gptr() == egptr() ){
            if ( readFromDev(in_buffer, 16) != 16 )
                return -1;
            setg(in_buffer, in_buffer, in_buffer + 16);
        }
        return 0;
    }
};


int main(int argc, char **argv){
    const char str1[] = "In 4 bytes contains 32 bits";
    const char str2[] = "Unix time starts from Jan 1, 1970";
    istringstream str(str1);

    CustomBuf buf; // читать из stringstream, выводить в консоль

    ostream oos(&buf);
    oos << '*' << "$$" << ' ' << 3 << " ";
    oos.flush();
    oos << "01234567890ABCDEFX";

    iostream ios(&buf); // таким образом обходимся без реализации своего наследника iostream



    string val;

    while ( ios >> val ){
        cout << "Line:" << val << endl;
        cout.flush();
    }


    return 0;
}
