#include <fft.h> // Fourier transform making, don't forget to install this library: https://www.dropbox.com/s/vw46osetrwgft43/FFT.zip
#define num 256  // number if data point for Fourier transform
#define FAN_PIN 13   // digital pin for fan (motor pin IN-A) connection
#define ERROR_LED_PIN 3 // digital pin for Error_Led connection - indication of high level of noise

int8_t im[num], data[num];
int i=0;
byte sped = 0, val = 0;
bool fail = false; // noise flag: true if level of noise is high

void setup() {
  Serial.begin(115200);    // Serial port initialization
  pinMode(FAN_PIN,OUTPUT); // Fan (motor) pin as output
  pinMode(ERROR_LED_PIN,OUTPUT); // Led pin as output
}

void loop() {
  
  int8_t sum = 0;
  for (i=0; i < num; i++){
    val = analogRead(A0)/8; // 10 bit to 8 bit from ADC convertion                                   
    data[i] = val;  
    Serial.write("A0"); // sending data to visualisation in Bitronics Software https://www.dropbox.com/s/oyoo81mhqclg5ow/Bitronics.exe
    Serial.write(val);  // sending data to visualisation in Bitronics Software https://www.dropbox.com/s/oyoo81mhqclg5ow/Bitronics.exe
    if (data[i] < 2 || data[i] > 120){ // if signal value is less or grater - we turn on noise flag true
      fail = true;
    }
   
    delay(2); // waiting for all calculations being prepaired...
    im[i] = 0;                                               
    sum = sum+data[i];
  }
 
 if (!fail){
   digitalWrite(ERROR_LED_PIN,LOW); // if noise is low - switching off the ERROR_LED
   
   for (i=0; i < num; i++){                                     
     data[i] = data[i] - sum/num;
   }
    
   fix_fft(data,im,8,0); // Fourier transform preparation
   
    bool flag = false;
    for (i=6; i<15; i++){ // alpha-rhytm spectral power calculation
      if(sqrt(data[i]*data[i] + im[i]*im[i]) > 3){
        flag = true;
      }
    }
    
    if (!flag){
      if (sped != 0){
        sped = sped - 25;
      }
    }

    if(flag){
      sped = 180;
      flag = false; 
    }
    
    analogWrite(FAN_PIN,sped); // Fan activation
    
 }
 else{ 
   digitalWrite(ERROR_LED_PIN,HIGH); // if noise level is high, we should turn on Error_Led,
   analogWrite(FAN_PIN,0);           // ... and to stop Fan rotation
 }
 
 fail = false;
}

