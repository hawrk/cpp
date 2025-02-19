/*
 * @Author: hawrkchen
 * @Date: 2024-12-04 11:09:43
 * @Description: 
 * @FilePath: /hv_demo/common/curl_lib.cpp
 */
#include "curl_lib.hpp"



CurlLib::CurlLib():
    curl_handle_(nullptr)
    ,port_(0)
    ,is_resume_from_large_(false)
    ,file_(nullptr)
    ,curl_list_(nullptr)
{
    std::cout << "CurlLib created" << std::endl;

    curl_handle_ = curl_easy_init();
}


CurlLib::~CurlLib() {
    curl_easy_cleanup(curl_handle_);
    if(file_ != nullptr) {
        fclose(file_);
    }
    if(curl_list_!= nullptr) {
        curl_slist_free_all(curl_list_);
        curl_list_ = nullptr;
    }
    std::cout << "CurlLib destroyed" << std::endl;
}

bool CurlLib::set_port(int port) 
{
    if(port < 1 || port > 65535) return false;

    port_ = port;
    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_PORT, port_);
    return CURLE_OK == curl_code_;
}

bool CurlLib::set_timeout(int seconds)
{
    if(seconds < 1) return false;
    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_TIMEOUT, seconds);
    return CURLE_OK == curl_code_;
}


bool CurlLib::set_connection_timeout(int seconds)
{
    if(seconds < 1) return false;
    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_CONNECTTIMEOUT, seconds);
    return CURLE_OK == curl_code_;
}


bool CurlLib::set_user_agent(const std::string& user_agent)
{
    if(user_agent.empty()) {
        curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_USERAGENT, UserAgent);
        return CURLE_OK == curl_code_;
    }

    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_USERAGENT, user_agent.c_str());
    return CURLE_OK == curl_code_;
}

bool CurlLib::set_resume_from(long long offset)
{
    if(offset < 0) return false;

    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_RESUME_FROM, offset);
    return CURLE_OK == curl_code_;
}

bool CurlLib::set_resume_from_large(long long offset)
{
    if(offset < 0) return false;
    
    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_RESUME_FROM_LARGE, offset);
    return CURLE_OK == curl_code_;
}

bool CurlLib::add_header(const std::string& header_key, const std::string& header_value)
{
    if(header_key.empty() && header_value.empty()) return false;

    std::string header = header_key + ": " + header_value;
    curl_list_ = curl_slist_append(curl_list_, header.c_str());
    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_HTTPHEADER, curl_list_);
    return CURLE_OK == curl_code_;
}


bool CurlLib::set_cookie(const std::string& cookie)
{
    if(cookie.empty()) return false;

    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_COOKIE, cookie.c_str());
    return CURLE_OK == curl_code_;
}


bool CurlLib::set_cookie_file(const std::string& file_path)
{
    if(file_path.empty()) return false;

    curl_code_ = curl_easy_setopt(curl_handle_, CURLOPT_COOKIEFILE, file_path.c_str());
    return CURLE_OK == curl_code_;
}

const char* CurlLib::get_error() const
{
    return curl_easy_strerror(curl_code_);
}

void CurlLib::set_call_back(CurlCallbackEx* call_back, void* param)
{
    curl_call_back_ = call_back;
    curl_call_back_param_ = param;
}

long CurlLib::getDownloadFileLenth(const char* url) 
{
    long downloadFileLenth = 0; 
    curl_easy_setopt(curl_handle_, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle_, CURLOPT_HEADER, 1);    //只需要header头
    curl_easy_setopt(curl_handle_, CURLOPT_NOBODY, 1);    //不需要body 

    if (curl_easy_perform(curl_handle_) == CURLE_OK) {  
        curl_easy_getinfo(curl_handle_, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloadFileLenth);  
    } else {  
        downloadFileLenth = -1;  
    }  
    return downloadFileLenth; 
}

