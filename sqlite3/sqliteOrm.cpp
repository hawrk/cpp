/*
 * @Author: hawrkchen
 * @Date: 2024-11-08 10:38:19
 * @Description: 
 * @FilePath: /sqlite3/sqliteOrm.cpp
 */
#include "header.hpp"
#include <iostream>

using namespace sqlite_orm;

int main(int argc, char* argv[])    
{
    auto storage = init_storage();
    storage.sync_schema();

    std::cout << "======== select * from tb_robot; ============ " << std::endl;
    auto robots = storage.get_all<Robot>();
    std::cout << "Total robots: " << robots.size() << std::endl;
    for(const auto &robot : robots)
    {
        std::cout << "robotId:" << robot.id << " ---" << "robotName:" << robot.name <<std::endl;
    }

    // 查询id 为3 的数据
    std::cout << "============select * from tb_robot where id = 3=================" << std::endl;
    auto robot = storage.get<Robot>(3);
    std::cout << "robotId:" << robot.id << " " << std::endl;
    std::cout << "robotName:" << robot.name << std::endl;

    // 查询name 为"diga"的数据  
    std::cout << "=========select * from tb_robot where name = 'diga'==============" << std::endl;
    auto robots2 = storage.get_all<Robot>(where(c(&Robot::name) == "diga"));
    std::cout << "Total robots2: " << robots2.size() << std::endl;
    for(const auto &robot : robots2)
    {
        std::cout << "robotId:" << robot.id << " " << "robotName:" << robot.name << std::endl;
    }
    //也可以这样查询
    std::cout << "======select id, name from tb_robot where name = 'gaiya'=============" << std::endl;
    auto robots3 = storage.select(columns(&Robot::id, &Robot::name), where(c(&Robot::name) == "gaiya"));
    std::cout << "Total robots3: " << robots3.size() << std::endl;
    for(const auto &robot : robots3)
    {
        std::cout << "robotId:" << std::get<0>(robot)<< " " << "robotName:" << std::get<1>(robot) << std::endl;
    }
    // 再加入几个奥特曼
    // Robot otaku1{7,"zoffy"};  // 佐菲
    // Robot otaku2{8,"seven"};    // 赛文
    // storage.insert(otaku1);
    // storage.insert(otaku2);

    std::cout << "======== select * from tb_robot; ============ " << std::endl;
    auto robot4 = storage.get_all<Robot>();
    std::cout << "Total robots: " << robot4.size() << std::endl;
    for(const auto &robot : robot4)
    {
        std::cout << "robotId:" << robot.id << " ---" << "robotName:" << robot.name <<std::endl;
    }

    // 根据条件修改，把id 为2 的数据修改为 奥特之王
    std::cout << "======== update tb_robot set name = '奥特之王' where id = 2; ============ " << std::endl;
    storage.update_all(set(c(&Robot::name) = "奥特之王"), where(c(&Robot::id) == 2));

    // 查询id 为2 的数据
    std::cout << "============select * from tb_robot where id = 2=" << std::endl;
    auto robot5 = storage.get<Robot>(2);
    std::cout << "robotId:" << robot5.id << " " << " robotName:" << robot5.name << std::endl;

    // 删除id 为 8 的数据
    std::cout << "======== delete from tb_robot where id = 8; ============ " << std::endl;
    storage.remove_all<Robot>(where(c(&Robot::id) == 8));

    // 查询id 为8 的数据   －－ 已级找不到了
    std::cout << "============select * from tb_robot where id = 8=" << std::endl;
    auto robot6 = storage.get_all<Robot>(where(c(&Robot::id) == 8));
    if(robot6.empty()) {
        std::cout << "robot not found" << std::endl;
    } else {
        std::cout << "robotId:" << robot6[0].id<< " " << " robotName:" << robot6[0].name << std::endl;
    }


    return 0;
}