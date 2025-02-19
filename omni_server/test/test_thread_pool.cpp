/*
 * @Author: hawrkchen
 * @Date: 2024-12-20 10:29:09
 * @Description: 
 * @FilePath: /omni_server/test/test_thread_pool.cpp
 */


#include <iostream>
#include <string>

#include "../common/thread_pool.hpp"

std::mutex cout_mutex;   // 防止打印错乱

void taskFunc(int i) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Task " << i << " running on thread " << std::this_thread::get_id() << std::endl;
}

auto lambdaTask = [](int i) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Lambda task " << i << " running on thread " << std::this_thread::get_id() << std::endl;
};

void exampleTask(int a, double b, const std::string& c) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Example task running on thread " << std::this_thread::get_id() << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
}


int main(int argc, char* argv[])   
{
    ThreadPool pool(4);

    int a = 5;
    double b = 3.14;
    std::string c = "Hello, world!";

    int k = 7;

    pool.enqueue([=]{taskFunc(a);});
    pool.enqueue([=]{lambdaTask(k);});
    pool.enqueue([=]{exampleTask(a, b, c);});

    std::cout << "Main thread exiting" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}