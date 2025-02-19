/*
 * @Author: hawrkchen
 * @Date: 2024-12-05 14:33:05
 * @Description: 
 * @FilePath: /hv_demo/test/test_curl_lib.cpp
 */
#include "../common/curl_lib.hpp"

static const char* url = "https://ftp.gnu.org/gnu/wget/wget2-latest.tar.gz";


void PostTest()
{
	CurlLib libcurl;
	libcurl.set_user_agent(UserAgent);
	libcurl.set_port(80);
	libcurl.set_connection_timeout(2);
	libcurl.add_header("name", "Jelin");
	libcurl.add_header("sex", "man");
	libcurl.set_cookie_file("c:\\cookie");
	std::string pData = "maintype=10001&subtype=100&appver=2.5.19.3753&sysver=Microsoft Windows 7&applist=100:15,200:2&sign=2553d888bc922275eca2fc539a5f0c1b";
	libcurl.post("http://interface.***********.com/v2/stat/index/jingpin", pData);
	std::string strRet = libcurl.get_response();
	std::cout	<< strRet << std::endl;
 
}
 
void GetTest()
{
	CurlLib libcurl;
	libcurl.set_user_agent(UserAgent);
	libcurl.get("https://www.baidu.com");
	const std::string& pHtml = libcurl.get_response();
	const char* pError = libcurl.get_error();
	std::cout << pHtml << std::endl;
	std::cout << pError << std::endl;
}

void DownloadTest()
{
	const char* pUrl = "http://download.*******.com/software/1.2.3.3639/32//Package";
	CurlLib libcurl;
	CurlCallbackEx cb;
	libcurl.set_user_agent(UserAgent);
	libcurl.set_connection_timeout(2);
	libcurl.set_resume_from(2);
	libcurl.set_call_back(&cb, NULL);
	libcurl.download_to_file(pUrl, "c:\\test.zip");
}

void DownloadFileTest() 
{
	CurlLib cul;
    CurlCallbackEx cbex;
    cul.set_user_agent(UserAgent);
    //cul.set_resume_from(2);
    cul.set_timeout(60);
    cul.set_connection_timeout(10);
    cul.set_call_back(&cbex, nullptr);

    cul.download_to_file(url, "/home/hawrk/src/cpp/libcurl/build/wget2-latest.tar.gz");

}


int main() {
	DownloadFileTest();
    return 0;
}