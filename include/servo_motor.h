#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <mbed.h>

class ServoMotor{
private:
    PwmOut &PWM;
    const uint32_t MAX_PERIOD;
    const uint32_t MIN_PERIOD;

public:
    ServoMotor(PwmOut &PWM_Pin, uint32_t max_p, uint32_t min_p);

    void Up();
    void Down();
};

#endif