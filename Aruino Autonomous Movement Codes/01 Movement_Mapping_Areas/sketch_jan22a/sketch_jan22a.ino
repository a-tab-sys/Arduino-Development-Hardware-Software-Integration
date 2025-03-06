// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// Adjustable parameters
int speed = 200;         // Motor speed (0-255)
int rowLength = 3000;    // Time to traverse one row (in milliseconds)
int turnDuration = 1000; // Time to make a 90-degree turn (in milliseconds)
int rows = 5;            // Total number of rows in the area

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  for (int i = 0; i < rows; i++) {
    moveForward(rowLength); // Move forward for the length of the row
    
    if (i < rows - 1) {     // Turn only if not at the last row
      turnRight(turnDuration);
      moveForward(1000);    // Small forward movement to align with the next row
      turnRight(turnDuration);
    }
  }
  
  stopMotors(); // Stop the robot after completing all rows
  while (1);    // Keep the robot stopped (end program)
}

// Function to move forward
void moveForward(int duration) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stopMotors();
}

// Function to move backward
void moveBackward(int duration) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stopMotors();
}

// Function to turn right (pivot turn)
void turnRight(int duration) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stopMotors();
}

// Function to turn left (pivot turn)
void turnLeft(int duration) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stopMotors();
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
