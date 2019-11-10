#ifndef TYPES
#define TYPES

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <deque>
#include <string>

typedef boost::asio::io_service IO_Service;
typedef boost::asio::ip::tcp::endpoint Endpoint;
typedef boost::asio::ip::tcp::acceptor TcpAcceptor;
typedef boost::asio::ip::tcp::socket Socket;
typedef boost::system::error_code ErrorCode;

#endif // TYPES

