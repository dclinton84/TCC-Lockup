#include <PWM.h>
int32_t frequency = 200; // PWM frequency in Hz
int d = 0; // Lockup switch state low/high
int dialSet = 0; // Potentiometer value
int duty = 0; // Duty cycle

void setup() {
  // put your setup code here, to run once:
InitTimersSafe();
pinMode(6, INPUT); // Lockup switch
pinMode(8, OUTPUT); // Relay 1 (ECU signal +)
pinMode(9, OUTPUT); // Relay 2 (Solenoid +)
pinMode(10, OUTPUT); // Relay 3 (Solenoid -)
pinMode(11, OUTPUT); // Relay 4 (ECU signal -)
pinMode(13, OUTPUT); // Built in LED
pinMode(A0, INPUT); // Potentiometer
}

void loop() {
  // put your main code here, to run repeatedly:

d = digitalRead(6); // Read lockup switch state
dialSet = analogRead(A0); // Read potentiometer value
duty = map(dialSet, 0, 1023, 50, 149); // Map potentiometer values to max/min values for PWM
if(d==1) // If lockup switch is on
{bool success = SetPinFrequencySafe(3, frequency); // Set pin 3 PWM freq to variable
analogWrite(3, duty); // Start PWM signal output on pin 3 according to where potentiometer is set
digitalWrite(13, HIGH); // Turn on built in LED
digitalWrite(8, HIGH); // Switch relay 1 (ECU signal + from solenoid + to resistor)
digitalWrite(9, HIGH); // Switch relay 2 (Solenoid + from ECU signal + to mosfet out +)
digitalWrite(10, HIGH); // Switch relay 3 (Solenoid - from ECU signal - to mosfet out -)
digitalWrite(11, HIGH); // Switch relay 4 (ECU signal - from solenoid - to resistor)
}
else
{digitalWrite(13, LOW); // Turn off built in LED
digitalWrite(8, LOW); // Switch relay 1 (ECU signal + from resistor to solenoid +)
digitalWrite(9, LOW); // Switch relay 2 (Solenoid + wire from mosfet out + to ECU signal +)
digitalWrite(10, LOW); // Switch relay 3 (Solenoid - from mosfet out - to ECU signal -)
digitalWrite(11, LOW); // Switch relay 4 (ECU signal - from resistor to solenoid -)
analogWrite(3, 0);} // Stop PWM signal output
}
