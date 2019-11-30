// Wi-fi
#include <ESP8266WiFi.h>


#include "constants.h"
#include "temperature_sensor.h"

Thermometer thermometer(constants::TEMP_SENSOR_PIN);

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

}

void loop() {

  Serial.println(thermometer.getTemp());
  delay(1000);
  
}
