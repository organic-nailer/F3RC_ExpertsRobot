#include <mbed.h>
#include "motor.h"

//手動機アーム

class ExpertsArm
{
private:
    Motor &Elevate, &Pinch;

private:
    ExpertsArm(Motor &, Motor &);

    void EBrake(void);
    void PBrake(void);
    void Up(uint32_t PulseWidth);
    void Down(uint32_t PulseWidth);
    void Close(uint32_t PulseWidth);
    void Open(uint32_t PulseWidths);
};