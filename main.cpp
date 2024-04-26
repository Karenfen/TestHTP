#include <thread>
#include <shared_mutex>
#include <iostream>
#include <chrono>

std::shared_mutex mtx;
int count = 0;

void ReadCount()
{
    std::shared_lock lock(mtx);
    std::cout << count << std::endl;
}

void IncrementCount(int &cnt)
{
    std::lock_guard lock(mtx);
    cnt += 1;
}

void WriteCount(int &cnt)
{
    for (size_t i = 0; i < 1000; i++)
    {
        IncrementCount(cnt);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{

    std::thread thr(WriteCount, std::ref(count));

    for (size_t i = 0; i < 1000; i++)
    {
        ReadCount();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    thr.join();
    return 0;
}