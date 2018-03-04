#include <Servo.h>

#define DELTA_A 40
#define DELTA_B 50
#define BUFFER_SIZE 3
#define ITERATIONS 40

#define THUMB_PIN 10                //pins
#define FOREFINGER_PIN 9
#define MIDDLEFINGER_PIN 6
#define RINGFINGER_PIN 5
#define LITTLEFINGER_PIN 3

#define ITERATION_TIME 2            //time 

#define THUMB_CLENCHED 150           //servo positions
#define FOREFINGER_CLENCHED  180
#define MIDDLEFINGER_CLENCHED  180
#define RINGFINGER_CLENCHED  0
#define LITTLEFINGER_CLENCHED  10

#define THUMB_RELAXED 10
#define FOREFINGER_RELAXED 10
#define MIDDLEFINGER_RELAXED 20
#define RINGFINGER_RELAXED 150
#define LITTLEFINGER_RELAXED 140

Servo thumb;
Servo foreFinger;
Servo middleFinger;
Servo ringFinger;
Servo littleFinger;

boolean flag = false;
int amplitudeAY = 0;
int amplitudeBY = 0;

unsigned long previousMillis = 0;   
double tresholdA = 1024;
double tresholdB = 1024;     
int k = 0;


int bufferA[BUFFER_SIZE];
int bufferB[BUFFER_SIZE];


int sumBufferA();
int sumBufferB();
void firstMode();
void gestureOne();
void gestureTwo();
void gestureThree();
void gestureFour();

  //  (szhatoe - razhatoe)
  // 10 - bolshoi, (10-150)
  // 9 - ukazatel   (180 - 10)
  // 6 - srednij (180 - 20)
  // 5 - bezymjnii (150-0)
  // 3 - mizinec   (0 - 140)



void setup() {
  thumb.attach(THUMB_PIN);
  foreFinger.attach(FOREFINGER_PIN);
  middleFinger.attach(MIDDLEFINGER_PIN);
  ringFinger.attach(RINGFINGER_PIN);
  littleFinger.attach(LITTLEFINGER_PIN);
  Serial.begin(9600);
}


void loop() {
  int sensorValueA;
  int sensorValueB;
  int i = 0;
  int maxValueA = 0;
  int minValueA = 1023;
  int maxValueB = 0;
  int minValueB = 1023;

  
  while(i < ITERATIONS){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= ITERATION_TIME){

        previousMillis = currentMillis;
        sensorValueA = analogRead(A0);
        sensorValueB = analogRead(A1);
      
        maxValueA = max(maxValueA, sensorValueA);
        maxValueB = max(maxValueB, sensorValueB);
        minValueA = min(minValueA, sensorValueA);
        minValueB = min(minValueB, sensorValueB);
        
        i++;
    }
  }

  
  int amplitudeA = maxValueA - minValueA;
  amplitudeAY = 0.15*amplitudeA + 0.85*amplitudeAY;

  int amplitudeB = maxValueB - minValueB;
  amplitudeBY = 0.15*amplitudeB + 0.85*amplitudeBY;

  tresholdA = amplitudeAY > tresholdA ? tresholdA : 0.95*tresholdA + 0.05*(amplitudeAY + DELTA_A);
  tresholdB = amplitudeBY > tresholdB ? tresholdB : 0.95*tresholdB + 0.05*(amplitudeBY + DELTA_B);


  
  
  if (amplitudeAY >= tresholdA){
    bufferA[k] = 1;
  } else bufferA[k] = 0;

  if (amplitudeBY >= tresholdB){
    bufferB[k] = 1;
  } else bufferB[k] = 0;

  k++;
  k = k%BUFFER_SIZE;
  

  Serial.print(amplitudeAY);
  Serial.print('/');
  Serial.print(tresholdA,0);
  Serial.print('\t');
  Serial.print(amplitudeBY);
  Serial.print('/');
  Serial.print(tresholdB,0);
  Serial.print('\t');
  Serial.print(amplitudeAY > tresholdA);
  Serial.print('\t');
  Serial.print(amplitudeBY > tresholdB);
  Serial.print('\t');
    
  firstMode();  
}


int sumBufferA(){
  int sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++){
    sum += bufferA[i];
  }
  return sum;
}


int sumBufferB(){
  int sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++){
    sum += bufferB[i];
  }
  return sum;
}


int gestureRecognize(){
  switch ( sumBufferA() + 10 * sumBufferB()){
    case 0:
      return 0;
      break;
    case BUFFER_SIZE:
      return 1;
      break;
    case BUFFER_SIZE * 10:
      return 2;
      break;
    case BUFFER_SIZE * 11:
      return 3;
      break;
    default:
      return -1; 
  }
}





void firstMode(){
  
  switch(gestureRecognize()){
    case 0:
      Serial.println("Gesture 1");
      gestureOne();
      flag = false;
      break;
    case 1:
      Serial.println("Gesture 2");
      gestureTwo();
      flag = true;
      break;
    case 2:
      Serial.println("Gesture 3");
      gestureThree();
      flag = true;
      break;
    case 3:
      if (!flag){ 
        Serial.println("Gesture 4");
        gestureFour();
        break;
      } else Serial.println("Relax");
    default:
    Serial.println("kek");
  }
  
}

void gestureOne(){                    //ладонь
  thumb.write(THUMB_RELAXED);
  foreFinger.write(FOREFINGER_RELAXED);
  middleFinger.write(MIDDLEFINGER_RELAXED);
  ringFinger.write(RINGFINGER_RELAXED);
  littleFinger.write(LITTLEFINGER_RELAXED); 
}

void gestureTwo(){                  // V
  thumb.write(THUMB_CLENCHED);
  foreFinger.write(FOREFINGER_RELAXED);
  middleFinger.write(MIDDLEFINGER_RELAXED);
  ringFinger.write(RINGFINGER_CLENCHED);
  littleFinger.write(LITTLEFINGER_CLENCHED); 
}

void gestureThree(){              //Коза  
  thumb.write(THUMB_CLENCHED);
  foreFinger.write(FOREFINGER_RELAXED);
  middleFinger.write(MIDDLEFINGER_CLENCHED);
  ringFinger.write(RINGFINGER_CLENCHED);
  littleFinger.write(LITTLEFINGER_RELAXED);
}

void gestureFour(){             //кулак
  thumb.write(THUMB_CLENCHED);
  foreFinger.write(FOREFINGER_CLENCHED);
  middleFinger.write(MIDDLEFINGER_CLENCHED);
  ringFinger.write(RINGFINGER_CLENCHED);
  littleFinger.write(LITTLEFINGER_CLENCHED);
}



