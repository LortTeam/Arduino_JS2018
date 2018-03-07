/*
  Оптический измеритель пульса
  Проект создан 6 марта 2016 года
  для канала Паяльник TV
  Автор: Evtomax (Евтихов Максим) 
  Email: evtomax@cxem.net
*/

// используемые пины
const int ledPin=6; // анод инфракрасного светодиода
const int sensorPin=A0; // выход датчика
//const int beepPin=7; // анод бипера со встроенным генератором

// размер буфера для вычисления порога
const int bufSize=16; 
// буфер для вычисления порога
int buf[bufSize];
// текущая позиция в буфере
int bufPos=0;
// сумма значений в буфере
long int bufSum=0;
// порог, вычисляемый, как среднее арифметическое 
// значений в буфере 
int  threshold=0;
// расстояние до верхнего и нижнего порогов 
// больше значение - меньше ложных срабатываний
// и меньше чувствительности
const int hyst=1; 

// пропуск некоторого количества замеров 
// после пересечения порога
int skipDetect=0; // количество замеров, 
                  // которые необходимо пропустить
const int crossSkip=4; // пишется в skipDetect
                       // после каждого пересечения порога
                       
// напряжение на датчике при включенном светодиоде
int sensorValueLedOn; 
// при выключенном светодиоде
// фоновая засветка
int sensorValueLedOff;
// значение на датчике с компенсацией фонового освещения
// по формуле sensorValueLedOff - sensorValueLedOn
int sensorValue;

// начало и конец текущего периода
// время записывается при детектировании
// пересечения порогового уровня сверху вниз
unsigned long prevTime, Time;

// находилось ли значение предыдущего отсчёта выше порога
boolean above; 

// мгновенное значение пульса
// количество ударов в минуту
int pulse;
// медианное значение пульса
int pulseMed;
// среднее значение пульса
int pulseAvg;

// медианный фильтр
int medFilt(int value){
  const int bufSize=7; // количество элементов
                       // должно быть нечётным
  static int buf[bufSize]; // массив нескольких 
                           // последних элементов
  static int sortBuf[bufSize]; // массив элементов
                               // который сортируется
  static int pos=0;  // текущая позиция в массиве
  
  buf[pos]=value;  // запись нового значения в массив
  
  // вычисление позиции следующего элемента
  pos++;
  if (pos==bufSize) pos=0;
  
  // копирование первого массива во второй
  for(int i=0; i<bufSize; i++){
    sortBuf[i]=buf[i];
  }
  
  // сортировка второго массива 
  for(int i=0; i<bufSize; i++){
    for(int j=i; j<bufSize; j++){
      if(sortBuf[i]<sortBuf[j]){
        int k=sortBuf[i];
        sortBuf[i]=sortBuf[j];
        sortBuf[j]=k;
      }
    }
  }
  
  // возвращается средний элемент 
  // из отсортированного массива
  return sortBuf[(bufSize/2)];
}

// вычисление среднего значения
int avg(int value){
  const int bufSize=16;  // количество значений
  static int buf[bufSize]; // массив из последних значений 
  static int pos; // текущая позиция
  static long int sum=0; // сумма всех значений
  int avg; // среднее значение
  
  buf[pos] = value; // добавление нового значения
  sum += value; // его добавление в сумму
  avg = sum/bufSize; // вычисление среднего значения
  // компенсация погрешности целочисленного деления
  if ((sum%bufSize)>=(bufSize/2)) avg++;
  
  // вычисление позиции следующего элемента
  pos++;
  if (pos==bufSize) pos=0;
    
  sum -= buf[pos]; // элемент, который будет перезаписан
                   // в следующий раз заранее вычитается
                   // из суммы 
  return avg;
}

// символьный дисплей HD44780 16x2
// RS, EN, D4, D5, D6, D7
//LiquidCrystal lcd(10, 8, 5, 4, 3, 2);

void setup() {
  pinMode(ledPin, OUTPUT);
  //pinMode(beepPin, OUTPUT);
  //digitalWrite(beepPin, LOW);
  Serial.begin(115200);
  //lcd.begin(16, 2);
}


void loop() {
  //digitalWrite(ledPin, HIGH); // светодиод включается
  //delay(10); // задержка, чтобы фототранзистор успел среагировать
  // замеряется напряжение с датчика со включенным светодиодом
  //sensorValueLedOn = analogRead(sensorPin); 
  //digitalWrite(ledPin, LOW); // светодиод выключается
  //delay(10);
  // замер с выключенным светодиодом
  //sensorValueLedOff = analogRead(sensorPin);
  
  // компенсация фоновой засветки
  //sensorValue = sensorValueLedOff-sensorValueLedOn;
  
  buf[bufPos] = map(analogRead(A0),0,1023,0,255);  // запись нового значения в буфер
  bufSum += sensorValue;  // прибавление его к сумме
  
  // вычисление порога
  // (среднее арифметическое всех значений в буфере)
  threshold = bufSum/bufSize+1; 

  // вычисление позиции следующего элемента
  bufPos++; 
  if (bufPos==bufSize) bufPos=0;
  
  // элемент, который будет перезаписан в следующий раз,
  // вычитается из суммы заранее
  bufSum -= buf[bufPos];
  
  // если не нужно пропускать замеры
  if (skipDetect==0){
    // детектирование того, что значение находится выше
    // верхнего порога
    if (sensorValue>(threshold+hyst)){ //+hyst
      // при пересечении порога детективрование отключается 
      // на несколько замеров 
      if (!above) skipDetect=crossSkip; 
      // показания с датчика теперь выше порога
      above=true; 
    }
    // детективрование того, что значение находится ниже 
    // нижнего порога
    else if (sensorValue<(threshold-hyst)){
      // при пересечении порога сверху вниз происходят вычисления
      if (above){
        // текущее время становится предыдущим
        prevTime = Time; 
        // текущее время обновляется
        Time = millis();
        // вычисляется мгновенное значение пульса
        // (60 секунд) * 1000 / (период в миллисекундах)
        int period = Time-prevTime;
        pulse = 60000/period;
        // компенсация погрешности целочисленного деления
        if ((60000%period)>=(60000/2)) pulse++;
        
        // если значение пульса реалистично, то оно выводится
        if ((pulse>=40)&&(pulse<=200)){
          // би
          //digitalWrite(beepPin, HIGH);
          // вывод данных
          //lcd.clear();
          //lcd.print("Inst:");
          //Serial.print(pulse);
          //lcd.setCursor(9,0);
          //Serial.print("Med:");
          pulseMed = medFilt(pulse);
          //Serial.print(pulseMed);
          //lcd.setCursor(4,1);
          //lcd.print("Avg: ");
          pulseAvg = avg(pulseMed);
          //Serial.print(pulseAvg);   
          Serial.print("Inst: ");
          Serial.print(pulse);
          Serial.print("; Med: ");
          Serial.print(pulseMed);
          Serial.print("; Avg: ");
          Serial.println(pulseAvg);    
          // п
          //digitalWrite(beepPin, LOW);
          // последнее значение с датчика ниже порога
          // above = false; на самом деле должно быть не тут
        }
        // при пересечении порога детективрование отключается 
        // на несколько замеров        
        skipDetect=crossSkip;
      }
      // а здесь
      above = false;
    }
  }else{
    skipDetect--; // один замер пропущен, 
                  // поэтому ещё надо пропустить
                  // на один меньше :-)
  } 
}
