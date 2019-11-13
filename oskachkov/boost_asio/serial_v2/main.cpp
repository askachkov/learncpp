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

void printFrame(Frame & f, const boost::system::error_code& error, size_t s)
{
    std::cout << "Frame:"<< f.id << std::endl;
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
        boost::asio::async_read(sport, boost::asio::buffer(frame.bytes, sizeof(Frame)),
            boost::bind(&printFrame, frame,
              boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

//        sport.async_read_some(boost::asio::buffer(frame.bytes, sizeof(Frame)),
//                              boost::bind(&printFrame, frame,
//                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));



//            boost::asio::async_read(socket_,
//                boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//                boost::bind(&chat_client::handle_read_body, this,
//                  boost::asio::placeholders::error));

//            boost::asio::async_write(socket_,
//                boost::asio::buffer(write_msgs_.front().data(),
//                  write_msgs_.front().length()),
//                boost::bind(&chat_client::handle_write, this,
//                  boost::asio::placeholders::error));
    } else {
        std::cout << "Device was not found" << std::endl;
    }
    boost::thread th1(boost::bind(&IOContext::run, &io_service));
    while ( true ){
        io_service.poll();
    }
    //io_service.run();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
