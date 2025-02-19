/*
 * @Author: hawrkchen
 * @Date: 2024-12-18 09:58:34
 * @Description: 
 * @FilePath: /omni_server/tcp_server/tcp_server.cpp
 */

#include "tcp_server.hpp"

#include <thread>
#include <iostream>

hio_t* OmniTCPServer::accept_io_ = nullptr;
//std::mutex OmniTCPServer::mutex_;
//std::vector<std::string> OmniTCPServer::msg_queue_;
ThreadSafeQueue<tcp_msg_t> OmniTCPServer::queue_;


// 初始化列表
OmniTCPServer::OmniTCPServer(size_t port, const std::string ip):
    port_(port)
    ,ip_(ip)
    ,listen_io_(nullptr)
    ,is_async_(false)
{
    queue_.clear();
    // 注册回调函数
    this->set_server_callback(std::bind(&OmniTCPServer::on_response, this, std::placeholders::_1));
}

void OmniTCPServer::start_serer()
{
    hloop_t* ploop = hloop_new();
    listen_io_ = hloop_create_tcp_server(ploop, ip_.c_str(), port_, OmniTCPServer::accept_callback);
    if(listen_io_ == nullptr) {
        std::cerr << "Create tcp server failed!" << std::endl;
        return;
    }

    std::thread{&OmniTCPServer::on_response_callback, this}.detach();

    hloop_run(ploop);  // blocking here
    hloop_free(&ploop);

}

void OmniTCPServer::accept_callback(hio_t* io)
{
    accept_io_ = io;
    std::cout << "Accept a new connection, fd: " << hio_fd(io) << std::endl;

    hio_setcb_close(io, OmniTCPServer::close_conn_callback);
    //hio_setcb_read(io, OmniTCPServer::on_read_callback);    // 同步
    hio_setcb_read(io, OmniTCPServer::on_read_callback_async);    // 异步
    
    hio_read(io);
}

void OmniTCPServer::close_conn_callback(hio_t* io)
{   
    queue_.clear();
    hio_close(io);
}

void OmniTCPServer::on_read_callback(hio_t* io, void* buf, int read_bytes)
{
    const char* data = (char*)(buf);
    std::string msg(data, read_bytes);
    if(msg.empty()) {
        return;
    }
    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

    msg += ",这里是服务端收到的消息";
    std::cout << "Recv msg, fd: " << hio_fd(io) << ", msg: " << msg << std::endl;

    hio_write(accept_io_, msg.c_str(), msg.size());

    //std::unique_lock<std::mutex> lock(mutex_);
    //msg_queue_.emplace_back(msg);
    //lock.unlock();

}

void OmniTCPServer::on_read_callback_async(hio_t* io, void* buf, int read_bytes)
{
    const char* data = (char*)(buf);
    std::string msg(data, read_bytes);
    if(msg.empty()) {
        return;
    }
    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

    msg += ",这里是服务端收到的消息";
    std::cout << "Recv msg, fd: " << hio_fd(io) << ", msg: " << msg << std::endl;

    tcp_msg_t resObj;
    resObj.data = msg;
    queue_.push(resObj);
    //msg_queue_.emplace_back(msg);
}


void OmniTCPServer::on_response(const tcp_msg_t& msg)
{
    std::string str = msg.data;
    hio_write(accept_io_, str.c_str(), str.size());
}

void OmniTCPServer::on_response_callback()
{
    while(true) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        std::cout << "data_callback, quesize:" << queue_.get_queue_size() << std::endl;
        auto data = queue_.wait_and_pop();
        if(data_callback_) {
            std::cout << "out msg to client, msg: " << data.data << std::endl;
            data_callback_(data);
        }
    }
}

void OmniTCPServer::set_server_callback(const tcp_callback_t& callback)
{
    this->data_callback_ = callback;
}

