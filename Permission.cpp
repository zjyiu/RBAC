#include "Permission.h"

using namespace std;

vector<Permission> permission_table;

Permission::Permission(int p){
    id=p;
    switch (id){ //根据不同id赋予不同信息。
    case NEW:
        remarks="new a file ";
        break;
    case READ:
        remarks="read a file ";
        break;
    case WRITE:
        remarks="write a file ";
        break;
    case EXECUTE:
        remarks="execute a file ";
        break;
    case DELETE:
        remarks="delete a file ";
        break;
    case MODIFY:
        remarks="modify a file ";
    }
}

void permission_table_init(){
    //权限在vector中的索引和其id相同，所以利用权限id即可引用权限。
    for(int i=0;i<6;i++)
        permission_table.push_back(Permission(i));
    return;
}