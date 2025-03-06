// Include NewPing Library for ultrasonic sensor
#include "NewPing.h"

// Motor A connections
int enA = 9;  // Enable pin for Motor A (controls speed)
int in1 = 8;  // Direction control pin 1 for Motor A
int in2 = 7;  // Direction control pin 2 for Motor A
// Motor B connections
int enB = 3;  // Enable pin for Motor B (controls speed)
int in3 = 5;  // Direction control pin 1 for Motor B
int in4 = 4;  // Direction control pin 2 for Motor B

// Store current location
int currentlocation[2] = { 0, 0 };
//currentlocation[0] = newX;  // Update x
//currentlocation[1] = newY;  // Update y

// Store target location
int targetlocation1[2] = { 1, 6 };
int targetlocation2[2] = { 1, 7 };
//int targetlocation3[2] = { 1, 8 };

//Store field starting point location
int fieldlocation[2] = { 4, 1 };

//Store Orientation: facing up=3; facing down=1, facing right = 0, facing left=2
int orientation = 2;

//Store delay/speed parameters
int turnDelay = 800;      //subject to change
int stepDelay = 500;      //subject to change
int standardSpeed = 150;  //max: 255

//after expirimentation, this will hold how far the robot goes after taking 1 "step"
int stepDistance;

//Completion condition (If we know the number objects)
int totalObjects = 70;     // Total crops in the field
int objectsHandled = 0;    // Counter for crops harvested and sorted
bool jobComplete = false;  // Flag to indicate the job is complete


/* Recieve Input - Input pin to simulate detecting something
int anySensor = PIN; 

IR AND LED - https://circuitdigest.com/microcontroller-projects/interfacing-ir-sensor-module-with-arduino
int IRSensor = 9; //input
int LED = 13; //output - conect LED to Arduino pin 13

ULTRASONIC - https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/
#define TRIGGER_PIN 9 // Trigger and Echo both on pin 9
#define ECHO_PIN 9

//COLOR Sensor - https://circuitdigest.com/microcontroller-projects/interfacing-color-sensor-with-arduino

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

*/

void setup() {
  // Set motor pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Serial Working");  // check if serial is working or not

  /* Set sensor pin as input
  pinMode(anySensor, INPUT);  
  --------------
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(LED, OUTPUT); // LED Pin Output
  */

  Serial.println("Starting task...");
  // Initially all motors off
  stopMotors();
}

void loop() {
  /* IR AND LED SENSOR
  int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
  if (sensorStatus == 1) // Check if the pin high or not
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW); // LED LOW
    Serial.println("Motion Ended!"); // print Motion Detected! on the serial monitor window
  }
  else
  {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH); // LED High
    Serial.println("Motion Detected!"); // print Motion Ended! on the serial monitor window
  }
  */

  /* ULRASONIC SENSOR
  Serial.print("Distance = ");
	Serial.print(sonar.ping_cm());              //whole number
  Serial.print((sonar.ping() / 2) * 0.0343);  //decimal
	Serial.println(" cm");
	delay(500);
  */

  pickUpAndNavigate();
}


// Stop Motors
void stopMotors() {
  Serial.println("Motors off");

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Turn Right
void turnRight() {
  Serial.println("Turning right");

  analogWrite(enA, standardSpeed);  // Set speed for Motor A
  analogWrite(enB, standardSpeed);  // Set speed for Motor B

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(turnDelay);  // Adjust delay for a 90-degree turn
  stopMotors();

  //Amend orientation
  if (orientation < 3) {
    orientation++;
  } else {
    orientation = 0;
  }
}

// Turn Left
void turnLeft() {
  Serial.println("Turning left");

  analogWrite(enA, standardSpeed);  // Set speed for Motor A
  analogWrite(enB, standardSpeed);  // Set speed for Motor B

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(turnDelay);  // Adjust delay for a 90-degree turn
  stopMotors();

  //Amend orientation
  if (orientation > 0) {
    orientation--;
  } else {
    orientation = 3;
  }
}

// Move forward
void stepsForward(int steps) {
  Serial.println("Moving forward");

  analogWrite(enA, standardSpeed);
  analogWrite(enB, standardSpeed);

  for (int i = 0; 1 < steps; i++) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(stepDelay);
  }
  stopMotors();

  //Amend location
  //currentlocation[0] = newX;  // Update x
  //currentlocation[1] = newY;  // Update y
  if (orientation == 3) {
    currentlocation[1] = (currentlocation[1] - steps);
  } else if (orientation == 1) {
    currentlocation[1] = (currentlocation[1] + steps);
  } else if (orientation == 0) {
    currentlocation[0] = (currentlocation[0] - steps);
  } else if (orientation == 2) {
    currentlocation[0] = (currentlocation[0] + steps);
  } else {
    Serial.print("You made some error, FIX ME!");
  }
}

// Move backward
void stepsBackward(int steps) {
  Serial.println("Moving backward");

  analogWrite(enA, standardSpeed);
  analogWrite(enB, standardSpeed);

  for (int i = 0; 1 < steps; i++) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(stepDelay);
  }
  stopMotors();
}

