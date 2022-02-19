#ifndef ROLE_H
#define ROLE_H

#include "Permission.h"

#define BOSS 0 //老板
#define G_MANAGER 1 //总经理
//A部门负责文件的创建
#define D_MANAGER_A 2 //A部门经理
#define STAFF_A 3 //A部门职员
//B部门负责文件的修改
#define D_MANAGER_B 4 //B部门经理
#define STAFF_B 5 //B部门职员
//C部门负责文件的执行
#define D_MANAGER_C 6 //C部门经理
#define STAFF_C 7 //C部门职员

class Role{ //角色对象
private:
    int id; //角色id
    std::string name; //角色名
public:
    Role(int i); //构造函数
    std::string get_name(); //角色名的接口函数
};

//角色表，表项:(角色)
extern std::vector<Role> role_table;
void role_table_init(); //初始化函数

//角色计数表，表项:(角色id,<角色最大数目.角色现有数目>)
extern std::map<int,std::pair<int,int>> role_count_table;
void role_count_table_init(); //初始化函数

//角色权限关联表，表项:(角色id,权限集合)
extern std::map<int,std::vector<int>> role_permission_table;
void role_permission_table_init(); //初始化函数

//角色继承关系表，表项:(角色id,可继承该角色的角色集合)
extern std::map<int,std::vector<int>> role_inherit_table;
void role_inherit_table_init(); //初始化函数

//角色互斥关系表，表项:(角色id,可以与该角色在同一名用户上共存的角色集合)
extern std::map<int, std::vector<int>> role_mutex_table;
void role_mutex_table_init(); //初始化函数

//检查角色r是否有权限p，有返回true，没有返回false
bool check_role_permission(int r,int p);

#endif