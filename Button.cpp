#include "Button.h"

Button::Button(int _pin) {
  pin = _pin;
}

void Button::begin() {
  pinMode(pin, INPUT);
}

int Button::read() {
  return digitalRead(pin);
}