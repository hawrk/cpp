/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 14:17:45
 * @Description: 
 * @FilePath: /hv_demo/internal/ota/ota_app_manager.cpp
 */


#include "ota_app_manager.hpp"

#include <sys/statvfs.h>
#include <signal.h>
#include <unistd.h>
#include <zlib.h>

#include "../../common/tc_file.hpp"

void OTAAppManager::start() 
{
    // TODO: start OTA app
    // TODO: check if OTA app is already running

    std::string app_path = "/home/hawrk/src/cpp/hv_demo/ota_app";
    std::string app_args = "";
    std::string app_name = "ota_app";

    std::vector<std::string> args = {app_path, app_args};
    std::vector<std::string> env = {};

    std::cout << "Starting OTA app..." << std::endl;
    std::cout << "App path: " << app_path << std::endl;

}

// 系统空间检查
bool OTAAppManager::check_sys_space() 
{
    //TODO:
    // 检查系统空间，当前空间＋500M >＝ 备份容量
    // 默认检查根目录，可根据需要修改
    struct statvfs st;
    if (statvfs("/", &st) != 0) {
        std::cout << "statvfs failed" << std::endl;
        return false;
    }
    long long free_size = st.f_bfree * st.f_frsize;
    long long total_size = st.f_blocks * st.f_frsize;
    long long available = st.f_frsize * st.f_bavail;

    std::cout << "总空间: " << total_size/(1024*1024) << " MB" << std::endl;
    std::cout << "可用空间:" << available/(1024*1024) << " MB" << std::endl;
    std::cout << "剩余空间:" << free_size/(1024*1024) << " MB" << std::endl;

    if (available < 500*1024*1024) {    // 以可用空间为准
        std::cout << "系统空间不足,无法进行OTA更新" << std::endl;
        return false;
    }

    return true;
}

// 备份节点服务
bool OTAAppManager::backup_app_files()
{
    // 1. stop当前程序节点
    // 2. 备份当前程序节点文件

    // 思路： 先解压当前下载的文件到临时目录
    // 然后根据临时目录的文件名，找到当前运行的目录文件名，把该文件名复制到备份目录
    std::string gzip_file = "wget2-latest.tar.gz";
    std::string ouput_dir = "/data/tmp/";

    TCFile::extract_tar_gz(gzip_file, ouput_dir);
    // 解压后，根据文件名，找到当前运行的目录文件名

    
    return true;
}

bool OTAAppManager::stop_app_nodes() 
{   
    if(app_name_.empty()) {
        std::cerr << "App name is empty" << std::endl;
        return false;
    }

    std::string command = "pgrep " + app_name_;
    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe) {
        std::cerr << "popen() failed" << std::endl;
        return false;
    }

    char buffer[128] = {0};
    int pid = -1;
    if(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        pid = atoi(buffer);
    }
    pclose(pipe);

    if(pid == -1) {
        std::cerr << "No app node found" << std::endl;
        return false;
    }

    // 发送终止信号
    if(kill(pid, SIGTERM) != 0) {
        std::cerr << "kill() failed" << std::endl;
        return false;
    }
    // kill -9 pid
    // kil (pid, SIGKILL)

    // TODO：这里或许需要再检查一下pid是否被杀掉了

    std::cout << "stop app node success...." << std::endl;

    return true;
    
}

// 更新节点服务程序
bool OTAAppManager::update_app_nodes()
{
    // 1. 替换当前程序节点文件
    // 2. 启动当前程序节点
    return true;
}

// 重启节点服务并验证
bool OTAAppManager::restart_app_nodes()
{
    // 1. 重启当前程序节点
    // 2. 验证当前程序节点是否正常运行
    return true;
}

// 回滚节点服务程序
void OTAAppManager::rollback_app_files()
{
    // TODO: 停止当前程序节点
    // 2. 找到之前备份的程序节点文件
    // 3. 替换当前程序节点文件
    // 4. 重新当前程序节点
}


