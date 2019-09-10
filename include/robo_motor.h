#ifndef ROBO_MOTOR_H
#define ROBO_MOTOR_H

#include <mbed.h>

class RoboMotor
{
private:
    PwmOut &PWM;
    DigitalOut &DIN1;
    DigitalOut &DIN2;
    const uint32_t PWM_PERIOD;
    const bool DIRECTION;

public:
    RoboMotor(
        PwmOut &PWM_PIN, 
        DigitalOut &DIN1_PIN, 
        DigitalOut &DIN2_PIN, 
        uint32_t pwmout_period, bool direction);

    void Brake(void);
    void CW(uint32_t pulsewidth);
    void CCW(uint32_t pulsewidth);
};

#endif 