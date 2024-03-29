/*
@ author: Kim Tuan Kien
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define GAS_PIN A0
#define DHT_PIN A1
#define DHT_TYPE DHT11

const uint64_t RxAddress = 0xF0F0F0F0E1LL;

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


// NRF reciever
void connectNRFModule(){
  radio.begin();
  radio.openWritingPipe(RxAddress);
  radio.stopListening();
}

// connect DHT
void connectDHTSensor(){
  dht11.begin();
}

void connectGasSensor(){
  pinMode(GAS_PIN, INPUT);
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
  connectDHTSensor();
  connectGasSensor();
  connectLCD();

}
void loop(){
  data.temperature = dht11.readTemperature();
  data.humidity = dht11.readHumidity();
  data.gas = analogRead(GAS_PIN);

  lcd.setCursor(2, 0);
  lcd.print(data.temperature);

  lcd.setCursor(11, 0);
  lcd.print(data.humidity);

  lcd.setCursor(5, 1);
  lcd.print(data.gas);
  //Send message to receiver

  radio.write(&data, sizeof(Data));

}