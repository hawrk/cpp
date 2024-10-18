/*
 * @Author: hawrkchen hawrk2012@163.com
 * @Date: 2024-10-18 14:42:43
 * @LastEditors: hawrkchen hawrk2012@163.com
 * @LastEditTime: 2024-10-18 15:05:08
 * @FilePath: /thread_awesome/thread_notify.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

bool ready = false;
std::mutex mtx;
std::condition_variable cv;

void worker(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while(!ready) {
        cv.wait(lck);  // 1. 条件变量等待，直到通知, 10个线程都在这里等待
    }
    // 10个线程都到达这里，开始执行任务
    // notify_all 时, 10个线程都被唤醒，但是需要拿到锁才能执行任务,所以这里10个线程不是并发执行的,只是串行执行
    // 全部执行完成后, 10个线程都释放锁, 程序退出

    // notify_one时,只有一个线程被唤醒,其结果是只要有一个线程还在等待,则程序不会退出
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<"id:"<< id <<",Worker thread is running..." << std::endl;
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    //cv.notify_all();  // 2. 通知所有等待线程，10个线程都在这里被唤醒
    cv.notify_one();   // 唤醒一个线程,其他9个继续等待,其结果是只要有一个线程还在等待,则程序不会退出
} 

int main() {
    std::thread thread[10];
    for(int i=0; i<10; i++) {
        thread[i] = std::thread(worker, i);
    }
    std::cout << "10 threads ready to race..." << std::endl;
    go();
    for(int i=0; i<10; i++) {
        thread[i].join();
    }
    std::cout << "All threads have finished." << std::endl;
    return 0;
}

