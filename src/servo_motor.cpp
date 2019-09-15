#include "servo_motor.h"

ServoMotor::ServoMotor(PwmOut &PWM_Pin, uint32_t max_p, uint32_t min_p) : PWM(PWM_Pin), MAX_PERIOD(max_p), MIN_PERIOD(min_p){

}

void ServoMotor::Up(){
    PWM.pulsewidth_us(MAX_PERIOD);
}

void ServoMotor::Down(){
    PWM.pulsewidth_us(MIN_PERIOD);
}