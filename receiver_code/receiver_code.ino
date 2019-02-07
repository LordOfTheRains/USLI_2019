#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


#define RX 2
#define TX 3
#define LED 13

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo pin10
Servo myservo2;  // create servo object to control a servo

int pos = 0;   
int servoInitial=20; 

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  AFMS.begin();
  myservo1.attach(10);
  myservo2.attach(9);
  myservo2.write(servoInitial);
}
int temp = 0;
void loop() {

  
  if (Serial.available() > 0)
  { // If data comes in from serial monitor, send it out to XBee4654665
    digitalWrite(13,HIGH);
    
    temp= Serial.read();

    switch (temp) {
      case 's':
        handleServoCommand();
        break;
      case 'x':
        handleMotorCommand();
        break;
      default:
        break;
    }

  }else{
    digitalWrite(13,LOW);
  }
}


void handleServoCommand(){
    for (pos = 20; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      //myservo1.write(pos);    
      myservo2.write(pos);           // tell servo to go to position in variable 'pos'
      delay(100);                       // waits 15ms for the servo to reach the position
    }
}
void handleMotorCommand(){
    myMotor1->setSpeed(1000);
    myMotor2->setSpeed(1000);
    myMotor2->run(FORWARD);
    myMotor1->run(FORWARD);
    delay(5000);
    myMotor1->setSpeed(0);
    myMotor2->setSpeed(0);
}
