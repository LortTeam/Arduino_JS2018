// подключаем библиотеку для работы с сервоприводами
#include <Servo.h> 

// длина массива для обработки значений с датчиков
#define arrSize 32

// чувствительность срабатывания 
double n0 = 2.0; 
double n1 = 3.0; 
double n2 = 3.0;

int reg = 1;

// создаем нужное количество объектов (для сервоприводов), например четыре:
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// пины для подключения сервоприводов, например такие:
const int serv_pin1 = 4; 
const int serv_pin2 = 5; 
const int serv_pin3 = 6; 
const int serv_pin4 = 7;

// пины для подключения светодиодов (по кол-ву датчиков или просто один на срабатывание), например такие:
const int led_pin1 = 13; 
const int led_pin2 = 12; 
const int led_pin3 = 11; 
const int led_pin4 = 10;
const int led_pinl = 9;
const int led_pinr = 8;
// пины для подключения датчиков электромиограммы, например такие:
const int bio_pin1 = 0; 
const int bio_pin2 = 1; 
const int bio_pin3 = 2; 
const int bio_pin4 = 3;

double sData_0 = 0;        // Результат обработки с 1-ого датчика
double sData_1 = 0;        // Результат обработки со 2-ого датчика
double sData_2 = 0;        // Результат обработки с 3-ого датчика
double sData_3 = 0;        // Результат обработки с 4-ого датчика

double avr_0 = 0;          // Пороговое значение (срабатывание) для 1-ого датчика
double avr_1 = 0;          // Пороговое значение для 2-ого датчика
double avr_2 = 0;          // Пороговое значение для 3-ого датчика
double avr_3 = 0;          // Пороговое значение для 4-ого датчика

int val_0[arrSize];        // Массив для обработки значений с датчика 1     
int val_1[arrSize];        // Массив для обработки значений с датчика 2       
int val_2[arrSize];        // Массив для обработки значений с датчика 3       
int val_3[arrSize];        // Массив для обработки значений с датчика 4     

// подпрограмма для считывания и обработки значений с датчиков электромиограммы
void readSensor() {

  for (int i = 0; i < arrSize; i++)
  {
  // считываем значения с датчиков, конвертация из 10 бит в байт, заносим в массивы
  val_0[i] = map(analogRead(bio_pin1), 0, 1023, 0, 255); 
  val_1[i] = map(analogRead(bio_pin2), 0, 1023, 0, 255);
  val_2[i] = map(analogRead(bio_pin3), 0, 1023, 0, 255);
  val_3[i] = map(analogRead(bio_pin4), 0, 1023, 0, 255);
  }
  
  // начальные значения мин. и макс.
  double maxV_0 = val_0[0], minV_0 = val_0[0];
  double maxV_1 = val_1[0], minV_1 = val_1[0];
  double maxV_2 = val_2[0], minV_2 = val_2[0];
  double maxV_3 = val_3[0], minV_3 = val_3[0];

  // определяем мин. и макс. значение в массиве, когда он заполнен
  for (int k = 0; k < arrSize; k++) {
    if ( val_1[k] > maxV_1)
      maxV_1 = val_1[k];
    if ( val_1[k] < minV_1)
      minV_1 = val_1[k];

    if ( val_0[k] > maxV_0)
      maxV_0 = val_0[k];
    if ( val_0[k] < minV_0)
     minV_0 = val_0[k];

    if ( val_2[k] > maxV_2)
      maxV_2 = val_2[k];
    if ( val_2[k] < minV_2)
      minV_2 = val_2[k];

    if ( val_3[k] > maxV_3)
      maxV_3 = val_3[k];
    if ( val_3[k] < minV_3)
      minV_3 = val_3[k];
          
    }

  // рассчитываем значения на основании полученных значений мин. и макс.
  sData_0 =  0.4*sData_0 + 0.6*(maxV_0 - minV_0); 
  sData_1 =  0.4*sData_1 + 0.6*(maxV_1 - minV_1);
  sData_2 =  0.4*sData_2 + 0.6*(maxV_2 - minV_2);
  sData_3 =  0.4*sData_3 + 0.6*(maxV_3 - minV_3);
  sData_0 = constrain(sData_0 * n0, 0, 255);
  sData_1 = constrain(sData_1 * n1, 0, 255);
  sData_2 = constrain(sData_2 * n2, 0, 255);
  sData_2 = constrain(sData_3 * n0, 0, 255);
  avr_0 = (maxV_0 + minV_0)/2;
  avr_1 = (maxV_1 + minV_1)/2;
  avr_2 = (maxV_2 + minV_2)/2;
  avr_3 = (maxV_3 + minV_3)/2;
}

void setup() 
{ 
  // устанавливаем пины для управления сервоприводом 
  myservo1.attach(serv_pin1);
  myservo2.attach(serv_pin2); 
  myservo3.attach(serv_pin3); 
  myservo4.attach(serv_pin4); 

  // выводим манипулятор в некоторое начальное положение
  myservo1.write(80);
  myservo2.write(70);
  myservo3.write(50);
  myservo4.write(9);

  // конфигурируем пины светодиодов, как выход
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(led_pin4, OUTPUT);
  pinMode(led_pinl, OUTPUT);
  pinMode(led_pinr, OUTPUT);

  // выключаем светодиоды
  //digitalWrite(led_pin1, LOW);
  digitalWrite(led_pin2, LOW);
  digitalWrite(led_pin3, LOW);
  digitalWrite(led_pin4, LOW);
  digitalWrite(led_pinl, LOW);
  digitalWrite(led_pinr, LOW);

  // Обнуляем исходные массивы
  for (int k = 0; k < arrSize; k++) {
    val_0[k] = 0;
    val_1[k] = 0;
    val_2[k] = 0;
    val_3[k] = 0;
  }
  
  Serial.begin(115200); 
}

/*
Интервал (Вращение основания) от 10 до 170
Интервал (Левое плечо) от 10 до 150
Интервал (Правое плечо) от 35 до 140
Интервал (Захват)  от 40 до 68
*/

/*
пример: 
датчик 1 - вращение основания по час. стрелке
датчик 2 - вращение основания против час. стрелке
датчик 3 - вращение плеча по час. стрелке
датчик 4 - вращение плеча против час. стрелке
1 и 2 одновременно - захват закрыть
3 и 4 одновременно - захват открыть
*/

void loop() 
{ 
  // пример реализации части задания с двумя датчиками - основание (два движения) и захват (одно движение)
  rss();
  // считываем и обрабатываем значения с датчиков   
  readSensor();
  
  // просмотр в мониторинге порта - для проверки и отслеживания полученных значений
  Serial.print("sData0: ");
  Serial.print(sData_0);
  Serial.print(", avr0: ");
  Serial.println(avr_0);
  Serial.print("sData1: ");
  Serial.print(sData_1);
  Serial.print(", avr1: ");
  Serial.println(avr_1);

  serv(reg);
  
  delay(100);
} 


