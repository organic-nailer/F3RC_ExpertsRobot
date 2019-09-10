#include "robo_motor.h"

RoboMotor::RoboMotor(
    PwmOut &PWM_PIN, 
    DigitalOut &DIN1_PIN,
    DigitalOut &DIN2_PIN,
    uint32_t pwmout_period = 100,
    bool direction): PWM(PWM_PIN), DIN1(DIN1_PIN), DIN2(DIN2_PIN), PWM_PERIOD(pwmout_period), DIRECTION(direction)
    {
        PWM.period_us(PWM_PERIOD);
        PWM.pulsewidth_us(0);
    }

    void RoboMotor::Brake(void){
        PWM.pulsewidth_us(0);
    }

    void RoboMotor::CW(uint32_t pulsewidth){
        if(pulsewidth > PWM_PERIOD * 0.95)
            pulsewidth = PWM_PERIOD * 0.95;

        PWM.pulsewidth_us(pulsewidth);
        DIN1.write(DIRECTION);
        DIN2.write(!DIRECTION);
    }

    void RoboMotor::CCW(uint32_t pulsewidth)
    {
        if (pulsewidth > PWM_PERIOD * 0.95)
            pulsewidth = PWM_PERIOD * 0.95;

        PWM.pulsewidth_us(pulsewidth);
        DIN1.write(!DIRECTION);
        DIN2.write(DIRECTION);
    }