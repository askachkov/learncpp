#include "asio_thread_pool.h"
#include <iostream>

void task1()
{
    std::cout << "Task1\n";
}

struct Task2
{
    void operator()()
    {
        std::cout << "Task2\n";
    }
};

void task3(int x)
{
    std::cout << "Task3 " << x << "\n";
}

int main()
{
    AsioThreadPool pool(3);
    pool.runTask(task1);
    pool.runTask(Task2());
    pool.runTask( boost::bind(task3, 3) );
    pool.runTask( boost::bind(task3, 4) );
    pool.runTask( boost::bind(task3, 5) );
    pool.runTask( boost::bind(task3, 6) );
    pool.runTask( boost::bind(task3, 7) );
    pool.runTask( boost::bind(task3, 8) );
    pool.runTask( boost::bind(task3, 9) );
    pool.runTask( boost::bind(task3, 10) );
    pool.runTask( boost::bind(task3, 11) );
    return 0;
}

