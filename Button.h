#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  public:
    Button(int _pin);
    void begin();
    int read();
  private:
    int pin;
};

#endif