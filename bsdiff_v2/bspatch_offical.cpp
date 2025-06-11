/*
 * @Author: hawrkchen
 * @Date: 2025-06-11 09:20:56
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-11 15:14:06
 * @Description: 
 * @FilePath: /bsdiff_v2/bspatch_offical.cpp
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "bsdiff/bspatch.h"
#ifdef __cplusplus
}
#endif

#include <iostream>

int main(int argc,char * argv[])
{

    const char* old_file_path = "old.txt";
    const char* new_file_path = "bspatch_new.txt";
    const char* patch_file_path = "patch.txt";

    int ret = bspatch_file(old_file_path, new_file_path, patch_file_path);

    if(ret!=0)
    {
        std::cout << "bspatch failed" << std::endl;
        return -1;
    }

    std::cout << "bspatch success" << std::endl;

	return 0;
}