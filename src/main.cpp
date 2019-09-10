#include <mbed.h>

#include "motor.h"
#include "wheel.h"

#include "robo_motor.h"
#include "experts_arm.h"

#include "controller.h"

namespace
{
//足回り
  PwmOut wpout[4] = {
    PwmOut(PC_8),
    PwmOut(PC_9),
    PwmOut(PA_5),
    PwmOut(PB_3)
  };
  //ピンを追加する！
  DigitalOut wdout[4] = {
    DigitalOut(PA_0),
    DigitalOut(PA_0),
    DigitalOut(PA_0),
    DigitalOut(PA_0)
  }; 
  uint32_t WHEEL_POWER = 100;
  Motor motor[4] = {
    Motor(wpout[0], wdout[0], WHEEL_POWER, true),
    Motor(wpout[1], wdout[1], WHEEL_POWER, true),
    Motor(wpout[2], wdout[2], WHEEL_POWER, true),
    Motor(wpout[3], wdout[3], WHEEL_POWER, true)
  };
  Wheel wheel(motor[0], motor[1], motor[2], motor[3], 150);

  //アーム
  PwmOut apout[2] = {
    PwmOut(PC_0),
    PwmOut(PC_0)
  };
  DigitalOut adout[5] = {
      DigitalOut(PA_0),
      DigitalOut(PA_0),
      DigitalOut(PA_0),
      DigitalOut(PA_0),
      DigitalOut(PA_0)
  };
  RoboMotor Rmotor[2] = {
    RoboMotor(apout[0], adout[0], adout[1], 100, true),
    RoboMotor(apout[1], adout[2], adout[3], 100, true)
  };
  ExpertsArm arm(Rmotor[0], Rmotor[1], adout[4]);

  //コントローラー
  CAN can1(PA_11, PA_12, 500000);
  Controller controller(can1, 0x334 /*, 0x2*/); //引数よくわからん

  //その他
  float CLOCK = 0.5;

} // namespace

int main() {

  // put your setup code here, to run once:
  int8_t JS1_X ,JS1_Y, JS2_X, JS2_Y;
  bool BT_A, BT_B, BT_X, BT_Y;

  while(1) {
    // put your main code here, to run repeatedly:
    JS1_X = controller.axes.LX;
    JS1_Y = controller.axes.LY;
    JS2_X = controller.axes.RX;
    JS2_Y = controller.axes.RY;
    BT_A = controller.buttons[1];
    BT_B = controller.buttons[2];
    BT_X = controller.buttons[0];
    BT_Y = controller.buttons[3];

    if(BT_B){
      //アーム開
      arm.Open(50);
    }
    else if(BT_X){
      //アーム閉
      arm.Close(50);
    }

    if(BT_Y){
      //アーム上
      arm.Up(50);
    }
    else if(BT_A){
      //アーム下
      arm.Down(50);
    }

    wheel.joystick(JS1_X, JS1_Y); //オムニ8方制御
    wheel.joystickRotate(JS2_X); //オムニ回転制御

    wait(CLOCK);
  }
}