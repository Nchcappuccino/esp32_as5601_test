#ifndef AS5601_H_
#define AS5601_H_
#include <Arduino.h>
#include <Wire.h>
// #include "esp_log.h"

#ifndef ROTATIONDIR

#define ROTATIONDIR
enum class RotationDir{
	REGULAR_DIR = 1,	//通常の方向.
	NEGATIVE_DIR = -1		//通常とは逆.
};
#endif

namespace as5601{

class AS5601{
    private:
        static constexpr uint8_t ZMCO = 0x00;
        static constexpr uint8_t ZPOS = 0x01;
        static constexpr uint8_t CONF = 0x07;
        static constexpr uint8_t ABN = 0x09;
        static constexpr uint8_t PUSHTHR = 0x0A;
        static constexpr uint8_t RAW_ANGLE = 0x0c;
        static constexpr uint8_t ANGLE = 0x0e;
        static constexpr uint8_t STATUS = 0x0b;
        static constexpr uint8_t AGC = 0x1a;
        static constexpr uint8_t MAGNITUDE = 0x1b;
        static constexpr uint8_t BURN = 0xff;
        static constexpr uint8_t DEVICE_ADDR = 0x36;

        //角度が4096から0に移り変わったときに角速度がおかしくならないようにする閾値.
        static constexpr uint16_t _range = 75;
        void _write(uint8_t reg, uint8_t data);
        uint8_t _read(uint8_t reg);
        uint16_t _read2Byte(uint8_t reg);
        void _getRawAngle();
        void _calculation();
        uint16_t _raw_angle;
        uint16_t _prev_raw_angle;
        float _time;             //[ms]
        float _prev_time;
        float _angle;           //[rad], -pi~pi
        float _prev_angle;
        float _angular_v;        //[rad/s]
        float _prev_angular_v;
        float _rpm;
        RotationDir _dir;
    public:
        AS5601(){};
        void init(RotationDir dir){_dir = dir;}
        void update();
        void print();
        const uint16_t& getRawAngle() const {return _raw_angle;}
        const float& getAngle() const {return _angle;}
        const float& getAngularV() const {return _angular_v;}
        const float& getRPM() const {return _rpm;}
};
}

#endif/*AS5601_H_*/
