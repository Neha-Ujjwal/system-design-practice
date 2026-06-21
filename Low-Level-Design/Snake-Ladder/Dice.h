#pragma once
#include <cstdlib>


class Dice {
  private:
    int diceCount; // as there can be multiple dices as well
    int min;
    int max;

  public:
    Dice(int count){
        diceCount = count;
        min = 1;
        max = 6;
    }

    int rollDice(){
      int diceUsed = 0;
      int totalSum = 0;

      while(diceUsed < diceCount){
        totalSum += (std::rand() % max) + min;
        diceUsed++;
      }

      return totalSum;
    }
};