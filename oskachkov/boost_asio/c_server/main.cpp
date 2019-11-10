#include "logger.h"
#include "server_impl.h"
#include "types.h"

int main()
{
    try
    {
        IO_Service io;
        Endpoint ep(boost::asio::ip::tcp::v4(), 1090);
        ServerImpl server(&io, &ep);
        server.prepare();
        Logger::write("Started...");
        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

