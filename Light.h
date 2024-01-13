#ifndef Light_h
#define Light_h

#include <Arduino.h>

class Light {
  public:
    Light(int _pin, int init_state=0);
    void begin();
    void set(int state);
    void open();
    void close();
    void get_current_state();
    void opposite();

  private:
    void update_state();
    int pin, cur_state;
};

#endif