/*
@ author: Kim Tuan Kien
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define LED_PIN 2
#define BUZZER_PIN 6
#define LIGHT_PIN 5
#define GAS_PIN A0
#define DHT_PIN A1
#define DHT_TYPE DHT11

// Address NRF Reciver
const uint64_t TxAddress = 0xF0F0F0F0E1LL; 

// struct contain all data from sensor
struct Data {
  float temperature;
  float humidity;
  int gas;
};

// Initialization instance
DHT dht11(DHT_PIN, DHT_TYPE);
RF24 radio(9, 8);  // CE, CSN
LiquidCrystal_I2C lcd(0x27,20,4);
Data data;


// NRF transmiter
void connectNRFModule(){
  radio.begin();
  radio.openWritingPipe(TxAddress);
  radio.stopListening();
}

void connectLCD(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("T: ");  
  lcd.setCursor(8, 0);
  lcd.print("H: ");
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
}

void setup(){  
  Serial.begin(9600);
  connectNRFModule();
  connectLCD();
  dht11.begin();
  pinMode(LIGHT_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}
void loop(){
  data.temperature = dht11.readTemperature();
  data.humidity = dht11.readHumidity();
  data.gas = analogRead(GAS_PIN);
  int light = digitalRead(LIGHT_PIN);

  lcd.setCursor(2, 0);
  lcd.print(data.temperature);

  lcd.setCursor(11, 0);
  lcd.print(data.humidity);

  lcd.setCursor(5, 1);
  lcd.print(data.gas);
  
  // buzzer
  if(data.gas >= 350){
    tone(BUZZER_PIN, 1000);
  }
  else noTone(BUZZER_PIN);

  // light sensor
  if (light == 1){
    digitalWrite(2, HIGH);
  }
  else digitalWrite(2, LOW);

  //Send message to NRF receiver
  radio.write(&data, sizeof(Data));
}
