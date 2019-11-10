//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    using namespace std;
    using namespace boost::posix_time;
    using namespace boost::asio;

    io_service io;
    deadline_timer t(io, seconds(5));
    cout << "Part 1. Wait 5 seconds..." << endl;
    t.wait();
    cout << "Hello, world!" << endl;
    return 0;
}

