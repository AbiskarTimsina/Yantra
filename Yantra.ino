/*
 * Code for Yantra (National League 2020)
 * Coded by: Abiskar Timsina for RAC Thapathali
 * Date: 28th Jan 2020
 */
 
#include <ibus.h>


// For motor Driver
//Enable Pins for the motor driver with PWM
#define enableRight 3
#define enableLeft 9

#define rightForwards 4
#define leftForwards 5
#define rightBackwards 6
#define leftBackwards 7

//relay control
#define relay_1 11
#define relay_2 12

int16_t channel[10];
int up,side,shoot;

void setup() {
  Serial.begin(115200);
  IBus.begin(Serial);
  
  pinMode (enableRight,OUTPUT);
  pinMode (enableLeft,OUTPUT);
  
  pinMode (rightForwards,OUTPUT);
  pinMode (leftForwards,OUTPUT);
  pinMode (rightBackwards,OUTPUT);
  pinMode (leftBackwards,OUTPUT);

  pinMode (relay_1,OUTPUT);
  pinMode (relay_2,OUTPUT);
}

void loop() {
  read_channel_data();

  up = map(channel[1],1000,2000,-255,255);
  side = map(channel[3],1000,2000,-255,255);
  shoot = map(channel[5],1000,2000,-255,255);

  Serial.println (up);
  
  if ( (up > 30 && up <= 255) && (side < 30 && side > -30) ){
    analogWrite(enableRight,abs(up));
    analogWrite(enableLeft,abs(up));

    forwards();
  }
  
  else if ( (up < -30 && up >= -255 ) && (side < 30 && side > -30) ){
    analogWrite(enableRight,abs(up));
    analogWrite(enableLeft,abs(up));

    backwards();
  }
  else if ( (side > 30 && side <= 255) ){
    analogWrite(enableRight,abs(side));
    analogWrite(enableLeft,abs(side));

    left();
  }
  else if ( (side < -30 && side >= -255) ){
    analogWrite(enableRight,abs(side));
    analogWrite(enableLeft,abs(side));

    right();
  }
  else
  {
    stopped();
  }
  
}


void read_channel_data(){
  IBus.loop();

  for (int i = 0; i<10; i++){
    channel[i] = IBus.readChannel(i);
  }

}

void forwards() {
  Serial.println("Going Forwards");
  digitalWrite(leftForwards, HIGH);
  digitalWrite(rightForwards, HIGH);
  digitalWrite (leftBackwards, LOW);
  digitalWrite (rightBackwards, LOW);
}

void backwards() {
  Serial.println("Going Backwards");
  digitalWrite(leftBackwards, HIGH);
  digitalWrite(rightBackwards, HIGH);
  digitalWrite(leftForwards, LOW);
  digitalWrite(rightForwards, LOW);
}

void left() {
  Serial.println("Going Left");
  digitalWrite (rightForwards, HIGH);
  digitalWrite (leftBackwards, HIGH);
  digitalWrite (rightBackwards, LOW);
  digitalWrite (leftForwards, LOW);
}

void right() {
  Serial.println("Going Right");
  digitalWrite (leftForwards, HIGH);
  digitalWrite (rightBackwards, HIGH);
  digitalWrite (leftBackwards, LOW);
  digitalWrite (rightForwards, LOW);
}

void stopped() {
  Serial.println("Stopped");
  digitalWrite (leftForwards, LOW);
  digitalWrite (leftBackwards, LOW);
  digitalWrite (rightBackwards, LOW);
  digitalWrite (rightForwards, LOW);
}
