
#include "../common/thead_pool_complex.hpp"

#include <iostream>
#include <chrono>

void func1(int slp) {
    std::cout << "in thread:" << std::this_thread::get_id() << ",func1 get val: " << slp << std::endl;

}

struct gfun{
    int operator()(int n) {
        std::cout << "gfun  in thread:" << std::this_thread::get_id() << std::endl;
        std::cout << "gfun  input for " << n << " param" << std::endl;
        return n * 2;
    }
};

class FireFly {
    public:
        static int Afun(int n =0) {
            std::cout << "Afun  in thread:" << std::this_thread::get_id() << std::endl;
            std::cout << "Afun  input for " << n << " param" << std::endl;
            return n * 3;
        }

        static std::string Bfun(int n , std::string s, char c) {
            std::cout << "Bfun  in thread:" << std::this_thread::get_id() << std::endl;
            std::cout << "Bfun  input for " << n << " param" << std::endl;
            std::cout << "Bfun  input for " << s << " param" << std::endl;
            std::cout << "Bfun  input for " << c << " param" << std::endl;
            return s + std::to_string(n) + c;
        }
};


int main(int argc, char* argv[])   
{
    ThreadPoolComplex executor{8};
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    //std::cout << "sleeping for 10 seconds=======================" << std::endl;

    //FireFly ff;

    std::future<void> fa = executor.addTask(func1, 1);
    std::future<int> fg = executor.addTask(gfun(), 10);
    std::future<int> fa2 = executor.addTask(FireFly::Afun, 99);
    std::future<std::string> fb = executor.addTask(FireFly::Bfun, 100, "hello", 'c');

    std::future<std::string> fh = executor.addTask([]() -> std::string{
        std::cout << "fh  in thread:" << std::this_thread::get_id() << std::endl;
        return "hello fh ret";
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "sleeping for 2 seconds=======================" << std::endl;

    for(int i = 0; i < 10; i++) {
        executor.addTask(func1, i*100);
    }

    fa.get();

    std::cout << "get fa get:" << fg.get() << std::endl;

    std::cout << "get fa2 get:" << fa2.get() << std::endl;

    std::cout << "get fb get:" << fb.get() << std::endl;

    std::cout << "get fh get:" << fh.get() << std::endl;

    return 0;

}