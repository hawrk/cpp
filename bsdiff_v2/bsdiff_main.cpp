/*
 * @Author: hawrkchen
 * @Date: 2025-06-10 11:10:20
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-10 16:56:52
 * @Description: 
 * @FilePath: /bsdiff_v2/bsdiff_main.cpp
 */
extern "C" {
    #include "bsdiff.h"
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

static int write_patch(struct bsdiff_stream* stream, const void* buffer, int size) {
    FILE* fp = (FILE*)stream->opaque;
    return (fwrite(buffer, 1, size, fp) == size)? 0 : -1;
}

static void* cus_malloc(size_t size) {
    return malloc(size);
}

static void cus_free(void* ptr) {
    free(ptr);
}

int bsdiff_file(const std::string& oldfile, const std::string& newfile, const std::string& patchfile) {
    // 读取旧文件
    std::ifstream ofile(oldfile, std::ios::binary|std::ios::ate);
    if(!ofile) {
        std::cerr << "Failed to open old file: " << oldfile << std::endl;
        return -1;
    }

    std::streamsize oldsize = ofile.tellg();
    ofile.seekg(0, std::ios::beg);
    std::vector<uint8_t> olddata(oldsize);
    if(!ofile.read((char*)olddata.data(), oldsize)) {
        std::cerr << "Failed to read old file: " << oldfile << std::endl;
        return -1;
    }
    std::cout << "Read old file size: " << oldsize << std::endl;
    // 读取新文件
    std::ifstream nfile(newfile, std::ios::binary|std::ios::ate);
    if(!nfile) {
        std::cerr << "Failed to open new file: " << newfile << std::endl;
        return -1;
    }

    std::streamsize newsize = nfile.tellg();
    nfile.seekg(0, std::ios::beg);
    std::vector<uint8_t> newdata(newsize);
    if(!nfile.read((char*)newdata.data(), newsize)) {
        std::cerr << "Failed to read new file: " << newfile << std::endl;
        return -1;
    }
    std::cout << "Read new file size: " << newsize << std::endl;
    //打开补丁输出文件
    FILE* patch_fp = fopen(patchfile.c_str(), "wb");
    if(!patch_fp) {
        std::cerr << "Failed to open patch file: " << patchfile << std::endl;
        return -1;
    }

    // 设置bsdiff_stream结构体
    bsdiff_stream stream;
    stream.opaque = patch_fp;
    stream.malloc = cus_malloc;
    stream.free = cus_free;
    stream.write = write_patch;

    int ret = bsdiff(olddata.data(), oldsize, newdata.data(), newsize, &stream);
    if(ret != 0) {
        std::cerr << "Failed to generate patch" << std::endl;
        fclose(patch_fp);
        return -1;
    }
    fclose(patch_fp);

    std::cout << "patch file size:" << patchfile.size() << std::endl;
    std::cout << "Generate patch file: " << patchfile << std::endl;
    return 0;
}
    

int main(int argc, char* argv[]) {

    const char* old_file_path = "old.txt";
    const char* new_file_path = "new.txt";
    const char* patch_file_path = "patch.txt";

    int ret = bsdiff_file(old_file_path, new_file_path, patch_file_path);
    if(ret != 0) {
        std::cerr << "Failed to generate patch" << std::endl;
        return -1;
    }
    return 0;
}

