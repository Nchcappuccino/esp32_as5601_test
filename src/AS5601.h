#ifndef AS5601_H_
#define AS5601_H_
#include <Arduino.h>
#include <Wire.h>

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

        void _write(uint8_t reg, uint8_t data);
        uint8_t _read(uint8_t reg);
        uint16_t _read2Byte(uint8_t reg);
        void _getRawAngle();
        uint16_t _raw_angle;

    public:
        AS5601();
        void update();
        void print();
        const uint16_t &getRawAngle() const { return _raw_angle; }
};
}

#endif/*AS5601_H_*/