long CurlLib::getLocalFileLenth(const char* file_path)
{
    if(!is_resume_from_large_) return 0;
    // TODO: 获取本地文件长度
    file_ = fopen(file_path, "rb");
    if(file_ == nullptr) {
        return 0;
    }
    fseek(file_, 0, SEEK_END);
    long long length = ftell(file_);
    fclose(file_);
    return length;
}

bool CurlLib::download_to_file(const std::string& url, const std::string& file_path)
{

    remove(file_path.c_str());

    curl_easy_setopt(curl_handle_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, write_callback);   // 大文件下载会多次调用
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, this);


    curl_easy_setopt(curl_handle_, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl_handle_, CURLOPT_PROGRESSFUNCTION, progress_callback);
    curl_easy_setopt(curl_handle_, CURLOPT_PROGRESSDATA, this);

    curl_easy_setopt(curl_handle_, CURLOPT_RESUME_FROM_LARGE, getLocalFileLenth(file_path.c_str()));    
    file_path_  = file_path;
    flag_ = CurlLibFlag::LIBCURL_FLAG_DOWNLOAD;
    curl_code_ = curl_easy_perform(curl_handle_);
    is_resume_from_large_ = true;
    if(curl_code_ != CURLE_OK) {
        is_resume_from_large_ = false;
        std::cout << "curl_easy_perform error:" << curl_easy_strerror(curl_code_) << std::endl;
    }
    return CURLE_OK == curl_code_;
}

bool CurlLib::post(const std::string& url, const std::string& post_data)
{
    if(post_data.empty()) return false;

    curl_easy_setopt(curl_handle_, CURLOPT_POST, 1);
    curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDSIZE, post_data.size());
    curl_easy_setopt(curl_handle_, CURLOPT_URL, url.c_str());

    flag_ = CurlLibFlag::LIBCURL_FLAG_POST;
    response_.clear();
    curl_code_ = curl_easy_perform(curl_handle_);
    return CURLE_OK == curl_code_;
    
}


bool CurlLib::get(const std::string& url)
{
    if(url.empty()) return false;

    curl_easy_setopt(curl_handle_, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl_handle_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl_handle_, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl_handle_, CURLOPT_SSL_VERIFYHOST, 0);

    flag_ = CurlLibFlag::LIBCURL_FLAG_GET;
    response_.clear();
    curl_code_ = curl_easy_perform(curl_handle_);
    return CURLE_OK == curl_code_;
}

const std::string& CurlLib::get_response() const 
{
    return response_;
}

size_t CurlLib::write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    CurlLib *curl_lib =(CurlLib*)userp;
    unsigned long written = 0;
    switch(curl_lib->flag_) {
        case CurlLibFlag::LIBCURL_FLAG_DOWNLOAD:
            curl_lib->file_ = fopen(curl_lib->file_path_.c_str(), "ab+");
            if(curl_lib->file_ == nullptr) {
                return 0;
            }
            written = fwrite(contents, size, nmemb, curl_lib->file_);         
            break;
        case CurlLibFlag::LIBCURL_FLAG_POST:
        case CurlLibFlag::LIBCURL_FLAG_GET:
            curl_lib->response_.append(static_cast<char*>(contents), size * nmemb);
            written = size * nmemb;
            break;
        case CurlLibFlag::LIBCURL_FLAG_NONE:
            break;
        default:
            break;
    }

    return written;

}

size_t CurlLib::handle_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    CurlLib *curl_lib = static_cast<CurlLib*>(userp);
    if(curl_lib == nullptr) {
        return -1;
    }
    return 0;
}

int CurlLib::progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
    CurlLib *curl_lib = (CurlLib*)clientp;
    if(curl_lib->curl_call_back_!= nullptr) {
        curl_lib->curl_call_back_->Progress((void*)curl_lib->curl_call_back_param_, dltotal, dlnow);
    }
    return 0;
}

int CurlLib::curl_debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr) {
    return 0;
}