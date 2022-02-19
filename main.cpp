#include "User.h"

using namespace std;

int main(){
    init();
    User u0 = create_user("Ma Yun", {BOSS,D_MANAGER_A});//马云为老板和A部门经理
    User u1 = create_user("Niu Yu", {G_MANAGER});//牛雨为总经理
    User u5 = create_user("Li Si", {D_MANAGER_B});//李四为B部门经理
    User u8 = create_user("Wang Wu", {D_MANAGER_C});//王五为C部门经理
    User u3 = create_user("Zhang Si", {STAFF_A});//张四为A部门职员
    User u4 = create_user("Zhang Wu", {STAFF_A});//张五为A部门职员
    User u6 = create_user("Li Wu", {STAFF_B});//李五为B部门职员
    User u7 = create_user("Li Liu", {STAFF_B});//李六为B部门职员
    User u9 = create_user("Wang Liu", {STAFF_C});//王六为C部门职员
    User u10 = create_user("Wang Qi", {STAFF_C});//王七为C部门职员
    u0.new_file("hello",BOSS);//老板马云创建文件“hello”
    u3.write_file("hello",STAFF_A);//A部门职员张四对“hello”进行写操作
    u4.read_file("hello",STAFF_A);//A部门职员张五想读“hello”文件，但他没有权限
    u6.modify_file("hello",STAFF_B);//B部门职员李五修改“hello”文件
    u5.delete_file("hello",D_MANAGER_B);//B部门经理李四删除“hello”文件
    u0.leave();//老板兼A部门经理马云离开
    User u2 = create_user("Zhang San", {D_MANAGER_A});//新人张三来成为A部门经理
    u3.inherit(BOSS);//A部门职员张四想当老板，但是他没有继承资格
    u1.inherit(BOSS);//总经理牛雨成为总经理加老板
    u2.new_file("hello_1",D_MANAGER_A);//A部门经理张三创建文件“hello_1”
    u4.write_file("hello_1",STAFF_A);//张五对“hello_1”文件进行写操作
    u5.read_file("hello_1",D_MANAGER_B);//B部门经理读“hello_1”文件
    u10.read_file("hello_1",STAFF_C);//C部门职员王七读“hello_1”文件
    u10.modify_file("hello_1",STAFF_C);//C部门职员想修改“hello_1”文件，但他没有权限
    u1.read_file("hello_1", G_MANAGER);//总经理牛雨读“hello_1”文件
    u9.execute_file("hello_1",STAFF_C);//C部门职员王六执行“hello_1”文件
    u8.inherit(BOSS);//C部门经理王五想成为老板，但是老板人数满了
    u8.inherit(G_MANAGER);//C部门经理王五想成为总经理，但是总经理人数也满了
    u8.leave();//C部门经理离开
    u7.inherit(D_MANAGER_C);//B部门职员李六想当C部门经理，但是他没有资格
    u9.inherit(D_MANAGER_C);//C部门职员成为C部门经理，不再是C部门职员
    u1.resign(G_MANAGER);//总经理兼老板牛雨辞去总经理的职务
    u5.inherit(G_MANAGER);//B部门经理李四成为B部门经理兼总经理
    return 0;
}