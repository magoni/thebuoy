/*
  Modified from: http://www.arduino.cc/en/Tutorial/Tone2 and https://www.arduino.cc/en/Tutorial/Debounce
  by Evan Magoni
*/

/* Configuration */
const int buttonPin = 8;
const int ledPins[] = {10, 9};
const int audioPin = 6;
const int sensorMax = 700;
const int sensorMin = 200;
int audioThreshold = 720;
/* End Configuration */

/* Global State */
int ledState = 0; /* 0 or 1 = pin 10 or 9*/
int buttonState;
int lastButtonState = 0;
int ledPin = ledPins[0];
int secondaryLedPin = ledPins[1];
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
/* End Global State */

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(audioPin, OUTPUT);
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // TODO change led color on modeswitch https://www.arduino.cc/en/Tutorial/StateChangeDetection
  // TODO read ultrasonic sensor on modeswitch https://www.sunfounder.com/ultrasonic-module-hc-sr04-distance-sensor.html
  // TODO copy sensorValue to audioThreshold when mode switches to photoresistor
  
  int buttonValue = digitalRead(buttonPin);
  int photoResistorValue = analogRead(A0);
  handleMode(buttonValue);
  generateAudio(photoResistorValue);
  delay(1);        // delay in between reads for stability
}

void handleMode(int buttonValue) {
  if (buttonValue != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the buttonValue is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (buttonValue != buttonState) {
      buttonState = buttonValue;

      // only toggle the LED if the new button state is ON (LOW)
      if (buttonState == LOW) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  if (ledState) {
    // output on pin 10
    ledPin = ledPins[0];
    secondaryLedPin = ledPins[1];
    analogWrite(secondaryLedPin, 255); // turn off the other pin
  } else {
    ledPin = ledPins[1];
    secondaryLedPin = ledPins[0];
    analogWrite(secondaryLedPin, 255); // turn off the other pin
  }
  
  // save the buttonValue. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = buttonValue;
}

void generateAudio(int sensorValue) {
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
