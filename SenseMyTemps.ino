// Wi-fi
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "constants.h"
#include "temperature_sensor.h"

Thermometer thermometer(constants::TEMP_SENSOR_PIN);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, constants::NTP_ADDRESS.c_str(), constants::NTP_OFFSET, constants::NTP_INTERVAL);

void setup() {
  // Serial
  Serial.begin(115200);
  delay(10);
  
  // Wifi 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(constants::SSID);
  WiFi.begin(constants::SSID.c_str(), constants::WIFI_PASSWORD.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP

  // Firebase
  Firebase.begin(constants::FIREBASE_HOST, constants::FIREBASE_AUTH);

  // NTP
  timeClient.begin();
}

void loop() {

  auto startTime = millis();

  timeClient.update();

  const int capacity = JSON_OBJECT_SIZE(3);
  StaticJsonBuffer<capacity> jb;
  JsonObject& obj = jb.createObject();
  obj["time"] = timeClient.getEpochTime();
  obj["temperature"] = thermometer.getTemp();
    
  Firebase.push(constants::ROOM_NAME, obj); 
  if (Firebase.failed()) { 
     Serial.print("setting /number failed:"); 
     Serial.println(Firebase.error());   
     return; 
  }

  auto runTime = millis() - startTime;
  
  if (runTime < constants::LOOP_RATE_MS) {
    delay(constants::LOOP_RATE_MS - runTime);
  }
  
}
