#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


#define RX 2
#define TX 3
#define LED 13

#include <Servo.h>
#include <LSM6.h>

LSM6 imu;

char report[80];

Servo myservo1;  // create servo object to control a servo pin10
Servo myservo2;  // create servo object to control a servo

int pos = 0;   
int servoInitial=0; 

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  AFMS.begin();
  myservo1.attach(10);
  myservo2.attach(9);
  myservo1.write(servoInitial);
  myservo2.write(servoInitial);
  /*if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();*/
  
}
int temp = 0;
void loop() {
  
  /*
  imu.read();
  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
    imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z);
  Serial.println(report);
  delay(100);
  */
  
  if (Serial.available() > 0)
  { // If data comes in from serial monitor, send it out to XBee4654665
    digitalWrite(LED,HIGH);
    
    temp= Serial.read();

    switch (temp) {
      case '%':
        openServoArm();
        break;
      case 's':
        closeServoArm();
        break;
      case 'x':
        letsGO();
        break;
      default:
        break;
    }

  }else{
    digitalWrite(13,LOW);
  }
}

void openServoArm(){
  
    myMotor1->setSpeed(0);
    myMotor2->setSpeed(0);
    for (pos = 0; pos <= 20; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      //myservo1.write(pos);
      myservo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(100);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 0; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo1.write(pos);    
          //myservo2.write(pos);           // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position
     }
}

void closeServoArm(){
    for (pos = 20; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      //myservo1.write(pos);    
      myservo2.write(pos);           // tell servo to go to position in variable 'pos'
      delay(100);                       // waits 15ms for the servo to reach the position
    }
}
void letsGO(){
    for (pos = 0; pos <= 20; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          //myservo1.write(pos);    
          myservo2.write(pos);           // tell servo to go to position in variable 'pos'
          delay(100);                       // waits 15ms for the servo to reach the position
     }
    
     
    myMotor1->setSpeed(2000);
    myMotor2->setSpeed(2000);
    myMotor2->run(FORWARD);
    myMotor1->run(FORWARD);
    delay(60000);
    myMotor1->setSpeed(0);
    myMotor2->setSpeed(0);
    
    for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo1.write(pos);    
          //myservo2.write(pos);           // tell servo to go to position in variable 'pos'
          delay(100);                       // waits 15ms for the servo to reach the position
     }
     myMotor3->setSpeed(2000);
     myMotor3->run(FORWARD);
     delay(10000);
     myMotor3->setSpeed(0);
     for (pos = 150; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo1.write(pos);    
          //myservo2.write(pos);           // tell servo to go to position in variable 'pos'
          delay(100);                       // waits 15ms for the servo to reach the position
     }
    
}
