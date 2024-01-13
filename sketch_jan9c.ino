#include "LinkedList.h"

#include "DHTSensor.h"
#include "SoundSensor.h"
#include "Light.h"
#include "Button.h"

#define DEVICE_CODE "b5ab92178e4b404b9f83a98abe2d7ce3"

#define LOOP_INTERVAL 1200
#define PORT 115200

#define DHT11_PIN 2
#define SOUND_SENSOR_PIN 3
#define LIGHT_PIN 4
#define BUTTON_CANCEL_PIN 5
#define BUTTON_ACTIVATE_PIN 6


DHTSensor dht(DHT11_PIN, DHT11);
SoundSensor sds(SOUND_SENSOR_PIN, 30);
Light lgt(LIGHT_PIN, 1);
Button cel_btn(BUTTON_CANCEL_PIN);
Button act_btn(BUTTON_ACTIVATE_PIN);

unsigned int CUR_LOOP;

void setup() {
  Serial.begin(PORT);
  while (!Serial) delay(10);
  CUR_LOOP = 0;

  dht.begin();
  sds.begin();
  lgt.begin();
  cel_btn.begin();
  act_btn.begin();
}

String get_json(LinkedList<String> data_list) {
  String res = "{";
  int n = data_list.size();
  for (int i = 0; i < n; i++) {
    res += data_list[i] + " }"[i == n - 1];
  }
  return res;
}

void loop() {
  delay(10);
  dht.update();
  sds.update();

  int button_state = cel_btn.read();
  if (button_state) {
    lgt.close();
  }
  button_state = act_btn.read();
  if (button_state) {
    lgt.open();
  }

  if (CUR_LOOP % 100 == 0) {
    Serial.println(CUR_LOOP);
  }

  if (++CUR_LOOP == LOOP_INTERVAL) {
    CUR_LOOP = 0;
    
    String res = "{ ";
    res += sds.get();
    res += dht.get();
    res += " }";
    Serial.println(res);
  }
}
