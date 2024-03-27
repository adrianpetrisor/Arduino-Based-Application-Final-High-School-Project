#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 7


LiquidCrystal_I2C lcd(0x27, 16, 2);
const int waterSensorPin = A0;


void setup() 
{
  Serial.println("[CONSOLE] - System is now operational!");
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("* Booting: ");

  for (int i = 0; i <= 100; i++) {
    lcd.setCursor(11, 0);
    if (i < 100) lcd.print(" ");
    if (i < 10) lcd.print(" ");
    lcd.print(i);
    lcd.print("%");
    delay(25);
  }

  lcd.setCursor(0,1); 
  lcd.print("System is now up!");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
}


void loop() 
{
    // Senzor Umiditate si Temperatura
    int chk = DHT.read11(DHT11_PIN);
    float humidity = DHT.humidity;
    float temp = DHT.temperature;

    // Senzor Water Sensor
    int sensorValue = analogRead(waterSensorPin);
    int waterLevel = map(sensorValue, 0, 1023, 0, 100);

  if (isnan(humidity) || isnan(temp)) {
      Serial.println("[CONSOLE - HUMIDITY SENSOR CRITICIAL FAIL] - Failed to read from DHT sensor!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Critical Error!");
      lcd.setCursor(0, 1);
      lcd.print("Check Console!");
      delay(2000);

      if(isnan(waterLevel)) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Error Water Level");
        delay(2000);
      } else {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("(S) Water: ");
        lcd.print(waterLevel);
        lcd.print("%");
        delay(2000);
      }
    return;
  } else {


  // TOP LEFT
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.print(" ");
  lcd.print("T: ");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");

  // BOTTOM LEFT
  lcd.setCursor(0, 1);
  lcd.print("(S) Water: ");
  lcd.print(waterLevel);
  lcd.print("%");
  }
}