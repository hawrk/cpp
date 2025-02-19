/*
 * @Author: hawrkchen
 * @Date: 2024-12-03 09:27:26
 * @Description: 
 * @FilePath: /hv_demo/tcp_server.cpp
 */


#include <hv/hv.h>
#include <hv/TcpServer.h>

using namespace hv;

void initLog() {
    hlog_set_level(LOG_LEVEL_DEBUG);
    hlog_set_file("tcp_server.log");
    
}

int main(int argc, char* argv[]) {
    initLog();
    TcpServer srv;
    int listen_fd = srv.createsocket(8080);
    if(listen_fd < 0) {
        perror("create socket error");
        return -1;
    }

    LOGD("server listen on port 8080, listen_fd=%d", listen_fd);

    srv.onConnection = [](const SocketChannelPtr& channel) {
        std::string peeraddr = channel->peeraddr();
        if(channel->isConnected()) {
            LOGD("new connection from %s, connfd:%d", peeraddr.c_str(), channel->fd());
        } else {
            LOGD("connection from %s closed, connfd:%d", peeraddr.c_str(),channel->fd());
        }
    };
    // up 设置服务端口号，进入监听状态

    srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buffer) {
        LOGD("recv data from %s, connfd:%d, data:%s", channel->peeraddr().c_str(), channel->fd(), buffer->data());
        Buffer retBuff;
        //retBuff.resize(1024);
        char ret[1024] = {0};
        sprintf(ret, "hello client:%s", (char*)buffer->data());
        LOGD("get data:%s", ret);

        retBuff.copy((void*)ret, strlen(ret));

        channel->write(&retBuff);  // 回填
    };

    // 
    srv.onWriteComplete = [](const SocketChannelPtr& channel, Buffer* buffer)  {
        LOGD("send data to %s, connfd:%d, data:%s", channel->peeraddr().c_str(), channel->fd(), buffer->data());
    };  

    srv.setThreadNum(4);
    srv.start();

    while(getchar() != 'q') {
        sleep(1);
    }

    srv.stop();
    return 0;
}