#include "controller.h"

#include <stddef.h>
#include <stdint.h>

#include <mbed.h>

/*
canから通信を受け取ったら
recieveData -> parse -> callback
の順に呼ばれる
*/


Controller::Controller(CAN& _can, const uint32_t _canId) : can(_can), canId(_canId) {
  can.attach(callback(this, &Controller::recieveData));
}

//ここにCallbackを設定する
void Controller::setButtonEventListener(Callback<void(size_t, bool)> cb) {
  buttonCallback = cb;
}

void Controller::recieveData() {
  CANMessage msg;
  if (can.read(msg) && msg.id == canId && msg.type == CANData) {
    parse(msg.data, msg.len);
  }
}

//QUESTION: dataってどんな形で来るの？

void Controller::parse(const uint8_t* data, const size_t length) {
  axes.LX = ((int8_t) data[0] > 5 || (int8_t) data[0] < -5) ? (int8_t) data[0] : 0;
  axes.LY = ((int8_t) data[1] > 5 || (int8_t) data[1] < -5) ? (int8_t) data[1] : 0;
  axes.RX = ((int8_t) data[2] > 5 || (int8_t) data[2] < -5) ? (int8_t) data[2] : 0;
  axes.RY = ((int8_t) data[3] > 5 || (int8_t) data[3] < -5) ? (int8_t) data[3] : 0;
  buttons.resize(data[4], false);
  for (size_t i = 0; i < data[4]; i++) {
    //二個目はi > 64でfalse
    const bool next = data[5 + i / 8] & 0x80 >> i % 8;
    if (buttons[i] != next && buttonCallback) {//前回と状態が異なった場合発火
      buttonCallback(i, next);
    }
    buttons[i] = next;
  }
}