if (sData_2 > avr_2)
  {
    reg++;
    if (reg > 4) reg = 1;
    if (reg < 1) reg = 1;
    led(reg);
  }

  void led(int sss)
  {
    if (sss == 1)
    {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
    }
    if (sss == 2)
    {
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
    }
    if (sss == 1)
    {
      digitalWrite(r, LOW);
      digitalWrite(g, LOW);
      digitalWrite(b, HIGH);
    }
    if (sss == 1)
    {
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, HIGH);
    }
  }

