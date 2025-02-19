/*
 * @Author: hawrkchen
 * @Date: 2024-10-11 17:23:29
 * @Description: 
 * @FilePath: /omni_server/test/main.cpp
 */
#include "hv/hv.h"
#include "../common/crypto_suite.hpp"
#include "../internal/omni_factory.hpp"
#include "../common/tc_file.hpp"

int main(int argc, char* argv[]) {
    
    std::string out = g_crypto_suite.get_md5_string("hello world");

    printf("md5: %s\n", out.c_str());

    auto task = OmniFactory::createOmniManager(OmniTask::TASK_OTA_QUERY);
    if(task) {
        task->process();
    }

    auto task2 = OmniFactory::createOmniManager(OmniTask::TASK_OTA_UPGRADE);
    if(task2) {
        task2->process();
    }

    // std::string gzip_file = "wget2-latest.tar.gz";
    // std::string ouput_dir = "/data/tmp/";

    // extract_tar_gz(gzip_file, ouput_dir);
    std::string temp_dir = "/data/tmp/wget2-2.2.0";
    TCFile::scan_directory(temp_dir);

    // 解压
    // if(!decompress_gzip(gzip_file, temp_tar_file)) {
    //    std::cout << "解压失败" << std::endl;
    //     return -1;
    // }
    // 解压 tar 
    //extract_tar(temp_tar_file, ouput_dir);
    // 删除临时文件
    //remove(temp_tar_file.c_str());

    std::cout << "解压成功" << std::endl;

    char exe_filepath[MAX_PATH] = {0};
    char run_dir[MAX_PATH] = {0};

    const char* version = hv_compile_version();

    get_executable_path(exe_filepath,sizeof(exe_filepath));
    get_run_dir(run_dir,sizeof(run_dir));

    printf("exefilepath: %s\n", exe_filepath);
    printf("rundir: %s\n", run_dir);
    printf("version: %s\n", version);

    LOGI("version: %s", version);
    return 0;
}
