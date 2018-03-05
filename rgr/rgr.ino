int a;
int b;
int green = 11;
int yellow = 12;
int red = 13;

void setup() {
pinMode(green, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(red, OUTPUT);
pinMode(A1, INPUT);
Serial.begin(9600);
}

void loop() {
kgr();
if (b = 1)
  {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
  }
  if (b = 2)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
  }
  if (b = 3)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
  }

void kgr()
{
  a = analogRead(A1);
  Serial.println(a);
  delay(100);
  if (a >= 205)
  {
    b = 1
  }
  if (a < 205 && a > 180)
  {
    b = 2;
  }
  if (a <= 180)
  {
    b = 3;
  }
}

