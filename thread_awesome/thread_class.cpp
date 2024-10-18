#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

class ThreadApp {
    public:
        ThreadApp();
        ~ThreadApp() {
            if(thread_ptr!= nullptr && thread_ptr->joinable()) {
                thread_ptr->join();
            }
            std::cout << "ThreadApp destroyed" << std::endl;
        };

        void RunServer();

    private:
    std::shared_ptr<std::thread> thread_ptr;
};

ThreadApp::ThreadApp() {
    std::cout << "ThreadApp created" << std::endl;
    while(true) {
        thread_ptr = std::make_shared<std::thread>(&ThreadApp::RunServer, this);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if(thread_ptr!= nullptr && thread_ptr->joinable()) {
            thread_ptr->join();
        }
    }

    
}


void ThreadApp::RunServer() {
    std::cout << "Server started running..." << std::endl;

}

int main(int argc, char* argv[]) {
    ThreadApp app;
    return 0;
}