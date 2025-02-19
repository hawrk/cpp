/*
 * @Author: hawrkchen
 * @Date: 2024-12-03 14:18:40
 * @Description: 
 * @FilePath: /hv_demo/tcp_client.cpp
 */


#include <hv/hloop.h>
#include <hv/htime.h>

void on_timer(htimer_t* timer) {
    char str[DATETIME_FMT_BUFLEN] = {0};
    datetime_t dt = datetime_now();

    datetime_fmt(&dt,str);
    printf("> %s\n", str);

    //get user data
    hio_t* io = (hio_t*)hevent_userdata(timer);
    hio_write(io, str, strlen(str));
}

void on_close(hio_t* io) {
    printf("client close\n");
}

void on_recv(hio_t* io, void* buf, int readbytes) {
    printf("recv: %d, %s\n", readbytes, (char*)buf);
}

void on_connect(hio_t* io) {
    hio_setcb_read(io, on_recv);
    hio_read(io);

    htimer_t* timer = htimer_add(hevent_loop(io), on_timer, 1000, INFINITE);

    hevent_set_userdata(timer, io);
}

int main(int argc, char* argv[]) {
    int port = 8080;

    hloop_t* loop = hloop_new(0);
    // 创建TCPpeer
    hio_t* tcp_client = hloop_create_tcp_client(loop, "127.0.0.1", port, on_connect, on_close);
    if(tcp_client == nullptr) {
        return -20;
    }
    // 设置连接参数
    
    hloop_run(loop);
    hloop_free(&loop);

    return 0;
}

