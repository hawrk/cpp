/*
 * @Author: hawrkchen hawrk2012@163.com
 * @Date: 2024-10-21 11:08:58
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-03-20 09:11:46
 * @FilePath: /sqlite3/sqlite3.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// 写一个sqlite3的C++接口，可以对数据库进行增删改查操作。
// 参考：https://www.sqlite.org/quickstart.html

#include <iostream>
#include <sqlite3.h>
#include "header.hpp"


int main(int argc, char **argv) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("/data/sqlite3/ros2/robot.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // 查询语句
    const char *sql = "SELECT * FROM tb_robot";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    // 输出查询结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        std::cout << "id: " << id << ", name: " << name  << std::endl;
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;
}