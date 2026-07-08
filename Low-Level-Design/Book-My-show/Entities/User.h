#pragma once
#include <string>

class User {
  private:
    int userId;
    std::string name;
  public:
    User(int userId, std::string name){
      this->userId = userId;
      this->name = name;
    }

    int getUserId(){
      return userId;
    }

    std::string getName(){
      return name;
    }
    
    void setName(std::string name){
      this->name = name;
    }
    
    void setUserId(int userId){
      this->userId = userId;
    }
};