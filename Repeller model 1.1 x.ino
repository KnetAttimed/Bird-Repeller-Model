/*  
  The project : Bird Repeller Model
  Program “Repeller model 1.1 x"
  coding by Knet Attimed (Kiattisak Phothawimoncharat)
  used for learning only please reference me
  https://github.com/KnetAttimed
*/
// Create a description by ChatGPT


// Setting general
int setd = 20;  // distance bird sensor (Distance used to detect the bird)
float temperature = 28; // Temperature in Celsius
float soundSpeed = 331.5 + 0.6 * (temperature); // Calculate sound speed based on temperature

// Ultrasonic sensor settings
int trig1 = 2;  // Trigger for front sensor
int echo1 = 3;  // Echo for front sensor
int timemisec1; // Time in microseconds for sensor 1
int distcm1;    // Distance in cm for sensor 1

int trig2 = 4;  // Trigger for back sensor
int echo2 = 5;  // Echo for back sensor
int timemisec2; // Time in microseconds for sensor 2
int distcm2;    // Distance in cm for sensor 2

int trig3 = 6;  // Trigger for left sensor
int echo3 = 7;  // Echo for left sensor
int timemisec3; // Time in microseconds for sensor 3
int distcm3;    // Distance in cm for sensor 3

int trig4 = 8;  // Trigger for right sensor
int echo4 = 9;  // Echo for right sensor
int timemisec4; // Time in microseconds for sensor 4
int distcm4;    // Distance in cm for sensor 4

// Relay module setup
const byte relayF = 10; // Front control
const byte relayB = 11; // Back control
const byte relayS = 12; // Side control & fan motor
const byte relayP = 13; // Buzzer (sound) control

// OLED display setup () want to use an extension
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// OLED display width in pixels 
#define SCREEN_WIDTH 128 
// OLED display height in pixels
#define SCREEN_HEIGHT 64 
// Reset pin (or -1 if sharing Arduino reset pin)
#define OLED_RESET -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Setup ultrasonic sensor pins
  pinMode(2, OUTPUT); // Front sensor trigger
  pinMode(3, INPUT);  // Front sensor echo
  pinMode(4, OUTPUT); // Back sensor trigger
  pinMode(5, INPUT);  // Back sensor echo
  pinMode(6, OUTPUT); // Left sensor trigger
  pinMode(7, INPUT);  // Left sensor echo
  pinMode(8, OUTPUT); // Right sensor trigger
  pinMode(9, INPUT);  // Right sensor echo

  // Setup relay control pins
  pinMode(relayF, OUTPUT); // Front control relay
  pinMode(relayB, OUTPUT); // Back control relay
  pinMode(relayS, OUTPUT); // Side control & fan motor relay
  pinMode(relayP, OUTPUT); // Buzzer control relay

  // Start serial communication
  Serial.begin(9600);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with I2C address
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
}

void loop() {
  checkSensor1(); // Read distance from front sensor
  checkSensor2(); // Read distance from back sensor
  checkSensor3(); // Read distance from left sensor
  checkSensor4(); // Read distance from right sensor
  oled(); // Output data to OLED display
  mainpumpF(); // Control front pump
  mainpumpB(); // Control back pump
  mainpumpS(); // Control side pump
}

// Coding by Knet Attimed (Kiattisak Phothawimoncharat)
// Create new functions
// Function to check the front sensor
void checkSensor1() {
  digitalWrite(trig1, LOW); // Set trigger pin low
  delayMicroseconds(2);      // Wait for 2 microseconds
  digitalWrite(trig1, HIGH); // Set trigger pin high
  delayMicroseconds(10);     // Wait for 10 microseconds
  digitalWrite(trig1, LOW);  // Set trigger pin low
  timemisec1 = pulseIn(echo1, HIGH); // Measure the pulse duration
  distcm1 = timemisec1 * (soundSpeed / 2.) * pow(10, -4); // Calculate the distance in cm
  Serial.print(distcm1); Serial.print(" "); // Output distance to serial monitor
}

// Function to check the back sensor
void checkSensor2() {
  digitalWrite(trig2, LOW); // Set trigger pin low
  delayMicroseconds(2);      // Wait for 2 microseconds
  digitalWrite(trig2, HIGH); // Set trigger pin high
  delayMicroseconds(5);      // Wait for 5 microseconds
  digitalWrite(trig2, LOW);  // Set trigger pin low
  timemisec2 = pulseIn(echo2, HIGH); // Measure the pulse duration
  distcm2 = timemisec2 * (soundSpeed / 2.) * pow(10, -4); // Calculate the distance in cm
  Serial.print(distcm2); Serial.print(" "); // Output distance to serial monitor
}

