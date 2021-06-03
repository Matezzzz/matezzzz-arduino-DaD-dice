#include "funshield.h"


class Stopwatch{
  uint16_t timer_start;
public:
  Stopwatch()
  {}
  void init(){
    reset();
  }
  inline uint16_t elapsedTime(){
    return millis() - timer_start;
  }
  inline void reset(){
    timer_start = millis();
  }
};


class Timer : public Stopwatch{
  uint16_t timer_length;
public:
  Timer(uint16_t length = 0) : timer_length(length)
  {}
  bool update(){
    if (elapsed()){
      reset();
      return true;
    }
    return false;
  }
  bool elapsed(){
    return elapsedTime() >= timer_length;
  }
};

class Button{
  uint8_t pin;
public:
  Button(uint8_t p) : pin(p)
  {}
  void init(){
    pinMode(pin, INPUT);
  }
  bool isPressed(){
    return !digitalRead(pin);
  }
};

class DoublyTimedButton : public Button{
  enum PressState{
    NOT_PRESSED,
    PRESSED_FIRST,
    PRESSED_LATER
  } state = NOT_PRESSED;
  Timer timer_first;
  Timer timer_later;
public:
  DoublyTimedButton(uint8_t pin, uint16_t cd_first, uint16_t cd) : Button(pin), timer_first(cd_first), timer_later(cd)
  {}
  void init(){
    Button::init();
    timer_first.init();
    timer_later.init();
  }
  bool isPressed(){
    if (Button::isPressed()){
      if (state == NOT_PRESSED){
        timer_first.reset();
        state = PRESSED_FIRST;
        return true;
      }else if (state == PRESSED_FIRST && timer_first.elapsed()){
        timer_later.reset();
        state = PRESSED_LATER;
        return true;
      }else if (state == PRESSED_LATER && timer_later.elapsed()){
        timer_later.reset();
        return true;
      }
      return false;
    }else{
      state = NOT_PRESSED;
      return false;
    }
  }
};

class LED{
  uint8_t pin;
public:
  LED(uint8_t p) : pin(p)
  {}
  void init(){
    pinMode(pin, OUTPUT);
  }
  void turnOn() const{
    digitalWrite(pin, ON);
  }
  void turnOff() const{
    digitalWrite(pin, OFF);
  }
};

const LED LEDs[]{LED(led1_pin), LED(led2_pin), LED(led3_pin), LED(led4_pin)};
constexpr uint8_t LED_count = sizeof(LEDs) / sizeof(uint8_t);

DoublyTimedButton b_incr{button1_pin, 1000, 300};
DoublyTimedButton b_subt{button2_pin, 1000, 300};

uint8_t counter = 0;

void setup(){
  for (LED l : LEDs){
    l.init();
  }
  b_incr.init();
  b_subt.init();
}


void loop() {
  if (b_incr.isPressed()){
    counter = (counter + 1) % 16;
  }
  if (b_subt.isPressed()){
    counter = (counter + 15) % 16;
  }
  for (int i = 0; i < LED_count; i++){
    if (counter & (8 >> i)){
      LEDs[i].turnOn();
    }else{
      LEDs[i].turnOff();
    }
  }
}
