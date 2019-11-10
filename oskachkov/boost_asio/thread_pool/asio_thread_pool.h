#ifndef ASIOTHREADPOOL_H
#define ASIOTHREADPOOL_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class AsioThreadPool
{
public:
    AsioThreadPool(size_t poolSize);
    ~AsioThreadPool();
    template<typename Task>
    void runTask(Task task)
    {
        boost::unique_lock< boost::mutex > lock(mMutex);
        mIO.post( boost::bind( &AsioThreadPool::wrapTask, this, boost::function<void()>(task)));
    }

private:
    void wrapTask(boost::function<void()> task);

private:
    boost::asio::io_context mIO;
    boost::thread_group     mThreads;
    size_t                  mAvaliable;
    boost::mutex            mMutex;
};

#endif // ASIOTHREADPOOL_H
