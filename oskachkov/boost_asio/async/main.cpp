#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::asio;

typedef boost::system::error_code SystemErrorCode;

class Controller
{
public:
    void onTick(const SystemErrorCode & /*e*/)
    {
        cout << "Hello, world int Ctrl!" << endl;
    }
};

int main()
{
    Controller ctrl;
    io_service io;
    deadline_timer t(io, seconds(5));
    cout << "Part 2. Wait 5 seconds..." << endl;
    t.async_wait( boost::bind(&Controller::onTick, &ctrl, boost::asio::placeholders::error) );
    io.run();
    return 0;
}
