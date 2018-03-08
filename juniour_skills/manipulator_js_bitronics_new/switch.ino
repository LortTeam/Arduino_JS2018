void rss()
 {
  //delay(1);
  //digitalWrite(led_pin3,HIGH);
  //timer++;
  /*if (timer == 1000)
  {*/
  //reg++;
  
  if (reg < 1) reg = 1;
  if (reg > 4) reg = 1;
  if (sData_0 > avr_0 && sData_1 <= avr_1 && sData_2 > avr_2) {
    reg--;
  } else if (sData_1 > avr_1 && sData_0 <= avr_1 && sData_2 > avr_2) {
    reg++;
  }
  if (reg == 1) {
    digitalWrite(led_pin1,HIGH);
    digitalWrite(led_pin2,LOW);
    digitalWrite(led_pin1,LOW);
    digitalWrite(led_pin1,LOW);
  } 
  if (reg == 2) {
    digitalWrite(led_pin1,LOW);
    digitalWrite(led_pin2,HIGH);
    digitalWrite(led_pin3,LOW);
    digitalWrite(led_pin4,LOW);
  } 
  if (reg == 3) {
    digitalWrite(led_pin1,LOW);
    digitalWrite(led_pin2,LOW);
    digitalWrite(led_pin3,HIGH);
    digitalWrite(led_pin4,LOW);
  } 
  if (reg == 4) {
    digitalWrite(led_pin1,LOW);
    digitalWrite(led_pin2,LOW);
    digitalWrite(led_pin3,LOW);
    digitalWrite(led_pin4,HIGH);
  } 
  
  
  //led(reg);
  //timer = 0;
  //}
  delay(1500);
 }

