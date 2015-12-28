/*
 * Author: Benjamin Low
 * Last updated: 3 Nov 2015
 * Description: 
 *      Using the DRV8825 driver and a Pololu NEMA 23 stepper
 *      200 step motor. 1/4 step configuration, so 800 steps per revolution.
 */

#define dirPin 7
#define stepPin 6

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
  Serial.begin(9600);
  
  digitalWrite(dirPin, LOW);
}

void loop() {

  for (int i=0; i<800; i++) {
          digitalWrite(stepPin, HIGH);
          delay(2);
          digitalWrite(stepPin, LOW);
          delay(2);
  }

  delay(3000);
}
