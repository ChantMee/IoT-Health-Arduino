#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTSensor::begin() {
  sum_temp = 0;
  sum_humi = 0;
  cnt = 0;
  dht.begin();
}

void DHTSensor::update() {
  float humi_val = dht.readHumidity();
  float temp_val = dht.readTemperature();
  cnt ++;
  sum_temp += temp_val;
  sum_humi += humi_val;
}

String DHTSensor::get() {
  float humi_avg = sum_humi / cnt, temp_avg = sum_temp / cnt;
  sum_temp = 0;
  sum_humi = 0;
  cnt = 0;
  return "\"humidity\": " + String(humi_avg) + ", \"temperature\": " + String(temp_avg) + ",";
}

int DHTSensor::size() {
  return cnt;
}