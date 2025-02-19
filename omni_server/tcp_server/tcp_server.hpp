/*
 * @Author: hawrkchen
 * @Date: 2024-12-18 09:58:25
 * @Description: 
 * @FilePath: /omni_server/tcp_server/tcp_server.hpp
 */


#pragma once

#include <functional>
#include <mutex>
#include <vector>

#include "hv/hloop.h"

#include "../common/threadsafe_queue.hpp"

typedef struct {
    std::string cmd;
    int len;
    std::string data;
} tcp_msg_t;

using tcp_callback_t = std::function<void(tcp_msg_t&)>;

class OmniTCPServer {
    public:
        OmniTCPServer(size_t port, const std::string ip);
        
        ~OmniTCPServer()= default;

        void start_serer();

        void on_response(const tcp_msg_t& msg);

        void set_server_callback(const tcp_callback_t& callback);

        void  on_response_callback();

    private:

        static void accept_callback(hio_t* io);

        static void close_conn_callback(hio_t* io);
        // 同步方式
        static void on_read_callback(hio_t* io, void* buf, int read_bytes);
        // 异步方式
        static void on_read_callback_async(hio_t* io, void* buf, int read_bytes);



    private:
        std::size_t port_ = 0;
        std::string ip_;
        hio_t* listen_io_;
        bool is_async_;    // 是否异步回包

        tcp_callback_t data_callback_;

        //static std::mutex mutex_;
        static hio_t* accept_io_;
        static ThreadSafeQueue<tcp_msg_t> queue_;
        //static std::vector<std::string> msg_queue_;

};
