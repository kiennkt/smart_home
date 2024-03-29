/*
@ author: kim tuan kien
*/

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ThingsBoard.h>
#include <Update.h>
#include <Arduino_MQTT_Client.h>
#include <Adafruit_Sensor.h>
#include <RF24.h>
#include <SPI.h>

/* define macro*/
#define WIFI_SSID "P2806A5"
#define WIFI_PASSWORD "24111981"

#define TOKEN "rfRnaMDlYkxRS2BVSdPg"
#define THINGSBOARD_SERVER "demo.thingsboard.io"
#define THINGSBOARD_PORT 1883U


#define NRF_MOSI 23
#define NRF_MISO 19
#define NRF_SCK 18
#define NRF_CSN 5
#define NRF_CE 4
const uint64_t RxAddress = 0xF0F0F0F0E1LL; // address NRF tranmister and reciever

// struct contain sensor values
struct Data {
  float temperature;
  float humidity;
  int gas;
};

// Initialization instances
WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard thingsBoard(mqttClient);
RF24 radio(NRF_CE, NRF_CSN);
Data data;

void connectWifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print('.');
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Failed to Connect!");
  }
  Serial.println("Wifi Connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void connectThingsBoard(){
  if (!thingsBoard.connected()) {
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token :");
    Serial.println(TOKEN);
    if (!thingsBoard.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println("Failed to connect");
    }
    else Serial.println("Connected Successfully!!");
  }
}

void connectNRFModule(){
  radio.begin();
  radio.openReadingPipe(0, RxAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void setup() {
  Serial.begin(9600);
  delay(500);
  connectWifi();
  connectThingsBoard();
  connectNRFModule();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){
    radio.read(&data, sizeof(Data));
    Serial.println(data.temperature);
    Serial.println(data.humidity);
    Serial.println(data.gas);

    thingsBoard.sendTelemetryData("temperature", data.temperature);
    thingsBoard.sendTelemetryData("humidity", data.humidity);
    thingsBoard.sendTelemetryData("gas", data.gas);

    delay(500);
  }
  else {
    Serial.println("No Data Receive!!!");
    digitalWrite(2, LOW);
    delay(500);
  }
}
