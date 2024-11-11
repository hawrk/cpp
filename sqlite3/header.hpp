/*
 * @Author: hawrkchen
 * @Date: 2024-11-08 10:23:21
 * @Description: 
 * @FilePath: /sqlite3/header.hpp
 */
#include <string>
#include <sqlite3.h>
#include <sqlite_orm/sqlite_orm.h>

//using namespace sqlite_orm;

struct Robot {
    int id;
    std::string name;
};

auto init_storage() {
    return sqlite_orm::make_storage("/data/sqlite3/ros2/robot.db",
                                    sqlite_orm::make_table("tb_robot",
                                        sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
                                        sqlite_orm::make_column("name", &Robot::name))    
                                    );
}
