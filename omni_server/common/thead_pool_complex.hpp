/*
 * @Author: hawrkchen
 * @Date: 2024-12-20 12:10:43
 * @Description: more complex thread pool implementation, support for return value
 * @FilePath: /omni_server/common/thead_pool_complex.hpp
 */


#pragma once

#include <queue>
#include <vector>
#include <future>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>
//#include <iostream>

#define THREADPOOL_MAX_NUM 16    // 线程池最大线程数

class ThreadPoolComplex {
    using Task = std::function<void()>;

    public:
        ThreadPoolComplex(unsigned short thread_num = 4) : thread_num_(thread_num)
        , run_(true) {
            add_thread(thread_num);
        }

        ~ThreadPoolComplex() {
            run_ = false;
            tasks_cv_.notify_all();
            for(auto& t : threads_pool_) {
                if(t.joinable()) {
                    t.join();
                }
            }

        }

        template<class F, class... Args>
        auto addTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
            if(!run_) {
                throw std::runtime_error("ThreadPool is not running");
            }
            using RetType = decltype(f(args...));
            auto task = std::make_shared<std::packaged_task<RetType()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));
                
            std::future<RetType> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(tasks_mutex_);
                tasks_queue_.emplace([task]() { (*task)(); });
            }

            tasks_cv_.notify_one();
            
            return res;
        }

        int threadd_count() {
            return threads_pool_.size();
        }


        void add_thread(unsigned short num) {
            if(!run_) {
                throw std::runtime_error("ThreadPool is not running");
            }
            
            for(; threads_pool_.size() < THREADPOOL_MAX_NUM && num > 0; --num) {
                threads_pool_.emplace_back([this]() {
                    while(true) {
                        Task task;
                        {
                            std::unique_lock<std::mutex> lock(tasks_mutex_);
                            tasks_cv_.wait(lock, [this]() {  //wait 直到有task 或者 线程池停止
                                return !run_ || !tasks_queue_.empty();
                            });

                            if(!run_ && tasks_queue_.empty()) {
                                return;
                            }
                            task = std::move(tasks_queue_.front());
                            tasks_queue_.pop();
                        }

                        task();  // 执行task
                    }
                });

            }  //for
                        
        }


    private:
        unsigned short thread_num_;
        std::vector<std::thread> threads_pool_;  // thread pool
        std::queue<Task> tasks_queue_;  // task queue
        std::mutex tasks_mutex_;  // mutex for task queue
        std::condition_variable tasks_cv_;  // condition variable for task queue
        std::atomic<bool> run_ {true};  // stop flag for thread pool
};