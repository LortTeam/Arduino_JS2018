void rss() {
  delay(10);
    
    if (reg < 1) reg = 1;
    if (reg > 4) reg = 1;
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
    
    delay(100);
  
  
 }

