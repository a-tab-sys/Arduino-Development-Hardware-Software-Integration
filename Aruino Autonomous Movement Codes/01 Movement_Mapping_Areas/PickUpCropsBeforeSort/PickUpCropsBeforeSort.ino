//Pick Up All Crops Before Sorting
//In this approach, the robot collects all crops first, stores them in a container, and then goes to the sorting station.

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// Other variables
int fieldWidth = 5;    // Number of rows
int fieldHeight = 7;   // Number of columns
int cropPickupPin = A0; // Simulate picking up a crop (e.g., through a sensor or mechanism)

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(cropPickupPin, INPUT);

  Serial.begin(9600);
  // Initial state: Motors off
  stopMotors();
}

void loop() {
  traverseField();
  goToSortingStation();
}

void traverseField() {
  for (int i = 0; i < fieldHeight; i++) {
    if (i % 2 == 0) {
      moveStraight(fieldWidth); // Move right
    } else {
      moveStraight(-fieldWidth); // Move left
    }
    moveToNextRow();
  }
}

void moveStraight(int steps) {
  for (int i = 0; i < abs(steps); i++) {
    driveForward();
    checkForCrop();
  }
}

void moveToNextRow() {
  turnRight();
  driveForward(1); // Move to the next row
  turnRight();
}

void goToSortingStation() {
  // Navigate to the sorting station
  stopMotors();
  Serial.println("All crops collected. Going to the sorting station...");
  // Logic to move to the sorting area
}

void checkForCrop() {
  if (digitalRead(cropPickupPin) == HIGH) {
    Serial.println("Crop picked up!");
    delay(500); // Simulate picking time
  }
}

void driveForward(int steps = 1) {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000 * steps);
  stopMotors();
}

void turnRight() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(800); // Adjust for turning angle
  stopMotors();
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}