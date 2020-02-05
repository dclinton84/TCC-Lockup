#include <PWM.h>
int32_t frequency = 200; // PWM frequency in Hz
int d = 0; // Lockup switch state low/high
int dialSet = 0; // Potentiometer value
int duty = 0; // Duty cycle

void setup() {
  InitTimersSafe();
  pinMode(3, OUTPUT); // PWM signal to MOSFET
  pinMode(6, INPUT); // Lockup switch
  pinMode(8, OUTPUT); // Relay 1 (ECU signal to solenoid or resistor)
  pinMode(9, OUTPUT); // Relay 2 (Solenoid to ECU signal or Arduino signal)
  pinMode(11, OUTPUT); // 5V feed to MOSFET board
  pinMode(12, OUTPUT); // 5V feed to potentiometer
  pinMode(13, OUTPUT); // Built in LED
  pinMode(A0, INPUT); // Potentiometer
  digitalWrite(11, HIGH); // Turn on pin 11 for MOSFET board
  digitalWrite(12, HIGH); // Turn on pin 12 for potentiometer
}

void loop() {
  d = digitalRead(6); // Read lockup switch state
  dialSet = analogRead(A0); // Read potentiometer value
  duty = map(dialSet, 0, 1023, 50, 149); // Map potentiometer values to max/min values for PWM
  if(d==1) // If lockup switch is on
    {bool success = SetPinFrequencySafe(3, frequency); // Set pin 3 PWM freq to variable
    analogWrite(3, duty); // Start PWM signal output on pin 3 according to where potentiometer is set
    digitalWrite(13, HIGH); // Turn on built in LED
    digitalWrite(8, HIGH); // Switch relay 1 (ECU signal from solenoid to resistor)
    digitalWrite(9, HIGH);} // Switch relay 2 (Solenoid from ECU signal to MOSFET out)
  else
    {digitalWrite(13, LOW); // Turn off built in LED
    digitalWrite(8, LOW); // Switch relay 1 (ECU signal from resistor to solenoid)
    digitalWrite(9, LOW); // Switch relay 2 (Solenoid from MOSFET out to ECU signal)
    analogWrite(3, 0);} // Stop PWM signal output
}
