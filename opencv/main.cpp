/*
 * @Author: hawrkchen hawrk2012@163.com
 * @Date: 2024-09-06 10:44:18
 * @LastEditors: hawrkchen hawrk2012@163.com
 * @LastEditTime: 2024-10-12 14:58:08
 * @FilePath: /opencv/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>

#include <opencv4/opencv2/opencv.hpp>



int main(int argc,char* argv[]) {
    (void)argc;
    (void)argv;
    cv::Mat image = cv::imread("/home/byd/pic/cat.jpg");
    if(image.empty()) {
        std::cout <<"read image fail..." << std::endl;
        return -1;
    }
    cv::Mat dest;
    //cv::cvtColor(image, dest, cv::COLOR_BGR2GRAY);   // 彩色变黑白
    //cv::GaussianBlur(image,dest,cv::Size(7,7),0,0);  // 图像模糊化, 最大在7值
    // 写一个canny算法
    cv::Canny(image,dest,100,200);  // 边缘检测, 100为低阈值, 200为高阈值 
    
    cv::imshow("teset", dest);
    //cv::imshow("src", image);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}
