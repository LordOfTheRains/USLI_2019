#define STRLED 11
#define SERVOLED 12
#define STARTBTN 2
#define SERVOBTN 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(STRLED, OUTPUT);
  pinMode(SERVOLED, OUTPUT);
  pinMode(STARTBTN, INPUT);
  pinMode(SERVOBTN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int startPressed =  digitalRead(STARTBTN);
  int servoPressed =  digitalRead(SERVOBTN);
  if (startPressed == HIGH ) {//button pressed
   
    Serial.println('x'); 
    digitalWrite(STRLED,HIGH);
    delay(1000);
  }else{
    digitalWrite(STRLED,LOW);
  }
  if (servoPressed == HIGH ) {//button pressed
   
    Serial.println('s'); 
    digitalWrite(SERVOLED,HIGH);
    delay(1000);
  }else{
    digitalWrite(SERVOLED,LOW);
  }
}
