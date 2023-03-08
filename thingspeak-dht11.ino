#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"
#define DHTPIN D1
// DHT11
#define DHTTYPE DHT11

// your network SSID (name)
const char* ssid = "********";
// your network password
const char* password = "********";

WiFiClient client;

unsigned long myChannelNumber = 19334061981;
const char* myWriteAPIKey = "5ZP22VSK8PTYVKYRR6Z";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial
  Serial.begin(115200);  
  dht.begin();
  WiFi.mode(WIFI_STA);
  // Initialize ThingSpeak  
  ThingSpeak.begin(client);  
}

void loop() {
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  delay(2000);
  float h = dht.readHumidity();

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.println(t);
  
  int x = ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  int y = ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
}