#include "DHTSensor.h"
#include "SoundSensor.h"
#include "Light.h"
#include "Button.h"

#define LOOP_INTERVAL 150
#define PORT 115200

#define DHT11_PIN 2
#define SOUND_SENSOR_PIN 3
#define LIGHT_PIN 4
#define BUTTON_CANCEL_PIN 5

DHTSensor dht(DHT11_PIN, DHT11);
SoundSensor sds(SOUND_SENSOR_PIN, 10);
Light lgt(LIGHT_PIN, 1);
Button cel_btn(BUTTON_CANCEL_PIN);

int CUR_LOOP;

void setup() {
  Serial.begin(PORT);
  while (!Serial) delay(10);
  CUR_LOOP = 0;

  dht.begin();
  sds.begin();
  lgt.begin();
  // cel_btn.begin();
}

void loop() {
  delay(10);
  dht.update();
  sds.update();

  int button_state = cel_btn.read();
  if (button_state) {
    lgt.opposite();
  }

  if (++CUR_LOOP == LOOP_INTERVAL) {
    CUR_LOOP = 0;
    String res = String(sds.get()) + String(dht.get());
    Serial.println(res);
  }
}
