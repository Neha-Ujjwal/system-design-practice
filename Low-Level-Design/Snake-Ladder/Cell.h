#pragma once
#include "Jump.h"

class Cell {
  private:
    Jump* jump;
  public:
    Cell(Jump* j){
      jump = j;
    }

    Jump* getJump(){
      return jump;
    }

    void setCell(Jump* j){
      jump = j;
    }
};