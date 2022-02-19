#include "User.h"

using namespace std;

int user_count;
map<int,User> user_table;
map<int,vector<int>> user_role_table;

User::~User(){}

User::User(string n,vector<int> r){
    name=n;
    id=user_count; //用户id按创建顺序赋予
    user_count++; //更新创建过的用户数
    //将新用户存进用户表
    user_table.insert(pair<int,User>(id,(*this)));
    //将新用户的角色信息存进用户角色关联表
    user_role_table.insert(pair<int,vector<int>>(id,r));
    //循环遍历用户角色，跟新各角色的数目，并输出用户入职信息
    for (auto i = r.begin(); i != r.end();i++){
        role_count_table[*i].second++;
        string r_name=role_table[*i].get_name();
        cout<<"welcome "<<name<<" to be a "<<r_name<<".\n";
    }
}

void User::resign(int r){
    //获取角色名
    string r_name=role_table[r].get_name();
    //检查用户是否拥有角色r，没有则报错返回
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ",cannot resign.\n";
        return;
    }
    //更新用户角色关联表和角色计数表并打印辞职信息
    user_role_table[id].erase(i);
    role_count_table[r].second--;
    cout << name << " resign " << r_name << ".\n";
}

void User::leave(){
    cout << name << " "; //先打印出用户名
    //遍历用户角色集合，更新角色技术表并打印出角色名
    for (auto r = user_role_table[id].begin(); r != user_role_table[id].end();r++){
        role_count_table[*r].second--;
        string r_name=role_table[*r].get_name();
        cout << "(" << r_name << ")" << " ";
    }
    //更新用户表
    auto i=user_table.find(id);
    user_table.erase(i);
    //更新用户角色表
    auto j=user_role_table.find(id);
    user_role_table.erase(j);
    //打印离开信息
    cout << " leave now.\n";
    //删除用户对象
    this->~User();
    return;
}

void User::inherit(int r){
    string new_r_name=role_table[r].get_name(); //获取角色名
    //检查角色数是否已满，已满则报错返回。
    if(role_count_table[r].second==role_count_table[r].first){
        cout<<"the number of "<<new_r_name<<" is full,cannot inherit it.\n";
        return;
    }
    cout << name << " "; //先打印用户名
    bool flag = false; //表示用户继承角色r是否合法
    //从角色继承关系表中获取可以继承角色r的角色集合
    vector<int> need_r=role_inherit_table[r];
    //遍历用户的角色集合，判断角色集合是否包含可以继承角色r的角色，并打印用户当前角色信息
    for (auto i = user_role_table[id].begin(); i != user_role_table[id].end();i++){
        int old_r = *i;
        string old_r_name=role_table[old_r].get_name();
        cout << "(" << old_r_name << ")" << " ";
        auto j = find(need_r.begin(), need_r.end(), old_r);
        if(j!=need_r.end()){
            flag = true;
            break;
        }
    }
    if(!flag) //没有权限则报错
        cout << " don't have access to inhert " << new_r_name << ".\n";
    else{ //有权限则进行继承
        //利用角色互斥关系表获取可以和角色r在同一个用户上共同存在的角色集合
        vector<int> mutex_t_table = role_mutex_table[r];
        //遍历用户角色集合，如果角色可以和r共存则保留，否则删除该角色，更新角色计数表
        for (auto i = user_role_table[id].begin(); i != user_role_table[id].end();){
            int old_r = *i;
            auto j = find(mutex_t_table.begin(), mutex_t_table.end(), old_r);
            if(j==mutex_t_table.end()){
                user_role_table[id].erase(i);
                role_count_table[old_r].second--;
            }
            else i++;
        }
        //赋予用户角色r，更新角色计数表
        user_role_table[id].push_back(r);
        role_count_table[r].second++;
        //打印用户新角色信息
        cout << "has become ";
        for (auto i = user_role_table[id].begin(); i != user_role_table[id].end();i++){
            string cur_r_name = role_table[*i].get_name();
            cout << "(" << cur_r_name << ") ";
        }
        cout << ".\n";
    }
    return;
}

void User::new_file(string fname,int r){
    //获取角色名
    string r_name=role_table[r].get_name();
    //判断用户是否有角色r，没有则报错返回
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    //检查角色r是否有权限创建文件
    if(!check_role_permission(r,NEW))
        cout<<r_name<<" "<<name<<" doesn't have the permission to new a file.\n";
    else cout<<r_name<<" "<<name<<" news a file named \""<<fname<<"\".\n";
}

//逻辑与new_file函数相同
void User::read_file(string fname,int r){
    string r_name=role_table[r].get_name();
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    if(!check_role_permission(r,READ))
        cout<<r_name<<" "<<name<<" doesn't have the permission to read a file.\n";
    else cout<<r_name<<" "<<name<<" reads a file named \""<<fname<<"\".\n";
}

//逻辑与new_file函数相同
void User::write_file(string fname,int r){
    string r_name=role_table[r].get_name();
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    if(!check_role_permission(r,WRITE))
        cout<<r_name<<" "<<name<<" doesn't have the permission to write a file.\n";
    else cout<<r_name<<" "<<name<<" writes a file named \""<<fname<<"\".\n";
}

//逻辑与new_file函数相同
void User::execute_file(string fname,int r){
    string r_name=role_table[r].get_name();
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    if(!check_role_permission(r,EXECUTE))
        cout<<r_name<<" "<<name<<" doesn't have the permission to execute a file.\n";
    else cout<<r_name<<" "<<name<<" executes a file named \""<<fname<<"\".\n";
}

//逻辑与new_file函数相同
void User::delete_file(string fname,int r){
    string r_name=role_table[r].get_name();
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    if(!check_role_permission(r,DELETE))
        cout<<r_name<<" "<<name<<" doesn't have the permission to delete a file.\n";
    else cout<<r_name<<" "<<name<<" deletes a file named \""<<fname<<"\".\n";
}

//逻辑与new_file函数相同
void User::modify_file(string fname,int r){
    string r_name=role_table[r].get_name();
    auto i = find(user_role_table[id].begin(), user_role_table[id].end(), r);
    if(i==user_role_table[id].end()){
        cout << name << " is not a " << r_name << ".\n";
        return;
    }
    if(!check_role_permission(r,MODIFY))
        cout<<r_name<<" "<<name<<" doesn't have the permission to modify a file.\n";
    else cout<<r_name<<" "<<name<<" modifies a file named \""<<fname<<"\".\n";
}

User create_user(string n,vector<int> r){
    //申请赋予用户的各个角色是否已满，如果有角色已满，则报错并终止程序
    for (auto i = r.begin(); i != r.end();i++){
        string r_name = role_table[*i].get_name();
        if (role_count_table[*i].first == role_count_table[*i].second){
            cout << "the number of " << r_name << " is full,cannot create a new one.\n";
            exit(1);
        }
        vector<int> t = role_mutex_table[*i];
        for (auto j = i + 1; j != r.end();j++){
            if(find(t.begin(),t.end(),*j)==t.end()){
                string r1_name = role_table[*j].get_name();
                cout << r_name << " and " << r1_name << " are mutually exclusive.\n";
                exit(1);
            }
        }
    }
    //返回用户名为n，角色集合为r的用户
    return User(n,r); 
}

void init(){
    //初始化user_count并调用各个初始化函数
    user_count=0;
    permission_table_init();
    role_table_init();
    role_permission_table_init();
    role_inherit_table_init();
    role_count_table_init();
    role_mutex_table_init();
}