#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"
#include "config.h"

// https://gist.github.com/Matheus-Garbelini/2cd780aed2eddbe17eb4adb5eca42bd6#comments
extern "C" {
#include "user_interface.h"
#include "wpa2_enterprise.h"
#include "c_types.h"
}

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

// https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/
//Your Domain name with URL path or IP address with path
String serverName = SERVER_BASE;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


void setup() {
    Serial.begin(115200);
    delay(100);

    pinMode(DHTPin, INPUT);
    dht.begin();

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if ((millis() - lastTime) > timerDelay) {
        //Check WiFi connection status
        if(WiFi.status()== WL_CONNECTED){
          
            WiFiClient client;
            HTTPClient http;
                      
            Temperature = dht.readTemperature(); // Gets the values of the temperature
            Humidity = dht.readHumidity(); // Gets the values of the humidity
            Serial.println("Temp: " + String(Temperature));
            Serial.println("Humi: " + String(Humidity));

            String serverPath = serverName + "?sensor=" + String(WiFi.macAddress()) + "&temp=" + String(Temperature) + "&humid=" + String(Humidity);

            Serial.println("TODO: Send data now!");
            Serial.println(serverPath);

            Serial.println(httpGETRequest(serverPath));
        }
        else {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}

String httpGETRequest(String serverName){
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
  }
