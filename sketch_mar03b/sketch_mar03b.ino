#define btn 11
#define led 13

bool temp = true;
bool ledt = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  bool local = digitalRead(btn);
  if(temp && !local) {
    delay(10);
    local = digitalRead(btn);
    if (!local)
      ledt = !ledt;
      digitalWrite(led, ledt);
    }
}
