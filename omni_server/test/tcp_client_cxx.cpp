/*
 * @Author: hawrkchen
 * @Date: 2024-12-03 14:42:05
 * @Description: 
 * @FilePath: /hv_demo/tcp_client_cxx.cpp
 */
#include <hv/TcpClient.h>
#include <hv/htime.h>

int main(int argc, char* argv[]) {
    int port = 8080;

    hv::TcpClient client;
    int connfd = client.createsocket(port);
    if(connfd < 0) {
        return -20;
    }

    printf("client connected to port:%d, connfd:%d\n", port, connfd);
    client.onConnection = [](const hv::SocketChannelPtr& channel) {
        std::string peeraddr = channel->peeraddr();
        if(channel->isConnected()) {
            printf("connected to %s connfd:%d\n", peeraddr.c_str(), channel->fd());
            hv::setInterval(3000, [channel](hv::TimerID timerid) {
                if(channel->isConnected()) {
                    // 拼装发送包
                    char str[DATETIME_FMT_BUFLEN] = {0};
                    datetime_t dt = datetime_now();
                    datetime_fmt(&dt, str);
                    channel->write(str);
                } else {
                    hv::killTimer(timerid);
                }
          });
        } else {
            printf("disconnected from %s connfd:%d\n", peeraddr.c_str(), channel->fd());
        }

    };

    // 回执包
    client.onMessage = [](const hv::SocketChannelPtr& channel, hv::Buffer* buffer) {
        printf("onMessage < %.*s\n", int(buffer->size()), (char*)buffer->data());
    };

    // 发送之前的完整包
    client.onWriteComplete = [](const hv::SocketChannelPtr& channel, hv::Buffer* buffer) {
        printf("onWriteComplete> %.*s\n", int(buffer->size()), (char*)buffer->data());
    };

    reconn_setting_t reconn;
    reconn_setting_init(&reconn);
    reconn.min_delay = 1000;
    reconn.max_delay = 10000;

    reconn.delay_policy = 2;
    client.setReconnect(&reconn);
    client.start();

    while(getchar() != 'q'){
        ;
    }

    return 0;


}