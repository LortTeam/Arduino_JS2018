 void rss()
 {
  //delay(1);
 if (sData_2 > avr_2)
  {
    digitalWrite(led_pin3,HIGH);
    //timer++;
    /*if (timer == 1000)
    {*/
    reg++;
    if (reg > 4) reg = 1;
    if (reg < 1) reg = 1;
    led(reg);
    timer = 0;
    //}
    delay(1500);
  }
  else digitalWrite(led_pin3,LOW);
 }

  void led(int sss)
  {
    lcd.setCursor(0,0);
    lcd.print(sss);
  }

