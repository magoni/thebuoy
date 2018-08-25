/*
  Modified from: http://www.arduino.cc/en/Tutorial/Tone2
  originally by Tom Igoe, with suggestion from Michael Flynn

  Modified 23 Aug 2018
  by Evan Magoni
*/

/* Configuration */
const int buttonPin = 8;
const int ledPin = 10;
const int audioPin = 6;
const int sensorMax = 700;
const int sensorMin = 200;
int audioThreshold = 720;
/* End Configuration */

int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // TODO change led color on modeswitch https://www.arduino.cc/en/Tutorial/StateChangeDetection
  // TODO read ultrasonic sensor on modeswitch https://www.sunfounder.com/ultrasonic-module-hc-sr04-distance-sensor.html
  // TODO copy sensorValue to audioThreshold when mode switches to photoresistor
  
  int photoResistorValue = analogRead(A0);
  generateAudio(photoResistorValue);
  delay(1);        // delay in between reads for stability
}

void generateAudio(int sensorValue) {
  // print the sensor reading so you know its range
  Serial.println(sensorValue);

  // TODO read maxpitch from a knob
  int pitch = map(sensorValue, sensorMax, sensorMin, 120, 1500);
  int ledBrightness = map(sensorValue, sensorMin, sensorMax, 0, 255);
  
  if (sensorValue < audioThreshold) {
    tone(audioPin, pitch, 10);
    analogWrite(ledPin, ledBrightness);
  } else {
    analogWrite(ledPin, 255);
  }
}
