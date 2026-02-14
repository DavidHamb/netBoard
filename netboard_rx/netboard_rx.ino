const int greenLed = 2;
const int yellowLed = 3;
const int redLed = 4;

void setup() {
  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // boot test
  digitalWrite(greenLed, HIGH); delay(200);
  digitalWrite(yellowLed, HIGH); delay(200);
  digitalWrite(redLed, HIGH); delay(200);
  oneLight(0); // set all leds off
}

void loop() {
  if (Serial.available() > 0) {
    int pingValue = Serial.parseInt(); // reads value received from python

    if (pingValue > 0 && pingValue <= 50) {
      oneLight(greenLed);
    }
    else if (pingValue > 50 && pingValue <= 150) {
      oneLight(yellowLed);
    }
    else if (pingValue > 150) {
      oneLight(redLed);
    }
  }
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
