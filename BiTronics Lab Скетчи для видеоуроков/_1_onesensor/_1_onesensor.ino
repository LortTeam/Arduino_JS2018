void setup(){
  Serial.begin(9600);
  }

void loop(){
  Serial.write("A0");
  Serial.write(map(analogRead(A0),0,1023,0,255));
  delay(3);
  }
