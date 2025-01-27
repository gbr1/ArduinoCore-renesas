#include "analogWave.h"

analogWave wave(DAC);

int freq = 10;  // in hertz, change accordingly

void setup() {
  Serial.begin(115200);
  wave.sine(freq);
}

void loop() {
  freq = map(analogRead(A5), 0, 1024, 0, 10000);
  Serial.println("Frequency is now " + String(freq) + " hz");
  wave.freq(freq);
  delay(1000);
}