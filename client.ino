// This scetch if for the client. It receives high and low from the server


#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "*****";
char pass[] = "*****";

unsigned long askTimer = 0;

IPAddress server(192,168,0,80);
WiFiClient client;

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  pinMode(ledPin, OUTPUT);
}

void loop ()
{
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  String answer = client.readStringUntil('\r');
  if (answer == "HIGH")
  {
    Serial.println("HIGH");
    digitalWrite(ledPin, HIGH);
    // do something
  } else 
  {
    Serial.println("LOW");
    digitalWrite(ledPin, LOW);
    // do something
  }
  client.flush();
  delay(2000);
}
