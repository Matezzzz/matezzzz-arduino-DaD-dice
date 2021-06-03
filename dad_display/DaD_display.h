#ifndef DAD_DISPLAY_H
#define DAD_DISPLAY_H

#include "../matezzzz-arduino-library/segment_display.h"


//all dice types - what will be displayed on the segment display to represent this size
constexpr uint8_t dice_types[][2]{{4, DIGIT_NONE}, {6, DIGIT_NONE}, {8, DIGIT_NONE}, {1, 0}, {1, 2}, {2, 0}, {0, 0}};
//respective dice sizes
constexpr uint8_t dice_sizes[]{4, 6, 8, 10, 12, 20, 100};
constexpr uint8_t dice_count = 7;


class DiceSegmentDisplay : public NumberSegmentDisplay<>{
  uint8_t throw_count;
  uint8_t dice_i;
public:
  DiceSegmentDisplay() : throw_count(3), dice_i(2){
    updateConfigState();
  }
  void incrThrowCount(){
    throw_count = throw_count % 9 + 1;
    updateConfigState();
  }
  void incrDiceType(){
    dice_i = (dice_i + 1) % dice_count;
    updateConfigState();
  }
  void generateNumber(uint16_t rand_seed){
    randomSeed(rand_seed);
    generateNumber();
  }
  void generateNumber(){
    uint16_t n = 0;
    for (int i = 0; i < throw_count; i++){
      n += random(dice_sizes[dice_i]) + 1;
    }
    setNumber(n);
  }
private:
  //update segments to match current configuration
  void updateConfigState(){
    setSegments(throw_count, DIGIT_d, dice_types[dice_i][0], dice_types[dice_i][1]);
  }
};


#endif