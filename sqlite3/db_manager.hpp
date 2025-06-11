/*
 * @Author: hawrkchen
 * @Date: 2025-03-20 18:55:13
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-03-20 19:11:51
 * @Description: 
 * @FilePath: /sqlite3/db_manager.hpp
 */
#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include "robot.hpp"

class DatabaseManager {
    public:
        static DatabaseManager& getInstance() {
            static DatabaseManager instance;
            return instance;
        }

        auto& getStorage() {
            return storage_;
        }

    private:

        static auto initializeStorage() { 
            return sqlite_orm::make_storage("example.db",
            sqlite_orm::make_table("users",
                sqlite_orm::make_column("id", &Robot::id, sqlite_orm::primary_key()),
                sqlite_orm::make_column("name", &Robot::name)
                )
            );
        }

        using Storage = decltype(initializeStorage());

        Storage storage_;

        DatabaseManager(): storage_(initializeStorage()) {
            storage_.sync_schema();
        }
};