// Function to check the left sensor
void checkSensor3() {
  digitalWrite(trig3, LOW); // Set trigger pin low
  delayMicroseconds(2);      // Wait for 2 microseconds
  digitalWrite(trig3, HIGH); // Set trigger pin high
  delayMicroseconds(5);      // Wait for 5 microseconds
  digitalWrite(trig3, LOW);  // Set trigger pin low
  timemisec3 = pulseIn(echo3, HIGH); // Measure the pulse duration
  distcm3 = timemisec3 * (soundSpeed / 2.) * pow(10, -4); // Calculate the distance in cm
  Serial.print(distcm3); Serial.print(" "); // Output distance to serial monitor
}

// Function to check the right sensor
void checkSensor4() {
  digitalWrite(trig4, LOW); // Set trigger pin low
  delayMicroseconds(2);      // Wait for 2 microseconds
  digitalWrite(trig4, HIGH); // Set trigger pin high
  delayMicroseconds(5);      // Wait for 5 microseconds
  digitalWrite(trig4, LOW);  // Set trigger pin low
  timemisec4 = pulseIn(echo4, HIGH); // Measure the pulse duration
  distcm4 = timemisec4 * (soundSpeed / 2.) * pow(10, -4); // Calculate the distance in cm
  Serial.print(distcm4); Serial.println(" "); // Output distance to serial monitor
}

// Function to control the front pump
void mainpumpF() {
  if (distcm1 > 0) {
    if (distcm1 < setd) {
      digitalWrite(relayF, LOW); // Turn off relay if distance is below set distance
      delay(50);
    } else {
      digitalWrite(relayF, HIGH); // Turn on relay if distance is above set distance
    }
  }
}

// Function to control the back pump
void mainpumpB() {
  if (distcm2 > 0) {
    if (distcm2 < setd) {
      digitalWrite(relayB, LOW); // Turn off relay if distance is below set distance
      delay(50);
    } else {
      digitalWrite(relayB, HIGH); // Turn on relay if distance is above set distance
    }
  }
}

// Function to control the side pump and buzzer
void mainpumpS() {
  if (distcm1 < setd || distcm2 < setd || distcm3 < setd || distcm4 < setd) {
    digitalWrite(relayS, LOW); // Turn off side relay if any sensor detects an object
    digitalWrite(relayP, LOW); // Turn off buzzer if any sensor detects an object
  } else {
    digitalWrite(relayS, HIGH); // Turn on side relay if no sensor detects an object
    digitalWrite(relayP, HIGH); // Turn on buzzer if no sensor detects an object
  }
}
// Coding by Knet Attimed (Kiattisak Phothawimoncharat)
// Function to output data to OLED display
void oled() {
  display.clearDisplay(); // Clear previous display data
  display.setTextSize(1); // Set text size to 1
  display.setCursor(0, 0); // Set text cursor at the top-left corner

  // Display the status of each sensor and its distance
  display.print(" F : ");
  if (distcm1 < setd) {
    display.print("On  ");
  } else {
    display.print("Off ");
  }
  display.println(distcm1);

  display.print(" B : ");
  if (distcm2 < setd) {
    display.print("On  ");
  } else {
    display.print("Off ");
  }
  display.println(distcm2);

  display.print(" L : ");
  if (distcm3 < setd) {
    display.print("On  ");
  } else {
    display.print("Off ");
  }
  display.println(distcm3);

  display.print(" R : ");
  if (distcm4 < setd) {
    display.print("On  ");
  } else {
    display.print("Off ");
  }
  display.println(distcm4);

  // Display the status of the buzzer and pump
  if(distcm1 < setd||distcm2 < setd||distcm3 < setd||distcm4 < setd){
    display.println("Buzzer: On  ");
    display.println("Pump  : On  ");
  }
  else{
  display.println("Buzzer: Off ");
  display.println("Pump  : Off  "); }

  display.display();// Update the display
}






/*  
  The project : Bird Repeller Model
  Program “Repeller model 1.1 x"
  coding by Knet Attimed (Kiattisak Phothawimoncharat)
  used for learning only please reference me
  https://github.com/KnetAttimed
*/

