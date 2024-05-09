// Прогресс-бар.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Timer.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::once_flag f;
std::mutex m1;
std::mutex m2;
std::mutex m3;
std::mutex m4;


static void ProgressBar(int numberThreadsNow)
{
    int progressBar = 10;
    int total = 29;
    int PositionForTime = 30;

    std::call_once(f, []() {
        std::cout << "# " << "ID\t\t" << "Progress\t" << "Time\n" << std::endl;
        });

    m1.lock();
    Timer t;
    consol_parameter con_p;
    m1.unlock();

    m2.lock();
    con_p.SetPosition(0, numberThreadsNow + 1);
    std::cout << numberThreadsNow + 1 << " " << std::this_thread::get_id() << "\t";
    m2.unlock();

    while (progressBar < total)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        m3.lock();
        con_p.SetPosition(progressBar, numberThreadsNow + 1);
        std::cout << char(219);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        ++progressBar;
        m3.unlock();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    m4.lock();
    con_p.SetPosition(PositionForTime, numberThreadsNow + 1);
    t.print();
    m4.unlock();
}

int main()
{

    int count = 5;

    std::vector<std::thread> Threads(count);

    for (size_t i = 0; i < count; i++)
    {
        Threads[i] = std::thread(ProgressBar, i);
    }

    for (auto& i : Threads)
    {
        i.join();
    }
    std::cout <<"\n\n\n"<< std::endl;
}