const int speaker = 11;

void setup() {

  pinMode(speaker, OUTPUT);
}

void loop() {

  //smallWarning();
  bigWarning();
}

void smallWarning() {
  tone(speaker, 400);
  delay(500);
  noTone(speaker);
  delay(500);
}

void bigWarning() {
  tone(speaker, 400);
  delay(175);
  noTone(speaker);
  delay(175);
}


