#define STRLED 11
#define SERVOcLED 12
#define SERVOoLED 13
#define STARTBTN 2
#define SERVOcBTN 3
#define SERVOoBTN 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(STRLED, OUTPUT);
  pinMode(SERVOcLED, OUTPUT);
  pinMode(SERVOoLED, OUTPUT);
  pinMode(STARTBTN, INPUT);
  pinMode(SERVOcBTN, INPUT);
  pinMode(SERVOoBTN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int startPressed =  digitalRead(STARTBTN);
  int servoCPressed =  digitalRead(SERVOcBTN);
  int servoOPressed =  digitalRead(SERVOoBTN);
  if (startPressed == HIGH ) {//button pressed
   
    Serial.println('x'); 
    digitalWrite(STRLED,HIGH);
    delay(1000);
  }else{
    digitalWrite(STRLED,LOW);
  }
  if (servoCPressed == HIGH ) {//button pressed
   
    Serial.println('s'); 
    digitalWrite(SERVOcLED,HIGH);
    delay(1000);
  }else{
    digitalWrite(SERVOcLED,LOW);
  }
  if (servoOPressed == HIGH ) {//button pressed
   
    Serial.println('o'); 
    digitalWrite(SERVOoLED,HIGH);
    delay(1000);
  }else{
    digitalWrite(SERVOoLED,LOW);
  }
}
