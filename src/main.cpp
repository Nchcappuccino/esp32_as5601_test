#include "AS5601.h"
as5601::AS5601 enc;

void setup() {
  // put your setup code here, to run once:
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  Serial.begin(115200);
  Wire.begin(26, 27);
  Wire.setClock(400000);
}

void loop() {
  // put your main code here, to run repeatedly:
  enc.update();
}