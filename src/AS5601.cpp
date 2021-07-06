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
    // Serial.printf("wire1 %d\t",data);
    data |= (uint16_t)Wire.read();
    // Serial.printf("wire2 %d\t",data);    
    return data;
}

void AS5601::_getRawAngle(){
    _prev_raw_angle = _raw_angle;
    _raw_angle = _read2Byte(RAW_ANGLE);
    if(_raw_angle == 65535)
        //ノイズなどで正常に通信できないと受信するデータが65535になる.
        _raw_angle = _prev_raw_angle;
}

void AS5601::_calculation(){
    //角度を-pi~pi[rad]に変換.
    _angle = ((float)_raw_angle - 2048.0f) / 4096.0f * 360.0f * DEG_TO_RAD
                 * static_cast<float>(_dir);
    _time = (float)millis();
    float dt = (_time - _prev_time) * 0.001f;
    //角度が4096から0に移り変わったときに角速度がおかしくならないようにする処理
    if(_raw_angle < _range && _prev_raw_angle > 4096 - _range){
        _angular_v = _prev_angular_v;
    }else if(_raw_angle > 4096 - _range && _prev_raw_angle < _range){
        _angular_v = _prev_angular_v;
    }else{
        _angular_v = (_angle - _prev_angle) / dt;
    }
    
    _rpm = _angular_v * 30.0f / PI;
    _prev_time = _time;
    _prev_angle = _angle;
    _prev_angular_v = _angular_v;
}

void AS5601::update(){
    _getRawAngle();
    _calculation();
}

void AS5601::print(){
    //使うときは自由にコメントアウトしてください.
    Serial.printf("raw angle %d ", _raw_angle);
    Serial.printf("angle %f[rad] %f[deg] ", _angle,degrees(_angle));
    Serial.printf("angular_v %f ",_angular_v);
    Serial.printf("RPM %f ",_rpm);
    Serial.printf("\r\n");
}

}/*as5601*/