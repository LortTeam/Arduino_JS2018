#include <TimerOne.h>

#define led1 13
#define led2 12
#define btn1 10
#define btn2 11
#define ton1 9

bool btnstart1 = true;
bool btnstart2 = true;

bool ledtemp1 = false;
bool ledtemp2 = false;

int pulse() {
  int k = 0;
  //Подсчет пульса
  return k;
}

bool calibrate() {
    bool temp2 = digitalRead(btn2);

  if(btnstart2 && !temp2) {
    delay(10);
    temp2 = digitalRead(btn2);
    if(!temp2) {  
      //tone(ton1, 500);                          
      //delay(5000);
      //noTone(ton1);
      ledtemp1 = !ledtemp1;
      digitalWrite(led1, ledtemp1);
      ledtemp2 = !ledtemp2;
      digitalWrite(led2, ledtemp2);

      for (int i = 0; i < 6000; i++) {
        pulse(); 
        delay(1);
      }

      //tone(ton1, 500);
      
      ledtemp1 = !ledtemp1;
      digitalWrite(led1, ledtemp1);
      delay(250);
      for (int i = 0; i < 8; i++) {
          ledtemp1 = !ledtemp1;
          digitalWrite(led1, ledtemp1);
          ledtemp2 = !ledtemp2;
          digitalWrite(led2, ledtemp2);
          delay(250);  
        }
    }
    ledtemp2 = !ledtemp2;
    digitalWrite(led2, ledtemp2);
      
    //noTone(ton1);
  }
  
  btnstart2 = temp2;
}

bool grant() {
     bool temp1 = digitalRead(btn1);
  
  if(btnstart1 && !temp1) {
    delay(10);
    temp1 = digitalRead(btn1);
    if(!temp1){
      //tone(ton1, 500);                         
      delay(5000);
      //noTone(ton1);
      ledtemp1 = !ledtemp1;
      digitalWrite(led1, ledtemp1);
      delay(250);
      for (int i = 0; i < 8; i++) {
          ledtemp1 = !ledtemp1;
          digitalWrite(led1, ledtemp1);
          ledtemp2 = !ledtemp2;
          digitalWrite(led2, ledtemp2);
          delay(250);  
      }
      for (int i = 0; i < 6000; i++) {
        pulse(); 
        delay(1);
      }

      ledtemp1 = !ledtemp1;
      digitalWrite(led1, ledtemp1);
      } 
  }
  
  btnstart1 = temp1; 
}

void setup() {
  pinMode(led1, OUTPUT);                  
  pinMode(led2, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}

void loop() {
  calibrate();
  grant();
}
