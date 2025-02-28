/*
 * @Author: hawrkchen
 * @Date: 2025-02-28 14:00:01
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-02-28 16:07:21
 * @Description: 
 * @FilePath: /usb_detect/main.cpp
 */

#include <iostream>
#include <libudev.h>
#include <string>

void print_device_attributes(struct udev_device* dev) {
    const char* syspath = udev_device_get_syspath(dev);
    if (syspath) {
        std::cout << "syspath: " << syspath << std::endl;
    }

    struct udev_list_entry* entry;

    // 打印设备属性
    entry = udev_device_get_properties_list_entry(dev);
    if (entry) {
        std::cout << "Properties:" << std::endl;
        while (entry) {
            const char* key = udev_list_entry_get_name(entry);
            const char* value = udev_list_entry_get_value(entry);
            if (key && value) {
                std::cout << key << ": " << value << std::endl;
            }
            entry = udev_list_entry_get_next(entry);
        }
    }

}


int main(int argc, char* argv[]) {

    struct udev* udev;
    struct udev_monitor* mon;

    // 创建udev对象
    udev = udev_new();
    if (!udev) {
        std::cerr << "Can't create udev object\n";
        return 1;
    }

    // 创建udev监视器
    mon = udev_monitor_new_from_netlink(udev, "udev");
    if (!mon) {
        std::cerr << "Can't create udev monitor\n";
        udev_unref(udev);
        return 1;
    }

    // 过滤usb设备事件
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");

    // 开启udev监视器
    if (udev_monitor_enable_receiving(mon) < 0) {
        std::cerr << "Can't enable udev monitor\n";
        udev_monitor_unref(mon);    
        udev_unref(udev);
        return 1;
    }

    // 创建文件描述符
    int fd = udev_monitor_get_fd(mon);

    // 循环等待设备插入
    while (true) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        
        std::cout << "Waiting for USB device..." << std::endl;
        int ret = select(fd + 1, &fds, NULL, NULL, NULL);
        if(ret >  0 && FD_ISSET(fd, &fds)) {
            // 设备插入事件发生
            struct udev_device* dev = udev_monitor_receive_device(mon);
            if (dev) {
                const char* action = udev_device_get_action(dev);
                if (action) {
                    std::string action_str(action);
                    if (action_str == "add") {
                        const char* syspath = udev_device_get_syspath(dev);
                        if (syspath) {
                            std::cout << "USB device inserted: " << syspath << std::endl;
                        }
                    } else if(action_str == "remove") {
                        const char* syspath = udev_device_get_syspath(dev);
                        if (syspath) {
                            std::cout << "USB device removed: " << syspath << std::endl;
                        }
                    }

                    // 打印设备属性
                    print_device_attributes(dev);
                    
                    udev_device_unref(dev);
                }
            }
        }
    }

    // 释放udev监视器
    udev_monitor_unref(mon);
    // 释放udev对象
    udev_unref(udev);
    std::cout << "Exiting..." << std::endl;
    return 0;
    
}