
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Pin definitions
const int sensorPin = 2;  // DS18B20 data pin
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;  // LCD pinout
const int ledPin = 13; // LED pin for indicating fitness status

// Setup the OneWire and DallasTemperature libraries
OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);

// Setup the LCD display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Start the DallasTemperature library
  sensors.begin();
  
  // Initialize the LCD display
  lcd.begin(16, 2);
  
  // Print a welcome message to the LCD display
  lcd.print("Temperature: ");
}

void loop() {
  // Request temperature readings from the DS18B20 sensor
  sensors.requestTemperatures();

  // Read the temperature and convert it to Celsius
  float tempC = sensors.getTempCByIndex(0);

  // Print the temperature to the serial monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  // Display the temperature on the LCD display
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" C");

  // Check if temperature exceeds 37°C
  if (tempC > 37.0) {
    // Display "NOT FIT TO WALK" on the LCD
    lcd.setCursor(0, 0);
    lcd.print("NOT FIT TO WALK");

    // Turn on LED to indicate not fit to walk
    digitalWrite(ledPin, HIGH);
  } else {
    // Display "FIT TO WALK" on the LCD
    lcd.setCursor(0, 0);
    lcd.print("FIT TO WALK");

    // Turn off LED to indicate fit to walk
    digitalWrite(ledPin, LOW);
  }
  
  // Wait for 1 second before repeating
  delay(1000);
}