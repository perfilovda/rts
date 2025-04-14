/*
  Реализовать приложение (прошивку) для платы Arduino UNO, осуществляющую генерацию
  одновременно пяти импульсов со скважностью 50%:
  - 3 ножка - 10 мс
  - 5 ножка - 1 мс
  - 6 ножка - 500 мкс
  - 9 ножка - 100 мкс
  - 10 ножка - 50 мкс
*/

// Конфигурация пинов и интервалов
const int ledPins[] = {3, 5, 6, 9, 10};
const unsigned long intervals[] = {10000, 1000, 500, 100, 50}; // Интервалы в мкс
const int numPins = 5;

// Переменные для хранения состояния и времени
int ledStates[numPins] = {LOW, LOW, LOW, LOW, LOW};
unsigned long previousTimes[numPins] = {0};

void setup() {
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentTime = micros();

  for (int i = 0; i < numPins; i++) {
    if (currentTime - previousTimes[i] >= intervals[i]) {
      ledStates[i] = (ledStates[i] == LOW) ? HIGH : LOW;
      digitalWrite(ledPins[i], ledStates[i]);
      previousTimes[i] = currentTime;
    }
  }
}