#include "asio_thread_pool.h"

AsioThreadPool::AsioThreadPool(size_t poolSize):
    mAvaliable(poolSize)
{
    for ( size_t i = 0; i < mAvaliable; ++i ){
        mThreads.create_thread( boost::bind( &boost::asio::io_context::run, &mIO ) );
    }
}

AsioThreadPool::~AsioThreadPool()
{
    mIO.stop();
    try {
        mThreads.join_all();
    } catch ( const std::exception & ){

    }
}

void AsioThreadPool::wrapTask(boost::function<void ()> task)
{
    try {
        task();
    } catch( const std::exception & ) {}
}

