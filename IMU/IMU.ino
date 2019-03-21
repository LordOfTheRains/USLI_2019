/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 11)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/

#include <Wire.h>
#include <LSM6.h>


LSM6 imu;

char report[80];
unsigned long lastTime;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
  lastTime = millis();//reference time
}

float x_vel = 0;
float x_pos = 0;

void loop()
{
  imu.read();
  
  
  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
    imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z);
  Serial.println(report);
  
  long currentT = millis();
  float acc = imu.a.y*0.061/1000*9.81;
  integrate((currentT-lastTime)/1000.0, acc);
  lastTime = currentT;
  Serial.print(x_vel);
  Serial.print(" : ");
  Serial.println(x_pos);
  delay(1000);
}

void integrate(float del_t, float x_acc) { 
  x_vel += x_acc*del_t;
  x_pos += x_vel*del_t;
  return;
  
}
