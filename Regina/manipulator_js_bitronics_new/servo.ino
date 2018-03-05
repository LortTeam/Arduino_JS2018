void serv(int s)
{
  int ss = 5;
  
  if (sData_0 > avr_0 && sData_1 <= avr_1)
  {
    digitalWrite(led_pin1, HIGH);//------
    digitalWrite(led_pin2, LOW);
    Serial.println("llllllllllllllllllll");
    if (s == 1)
    {
      if (myservo1.read() > 10)
      {
        myservo1.write(myservo1.read() - ss);
      }
    }

    if (s == 2)
    {
      if (myservo2.read() > 10)
      {
        myservo2.write(myservo2.read() - ss);
      }
    }

    if (s == 3)
    {
      if (myservo3.read() > ss)
      {
        myservo3.write(myservo3.read() - ss);
      }
    }

    if (s == 4)
    {
      if (myservo4.read() > ss)
      {
        myservo4.write(myservo4.read() - ss);
      }
    }
  }

  // если превышен порог для 2 датчика активируем вращение основания в против.направлении и включаем светодиод,
  // также проверяем, чтобы угол на который поворачивается сервопривод не вышел за границы интервала
  else if (sData_1 > avr_1 && sData_0 <= avr_1) 
  {
    if (s == 1)
    {
      if (myservo1.read() < 170)
      {
        myservo1.write(myservo1.read() + ss);
      }
    }

    if (s == 2)
    {
      if (myservo2.read() < 170)
      {
        myservo2.write(myservo2.read() + ss);
      }
    }

    if (s == 3)
    {
      if (myservo3.read() < 170)
      {
        myservo3.write(myservo3.read() + ss);
      }
    }

    if (s == 4)
    {
      if (myservo4.read() < 170)
      {
        myservo4.write(myservo4.read() + ss);
      }
    }
  }else
  {
    digitalWrite(led_pin1, LOW); 
    digitalWrite(led_pin2, LOW);
    Serial.println(" ");
  }
}

