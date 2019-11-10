#include "server_impl.h"

ServerImpl::ServerImpl(IO_Service *pIO, Endpoint *pEP):
    m_pIO(pIO),
    m_acc(*pIO, *pEP)
{

}

void ServerImpl::prepare()
{
    asyncAcceptEx();
}

void ServerImpl::asyncAcceptEx()
{
    Session * pSession = new Session(m_pIO, this);
    m_acc.async_accept(pSession->socket(),
                       boost::bind(&ServerImpl::onAccept, this, pSession,
                                   boost::asio::placeholders::error));
    Logger::write("ServerImpl::asyncAcceptEx");
}

void ServerImpl::onRemove(Session *p)
{
    m_Clients.erase(p);
    Logger::write("ServerImpl::onRemove %d", (int)p);
    delete p;
}

void ServerImpl::onRecieve(const Message &msg)
{
    m_Room.push_back(msg);
    for ( Session * p: m_Clients ){
        if ( p != msg.owner )
            p->send(msg);
    }
    Logger::write("ServerImpl::onRecieve '%s'", msg.body());
}

void ServerImpl::onAccept(Session * pSession, const ErrorCode &e)
{
    if (!e)
    {
        Logger::write("ServerImpl::onAccept %d", (int) pSession);
        m_Clients.insert(pSession);
        pSession->prepare();
        asyncAcceptEx();
    } else {
        Logger::write("onAccept error = %d", e.value());
    }
}

