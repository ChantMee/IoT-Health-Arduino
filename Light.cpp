#include "Light.h"

Light::Light(int _pin, int init_state) {
  pin = _pin;
  cur_state = init_state;
}

void Light::begin() {
  pinMode(pin, OUTPUT);
  update_state();
}

void Light::set(int state) {
  cur_state = state;
  update_state();
}

void Light::open() {
  cur_state = 1;
  update_state();
}

void Light::close() {
  cur_state = 0;
  update_state();
}

void Light::get_current_state() {
  return cur_state;
}

void Light::opposite() {
  cur_state = cur_state ^ 1;
  update_state();
}

void Light::update_state() {
  digitalWrite(pin, cur_state);
}