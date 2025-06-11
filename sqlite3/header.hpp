/*
 * @Author: hawrkchen
 * @Date: 2024-11-08 10:23:21
 * @Description: 
 * @FilePath: /sqlite3/header.hpp
 */
#include <string>
#include <sqlite3.h>
#include "sqlite_orm/sqlite_orm.h"

//using namespace sqlite_orm;

struct Robot {
    int id;
    std::string name;
};

auto app_version_table = sqlite_orm::make_table("tb_app_version",
    sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
    sqlite_orm::make_column("app_name", &Robot::name));


// auto storage = sqlite_orm::make_storage("/home/hawrk/sqlite3/robot.db",
//             app_version_table   
//                                     );
                  