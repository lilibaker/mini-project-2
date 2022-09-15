#include <Servo.h>
//#include <SharpIR.h>

Servo servo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo servo2;

int pos = 0;    // variable to store the servo position

#define model 20150
//const int SENSOR_TO_CM = 25.4 / 410;
const int delay_const = 100;
const int sensorPin = A0;
const int servoPin1 = 9;
const int servoPin2 = 10;
int distance = 0;

//SharpIR IR_prox(model, sensorPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(servoPin1);
  // servo2.attach(servoPin2);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (int x_pos = 0; x_pos <= 180; x_pos++) {
    scan();
    servo1.write(x_pos);
    delay(delay_const);
  }
}

void scan(){
  distance = analogRead(sensorPin);
  float new_distance = 29.988 * pow(distance, -1.173) * 100; // in cm
  Serial.print(new_distance);
}
