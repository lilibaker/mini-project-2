int buttonPin = 8; // data pin corresponding to button
int lastButtonState = 0;
long lastInterruptTime = 0; // define last interrupt time for debouncing


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  Serial.println("Sketch starting...");
  // Set up button pin
  pinMode(buttonPin, INPUT);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  int currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == 0 && currentButtonState == 1) {
    // get time of current interrupt
    long interruptTime = millis();
  
    // if time since last interrupt is greater than arbitrary threshold
    // then button was pressed
    if (interruptTime - lastInterruptTime >  200) {
        Serial.println("Button was pressed");
    }
    
    // set last interrupt time
    lastInterruptTime = interruptTime; 
  }
  lastButtonState = currentButtonState;
}
