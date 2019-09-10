#include <mbed.h>
#include "robo_motor.h"

//手動機アーム

class ExpertsArm
{
private:
    RoboMotor &Elevate, &Pinch;
    DigitalOut &STBY;

public:
    ExpertsArm(RoboMotor &, RoboMotor &, DigitalOut &stby);

    void EBrake(void);
    void PBrake(void);
    void Up(uint32_t PulseWidth);
    void Down(uint32_t PulseWidth);
    void Close(uint32_t PulseWidth);
    void Open(uint32_t PulseWidths);
};