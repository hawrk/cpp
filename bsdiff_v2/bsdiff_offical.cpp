/*
 * @Author: hawrkchen
 * @Date: 2025-06-11 09:50:46
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-13 13:50:38
 * @Description: 
 * @FilePath: /bsdiff_v2/bsdiff_offical.cpp
 */
#include <sys/types.h>

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#include "bsdiff/bsdiff.h"
#ifdef __cplusplus
}
#endif

int main(int argc,char *argv[])
{

    const char* old_file_path = "old.txt";
    const char* new_file_path = "new.txt";
    const char* patch_file_path = "patch.txt";

    int ret = bsdiff_file(old_file_path, new_file_path, patch_file_path);

    if(ret!=0)
    {
        std::cout << "bsdiff failed" << std::endl;
        return -1;
    }

    std::cout << "bsdiff success" << std::endl;

    return 0;
}