/*  PIE Mini Project 2: 3D Scanner
 *  Olivia Chang, Lili Baker, Tara Lee
 *  9/29/22
*/

/* LIBRARIES */
#include <Servo.h>

/* DEFINITIONS */
Servo servoV; // vertical servo = up and down
Servo servoH; // horizontal servo = left and right

/* Constants */
const int SERVO_UNIT_OF_DISTANCE = 1; // size of each servo movement interval

// Time in between servo pan movements
const int PAN_DELAY = 200;

// Servos can be programmed from 0 to 180
// Set minimum/maximum bounds for sensor scanning
const int SERVO_MAX_V = 60;
const int SERVO_MIN_V = 20;
const int SERVO_MAX_H = 50;
const int SERVO_MIN_H = 0;

// Initial servo positions
int servoV_pos = SERVO_MIN_V;
int servoH_pos = SERVO_MIN_H;

// pin definitions
const int sensorPin = A0;
const int servoPin1 = 9;
const int servoPin2 = 10;
const int buttonPin = 8;

// Track last button state (for detecting button press)
int lastButtonState = 0;
long lastInterruptTime = 0; // define last interrupt time for debouncing


void setup() {
  // Set up serial
  Serial.begin(9600);
  
  // Set up servos
  servoV.attach(servoPin1);
  servoH.attach(servoPin2);

  // Set up button pin
  pinMode(buttonPin, INPUT);

  // Reset servo position to initial position
  resetServos();
}

void loop() {
  // detect button press + debounce
  int currentButtonState = digitalRead(buttonPin);
  // if button is now pressed and wasn't before
  if (lastButtonState == 0 && currentButtonState == 1) {
    // get time of current interrupt
    long interruptTime = millis();
  
    // if time since last interrupt is greater than arbitrary threshold
    // then button was pressed and begin scan
    if (interruptTime - lastInterruptTime >  200) {
      startScan();
    }
    
    // set last interrupt time
    lastInterruptTime = interruptTime; 
  }
  lastButtonState = currentButtonState; // set last button state to compare
}

void startScan() {
  resetServos();
  
  // pan vertical servo starting from minimum position, incrementing by given unit until hit max position
  for (servoV_pos = SERVO_MIN_V; servoV_pos <= SERVO_MAX_V; servoV_pos = servoV_pos + SERVO_UNIT_OF_DISTANCE) {
    // in each vertical servo value, pan servo left to right starting from min position and incrementing until hit max position
    for (servoH_pos = SERVO_MIN_H; servoH_pos <= SERVO_MAX_H; servoH_pos = servoH_pos + SERVO_UNIT_OF_DISTANCE) {
      // update servo position
      writeToServos();
      // get current sensor value
      scanOnce();
      // wait PAN_DELAY ms
      delay(PAN_DELAY);
    }
  }
}

// Set current servo position based on global servo v/h position variables
void writeToServos() {
  servoV.write(servoV_pos);
  servoH.write(servoH_pos);
}

// Reset servos to initial position
void resetServos() {
  servoV_pos = SERVO_MIN_V;
  servoH_pos = SERVO_MIN_H;
  writeToServos();
}

void scanOnce(){
  // read from sensor pin
  float rawDistance = analogRead(sensorPin);
  // convert sensor value to distance (in cm) according to calibration curve
  float convertedDistance = 29.988 * pow(rawDistance, -1.173) * 100;
  // print to serial, to be read from matlab
  Serial.print(servoH_pos);
  Serial.print(",");
  Serial.print(servoV_pos);
  Serial.print(",");
  Serial.println(convertedDistance);
}
