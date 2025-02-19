/*
 * @Author: hawrkchen
 * @Date: 2024-12-04 11:09:37
 * @Description: 
 * @FilePath: /hv_demo/common/curl_lib.hpp
 */
#pragma once

#include <curl/curl.h>

#include <string>
#include <iostream>
#include <fstream>

static const char* UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";

class CurlCallback {
    public:
        virtual void Progress(void* param, double dlTotal, double dlNow) = 0;
};

class CurlCallbackEx: public CurlCallback {
    public:
        virtual void Progress(void* param, double dlTotal, double dlNow) override 
        {
            if(dlTotal == 0.0) return;
            double percent = dlNow / dlTotal * 100;
            std::cout << "Progress: " << percent << "%" << std::endl;
        }
};

enum CurlLibFlag : uint8_t {
    LIBCURL_FLAG_NONE = 0,
    LIBCURL_FLAG_DOWNLOAD = 1,
    LIBCURL_FLAG_POST = 2,
    LIBCURL_FLAG_GET= 3,
};


class CurlLib {
    public:
        CurlLib();
        ~CurlLib();

        bool set_port(int port);
        bool set_timeout(int seconds);
        bool set_connection_timeout(int seconds);
        bool set_user_agent(const std::string& user_agent);
        bool set_resume_from(long long offset);
        bool set_resume_from_large(long long offset);
        bool add_header(const std::string& header_key, const std::string& header_value);
        bool set_cookie(const std::string& cookie);
        bool set_cookie_file(const std::string& file_path);
        const char* get_error() const;

        void set_call_back(CurlCallbackEx* call_back, void* param);
        bool download_to_file(const std::string& url, const std::string& file_path);
        bool post(const std::string& url, const std::string& post_data);
        bool get(const std::string& url);

        const std::string& get_response() const;
        long getDownloadFileLenth(const char* file_path);
        long getLocalFileLenth(const char* file_path);   

        
    protected:
        static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
        static size_t handle_callback(void *contents, size_t size, size_t nmemb, void *userp);
        static int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
        static int curl_debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr);

    private:
        CURL*               curl_handle_;   // curl对象
        CURLcode            curl_code_;
        int                 port_;          // 端口号
        bool                is_resume_from_large_;   // 是否支持大文件断点续传
        FILE*               file_;
        std::string         file_path_;
        std::string         response_;
        CurlLibFlag         flag_;
        curl_slist*         curl_list_;
        void*               curl_call_back_param_;
        CurlCallbackEx*     curl_call_back_;
};