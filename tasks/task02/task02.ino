/*
  Цель:
  Освоить работу с прерываниями и анализ временных интервалов на плате Arduino.

  Задача:
  Реализовать приложение для платы Arduino, которое:
  - измеряет временные интервалы между срабатываниями прерывания на пине 18;
  - вычисляет среднее значение интервалов и среднеквадратичное отклонение;
  - выводит результаты в Serial-порт в микросекундах.
*/

// Конфигурация
const int INT_PIN = 18;
const int DATA_SIZE = 1000;

// Переменные для хранения данных
volatile uint32_t sampleCount = 0;
volatile uint32_t lastTime = 0;
uint32_t intervals[DATA_SIZE];
volatile bool isDataReady = false;

void setup() {
  Serial.begin(9600);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), handleInterrupt, HIGH);
}

void loop() {
  if (isDataReady) {
    noInterrupts();
    calculateAndPrintStats();
    sampleCount = 0;
    isDataReady = false;
    interrupts();
  }
}

// Обработчик прерывания
void handleInterrupt() {
  uint32_t currentTime = micros();
  if (sampleCount < DATA_SIZE) {
    intervals[sampleCount] = currentTime - lastTime;
    sampleCount++;
    lastTime = currentTime;
  }
  if (sampleCount >= DATA_SIZE) {
    isDataReady = true;
  }
}

// Вычисление и вывод статистики
void calculateAndPrintStats() {
  uint32_t sum = 0;
  for (int i = 0; i < DATA_SIZE; i++) {
    sum += intervals[i];
  }
  float avgInterval = sum / (float)DATA_SIZE;

  float varianceSum = 0;
  for (int i = 0; i < DATA_SIZE; i++) {
    float diff = intervals[i] - avgInterval;
    varianceSum += diff * diff;
  }

  Serial.print("Средний интервал: ");
  Serial.print(avgInterval);
  Serial.print(" мкс, Среднеквадратичное отклонение: ");
  Serial.print(sqrt(varianceSum /.DATA_SIZE));
  Serial.println(" мкс");
}