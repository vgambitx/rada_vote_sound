/*
*    Emulating voting sound from the ukrainian "Rada" information and analytical system
*    Made just for fun for ESP8266 (WeMos D1 mini clone)
*    vGamBIT 
*    v0.3
*/

static const uint8_t buzzerPin =  D1;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void radaVoteSound(bool withLED = true) {
  const int toneDelay = 1000;
  const int tonesCount = 10;
  const int tones[tonesCount] = {698, 622, 587, 523, 466, 415, 392, 349, 311, 1568};
  const int tonesDuration[tonesCount] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 120};
  for (int index = 0; index < tonesCount; index++) {
    if (withLED) {
      digitalWrite(LED_BUILTIN, LOW);
      tone(buzzerPin, tones[index], tonesDuration[index]);
      delay(tonesDuration[index]);
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(toneDelay - tonesDuration[index]);
    } else {
      tone(buzzerPin, tones[index], tonesDuration[index]);
      delay(toneDelay);
    }
  }
}

bool isPlayedOnce = false;

void loop() {
  if (!isPlayedOnce) {
    radaVoteSound();
    isPlayedOnce = true;
  } else {
    ESP.deepSleep(0); // Don't waste energy
  }
}
