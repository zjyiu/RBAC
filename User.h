#ifndef USER_H
#define USER_H

#include "Role.h"

class User{ //用户对象
private:
    int id; //用户id
    std::string name; //用户名
public:
    ~User(); //析构函数
    User(std::string n,std::vector<int> r); //构造函数
    void resign(int r); //用户辞去某个职务（放弃某个角色）
    void leave(); //用户离开（删除用户）
    void inherit(int r); //用户继承某个角色
    void new_file(std::string fname,int r); //以角色r的身份新建一个名为n的文件
    void read_file(std::string fname,int r); //以角色r的身份读一个名为n的文件
    void write_file(std::string fname,int r); //以角色r的身份写一个名为n的文件
    void execute_file(std::string fname,int r); //以角色r的身份执行一个名为n的文件
    void delete_file(std::string fname,int r); //以角色r的身份删除一个名为n的文件
    void modify_file(std::string fname,int r); //以角色r的身份修改一个名为n的文件
};

extern int user_count; //记录创建过的用户的总数及下一个新用户的id

//用户表，表项:用户id,(用户)
extern std::map<int,User> user_table;

//用户角色关联表，表项:(用户id,用户的角色集合)
extern std::map<int,std::vector<int>> user_role_table;
 
//创建名为n，角色集合为r的用户
User create_user(std::string n,std::vector<int> r);

//初始化所有全局变量
void init();

#endif