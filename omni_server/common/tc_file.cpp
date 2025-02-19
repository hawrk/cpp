/*
 * @Author: hawrkchen
 * @Date: 2024-12-10 14:48:52
 * @Description: 
 * @FilePath: /hv_demo/common/tc_file.cpp
 */

#include "tc_file.hpp"


bool TCFile::decompress_gzip(const std::string& gzip_file, const std::string& output_file)
{
    gzFile inFile = gzopen(gzip_file.c_str(), "rb");
    if(!inFile) {
        std::cerr << "Failed to open file: " << gzip_file << std::endl;
        return false;
    }

    FILE* outFile = fopen(output_file.c_str(), "wb");
    if(!outFile) {
        std::cerr << "Failed to create file: " << output_file << std::endl;
        gzclose(inFile);
        return false;
    }

    char buffer[4096];
    int bytes_read;
    while((bytes_read = gzread(inFile, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, outFile);
    }

    gzclose(inFile);
    fclose(outFile);

    return true;
}

// TODO: 未调试通过
void TCFile::extract_tar(const std::string& tar_file, const std::string& output_dir)
{
    FILE* file = fopen(tar_file.c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file: " << tar_file << std::endl;
        return;
    }

    char buffer[512];
    while(fread(buffer, 1, sizeof(buffer), file) == sizeof(buffer)) {
        posix_header* header = (struct posix_header*)buffer;
        /*
        posix_header* header = (posix_header*)buffer;
        std::cout << "Name: " << header->name << std::endl;
        std::cout << "Mode: " << header->mode << std::endl;
        std::cout << "UID: " << header->uid << std::endl;
        std::cout << "GID: " << header->gid << std::endl;
        std::cout << "Size: " << header->size << std::endl;
        std::cout << "MTime: " << header->mtime << std::endl;
        std::cout << "Checksum: " << header->checksum << std::endl;
        std::cout << "Typeflag: " << header->typeflag << std::endl;
        std::cout << "Linkname: " << header->linkname << std::endl;
        std::cout << "Magic: " << header->magic << std::endl;
        std::cout << "Version: " << header->version << std::endl;
        std::cout << "Uname: " << header->uname << std::endl;
        std::cout << "Gname: " << header->gname << std::endl;
        std::cout << "Devmajor: " << header->devmajor << std::endl;
        std::cout << "Devminor: " << header->devminor << std::endl;
        std::cout << "Prefix: " << header->prefix << std::endl;
        */
        //if(std::filesystem::exists(tar_file)) {
            //std::cout << "file:" << tar_file << " exists" << std::endl;
        std::cout << "size:" << std::filesystem::file_size(tar_file) << std::endl;
        //}
        // 计算文件大小
        //int size = strtol(header->size, nullptr, 8);
        int size = std::filesystem::file_size(tar_file);
        if(size == 0) {
            std::cout << "End of archive" << std::endl;
            break;
        }
        std::string file_name(header->name);
        std::string full_path = output_dir + "/" + file_name;
        std::cout << "Extracting " << file_name << ", to full_path" << full_path <<std::endl;
        // 创建目录
        if(header->typeflag == '0' || header->typeflag == '\0') {  // 普通文件
            FILE* outFile = fopen(full_path.c_str(), "wb");
            if(outFile) {
              char* file_buffer = new char[size];
              size_t bytes_read = fread(file_buffer, 1, size, file);
              (void)bytes_read;
              size_t bytes_write = fwrite(file_buffer, 1, size, outFile);
              (void)bytes_write;
              delete[] file_buffer;
              fclose(outFile);
            } else {
                std::cerr << "Failed to create file: " << full_path << std::endl;
            }
        } else if(header->typeflag == '5') {   // 目录
            mkdir(full_path.c_str(), 0755);
        }
        //std::cout << "step 1" << std::endl;
        fseek(file, (size+511)/512*512, SEEK_CUR);
    }
        
    fclose(file);
}


// 依赖 libz, libarchive 库
/*
* @param gz_filename: .tar.gz压缩文件名
* @param output_dir: 解压输出目录
* @return: 无
*/
void TCFile::extract_tar_gz(const std::string& gz_filename, const std::string& output_dir)
{
    gzFile gz_file = gzopen(gz_filename.c_str(), "rb");
    if (!gz_file) {
        std::cerr << "Failed to open file: " << gz_filename << std::endl;
        return;
    }
    // 创建临时文件
    const char  *tmp_tar_filename = "tmp.tar";
    FILE* tmp_tar_file = fopen(tmp_tar_filename, "wb");
    if (!tmp_tar_file) {
        std::cerr << "Failed to create file: " << tmp_tar_filename << std::endl;
        gzclose(gz_file);
        return;
    }
    // 解压到tar临时文件
    char buffer[8192];
    int bytes_read;
    while((bytes_read = gzread(gz_file, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, tmp_tar_file);    
    }
    fclose(tmp_tar_file);
    gzclose(gz_file);

    // 解压tar文件
    struct archive* a = archive_read_new();
    struct archive* ext = archive_write_disk_new();
    archive_read_support_format_tar(a);

    //archive_read_support_compression_gzip(a);
    //archive_read_support_compression_all(a);

    if(archive_read_open_filename(a, tmp_tar_filename, 10240)!= ARCHIVE_OK) {
        std::cerr << "Failed to open tar file: " << tmp_tar_filename << std::endl;
        archive_read_free(a);
        return;
    }

    archive_entry* entry;
    while(archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* currnet_file = archive_entry_pathname(entry);
        //std::cout << "Extracting " << currnet_file << std::endl;
        std::string full_path = output_dir + "/" + currnet_file;

        archive_entry_set_pathname(entry, full_path.c_str());
        archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME);
        if(archive_write_header(ext, entry) != ARCHIVE_OK) {
            std::cerr << "Failed to write header for file: " << currnet_file << std::endl;
        } else {
            archive_write_finish_entry(ext);
        }
    }

    archive_write_close(ext);
    archive_write_free(ext);

    archive_read_close(a);
    archive_read_free(a);

    // 删除临时文件
    remove(tmp_tar_filename);
}

void TCFile::scan_directory(const std::string& dir_path) 
{
    for(const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        if(entry.is_directory()) {
            std::cout << "Directory: " << entry.path() << std::endl;
        } else if(entry.is_regular_file()) {
            std::cout << "File: " << entry.path() << std::endl;
        }
    }
}

void TCFile::copy_file(const std::string& src_file, const std::string& dst_file) 
{
    std::filesystem::copy(src_file, dst_file, std::filesystem::copy_options::overwrite_existing);
}

void TCFile::copy_directory(const std::string& src_dir, const std::string& dst_dir) 
{
    std::filesystem::copy(src_dir, dst_dir, std::filesystem::copy_options::recursive|
        std::filesystem::copy_options::overwrite_existing);
}