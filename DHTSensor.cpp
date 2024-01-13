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
  float humi_avg = 0.0, temp_avg = 0.0;
  int n = _humi.size();
  for (int i = 0; i < n; i++) {
    humi_avg += _humi[i];
    temp_avg += _temp[i];
  }
  _humi.clear();
  _temp.clear();
  humi_avg /= n;
  temp_avg /= n;
  return "\"humidity\": " + String(humi_avg) + ", \"temperature\": " + String(temp_avg) + ",";
}

int DHTSensor::size() {
  return humi.size() + _humi.size();
}