#include "matezzzz-arduino-library/segment_display.h"
#include "matezzzz-arduino-library/button.h"
#include "matezzzz-arduino-library/segment_display_animation.h"
#include "dad_display/DaD_display.h"


EventButton generate_button(button1_pin);
TimedButton throw_config_button(button2_pin, 250);
TimedButton dice_type_button(button3_pin, 250);
DiceSegmentDisplay display;
AnimatedSegmentDisplay<2, 10> display_animated(50);

void setup(){
}


void loop() {
  generate_button.update();
  if (throw_config_button.isPressed()) display.incrThrowCount();
  if (dice_type_button.isPressed()) display.incrDiceType();
  if (generate_button.isPressed()){
    display_animated.update();
    //display.generateNumber();
  }else{
    display.update();
  }
}