void orientUp() {
  if (orientation == 3) {
    Serial.println("I am looking up");
  } else if (orientation == 2) {
    Serial.println("Turning...");
    turnRight();
  } else if (orientation == 1) {
    Serial.println("Turning...");
    turnRight();
    turnRight();
  } else if (orientation == 0) {
    Serial.println("Turning...");
    turnLeft()
  }
}

void goToTarget() {  //depends on my sensor reading
                     //Sensor reads HIGH - i will redirect to target location 1
  if (anySensor == HIGH) {
    //where to go on the x-axis
    orientUp();
    Serial.println("Heading to the sorting station in x- direction");
    if (currentlocation[0] > targetlocation1[0]) {
      turnRight();
      int onXAxis = abs(currentlocation[0] - targetlocation1[0]);
      stepsForward(onXAxis);
    } else if (currentlocation[0] == targetlocation1[0]) {
      //no action required in x direction
    } else if (currentlocation[0] < targetlocation1[0]) {
      turnLeft();
      int onXAxis = abs(currentlocation[0] - targetlocation1[0]);
      stepsForward(onXAxis);
    }

    //where to go on the y-axis
    orientUp();
    Serial.println("Heading to the sorting station in y- direction");
    if (currentlocation[1] > targetlocation1[1]) {
      int onYAxis = abs(currentlocation[1] - targetlocation1[1]);
      stepsForward(onYAxis);
    } else if (currentlocation[1] == targetlocation1[1]) {
      //no action required in x direction
    } else if (currentlocation[1] < targetlocation1[1]) {
      turnLeft();
      turnLeft();
      int onYAxis = abs(currentlocation[1] - targetlocation1[1]);
      stepsForward(onYAxis);
    }
  }

  //Sensor reads LOW - i will redirect to target location 2
  else if (anySensor == LOW) {
    //where to go on the x-axis
    orientUp();
    Serial.println("Heading to the sorting station in x- direction");
    if (currentlocation[0] > targetlocation2[0]) {
      turnRight();
      int onXAxis = abs(currentlocation[0] - targetlocation2[0]);
      stepsForward(onXAxis);
    } else if (currentlocation[0] == targetlocation2[0]) {
      //no action required in x direction
    } else if (currentlocation[0] < targetlocation2[0]) {
      turnLeft();
      int onXAxis = abs(currentlocation[0] - targetlocation2[0]);
      stepsForward(onXAxis);
    }

    //where to go on the y-axis
    orientUp();
    Serial.println("Heading to the sorting station in y- direction");
    if (currentlocation[1] > targetlocation2[1]) {
      int onYAxis = abs(currentlocation[1] - targetlocation2[1]);
      stepsForward(onYAxis);
    } else if (currentlocation[1] == targetlocation2[1]) {
      //no action required in x direction
    } else if (currentlocation[1] < targetlocation2[1]) {
      turnLeft();
      turnLeft();
      int onYAxis = abs(currentlocation[1] - targetlocation2[1]);
      stepsForward(onYAxis);
    }
  }
}

//print coordinates for any location array
void printCoordinates(const int location[], const char* locationName) {
  // Print the name of the location and its coordinates
  Serial.print(locationName);
  Serial.print(" -> Row: ");
  Serial.print(location[0]);
  Serial.print(", Column: ");
  Serial.println(location[1]);

  //Call function like below
  //printCoordinates(targetLocation1, "Target Location 1");
  //printCoordinates(currentLocation, "Current Location");
  //printCoordinates(fieldLocation, "Field Location");
}

//goes to field starting location
void returnToField() {
  //where to go on the x-axis
  orientUp();
  Serial.println("Heading to the field station in x- direction");
  if (currentlocation[0] > fieldlocation[0]) {
    turnRight();
    int onXAxis = abs(currentlocation[0] - fieldlocation[0]);
    stepsForward(onXAxis);
  } else if (currentlocation[0] == fieldlocation[0]) {
    //no action required in x direction
  } else if (currentlocation[0] < fieldlocation[0]) {
    turnLeft();
    int onXAxis = abs(currentlocation[0] - fieldlocation[0]);
    stepsForward(onXAxis);
  }

  //where to go on the y-axis
  orientUp();
  Serial.println("Heading to the sorting station in y- direction");
  if (currentlocation[1] > fieldlocation[1]) {
    int onYAxis = abs(currentlocation[1] - fieldlocation[1]);
    stepsForward(onYAxis);
  } else if (currentlocation[1] == fieldlocation[1]) {
    //no action required in x direction
  } else if (currentlocation[1] < fieldlocation[1]) {
    turnLeft();
    turnLeft();
    int onYAxis = abs(currentlocation[1] - fieldlocation[1]);
    stepsForward(onYAxis);
  }
  orient();
}

