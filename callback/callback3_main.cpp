/*
 * @Author: hawrkchen
 * @Date: 2024-10-30 11:40:18
 * @Description: 
 * @FilePath: /callback/callback3_main.cpp
 */
#include <iostream>
#include <functional>
#include <thread>

using namespace std;


class ProjB {
    typedef std::function<void(int)> CallbackT;
    public:
        ProjB() = default;

        // 回调原型
        int start_run(CallbackT cb) {
            cout << "ProjB::start_run" << endl;
            for (auto i = 0; i < 10; i++) {
                cb(i);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            return 0;
        }

        ~ProjB() = default;

    private:
};

class ProjA {
    public:
        ProjA() = default;

        void start() {
            proj_b_.start_run(std::bind(&ProjA::publishing, this, std::placeholders::_1));
        }

        ~ProjA() = default;


    private:
        ProjB proj_b_;

        void publishing(int data) {
            cout << "ProjA::publishing: " << data << endl;
        }
};


class ProjC {
    public:
        ProjC() = default;

        void start() {
            proj_b_.start_run(std::bind(&ProjC::publishing, this, std::placeholders::_1));
        }

        ~ProjC() = default;

    private:
        ProjB proj_b_;

        void publishing(int data) {
            cout << "ProjC::publishing: " << data << endl;
        }
};

int main() {
    ProjA proj_a;
    ProjC proj_c;

    std::thread{&ProjA::start, &proj_a}.detach();
    std::thread{&ProjC::start, &proj_c}.detach();

    //proj_a.start();

    //proj_c.start(); 

    this_thread::sleep_for(chrono::seconds(100));

    return 0;
}