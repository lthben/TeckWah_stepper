/*
 * Author: Benjamin Low
 *
 * Description:
 *      Using the DRV8825 driver and a Pololu NEMA 23 stepper
 *      200 step motor. 1/4 step configuration, so 800 steps per revolution.
 *
 * Last updated: 26 Jan 2016
 */

#define dirPin 7
#define stepPin 6
#define nSleepPin 4

//USER DEFINED SETTINGS
const float NUM_TURNS = 1; //num of revolutions
const int STEP_DELAY = 8; //delay in ms between steps. The smaller the delay, the faster the speed.
bool DEBUG = false;

int total_step_num, my_step_delay, step_interval, num_of_accel_steps;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(nSleepPin, OUTPUT);

  Serial.begin(9600);

  digitalWrite(nSleepPin, LOW); //initialise to sleep mode

  total_step_num = int(NUM_TURNS * 800);
  my_step_delay = STEP_DELAY * 5;
  step_interval = 1; //the rate of accel and decel in steps of 1, 2, 4 or 8ms
  num_of_accel_steps = (my_step_delay - STEP_DELAY) / step_interval;

  if (DEBUG) Serial.println("initialised");
}

void loop() {

    unsigned char incoming = 0; 

  if (Serial.available() > 0) {
    
    incoming = Serial.read();

    if (incoming == '1') {

      if (DEBUG) Serial.println("spinning cw");

      digitalWrite(dirPin, HIGH); //clockwise motion

      delay(2);

      do_rotation();
      
    } else if (incoming == '2') {

       if (DEBUG) Serial.println("spinning ccw");

      digitalWrite(dirPin, LOW); //counter-clockwise motion

      delay(2);

      do_rotation();
    }
  }
  delay(10);
}

void do_rotation() {

      digitalWrite(nSleepPin, HIGH); //awake from sleep
      delay(2); //need 2ms delay

      for (int i = 0; i < total_step_num; i++) {

        calc_step_delay(i);

        if (DEBUG) {
            Serial.print(i); 
            Serial.print("   ");
            Serial.println(my_step_delay);
        }

        digitalWrite(stepPin, HIGH);
        delay(my_step_delay);
        digitalWrite(stepPin, LOW);
        delay(my_step_delay);

      }
      
      digitalWrite(nSleepPin, LOW); //put back to sleep to prevent current draw
      delay(2);//need 2ms delay
}

void calc_step_delay(int index) {

  if (index < num_of_accel_steps) {
    //accel
    my_step_delay -= step_interval;
  }

  else if (index > total_step_num - num_of_accel_steps) {
    //decel
    my_step_delay += step_interval;

  } else {
    //constant speed
    my_step_delay = STEP_DELAY;
  }
}

