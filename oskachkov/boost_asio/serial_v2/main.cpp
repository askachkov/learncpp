//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <searchdev.h>

void printFrame(Frame & frame, boost::asio::serial_port & port, const boost::system::error_code& error, size_t s)
{
    static int x = 1;
    std::cout << "Frame:" << x++ << " " << std::hex << frame.id << std::endl;
    port.async_read_some(boost::asio::buffer(frame.bytes, sizeof(Frame)),
                          boost::bind(&printFrame, boost::ref(frame), boost::ref(port),
                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

}
typedef boost::asio::io_context IOContext;
typedef boost::asio::executor_work_guard<IOContext::executor_type> IOGuard;

int main(int argc, char* argv[])
{
  try
  {
    boost::asio::io_service io_service;
    IOGuard guard = boost::asio::make_work_guard(io_service);
    boost::asio::serial_port sport(io_service);
    std::string dev = SearchDev::findDevice();
    Frame frame;
    if ( !dev.empty() ){
        std::cout << "Device:" << dev << std::endl;
        sport.open(dev);
        sport.async_read_some(boost::asio::buffer(frame.bytes, sizeof(Frame)),
                              boost::bind(&printFrame, boost::ref(frame), boost::ref(sport),
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Device was not found" << std::endl;
    }
    boost::thread th1(boost::bind(&IOContext::run, &io_service));
    while ( true ){
    }
    th1.join();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
