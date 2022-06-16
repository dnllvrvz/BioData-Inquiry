#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE    DHT11     // DHT 11
#define DHTPIN 7

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int measurement_count = 0;
float temperature_sum = 0.0;
float humidity_sum = 0.0;

unsigned long previousMillis = 0;

const long interval = 1000;
LiquidCrystal_I2C lcd(0x27, 16, 4);
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Iniciado");
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  delayMS = sensor.min_delay;
}

void loop()
{
  unsigned long currentMillis = millis();
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  temperature_sum += event.temperature;
  
  dht.humidity().getEvent(&event);
  humidity_sum += event.relative_humidity;

  measurement_count += 1;
  
  if (currentMillis - previousMillis >= interval) {
  // save the last time you blinked the LED
  previousMillis = currentMillis;
  // Serial.print(F("Minutes:"));
  // Serial.print(currentMillis / (1000.0 * 60.0));
  // Serial.print(",");
  Serial.print(F("Count/1000:"));
  Serial.print(measurement_count / 1000.0);
  Serial.print(",");
  Serial.print(F("Temperature:"));
  Serial.print(temperature_sum / measurement_count);
  Serial.print(",");
  Serial.print(F("Humidity:"));
  Serial.println(humidity_sum / measurement_count);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperature_sum / measurement_count, 1);
  lcd.print("|H:");
  lcd.print(humidity_sum / measurement_count, 0);
  lcd.setCursor(0,1);
  lcd.print("#k:");
  lcd.print(measurement_count / 1000.0, 1);
  lcd.print("|t:");
  lcd.print(currentMillis / (1000.0 * 60.0), 1);
  
  measurement_count = 0;
  temperature_sum = 0;
  humidity_sum = 0;
  }
}
