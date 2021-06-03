#include "matezzzz-arduino-library/segment_display.h"
#include "matezzzz-arduino-library/button.h"
#include "matezzzz-arduino-library/segment_display_animation.h"
#include "dad_display/DaD_display.h"


//Holds time since last press down
class TimedEventButton : public EventButton{
  Stopwatch<> time_pressed;
public:
  TimedEventButton(uint8_t pin) : EventButton(pin)
  {}
  void init(){
    EventButton::init();
    time_pressed.init();
  }
  void update(){
    EventButton::update();
    //if button was pressed, reset the timer
    if (pressEvent()) time_pressed.reset();
  }
  uint16_t timeSinceLastPress(){
    return time_pressed.elapsedTime();
  }
};


TimedEventButton generate_button(button1_pin);
TimedButton throw_config_button(button2_pin, 250);
TimedButton dice_type_button(button3_pin, 250);
DiceSegmentDisplay display;
AnimatedSegmentDisplay<2, 10> display_animated(50);

void setup(){
  generate_button.init();
  throw_config_button.init();
  dice_type_button.init();
  display.init();
  display_animated.init();
}


void loop() {
  generate_button.update();
  if (throw_config_button.isPressed()) display.incrThrowCount();
  if (dice_type_button.isPressed()) display.incrDiceType();
  if (generate_button.isPressed()){
    display_animated.update();
  } else if (generate_button.liftEvent()){
    display.generateNumber(generate_button.timeSinceLastPress());
  }else{
    display.update();
  }
}
