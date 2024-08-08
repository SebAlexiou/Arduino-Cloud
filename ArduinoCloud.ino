#include <WiFiNINA.h>
#include <DHT.h>

const char* ssid = "your_SSID";         // Replace with your Wi-Fi network name
const char* password = "your_PASSWORD"; // Replace with your Wi-Fi password
const char* server = "http://<server_ip>:<port>/data"; // Replace <server_ip> and <port> with your server's IP and port

const int dhtPin = 2;  // Pin connected to the DHT22 sensor
DHT dht(dhtPin, DHT22);

WiFiClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  connectToWiFi();
}

void loop() {
  if (client.connect(server, 80)) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
    
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postData.length()));
    client.println();
    client.println(postData);

    Serial.println("Data sent: " + postData);

    client.stop();
  } else {
    Serial.println("Connection to server failed.");
  }
  
  delay(60000);  // Send data every minute
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(10000);
  }
  Serial.println("Connected to Wi-Fi.");
}
