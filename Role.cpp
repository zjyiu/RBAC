#include "Role.h"

using namespace std;

map<int,pair<int,int>> role_count_table;
map<int,vector<int>> role_permission_table;
map<int,vector<int>> role_inherit_table;
map<int, vector<int>> role_mutex_table;
vector<Role> role_table;

Role::Role(int i){
    id=i;
    switch (id){ //根据不同的角色id赋予角色不同的名字
    case BOSS:
        name="boss";
        break;
    case G_MANAGER:
        name="general manager";
        break;
    case D_MANAGER_A:
        name="department A manager";
        break;
    case D_MANAGER_B:
        name="department B manager";
        break;
    case D_MANAGER_C:
        name="department C manager";
        break;
    case STAFF_A:
        name="department A staff";
        break;
    case STAFF_B:
        name="department B staff";
        break;
    case STAFF_C:
        name="department C staff";
        break;
    }
}

string Role::get_name(){
    return name;
}

void role_table_init(){
    //和权限表类似，角色在vector中的索引与其id相同，可利用角色id引用角色。
    for(int i=0;i<8;i++)
        role_table.push_back(Role(i));
    return;
}

//老板、总经理和部门经理的最大人数均为一。
//部门职员的最大人数均为五。
void role_count_table_init(){
    for (int i = 0; i < 8;i++){
        if(i==3||i==5||i==7)
            role_count_table.insert(pair<int, pair<int, int>>(i, pair<int, int>(5, 0)));
        else
            role_count_table.insert(pair<int, pair<int, int>>(i, pair<int, int>(1, 0)));
    }
}

void role_permission_table_init(){
    vector<int> vp0,vp1,vp2,vp3,vp4,vp5,vp6,vp7;
    vp0={0,1,2,3,4,5}; //老板具有所有权限
    vp1={0,1,2,3,4,5}; //总经理具有所有权限
    vp2={0,1,2}; //A部门经理具有新建、读和写权限
    vp3={0,2}; //A部门职员具有新建和写权限
    vp4={1,4,5}; //B部门经理具有读、删除和修改权限
    vp5={1,5}; //B部门职员具有读和修改权限
    vp6={1,3,4}; //C部门经理具有读、执行和删除的权限
    vp7={1,3}; //C部门职员具有读和执行的权限
    role_permission_table.insert(pair<int,vector<int>>(0,vp0));
    role_permission_table.insert(pair<int,vector<int>>(1,vp1));
    role_permission_table.insert(pair<int,vector<int>>(2,vp2));
    role_permission_table.insert(pair<int,vector<int>>(3,vp3));
    role_permission_table.insert(pair<int,vector<int>>(4,vp4));
    role_permission_table.insert(pair<int,vector<int>>(5,vp5));
    role_permission_table.insert(pair<int,vector<int>>(6,vp6));
    role_permission_table.insert(pair<int,vector<int>>(7,vp7));
    return;
}

void role_inherit_table_init(){
    vector<int> vr0,vr1,vr2,vr3,vr4,vr5,vr6,vr7;
    vr0={1}; //只有总经理才能继承老板
    vr1={2,4,6}; //只有部门经理才能继承总经理
    vr2={3}; //只有A部门职员才能继承A部门经理
    vr4={5}; //只有B部门职员才能继承B部门经理
    vr6={7}; //只有C部门职员才能继承C部门经理
    vr3=vr5=vr7={}; //职员为最底层，没有人能继承
    role_inherit_table.insert(pair<int,vector<int>>(0,vr0));
    role_inherit_table.insert(pair<int,vector<int>>(1,vr1));
    role_inherit_table.insert(pair<int,vector<int>>(2,vr2));
    role_inherit_table.insert(pair<int,vector<int>>(3,vr3));
    role_inherit_table.insert(pair<int,vector<int>>(4,vr4));
    role_inherit_table.insert(pair<int,vector<int>>(5,vr5));
    role_inherit_table.insert(pair<int,vector<int>>(6,vr6));
    role_inherit_table.insert(pair<int,vector<int>>(7,vr7));
    return;
}

void role_mutex_table_init(){
    vector<int> vr0,vr1,vr2,vr3,vr4,vr5,vr6,vr7;
    //一个人可以同时拥有老板、总经理、部门经理中的一个或多个角色
    vr0={1,2,4,6};
    vr1={0,2,4,6};
    vr2={0,1,4,6};
    vr4={0,1,2,6};
    vr6={0,1,2,4};
    //职员不能同时成为领导，也不能同时做多个部门的职员
    vr3=vr5=vr7={};
    role_mutex_table.insert(pair<int,vector<int>>(0,vr0));
    role_mutex_table.insert(pair<int,vector<int>>(1,vr1));
    role_mutex_table.insert(pair<int,vector<int>>(2,vr2));
    role_mutex_table.insert(pair<int,vector<int>>(3,vr3));
    role_mutex_table.insert(pair<int,vector<int>>(4,vr4));
    role_mutex_table.insert(pair<int,vector<int>>(5,vr5));
    role_mutex_table.insert(pair<int,vector<int>>(6,vr6));
    role_mutex_table.insert(pair<int,vector<int>>(7,vr7));
    return;
}

bool check_role_permission(int r,int p){
    //获取角色拥有的权限集合
    vector<int> ps=role_permission_table[r];
    //检查权限集合是否包含权限p
    auto i=find(ps.begin(),ps.end(),p);
    if(i==ps.end()) return false;
    else return true;
}