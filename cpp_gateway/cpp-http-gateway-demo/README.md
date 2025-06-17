# cpp-http-gateway-demo

这是一个简单的C++ HTTP网关示例，支持处理JSON请求。

## 项目结构

```
cpp-http-gateway-demo
├── src
│   ├── main.cpp          # 应用程序入口点
│   ├── gateway.cpp       # Gateway类实现
│   ├── gateway.h         # Gateway类声明
│   └── utils
│       ├── json_parser.cpp  # JsonParser类实现
│       └── json_parser.h    # JsonParser类声明
├── CMakeLists.txt        # CMake构建配置
├── README.md              # 项目文档
└── .gitignore             # 版本控制忽略文件
```

## 构建项目

1. 确保已安装CMake和C++编译器。
2. 在项目根目录下创建构建目录并进入该目录：

   ```bash
   mkdir build
   cd build
   ```

3. 运行CMake以生成构建文件：

   ```bash
   cmake ..
   ```

4. 编译项目：

   ```bash
   make
   ```

## 运行应用程序

在构建目录中，运行生成的可执行文件：

```bash
./cpp-http-gateway-demo
```

## 使用示例

发送HTTP POST请求到`http://localhost:8080/`，请求体为JSON格式，例如：

```json
{
    "key": "value"
}
```

应用程序将解析请求并返回相应的JSON数据。

## 贡献

欢迎提交问题和拉取请求！