#pragma once

class Jump {
  private:
    int startPoint;
    int endPoint;
  public:
    Jump(int s, int e) {
      startPoint = s;
      endPoint = e;
    }

    int getStartPoint(){
      return startPoint;
    }

    int getEndPoint(){
      return endPoint;
    }
};