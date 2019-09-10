#include "experts_arm.h"

ExpertsArm::ExpertsArm(
    RoboMotor &elevate, 
    RoboMotor &pinch,
    DigitalOut &stby): Elevate(elevate), Pinch(pinch), STBY(stby)
{
    STBY.write(1);
}

void ExpertsArm::EBrake(void){
    Elevate.Brake();
}

void ExpertsArm::PBrake(void){
    Pinch.Brake();
}

void ExpertsArm::Up(uint32_t PulseWidth){
    Elevate.CW(PulseWidth);
}

void ExpertsArm::Down(uint32_t PulseWidth){
    Elevate.CCW(PulseWidth);
}

void ExpertsArm::Close(uint32_t PulseWidth){
    Pinch.CW(PulseWidth);
}

void ExpertsArm::Open(uint32_t PulseWidth){
    Pinch.CCW(PulseWidth);
}