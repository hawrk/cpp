/*
 * @Author: hawrkchen
 * @Date: 2024-12-18 17:03:57
 * @Description: A thread-safe queue implementation.
 * @FilePath: /omni_server/common/threadsafe_queue.hpp
 */
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>

template <typename T>
class ThreadSafeQueue {
    public:
        ThreadSafeQueue():time_out_seconds(30) {}
        ~ThreadSafeQueue()  = default;

        void push(T item) {
            std::lock_guard<std::mutex> lock(m_mutex);
            this->m_queue.push(std::move(item));
            m_condition.notify_one();
        }

        void wait_and_pop(T& item) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this]{return !this->m_queue.empty();});

            item = std::move(this->m_queue.front());
            this->m_queue.pop();
        }

        T wait_and_pop() {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this]{return !this->m_queue.empty();});

            auto item = std::move(this->m_queue.front());
            this->m_queue.pop();
            return item;
        }

        bool try_pop(T& item) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if(this->m_queue.empty()) {
                return false;
            }
            item = std::move(this->m_queue.front());
            this->m_queue.pop();
            return true;
        }

        T try_pop() {
            std::lock_guard<std::mutex> lock(m_mutex);
            if(this->m_queue.empty()) {
                return T{};
            }
            auto item = std::move(this->m_queue.front());
            this->m_queue.pop();
            return item;
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->m_queue.empty();
        }

        size_t get_queue_size() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->m_queue.size();        
        }

        void set_timeout(int seconds) {
            time_out_seconds = seconds;
        }   

        void clear() {
            std::lock_guard<std::mutex> lock(m_mutex);
            while(!this->m_queue.empty()) {
                this->m_queue.pop();
            }
        }


    private:
        std::queue<T> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_condition;   
        int time_out_seconds;
};

