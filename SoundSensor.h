#ifndef SoundSensor_h
#define SoundSendor_h

#include <Arduino.h>
#include "LinkedList.h"

class SoundSensor {
  public:
    SoundSensor(uint8_t _pin, int _window_size);
    void begin();
    void update();
    String get();
    int size();
  private:
    LinkedList<short> breath;
    // LinkedList<unsigned int> timestamp;
    unsigned int window_size;
    uint8_t pin;
    int last_state;
    int bre_cnt;
};

# endif