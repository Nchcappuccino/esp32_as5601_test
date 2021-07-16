#include "AS5601.h"
as5601::AS5601 enc(RotationDir::REGULAR_DIR,250);

void setup() {
  //内部プルアップ抵抗を有効にする.
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  Serial.begin(115200);
  Wire.begin(26, 27);
  Wire.setClock(100000);
}

void loop() {
  enc.update();
  enc.print();
}