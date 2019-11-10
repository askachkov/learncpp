#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#include "types.h"
#include "session.h"
#include "logger.h"

class ServerImpl:
        private ISessionManager
{
public:
    ServerImpl(IO_Service * pIO, Endpoint * pEP);
    void prepare();

private:
    void asyncAcceptEx();
    void onRemove(Session * p);
    void onRecieve(const Message &msg);

private:
    void onAccept(Session *pSession, const ErrorCode & e);

private:
    IO_Service * m_pIO;
    TcpAcceptor  m_acc;
    MessageList  m_Room;
    SessionMap   m_Clients;
};

#endif // SERVERIMPL_H
