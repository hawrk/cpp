/*
 * @Author: hawrkchen
 * @Date: 2025-03-21 09:04:28
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-03-21 09:08:27
 * @Description: 
 * @FilePath: /sqlite3/sqlite_storage.hpp
 */
#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include <nlohmann/json.hpp>

// 假设我们有两个类 AppVersion 和 RobotStatus
class Robot {
public:
    int id;
    std::string app_name;
    std::string version;
};

class RobotStatus {
public:
    int id;
    std::string robot_sn;
};

// 数据库单例类
class SQLiteStorageSingleton {
private:
    // 私有构造函数，防止外部实例化
    SQLiteStorageSingleton() {
        // 假设 constant::SQLITE3_DB_PATH 是数据库路径
        storage_ = sqlite_orm::make_storage(
            "db.sqlite",
            sqlite_orm::make_table("tb_app_version",
                sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
                sqlite_orm::make_column("app_name", &Robot::app_name),
                sqlite_orm::make_column("version", &Robot::version)
            ),
            sqlite_orm::make_table("tb_robot_status",
                sqlite_orm::make_column("id", &RobotStatus::id, sqlite_orm::primary_key()),
                sqlite_orm::make_column("robot_sn", &RobotStatus::robot_sn)
            )
        );
        // 同步模式，确保表结构正确
        storage_.sync_schema();
    }

    // 禁用拷贝构造函数和赋值操作符
    SQLiteStorageSingleton(const SQLiteStorageSingleton&) = delete;
    SQLiteStorageSingleton& operator=(const SQLiteStorageSingleton&) = delete;

    // 存储对象
    sqlite_orm::storage_t<
        sqlite_orm::make_storage_t<
            decltype(sqlite_orm::make_storage(
                "db.sqlite",
                sqlite_orm::make_table("tb_app_version",
                    sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
                    sqlite_orm::make_column("app_name", &Robot::app_name),
                    sqlite_orm::make_column("version", &Robot::version)
                ),
                sqlite_orm::make_table("tb_robot_status",
                    sqlite_orm::make_column("id", &RobotStatus::id, sqlite_orm::primary_key()),
                    sqlite_orm::make_column("robot_sn", &RobotStatus::robot_sn)
                )
            ))
        >
    > storage_;

public:
    // 获取单例实例的方法
    static SQLiteStorageSingleton& getInstance() {
        static SQLiteStorageSingleton instance; // C++11之后的线程安全局部静态变量初始化
        return instance;
    }

    // 获取存储对象的方法
    sqlite_orm::storage_t<
        sqlite_orm::make_storage_t<
            decltype(sqlite_orm::make_storage(
                "db.sqlite",
                sqlite_orm::make_table("tb_app_version",
                    sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
                    sqlite_orm::make_column("app_name", &Robot::app_name),
                    sqlite_orm::make_column("version", &Robot::version)
                ),
                sqlite_orm::make_table("tb_robot_status",
                    sqlite_orm::make_column("id", &RobotStatus::id, sqlite_orm::primary_key()),
                    sqlite_orm::make_column("robot_sn", &RobotStatus::robot_sn)
                )
            ))
        >
    >& getStorage() {
        return storage_;
    }
};