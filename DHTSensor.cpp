#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTSensor::begin() {
  dht.begin();
}

void DHTSensor::update() {
  float humi_val = dht.readHumidity();
  float temp_val = dht.readTemperature();
  humi.add(humi_val);
  temp.add(temp_val);
  if (humi.size() == interval) {
    float sum_humi = 0.0, sum_temp = 0.0;
    for (int i = 0; i < interval; i++) {
      sum_humi += humi[i];
      sum_temp += temp[i];
    }
    _humi.add(sum_humi / interval);
    _temp.add(sum_temp / interval);
    humi.clear();
    temp.clear();
  }
}

String DHTSensor::get() {
  String humi_arr = "[", temp_arr = "[";
  int n = _humi.size();
  for (int i = 0; i < n; i++) {
    humi_arr += String(_humi[i]);
    temp_arr += String(_temp[i]);
    if (i != n - 1) {
      humi_arr += ", ";
      temp_arr += ", ";
    }
  }
  humi_arr += "]";
  temp_arr += "]";
  _humi.clear();
  _temp.clear();
  return "humidity: " + humi_arr + ", temperature: " + temp_arr + ",";
}