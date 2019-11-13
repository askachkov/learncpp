#include "searchdev.h"
#include <list>
#include <string>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <memory>

typedef boost::asio::io_context IOContext;
typedef boost::asio::executor_work_guard<IOContext::executor_type> IOGuard;
typedef std::shared_ptr<IOGuard> IOGuardShared;
typedef IOContext::strand IOStrand;
typedef boost::thread Thread;
typedef std::string String;
typedef boost::asio::serial_port BSerialPort;
typedef std::shared_ptr<BSerialPort> BSerialPortShared;
typedef boost::asio::deadline_timer DeadlineTimer;
typedef std::shared_ptr<DeadlineTimer> DeadlineTimerShared;
typedef std::shared_ptr<Frame> FrameShared;

typedef std::list<String> StringList;

struct Data
{
    String COM;
    StringList & devs;
    IOStrand & strand;
    IOGuard w;

    BSerialPortShared serial;
    FrameShared   buffer;
    DeadlineTimerShared timeout;
};


void cancelAwating(Data d)
{
    d.serial->close();
}

void procMsg(Data d)
{
    if ( d.buffer->id == 0xFFFFFFF1 ){
        d.devs.push_back(d.COM);
    }
    d.timeout->cancel();
}

void proc(Data d)
{
    d.buffer->id = 0;
    try {
        d.serial->open(d.COM);
        d.timeout->expires_from_now(boost::posix_time::microsec(110));
        d.timeout->async_wait(boost::bind(&cancelAwating, d));
        d.serial->async_read_some(boost::asio::buffer(d.buffer.get(), 5), d.strand.wrap( boost::bind(&procMsg, d)));
    } catch ( ... ){
    }
}

std::string SearchDev::findDevice()
{
    StringList avaliableDevices;
    IOContext io;
    IOGuard work = make_work_guard(io);
    IOStrand mStrand(io);

    Thread th1(boost::bind(&IOContext::run, &io));
    Thread th2(boost::bind(&IOContext::run, &io));

    for ( int i = 0; i < 100; ++i ){
        Data data = {
            (boost::format("COM%1%") % i).str(),
            avaliableDevices,
            mStrand,
            work,
            BSerialPortShared(new BSerialPort(io)),
            FrameShared(new Frame),
            DeadlineTimerShared(new DeadlineTimer(io))
        };
        boost::asio::post(io, boost::bind(&proc, data));
    }
    work.reset();
    //io.run();
    th1.join();
    th2.join();
    if ( avaliableDevices.empty() )
        return "";
    return avaliableDevices.front();
}

