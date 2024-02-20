#ifndef inclu
#include <bits/stdc++.h>
#define inclu
#endif

class account{
public:
  int privilege, count, select;
  char user_id[32], pass_word[32], user_name[32];
  account(){
    count = privilege = select = 0; 
    for(int i = 0; i < max_len + 1; ++i) user_id[i] = pass_word[i] = user_name[i] = 0;
  }
  account(const std::string &a, const std::string &b, const std::string &c, const int &d, const int &e = 0){
    for(int i = 0; i < max_len + 1; ++i) user_id[i] = pass_word[i] = user_name[i] = 0;
    for(int i = 0; i < a.size(); ++i) user_id[i] = a[i];
    for(int i = 0; i < b.size(); ++i) pass_word[i] = b[i];
    for(int i = 0; i < c.size(); ++i) user_name[i] = c[i];
    privilege = d;
    count = 0;
    select = e;
  }
  account& operator=(const account &rhs){
    privilege = rhs.privilege;
    count = rhs.count;
    for(int i = 0; i < max_len; ++i){
      user_id[i] = rhs.user_id[i];
      pass_word[i] = rhs.pass_word[i];
      user_name[i] = rhs.user_name[i];
    }
    return *this;
  }
  friend bool operator==(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i) if(a.user_id[i] ^ b.user_id[i]) return false;
    return true; 
  }
  friend bool operator<(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i)
      if(a.user_id[i] < b.user_id[i]) return true;
      else if(a.user_id[i] > b.user_id[i]) return false;
    return false; 
  }
  friend bool operator<=(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i)
      if(a.user_id[i] < b.user_id[i]) return true;
      else if(a.user_id[i] > b.user_id[i]) return false;
    return true; 
  }
  friend bool operator>(const account &a, const account &b){
    return b < a;
  }
  friend bool operator>=(const account &a, const account &b){
    return b <= a;
  }
  void simple_write(std::fstream &File){
    File.write(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.write(reinterpret_cast<char *>(&count), sizeof(int));
    File.write(reinterpret_cast<char *>(&select), sizeof(int));
    return ;
  }
  void write(std::fstream &File, std::string &file_name, const int &index){
    File.open(file_name, std::ios::out | std::ios::binary);
    File.seekp(index * sizeof(char), std::ios::beg);
    File.write(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.write(reinterpret_cast<char *>(&count), sizeof(int));
    File.write(reinterpret_cast<char *>(&select), sizeof(int));
    File.close();
    return ;
  }
  void read(std::fstream &File, std::string &file_name, const int &index){
    File.open(file_name, std::ios::in | std::ios::binary);
    File.seekg(index * sizeof(char), std::ios::beg);
    File.read(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.read(reinterpret_cast<char *>(&count), sizeof(int));
    File.read(reinterpret_cast<char *>(&select), sizeof(int));
    File.close();
    return ;
  }
  void simple_read(std::fstream &File){
    File.read(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.read(reinterpret_cast<char *>(&count), sizeof(int));
    File.read(reinterpret_cast<char *>(&select), sizeof(int));
    return ;
  }
};

#include "Block.hpp"

bool check_user_id_or_pass_word(const std::string &a){
  if(a.size() > max_len) return false;
  for(int i = 0; i < a.size(); ++i) 
    if(a[i] != '_' && !(a[i] >= '0' && a[i] <= '9')
    && !(a[i] >= 'a' && a[i] <= 'z') && !(a[i] >= 'A' && a[i] <= 'Z'))
      return false;
  return true;
}

bool check_user_name(const std::string &user_name){
  if(user_name.size() > max_len) return false;
  for(int i = 0; i < user_name.size(); ++i) 
    if(user_name[i] == 127 || (user_name[i] >= 0 && user_name[i] <= 32))
      return false;
  return true;
}

bool check_privilege(const std::string &privilege){
  if(privilege.size() != 1) return false;
  if(privilege[0] != '7' && privilege[0] != '3' && privilege[0] != '1') return false;
  return true;
}

std::vector <account> log_in;
int current_privilege = 0;

inline void update_current_privilege(){
  if(log_in.size() == 0) current_privilege = 0;
  else current_privilege = log_in[log_in.size() - 1].privilege;
  return ;
}

void LogIn_account(std::string &read_in, std::vector <interval> &info){
  if(info.size() <= 1 || info.size() >= 4){
    fail();
    return ;
  } // fail in form
  assert(info.size());
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  //std::cout << "user_id = " << user_id << "\n";
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege == -1){
    fail();
    //printf("fail on privilege == -1\n");
    return ;
  } 
  if(info.size() == 3){
    std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1);
    if(pass_word != now.pass_word){
      fail();
      return ;
    }
    else {
      log_in.push_back(now);
      update_current_privilege();
      return ;
    }
  }
  if(current_privilege > now.privilege){
    log_in.push_back(now);
    update_current_privilege();
    return ;
  }
  else {
    fail();
    return ;
  }
}

void LogOut_account(){
  if(log_in.size() == 0){
    fail();
    return ;
  }
  log_in.pop_back();
  update_current_privilege();
  return ;
} 

void Register_account(std::string &read_in, std::vector <interval> &info){
  if(info.size() != 4){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege != -1){
    fail();
    return ;
  }
  std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1), 
              user_name = read_in.substr(info[3].l, info[3].r - info[3].l + 1);
  if(!check_user_id_or_pass_word(pass_word)){
    fail();
    return ;
  }
  if(!check_user_name(user_name)){
    fail();
    return ;
  }
  account tmp(user_id, pass_word, user_name, 1);
  block::Insert(tmp);
  return ;
}

