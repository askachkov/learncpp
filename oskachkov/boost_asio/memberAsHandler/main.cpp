#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::asio;

typedef boost::system::error_code SystemErrorCode;

class Controller
{
public:
    typedef void (Controller::*Tick)(const SystemErrorCode &, deadline_timer *);

    Controller(io_context & io):
        mCount(0),
        mStrand(io),
        mTimer1(io, seconds(1)),
        mTimer2(io, seconds(1))
    {
        runTimer(&mTimer1, &Controller::onTick1);
        runTimer(&mTimer2, &Controller::onTick2);
    }

    void runTimer(deadline_timer * pTimer, Tick tick)
    {
        pTimer->async_wait( mStrand.wrap(boost::bind(tick, this, boost::asio::placeholders::error, pTimer)));
    }

    void onTick1(const SystemErrorCode & /*e*/, deadline_timer * pTimer)
    {
        if ( mCount++ < 500 ){
            cout << "onTick1 Ctrl! " << mCount << " " << endl;
            pTimer->expires_at( pTimer->expires_at() + milliseconds(10) );
            runTimer(&mTimer1, &Controller::onTick1);
        }
    }

    void onTick2(const SystemErrorCode & /*e*/, deadline_timer * pTimer)
    {
        if ( mCount++ < 500 ){
            cout << "onTick2 Ctrl! " << mCount << " " << endl;
            pTimer->expires_at( pTimer->expires_at() + milliseconds(10) );
            runTimer(&mTimer2, &Controller::onTick2);
        }
    }

private:
    int mCount;
    io_context::strand mStrand;
    deadline_timer mTimer1;
    deadline_timer mTimer2;
};

int main()
{
    io_context io;
    cout << "Part 3. Wait 5 seconds..." << endl;
    Controller ctrl(io);
    thread th(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    th.join();
    return 0;
}
