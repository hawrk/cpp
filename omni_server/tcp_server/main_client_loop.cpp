/*
 * @Author: hawrkchen
 * @Date: 2024-12-18 13:55:03
 * @Description: 
 * @FilePath: /omni_server/tcp_server/main_client.cpp
 */
#include <iostream>

#include "hv/hloop.h"

static void on_close(hio_t* io) {
    std::cout << "connection closed" << std::endl;
}

static void on_recv(hio_t* io, void* buf, int readbytes) {
    std::cout << "recv: " << std::string((char*)buf, readbytes) << std::endl;
    
}

static void on_connection(hio_t* io) {
    //hio_setcb_close(io, on_close);
    hio_setcb_read(io, on_recv);
    hio_read(io);

    hio_write(io, "hello world\n", strlen("hello world\n"));
}


int main(int argc, char* argv[]) {
    const char* host = "127.0.0.1";
    int port = 8080;

    hloop_t* loop = hloop_new(2);
    hio_t* conn = hloop_create_tcp_client(loop, host, port, on_connection, on_close);
    if(conn == nullptr) {
        return -1;
    }        

    hloop_run(loop);
    hloop_free(&loop);
    return 0;
}