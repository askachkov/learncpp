#include "session.h"
#include "logger.h"

Session::Session(IO_Service *pIO, ISessionManager *pRemover):
    m_Socket(*pIO),
    m_pMgr(pRemover)
{
    m_InMsg.owner = this;
}

void Session::prepare()
{
    asyncReadHeaderEx();
}

void Session::send(const Message &msg)
{
    bool inProgress = !m_OutMsgs.empty();
    m_OutMsgs.push_back(msg);
    Logger::write("Session::send: %s", msg.data());
    if (!inProgress) {
        asyncWriteEx();
    }
}

Socket &Session::socket()
{
    return m_Socket;
}

void Session::asyncWriteEx()
{
    auto buf = boost::asio::buffer(m_OutMsgs.front().data(), m_OutMsgs.front().length());
    auto callback =  boost::bind(&Session::onWrite, this, boost::asio::placeholders::error);
    boost::asio::async_write(m_Socket, buf, callback);
}

void Session::asyncReadHeaderEx()
{
    auto buf = boost::asio::buffer(m_InMsg.data(), Message::header_length);
    auto callback = boost::bind(&Session::onReadHeader, this, boost::asio::placeholders::error);
    boost::asio::async_read(m_Socket, buf, callback);
}

void Session::asyncReadBodyEx()
{
    auto buf = boost::asio::buffer(m_InMsg.body(), m_InMsg.body_length());
    auto callback = boost::bind(&Session::onReadBody, this, boost::asio::placeholders::error);
    boost::asio::async_read(m_Socket, buf, callback);
}

void Session::onReadHeader(const ErrorCode &e)
{
    if (!e && m_InMsg.decode_header()) {
        asyncReadBodyEx();
    } else {
        m_pMgr->onRemove(this);
    }
}

void Session::onReadBody(const ErrorCode &e)
{
    if (!e) {
        m_pMgr->onRecieve(m_InMsg);
        asyncReadHeaderEx();
    } else {
        m_pMgr->onRemove(this);
    }
}

void Session::onWrite(const ErrorCode &e)
{
    if (!e) {
        Logger::write("Session::onWrite: %s", m_OutMsgs.front().data());
        m_OutMsgs.pop_front();
        if (!m_OutMsgs.empty()) {
            asyncWriteEx();
        }
    } else {
        m_pMgr->onRemove(this);
    }
}

