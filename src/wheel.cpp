#include "wheel.h"

int8_t ufo(int8_t a);

Wheel::Wheel(Motor &_FR, Motor &_FL, Motor &_RR, Motor &_RL, uint32_t _pow) : FR(_FR), FL(_FL), RR(_RR), RL(_RL), pow(_pow)
{
}

void Wheel::Brake(void)
{
    FR.Brake();
    FL.Brake();
    RR.Brake();
    RL.Brake();
}

void Wheel::North(uint32_t pulsewidth)
{
    FR.CW(pulsewidth);
    FL.CCW(pulsewidth);
    RR.CW(pulsewidth);
    RL.CCW(pulsewidth);
}

void Wheel::East(uint32_t pulsewidth)
{
    FR.CCW(pulsewidth);
    FL.CCW(pulsewidth);
    RR.CW(pulsewidth);
    RL.CW(pulsewidth);
}

void Wheel::West(uint32_t pulsewidth)
{
    FR.CW(pulsewidth);
    FL.CW(pulsewidth);
    RR.CCW(pulsewidth);
    RL.CCW(pulsewidth);
}

void Wheel::South(uint32_t pulsewidth)
{
    FR.CCW(pulsewidth);
    FL.CW(pulsewidth);
    RR.CCW(pulsewidth);
    RL.CW(pulsewidth);
}

void Wheel::NorthEast(uint32_t pulsewidth)
{
    FR.Brake();
    FL.CCW(pulsewidth);
    RR.CW(pulsewidth);
    RL.Brake();
}

void Wheel::NorthWest(uint32_t pulsewidth)
{
    FR.CW(pulsewidth);
    FL.Brake();
    RR.Brake();
    RL.CCW(pulsewidth);
}

void Wheel::SouthEast(uint32_t pulsewidth)
{
    FR.CCW(pulsewidth);
    FL.Brake();
    RR.Brake();
    RL.CW(pulsewidth);
}

void Wheel::SouthWest(uint32_t pulsewidth)
{
    FR.Brake();
    FL.CW(pulsewidth);
    RR.CCW(pulsewidth);
    RL.Brake();
}

void Wheel::rotate_right(uint32_t pulsewidth)
{
    FR.CCW(pulsewidth);
    FL.CCW(pulsewidth);
    RR.CCW(pulsewidth);
    RL.CCW(pulsewidth);
}

void Wheel::rotate_left(uint32_t pulsewidth)
{
    FR.CW(pulsewidth);
    FL.CW(pulsewidth);
    RR.CW(pulsewidth);
    RL.CW(pulsewidth);
}

void Wheel::joystick(int8_t x, int8_t y){
    auto xu = ufo(x);
    auto yu = ufo(y);

    if(xu == -1){
        switch(yu){
            case -1:
                //南西
                break;
            case 0:
                //西
                break;
            case 1:
                //北西
                break;
        }
    }
    else if(xu == 0){
        switch (yu)
        {
        case -1:
            //南
            break;
        case 0:
            //ブレーキ
            break;
        case 1:
            //北
            break;
        }
    }
    else if(xu == 1){
        switch (yu)
        {
        case -1:
            //北東
            break;
        case 0:
            //東
            break;
        case 1:
            //南東
            break;
        }
    }
}

int8_t ufo(int8_t a){
    if(a > 33){
        return 1;
    }
    else if(a < -33){
        return -1;
    }
    else{
        return 0;
    }
}