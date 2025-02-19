/*
 * @Author: hawrkchen
 * @Date: 2024-12-10 09:25:22
 * @Description: 
 * @FilePath: /hv_demo/common/tc_file.hpp
 */
#pragma once

#include <sys/stat.h>
#include <string>
#include <iostream>
#include <fstream>  
#include "unistd.h"
#include "zlib.h"
#include <filesystem>

#include <archive.h>
#include <archive_entry.h>


struct posix_header {
    char name[100];         // 文件名
    char mode[8];          // 文件权限
    char uid[8];           // 用户ID
    char gid[8];           // 组ID
    char size[12];         // 文件大小
    char mtime[12];        // 修改时间
    char checksum[8];      // 校验和
    char typeflag;         // 文件类型
    char linkname[100];    // 链接名
    char magic[6];         // 魔术数字
    char version[2];       // 版本
    char uname[32];        // 用户名
    char gname[32];        // 组名
    char devmajor[8];      // 主设备号
    char devminor[8];      // 次设备号
    char prefix[155];      // 前缀
};

class TCFile {
    public: 
        TCFile() = default;
        ~TCFile() = default;

        static bool decompress_gzip(const std::string& gzip_file, const std::string& output_file);

        // TODO: 未调试通过
        static void extract_tar(const std::string& tar_file, const std::string& output_dir);


        // 依赖 libz, libarchive 库
        /*
        * @param gz_filename: .tar.gz压缩文件名
        * @param output_dir: 解压输出目录
        * @return: 无
        */
        static void extract_tar_gz(const std::string& gz_filename, const std::string& output_dir);


        /*
        *@param dir_path: 待扫描目录路径
        *@return: 无
        */
        static void scan_directory(const std::string& dir_path); 

        /*
        *@param src_file: 源文件路径
        *@param dst_file: 目标文件路径
        *@return: 无
        */
        static void copy_file(const std::string& src_file, const std::string& dst_file); 


        /*
        *@param src_dir: 源目录路径
        *@param dst_dir: 目标目录路径
        *@return: 无
        */
        static void copy_directory(const std::string& src_dir, const std::string& dst_dir);
};