void Create_account(std::string &read_in, std::vector <interval> &info){
  if(info.size() != 5 || current_privilege < 3){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  //std::cout << "To create user_id = " << user_id << "\n";
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  } 
  account now; 
  block::get_info(user_id, now);
  if(now.privilege != -1){
    fail();
    return ;
  }
  std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1), 
              user_name = read_in.substr(info[4].l, info[4].r - info[4].l + 1);
  if(!check_user_id_or_pass_word(pass_word)){
    fail();
    return ;
  } 
  if(!check_user_name(user_name)){
    fail();
    return ;
  }
  if(!check_privilege(read_in.substr(info[3].l, info[3].r - info[3].l + 1))){
    fail();
    return ;
  }
  int privilege = read_in[info[3].l] - '0';
  if(privilege >= current_privilege){
    fail();
    return ;
  }
  account tmp(user_id, pass_word, user_name, privilege);
  block::Insert(tmp);
  return ;
}

void Change_pass_word(std::string &read_in, std::vector <interval> &info){
  if(info.size() < 3 || info.size() > 4 || current_privilege < 1){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege == -1){
    fail();
    return ;
  }
  if(info.size() == 3){
    if(current_privilege != 7){
      fail();
      return ;
    }
    std::string new_pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1);
    if(!check_user_id_or_pass_word(new_pass_word)){
      fail();
      return ;
    }
    block::Update_pass_word(user_id, new_pass_word);
    return ;
  }
  std::string previous_pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1),
              new_pass_word = read_in.substr(info[3].l, info[3].r - info[3].l + 1);
  if(!check_user_id_or_pass_word(previous_pass_word)){
    fail();
    return ;
  }
  if(!check_user_id_or_pass_word(new_pass_word)){
    fail();
    return ;
  }
  if(previous_pass_word != now.pass_word){
    fail();
    return ;
  }
  block::Update_pass_word(user_id, new_pass_word);
  return ;
}

void Delete_account(std::string &read_in, std::vector <interval> &info){
  if(info.size() != 2 || current_privilege < 7){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege == -1 || now.count > 0){
    fail();
    return ;
  }
  block::Delete(user_id);
  return ;
}