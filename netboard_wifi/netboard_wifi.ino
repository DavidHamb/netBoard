#include <WiFiS3.h>

const char* ssid = "REDACTED";
const char* password = "REDACTED";
int status = WL_IDLE_STATUS;
IPAddress ipToPing(8, 8, 8, 8); // adresse IP à pinger
const int greenLed = 2;
const int yellowLed = 3;
const int redLed = 4;

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // boot test
  digitalWrite(greenLed, HIGH); delay(200);
  digitalWrite(yellowLed, HIGH); delay(200);
  digitalWrite(redLed, HIGH); delay(200);
  oneLight(0); // set all leds off

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
    delay(2000);
  }
}

void loop() {
  // Lancement du ping
  int pingResult = WiFi.ping(ipToPing);

  if (pingResult > 0 && pingResult <= 50) {
    oneLight(greenLed);
  }
  else if (pingResult > 50 && pingResult <= 200) {
    oneLight(yellowLed);
  }
  else if (pingResult > 200) {
    oneLight(redLed);
  }
  else if (pingResult < 0 || WiFi.status() == WL_NO_MODULE){
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, !digitalRead(redLed)); // led flashes when network is unavailable
    delay(100);
  }

  delay(500); // Attendre une seconde avant le prochain ping
}

// function lightening only one led a time
void oneLight(int pinToLight) {
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);

  if (pinToLight != 0) {
    digitalWrite(pinToLight, HIGH);
  }
}