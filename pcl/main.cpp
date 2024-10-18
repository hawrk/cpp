/*
 * @Author: hawrkchen hawrk2012@163.com
 * @Date: 2024-10-15 12:01:39
 * @LastEditors: hawrkchen hawrk2012@163.com
 * @LastEditTime: 2024-10-15 14:06:30
 * @FilePath: /pcl/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/common/common_headers.h>  
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>



int main(int argc, char** argv) {
    std::cout << "Hello, PCL!" << std::endl;    

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
    uint8_t hr(255),hg(15),hb(15);

    for(float z(-1.0); z<=1.0; z+=0.05) {
        for(float angle(0.0); angle<=360; angle+=5.0) {
            pcl::PointXYZRGB point;
            point.x = 0.5*cosf(pcl::deg2rad(angle));
            point.y = sinf(pcl::deg2rad(angle));
            point.z = z;

            uint32_t rgb = ((uint32_t)hr << 16 | (uint32_t)hg << 8 | (uint32_t)hb);
            point.rgb = *reinterpret_cast<float*>(&rgb);
            point_cloud_ptr->points.push_back(point);
        }
        if(z < 0.0) {
            hr -= 12;
            hg += 12;
        } else {
            hg -= 12;
            hb += 12;
        }
    }

    point_cloud_ptr->width = point_cloud_ptr->points.size();
    point_cloud_ptr->height = 1;

    pcl::visualization::PCLVisualizer::Ptr RGBViewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(point_cloud_ptr);
    RGBViewer->setBackgroundColor(0, 0, 0);
    RGBViewer->addPointCloud<pcl::PointXYZRGB>(point_cloud_ptr, rgb, "sample cloud");
    RGBViewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    RGBViewer->addCoordinateSystem(1.0);
    RGBViewer->initCameraParameters();

    while (!RGBViewer->wasStopped()) {
        RGBViewer->spin();
    }

    RGBViewer->close();

    return 0;
}