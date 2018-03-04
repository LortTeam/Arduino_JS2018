#include <Servo.h>
Servo s;
int val = 90;
void setup(){
  Serial.begin(9600);
  s.attach(3);
  delay(1000);
}

void loop(){
  if(Serial.available())
    val = Serial.parseInt();
 s.write(val);
}