void pickUp() {  //This will probably be moving a servo motor
  // // scan from 0 to 180 degrees
  // for(angle = 0; angle < 180; angle++) {
  //     servo.write(angle);
  //     delay(15);
  // }

  // // now scan back from 180 to 0 degrees
  // for(angle = 180; angle > 0; angle--) {
  //     servo.write(angle);
  //     delay(15);
  // }

  //Track how many objects we have dealt with / check if task is complete or not
  objectsHandled++;
  if (objectsHandled == totalObjects) {
    jobComplete = true;  // Set job complete flag
    Serial.println("All crops have been harvested and sorted. Job complete!");
  }
}

void dropOff() {  //This will probably be moving a servo motor
                  // // scan from 0 to 180 degrees
                  // for(angle = 0; angle < 180; angle++) {
                  //     servo.write(angle);
                  //     delay(15);
                  // }

  // // now scan back from 180 to 0 degrees
  // for(angle = 180; angle > 0; angle--) {
  //     servo.write(angle);
  //     delay(15);
  // }
}

void goHome() {
  //logic to get robot to go back to home base
}


//MOST IMPORTANT FUNCTION
// Function to pick up one crop at a time and navigate throught the field of crop
void pickUpAndNavigate(int numFieldRows, int rowLength, int cellSize) {

  returnToField();
  turnLeft();

  int fieldLengthSteps = rowLength / stepDistance;
  int nextRowSteps = cellSize / stepDistnce;

  if (!jobComplete) {
    returnToField();
    turnLeft();

    while (anySensor == LOW) {

      for (int y = 1; y <= numFieldRows, y++) {

        stepsForward(fieldLengthSteps);

        if (y % 2 == 0) {  //if row is even - go right
          turnRight();
          stepsForward(nextRowSteps);
          turnRight();

        } else {  // if row is odd - go left
          turnLeft();
          stepsForward(nextRowSteps);
          turnleft();
        }
      }
    }
    pickup();
    goToTarget();
    dropOff();
  } else {
    Serial.println("Robot is going home for rest.");
    goHome();

    // Stop the program - created infinite loop - will not follow any instruction now
    while (true)
      ;
  }
}


/*
// Motor A connections
int enA = 9, in1 = 8, in2 = 7;
// Motor B connections
int enB = 3, in3 = 5, in4 = 4;

// Field dimensions (rows x columns)
const int rows = 4;  // Adjust based on field layout
const int cols = 5;  // Adjust based on field layout

// Field representation: 0 = unprocessed, 1 = processed
int field[rows][cols] = {
  {0, 0, 0, 0, 0},  // Row 0
  {0, 0, 0, 0, 0},  // Row 1
  {0, 0, 0, 0, 0},  // Row 2
  {0, 0, 0, 0, 0}   // Row 3
};

int currentRow = 0; // Starting row
int currentCol = 0; // Starting column

bool jobComplete = false; // Flag for completion

void setup() {
  // Motor setup
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Start Serial communication
  Serial.begin(9600);
  Serial.println("Starting crop harvesting task...");
}

void loop() {
  if (!jobComplete) {
    processField(); // Process all crops in the field
  } else {
    // Stop all robot operations
    Serial.println("All crops have been harvested and sorted. Job complete!");
    while (true); // Halt the program
  }
}

// Function to process the entire field
void processField() {
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (field[r][c] == 0) { // If crop is unprocessed
        navigateToLocation(r, c); // Navigate to the location
        handleCrop(r, c); // Harvest and mark as processed
      }
    }
  }
  // Check if all crops are processed
  if (checkCompletion()) {
    jobComplete = true;
  }
}

// Function to navigate to a specific field location
void navigateToLocation(int targetRow, int targetCol) {
  Serial.print("Navigating to location: [");
  Serial.print(targetRow);
  Serial.print(", ");
  Serial.print(targetCol);
  Serial.println("]");
  
  // Insert motor control code here to move the robot to (targetRow, targetCol)
  delay(1000); // Simulate travel time
}

// Function to handle a crop (harvest and mark as processed)
void handleCrop(int row, int col) {
  Serial.print("Handling crop at location: [");
  Serial.print(row);
  Serial.print(", ");
  Serial.print(col);
  Serial.println("]");
  
  // Simulate crop harvesting
  delay(500); // Simulate harvesting time
  
  // Mark the crop as processed
  field[row][col] = 1;
  Serial.println("Crop processed.");
}

// Function to check if all crops are processed
bool checkCompletion() {
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      if (field[r][c] == 0) { // If any crop is unprocessed
        return false;
      }
    }
  }
  return true; // All crops are processed
}



field Array:

Represents the crop field. Each element indicates whether the crop at that location is processed (0 = unprocessed, 1 = processed).
processField():

Iterates through all locations in the field and processes unprocessed crops.
navigateToLocation(int targetRow, int targetCol):

Simulates navigation to a specific crop location.
Replace the delay with your actual navigation logic.
handleCrop(int row, int col):

Simulates harvesting the crop at the specified location and marks it as processed in the field array.
checkCompletion():

Checks if all crops in the field are marked as processed. If all are processed, it sets the jobComplete flag.

*/


