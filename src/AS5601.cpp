#include "AS5601.h"
namespace as5601{

void AS5601::_write(uint8_t reg, uint8_t data){
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t AS5601::_read(uint8_t reg){
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(reg);
    Wire.endTransmission(true);
    Wire.requestFrom(DEVICE_ADDR,1);
    uint8_t data = Wire.read();
    return data;
}

uint16_t AS5601::_read2Byte(uint8_t reg){
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(RAW_ANGLE);
    Wire.endTransmission(false);
    Wire.requestFrom(DEVICE_ADDR, 2);
    uint16_t data;
    data = ((uint16_t)Wire.read() << 8) & 0x0F00;
    data |= (uint16_t)Wire.read();
    return data;
}

void AS5601::_getRawAngle(){
    _raw_angle = _read2Byte(RAW_ANGLE);

}

void AS5601::update(){
    _getRawAngle();
}

void AS5601::print(){
    Serial.printf("raw angle %d ", _raw_angle);
    Serial.println("\r\n");
}

}/*as5601*/