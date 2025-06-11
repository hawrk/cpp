/*
 * @Author: hawrkchen
 * @Date: 2025-06-10 14:22:14
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-11 09:18:25
 * @Description: 
 * @FilePath: /bsdiff_v2/bspatch_main.cpp
 */


extern "C" {
    #include "bspatch.h"
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>

static int64_t offtin(uint8_t *buf)
{
	int64_t y;

	y=buf[7]&0x7F;
	y=y*256;y+=buf[6];
	y=y*256;y+=buf[5];
	y=y*256;y+=buf[4];
	y=y*256;y+=buf[3];
	y=y*256;y+=buf[2];
	y=y*256;y+=buf[1];
	y=y*256;y+=buf[0];

	if(buf[7]&0x80) y=-y;

	return y;
}

static int read_patch(const struct bspatch_stream* stream, void* buffer, int length) {
    FILE* fp = (FILE*)stream->opaque;
    return (fread(buffer, 1, length, fp) == (size_t)length) ? 0 : -1;
}

int bspatch_file(const std::string& old_file_path, const std::string& new_file_path, const std::string& patch_file_path) {
    // 读取旧文件
    std::ifstream old_file(old_file_path, std::ios::binary|std::ios::ate);
    if(!old_file) {
        std::cerr << "open old file failed: " << old_file_path << std::endl;
        return -1;
    }
    std::streamsize old_file_size = old_file.tellg();
    old_file.seekg(0, std::ios::beg);
    std::vector<uint8_t> old_data(old_file_size);
    if(!old_file.read((char*)old_data.data(), old_file_size)) {
        std::cerr << "read old file failed: " << old_file_path << std::endl;
        return -1;
    }
    std::cout << "old file size:" << old_file_size << std::endl;
    // 打开补丁文件
    FILE* patch_fp = fopen(patch_file_path.c_str(), "rb");
    if(!patch_fp) {
        std::cerr << "open patch file failed: " << patch_file_path << std::endl;
        return -1;
    }
    // 读取补丁头部
    uint8_t header[24];
    if (fread(header, 1, 24, patch_fp) != 24) {
        if(feof(patch_fp)) {
            std::cerr << "patch file is too small: " << patch_file_path << std::endl;
            fclose(patch_fp);
            return -1;
        }
        std::cerr << "read patch header failed: " << patch_file_path << std::endl;
        fclose(patch_fp);
        return -1;
    }
    // 检查magic
    if (memcmp(header, "ENDSLEY/BSDIFF43", 16) != 0) {
        std::cerr << "patch magic error: " << patch_file_path << std::endl;
        fclose(patch_fp);
        return -1;
    }
    int64_t new_file_size = offtin(header + 16);

    // 回到补丁头部
    fseek(patch_fp, 0, SEEK_SET);
    // 读取补丁
    std::vector<uint8_t> new_data(new_file_size);
    // 构造 stream
    bspatch_stream stream;
    stream.opaque = patch_fp;
    stream.read = read_patch;

    int ret = bspatch(old_data.data(), old_file_size,
        new_data.data(), new_file_size, &stream);

    fclose(patch_fp);
    if(ret != 0) {
        std::cerr << "bspatch failed: " << patch_file_path << std::endl;
        return -1;
    }
    // 写入新文件
    std::ofstream new_file(new_file_path, std::ios::binary);
    if(!new_file) {
        std::cerr << "open new file failed: " << new_file_path << std::endl;
        return -1;
    }
    if(!new_file.write((char*)new_data.data(), new_file_size)) {
        std::cerr << "write new file failed: " << new_file_path << std::endl;
        return -1;
    }
    std::cout << "还原成功" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    
    const char* old_file_path = "old.txt";
    const char* new_file_path = "bspatch_new.txt";
    const char* patch_file_path = "patch.txt";

    int ret = bspatch_file(old_file_path, new_file_path, patch_file_path);
    if(ret != 0) {
        std::cerr << "Failed to generate patch" << std::endl;
        return -1;
    }
    return 0;
}
