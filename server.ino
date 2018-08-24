// Include this library: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Put a 5mm LED from GPIO 13 (D7 on nodemcu) to GND
// Put a 100k resistor between GPIO 2 (D4 on nodemcu) to GND
// Put your device (or a button/ switch) between GPIO 2 (D4 on nodemcu) and GND
//
// This scetch if for the server. It reads high and low and sends it to the client


#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "******";
char pass[] = "******";
WiFiServer server(80);                    

IPAddress ip(192, 168, 0, 80);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

const int readPin = 2;
const int ledPin = 13;
int readState = 0;

void setup() 
{
  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  server.begin();
  pinMode(readPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop ()
{
  readState = digitalRead(readPin);
  WiFiClient client = server.available();
  if (client) 
  {
    if (client.connected()) 
    {
      client.flush();
      if (readState == HIGH) 
      {
        Serial.println("HIGH\r");
        client.println("HIGH\r");
        digitalWrite(ledPin, HIGH);
      } else
      {
        Serial.println("LOW\r");
        client.println("LOW\r");
        digitalWrite(ledPin, LOW);
      }
    }
    client.stop();
  }
  delay(2000);
}
