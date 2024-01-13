#ifndef DHTSensor_h
#define DHTSendor_h

#include <Arduino.h>
#include "DHT.h"  // "DHT sensor library"
#include "LinkedList.h"

#define interval 50

class DHTSensor {
  public:
    DHTSensor(uint8_t pin, uint8_t type);
    void begin();
    void update();
    String get();
  private:
    DHT dht;
    LinkedList<float> humi, temp, _humi, _temp;
};

# endif