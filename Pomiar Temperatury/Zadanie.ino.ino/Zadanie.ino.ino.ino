//Napisz program dokonujący pomiaru temperatury 
//- Temperatura zostanie wyswietlona na wyswietlaczu 
//- Po przekroczeniu okreslonej temperatury obroci serwo o wybrany kat. 
#include <Servo.h>
#include <DHT.h>
#include <Wire.h> 
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


//Constants
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//ALWAYS USE THIS WITH LCD I2C and Addres 0x3F
#define I2C_ADDR 0x3F
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27
Servo serwo;
int pozycja = 45;
int zmiana = 45;

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int val;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  serwo.attach(6);
  serwo.write(pozycja);

}

void loop() {
  delay(1000);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  val = map(temp, 25, 35, 0, 180);
  serwo.write(val);
//  if(temp > 26)
//  {
//    if(pozycja == 90)
//    {
//      pozycja = 45;
//      serwo.write(pozycja);
//      delay(1000);
//    }
//    else
//    {
//      pozycja = pozycja + zmiana;
//      serwo.write(pozycja);
//      delay(1000);
//    } 
//  }
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum:  ");
  lcd.print(hum);
  lcd.print(" %");

  
  delay(1000);
  

}
