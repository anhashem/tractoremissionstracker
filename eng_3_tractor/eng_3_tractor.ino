#include <Wire.h> 
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h> // initalizing the display
#include <SPI.h> 
#include <SD.h> //  SD card

int sensorValue;
int sensorPin = 1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int chipSelect = 4;
const int ledPin =  3;      // the number of the LED pin
const int ledPinerror =  6; // number of the error LED 
const int buttonPin = 2; // button
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal_I2C lcd(0x27, 16, 2); // initalizing dimentions of screen
File dataFile; // file that would take the AQI data
File tempData; // file that would take temp data

int buttonState = 0; // button state

void setup(){  
  
  //lcd.begin(16, 2);
  lcd.begin();
  lcd.backlight();
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinerror, OUTPUT);
Serial.begin(9600);     // sets the serial port to 9600
Serial.print("Initializing SD card...");
lcd.print("Initializing SD card...");


// make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    lcd.print("                         ");
    Serial.println("Card failed, or not present");
    digitalWrite(ledPinerror, HIGH);
    lcd.setCursor(0,1);
    lcd.print("error opening datalog.txt");
    // don't do anything more:
    while (1) ;
  }
   Serial.println("card initialized.");
   lcd.print("card initialized.");
   // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  tempData = SD.open("tempdata.txt", FILE_WRITE);
  digitalWrite(ledPin, HIGH);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    digitalWrite(ledPinerror, HIGH);
    lcd.print("                         ");
    lcd.setCursor(0,1);
    lcd.print("error opening datalog.txt");
    digitalWrite(ledPin, LOW);
    // Wait forever since we cant write data
    while (1) ;
  }
 }

void loop(){
// make a string for assembling the data to log:
sensorValue = analogRead(0);       // read analog input pin 0


Serial.print("AirQuality = ");
Serial.print(sensorValue, DEC);               // prints the value read
Serial.println(" PPM");
lcd.setCursor(0,0);


lcd.print("AirQ =");
lcd.print(sensorValue,DEC);
lcd.print(" PPM");


 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
  float voltage = reading * 5.0;
 voltage /= 1024.0;
  Serial.print(voltage); Serial.println(" volts"); 
   // now print out the temperature
 float temperatureC = (voltage - 0.7) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(1000);

  if (!SD.begin(chipSelect)) {
    lcd.print("                         ");
    Serial.println("Card failed, or not present");
    digitalWrite(ledPinerror, HIGH);
    lcd.setCursor(0,1);
    lcd.print("SD Card removed");
    // don't do anything more:
    while (1) ;
  }

  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    digitalWrite(ledPinerror, HIGH);
    lcd.print("                         ");
    lcd.setCursor(0,1);
    lcd.print("error datafile");
    digitalWrite(ledPin, LOW);
    // Wait forever since we cant write data
    while (1) ;
  }
 
 
if (sensorValue < 50) {
  lcd.setCursor(0,1);
  lcd.print("Safe");
}
 else if (sensorValue <= 100) {
  lcd.setCursor(0,1);
  lcd.print("Mod");
  
}
else if (sensorValue <= 300) {
  lcd.setCursor(0,1);
  lcd.print("Unheal");
}
else if (sensorValue > 300) {
  lcd.setCursor(0,1);

  lcd.print("Haz");
}



if (temperatureC > 30) {
 lcd.setCursor(7,1);
  lcd.print("TEMP:HOT");
}

lcd.println("         "); 
lcd.print("            ");
delay(100);                                  


dataFile.println(sensorValue);
tempData.println(temperatureF);
dataFile.flush();
tempData.flush();
// print to serial port
delay(500);
}
