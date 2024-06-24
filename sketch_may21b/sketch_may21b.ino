#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 7 // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display

int sensorValue;
int digitalValue;
const int buzzerPin = 5; // Pin connected to the buzzer

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx and Sensor test!");

  dht.begin();

  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight

  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(t * 1.8 + 32, h);

  // Read additional sensor values
  sensorValue = analogRead(0); // read analog input pin A0
  digitalValue = digitalRead(2);

  // Control the LED based on sensorValue
  if (sensorValue > 400) {
    digitalWrite(13, HIGH);
    digitalWrite(buzzerPin, HIGH); // Sound the buzzer
  } else {
    digitalWrite(13, LOW);
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }

  // Print data to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Heat ind: ");
  Serial.print(hi);
  Serial.println(" F");
  Serial.print("Analog Sen: ");
  Serial.println(sensorValue);
  Serial.print("Digital Sen: ");
  Serial.println(digitalValue);

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(-4, 2);
  lcd.print("Analog: ");
  lcd.print(sensorValue);

  lcd.setCursor(-4, 3);
  lcd.print("Digital: ");
  lcd.print(digitalValue);
}
