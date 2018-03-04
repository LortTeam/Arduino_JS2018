#include <TimerOne.h>

int count = 0; 
void setup() {
  Serial.begin(115200);
  
  Timer1.initialize(3000); //30000
  Timer1.attachInterrupt(sendData);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void sendData(){
 
// count++;
 
 Serial.write("A0");  
 Serial.write(map(analogRead(A0),0,1023,0,255));
// Serial.println(map(analogRead(A0),0,1023,0,255));
 
 //  if (count == 10){
     Serial.write("A1");  
     Serial.write(map(analogRead(A1),0,1023,0,255));
//     count=0; 
 //  }
  
}
