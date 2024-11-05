/*
 * @Author: hawrkchen
 * @Date: 2024-10-30 11:05:47
 * @Description: 
 * @FilePath: /callback/callback_main.cpp
 */

// case 1:直接调用回调函数  ，把回调函数放到map中，根据key调用
#include <iostream>
#include <map>
#include <functional>

using namespace std;

using CallBackT = std::function<int(int, int)>;

// 除法运算类
class Division {
    public:
        int operator()(int a, int b) {
            return a / b;
        }
};

int Multiplication(int a, int b) {
    return a * b;
}

int Subtraction(int a, int b) {
    return a - b;
}   

int RegCallback(CallBackT& callback, int i, int j) {
    return callback(i, j);
}

//int RegCallback2(CallBackT&& callback, int i) {
//    return callback(i);
//}
int main() {
    // 注册回调函数
    auto func1 = [](int a, int b) { return a + b;};
    auto func2 = &Subtraction;
    auto func3 = Multiplication;
    auto func4 = Division();

    map<string, CallBackT> callback_map = {
        {"add", func1},
        {"sub", func2},
        {"mul", func3},
        {"div", func4}
    };

    map<int,string> key_map = {
        {1,"add"},
        {2,"sub"},
        {3,"mul"},
        {4,"div"}
    };

    for(auto& key: key_map) {
        cout << "key: " << key.first << " value: " << RegCallback(callback_map[key.second], 10, 2) << endl;
    }

    return 0;  
}
