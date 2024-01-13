#include "SoundSensor.h"

SoundSensor::SoundSensor(uint8_t _pin, int _window_size) {
  pin = _pin;
  window_size = _window_size;
}

void SoundSensor::begin() {
  pinMode(pin, INPUT);
}

void SoundSensor::update() {
  short t = digitalRead(pin);
  breath.add(t);
  timestamp.add(millis());
}

String SoundSensor::get() {
  String res = "[";
  if (breath.size() >= window_size) {
    res += String(timestamp[0]);
    int num[2] = {0, 0};
    int n = breath.size();
    for (int i = 0; i < window_size; i++) {
      num[breath[i]]++;
    }
    int last_state = num[1] > num[0];
    for (int i = 0, j = i + window_size; j < n; i++, j++) {
      num[breath[i]]--;
      num[breath[j]]++;
      int state = num[1] > num[0];
      if (state != last_state) {
        last_state = state;
        res += ", " + String(timestamp[(i + j) / 2]);
      }
    }
    breath.clear();
    timestamp.clear();
  }
  res += "]";
  return "breathing: " + res + ",";
}

int SoundSensor::size() {
  return breath.size();
}