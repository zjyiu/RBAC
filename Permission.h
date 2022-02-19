#ifndef PERMISSION_H
#define PERMISSION_H

//所需的所有库文件。
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define NEW 0 //新建文件的权限
#define READ 1 //阅读文件的权限
#define WRITE 2 //写文件的权限（针对的是新文件）
#define EXECUTE 3 //执行文件的权限
#define DELETE 4 //删除文件的权限
#define MODIFY 5 //修改文件的权限（针对的是已经写过的文件）

class Permission{ //权限对象
private:
    int id; //权限id
    std::string remarks; //权限备注，及具体内容
public:
    Permission(int p); //构造函数
};

//权限表，表项:(权限)
extern std::vector<Permission> permission_table;
void permission_table_init(); //初始化权限表

#endif