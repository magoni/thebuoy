/*
  Modified from: http://www.arduino.cc/en/Tutorial/Tone2
  originally by Tom Igoe, with suggestion from Michael Flynn

  Modified 23 Aug 2018
  by Evan Magoni
*/

int ledPin = 10;
int sensorMax = 700;
int sensorMin = 200;

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int photoResistorValue = analogRead(A0);
  // print the sensor reading so you know its range
  Serial.println(photoResistorValue);

  // TODO read maxpitch from a knob
  int pitch = map(photoResistorValue, sensorMax, sensorMin, 120, 1500);
  int ledBrightness = map(photoResistorValue, sensorMin, sensorMax, 0, 255);

  // TODO change led color on modeswitch https://www.arduino.cc/en/Tutorial/StateChangeDetection
  // TODO read ultrasonic sensor on modeswitch https://www.sunfounder.com/ultrasonic-module-hc-sr04-distance-sensor.html
  // TODO copy photoResistorValue to threshold when mode switches to photoresistor
  
  int threshold = 720;
  
  if (photoResistorValue < threshold) {
    tone(8, pitch, 10);
    analogWrite(ledPin, ledBrightness);
  } else {
    analogWrite(ledPin, 255);
  }
  delay(1);        // delay in between reads for stability
}
