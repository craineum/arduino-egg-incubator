// Needed Libraries:
// LCD Shield: https://github.com/adafruit/Adafruit-RGB-LCD-Shield-Library
// DHT Sensor: https://github.com/adafruit/DHT-sensor-library

// Temp/Humidity Sensor
#include "DHT.h"

// LCD
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// Temp/Humidity Sensor
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// LCD
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Relay
#define RELAYPIN 3

void setup() {
  Serial.begin(9600); 
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.print("Lets Hatch Some");
  lcd.setCursor(0,1);
  lcd.print("EGGS!!!");
  lcd.setBacklight(0x1);
 
  // setup the Tempt/Humidity Sensor 
  dht.begin();
  
  // Setup relay
  pinMode(RELAYPIN, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Fahrenheit
  float temp = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if (temp < 100) {
    digitalWrite(RELAYPIN, HIGH);
  } else if (temp > 101) {
    digitalWrite(RELAYPIN, LOW);
  }    
  
  lcd.setCursor(0,0);
  lcd.print("H: "); 
  lcd.print(humidity);
  lcd.print(" %      ");
  lcd.setCursor(0,1);
  lcd.print("T: "); 
  lcd.print(temp);
  lcd.print(" F      ");
}
