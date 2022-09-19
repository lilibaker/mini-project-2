#include <Servo.h>

// servo 1 = up and down
Servo servoV;
// servo 2 = left and right
Servo servoH;

int servoV_pos = 0; // 0 to 180
int servoH_pos = 0; // 0 to 180

int servo_unit_of_distance = 18;

const int SERVO_MAX = 180; // defined by servo/arduino

// pin definitions
const int sensorPin = A0;
const int servoPin1 = 9;
const int servoPin2 = 10;
const int buttonPin = 8;

const int PAN_DELAY = 200;

int distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Sketch starting...");
  
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
  
}

void onButtonPress() {
  resetServos();
  Serial.println("Start scanning");
  // for loop up and down
  for (servoV_pos = 0; servoV_pos <= SERVO_MAX; servoV_pos = servoV_pos + servo_unit_of_distance) {
    // for loop left and right
    for (servoH_pos = 0; servoH_pos <= SERVO_MAX; servoH_pos = servoH_pos + servo_unit_of_distance) {
      scan();
      writeToServos();
      delay(PAN_DELAY);
    }
  }
  Serial.println("Finished scanning");
}

void writeToServos() {
  Serial.print("Current pos: x ");
  Serial.print(servoH_pos);
  Serial.print(", y ");
  Serial.println(servoV_pos);
  
  servoV.write(servoV_pos);
  servoH.write(servoH_pos);
}

void resetServos() {
  Serial.println("Reset servos");
  servoV_pos = 0;
  servoH_pos = 0;
  writeToServos();
}

void scan(){
  float rawDistance = analogRead(sensorPin);
  float convertedDistance = 29.988 * pow(rawDistance, -1.173) * 100; // in cm
  Serial.println(convertedDistance);
}
