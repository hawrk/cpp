/*
 * @Author: hawrkchen
 * @Date: 2024-10-30 11:23:26
 * @Description: 
 * @FilePath: /callback/callback2_main.cpp
 */

// case 2 多个类之间的回调

#include <iostream>
#include <functional>

using CallbackType = std::function<void(std::string&)>;

class A {
    public:
        A(): callback_(nullptr), message_("default message") {}
        ~A() {}

        // 注册回调函数
        void setCallback(CallbackType callback) {
            callback_ = callback;
        }

        void run() {
            if (callback_) {
                callback_(message_);
            }
        }
    
    private:
        CallbackType callback_;
        std::string message_;

};


class B {
    public:
        B(): a_(nullptr) {
            a_ = new A();
        }

        ~B() {
            if(a_) {
                delete a_;
            }
        }

        void MyFunc(std::string& message) {
            std::cout << "B::MyFunc: " << message << std::endl;
        }

        void RegCallback() {
            a_->setCallback(std::bind(&B::MyFunc, this, std::placeholders::_1));
        }

        void Run() {
            a_->run();
        }
            
    private:
        A *a_;
};


int main() {
    B b;
    b.RegCallback();
    b.Run();
    return 0;
}