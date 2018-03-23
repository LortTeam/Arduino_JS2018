 void rss()
 {
  //delay(1);
 if (sData_2 > avr_2)
  {
    if (sData_0 > avr_0 && sData_1 <= avr_1)
  {
    Serial.println("dddddddddd");
    digitalWrite(led_pin3,HIGH);
    //timer++;
    /*if (timer == 1000)
    {*/
    reg--;
    if (reg > 4) reg = 1;
    if (reg < 1) reg = 4;
    led(reg);
    timer = 0;
    //}
    delay(1500);
  }

  // если превышен порог для 2 датчика активируем вращение основания в против.направлении и включаем светодиод,
  // также проверяем, чтобы угол на который поворачивается сервопривод не вышел за границы интервала
   if (sData_1 > avr_1 && sData_0 <= avr_1) 
  {
    Serial.println("dddddddddd");
    digitalWrite(led_pin3,HIGH);
    //timer++;
    /*if (timer == 1000)
    {*/
    reg++;
    if (reg > 4) reg = 1;
    if (reg < 1) reg = 4;
    led(reg);
    timer = 0;
    //}
    delay(1500);
    }
  }else digitalWrite(led_pin3,LOW);
    
  }
  
 

  void led(int sss)
  {
    lcd.setCursor(0,0);
    lcd.print(sss);
  }

