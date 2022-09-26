#include <Servo.h>

// servo 1 = up and down
Servo servoV;
// servo 2 = left and right
Servo servoH;

int servoV_pos = 20; // 0 to 180
int servoH_pos = 0; // 0 to 180

int servo_unit_of_distance = 1;

const int SERVO_MAX_V = 60;
const int SERVO_MIN_V = 20;
const int SERVO_MAX_H = 50;
const int SERVO_MIN_H = 0;

// pin definitions
const int sensorPin = A0;
const int servoPin1 = 9;
const int servoPin2 = 10;
const int buttonPin = 8;
int lastButtonState = 0;
long lastInterruptTime = 0;

const int PAN_DELAY = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Sketch starting...");
  
  // Set up servos
  servoV.attach(servoPin1);
  servoH.attach(servoPin2);

  // Set up button pin
  pinMode(buttonPin, INPUT);
  
  // Attach interrupt function that is called when button pin state goes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPress, RISING);

  resetServos();
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == 0 && currentButtonState == 1) {
    // get time of current interrupt
    long interruptTime = millis();
  
    // if time since last interrupt is greater than arbitrary threshold
    // then button was pressed
    if (interruptTime - lastInterruptTime >  200) {
        onButtonPress();
    }
    
    // set last interrupt time
    lastInterruptTime = interruptTime; 
  }
  lastButtonState = currentButtonState;
  
}

void onButtonPress() {
  resetServos();
  //Serial.println("----- BEGIN CSV -----");
  //Serial.println("x,y,scan");
  // for loop up and down
  for (servoV_pos = SERVO_MIN_V; servoV_pos <= SERVO_MAX_V; servoV_pos = servoV_pos + servo_unit_of_distance) {
    // for loop left and right
    for (servoH_pos = SERVO_MIN_H; servoH_pos <= SERVO_MAX_H; servoH_pos = servoH_pos + servo_unit_of_distance) {
      writeToServos();
      scan();
      delay(PAN_DELAY);
    }
  }
  //Serial.println("----- END CSV -----");
}

void writeToServos() {
   
  servoV.write(servoV_pos);
  servoH.write(servoH_pos);
}

void resetServos() {
  //Serial.println("Reset servos");
  servoV_pos = 0;
  servoH_pos = 0;
  writeToServos();
}

void scan(){
  float rawDistance = analogRead(sensorPin);
  float convertedDistance = 29.988 * pow(rawDistance, -1.173) * 100; // in cm
  Serial.print(servoH_pos);
  Serial.print(",");
  Serial.print(servoV_pos);
  Serial.print(",");
  Serial.println(convertedDistance);
}
