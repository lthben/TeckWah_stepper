/*
 * Author: Benjamin Low
 * Last updated: 3 Nov 2015
 * Description:
 *      Using the DRV8825 driver and a Pololu NEMA 23 stepper
 *      200 step motor. 1/4 step configuration, so 800 steps per revolution.
 */

#define dirPin 7
#define stepPin 6
#define nSleepPin 4

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(nSleepPin, OUTPUT);

  Serial.begin(9600);

  digitalWrite(dirPin, HIGH); //clockwise motion
  digitalWrite(nSleepPin, LOW); //initialise to sleep mode 
  
}

void loop() {

  int incoming = Serial.read();

  if (incoming == '1') {

    digitalWrite(nSleepPin, HIGH);
    delay(2); //need 2ms delay

    for (int i = 0; i < 800*3; i++) {
      digitalWrite(stepPin, HIGH);
      delay(2);
      digitalWrite(stepPin, LOW);
      delay(2);
    }

    digitalWrite(nSleepPin, LOW);
    delay(2);
  }

  delay(3000);
}
