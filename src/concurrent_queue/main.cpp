#include <iostream>
#include <thread>

#include "concurrent_queue.h"

using std::string;

int main(int argc, char *argv[])
{
    TKS::ConcurrentQueue<string> queue;

    std::thread writeThread = std::thread([&queue]() {
        std::cout << "Writing thread ID ";
        std::cout << std::this_thread::get_id() << std::endl;
        std::cout << ">>> ";

        for (int i = 1; i <= 20; i++) {
            string x = std::to_string(i);
            std::cout << x << " ";
            queue.push(x);
        }

        std::cout << std::endl;
    });

    std::thread readThread = std::thread([&queue]() {
        std::cout << "Reading thread ID ";
        std::cout << std::this_thread::get_id() << std::endl;
        std::cout << "<<< ";

        while (!queue.empty()) {
            std::cout << queue.pop() << " ";
        }

        std::cout << std::endl;
    });

    if (writeThread.joinable())
        writeThread.join();

    if (readThread.joinable())
        readThread.join();

    return 0;
}
