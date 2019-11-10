#ifndef SESSION_H
#define SESSION_H

#include "types.h"
#include "message.h"
#include <set>

class Session;

struct ISessionManager
{
    virtual void onRemove(Session *) = 0;
    virtual void onRecieve(const Message & msg) = 0;
};

class Session
{
public:
    Session(IO_Service * pIO, ISessionManager * pRemover);
    void prepare();
    void send(const Message & msg);
    Socket& socket();

private:
    void asyncWriteEx();
    void asyncReadHeaderEx();
    void asyncReadBodyEx();

private:
    void onReadHeader(const ErrorCode & e);
    void onReadBody(const ErrorCode & e);
    void onWrite(const ErrorCode & e);

private:
    Socket m_Socket;
    ISessionManager * m_pMgr;
    Message m_InMsg;
    MessageList m_OutMsgs;
};

typedef std::set<Session*> SessionMap;

#endif // SESSION_H
