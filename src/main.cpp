#include <mbed.h>

#include "motor.h"
#include "wheel.h"

#include "robo_motor.h"
#include "experts_arm.h"

#include "controller.h"

void ControllerCheck(vector<int8_t> axes, vector<bool> buttons);


namespace
{
  //足回り
  uint32_t WHEEL_POWER = 100;

  PwmOut FRpout(PA_8); //MD1
  PwmOut FLpout(PA_0); //MD2
  PwmOut RRpout(PA_6); //MD3
  PwmOut RLpout(PB_6); //MD4

  DigitalOut FRdout(PC_11);
  DigitalOut FLdout(PD_2);
  DigitalOut RRdout(PC_9);
  DigitalOut RLdout(PB_9);

  Motor FRmotor(FRpout, FRdout, WHEEL_POWER, true);
  Motor FLmotor(FLpout, FLdout, WHEEL_POWER, true);
  Motor RRmotor(RRpout, RRdout, WHEEL_POWER, true);
  Motor RLmotor(RLpout, RLdout, WHEEL_POWER, true);

  Wheel wheel(FRmotor, FLmotor, RRmotor, RLmotor, 150);

  //アーム
  PwmOut EPwm(PB_13);
  PwmOut PPwm(PB_14);

  DigitalOut EdIn1(PA_9);
  DigitalOut EdIn2(PA_7);
  DigitalOut PdIn1(PB_5);
  DigitalOut PdIn2(PB_10);
  DigitalOut Rstby(PA_1);

  RoboMotor Emotor(EPwm, EdIn1, EdIn2, 100, true);
  RoboMotor Pmotor(PPwm, PdIn1, PdIn2, 100, true);
  ExpertsArm arm(Emotor, Pmotor, Rstby);

  //コントローラー
  CAN can1(PA_11, PA_12, 500000);
  Controller controller(can1, 0x334 /*, 0x2*/); //引数よくわからん

  //その他
  float CLOCK = 0.5;

  Serial pc(USBTX, USBRX);

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

    //コントローラデバッグ
    ControllerCheck(
      vector<int8_t>{ JS1_X, JS1_Y, JS2_X, JS2_Y },
      controller.buttons
    );

    if(BT_B){
      //アーム開
      //arm.Open(50);
      pc.printf("arm: OPEN \n");
    }
    else if(BT_X){
      //アーム閉
      //arm.Close(50);
      pc.printf("arm: CLOSE \n");
    }

    if(BT_Y){
      //アーム上
      //arm.Up(50);
      pc.printf("arm: UP \n");
    }
    else if(BT_A){
      //アーム下
      //arm.Down(50);
      pc.printf("arm: DOWN \n");
    }

    wheel.joystick(JS1_X, JS1_Y, pc); //オムニ8方制御
    wheel.joystickRotate(JS2_X, pc); //オムニ回転制御

    wait(CLOCK);
  }
}

void ControllerCheck(vector<int8_t> axes, vector<bool> buttons){
  pc.printf("AXES: %d , %d , %d , %d \n", axes[0], axes[1], axes[2], axes[3]);
  pc.printf("BUTTONS: ");
  for(int i = 0; i < buttons.size(); i++){
    pc.printf(" %d ,", buttons[i]);
  }
  pc.printf("\n");
}