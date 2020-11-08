// Simple script to control a 4-wire PWM fan using a rotary potentiometer
// Based on the Fancontroller library by Giorgio Aresu
// Install the fancontroller library 


#include <FanController.h>

// Analog read of the potentiometer 

#define Pot A0

// Sensor tach speed signal is connected to pin 9. Green wire on Noctua fans. 

#define SENSOR_PIN 9


// PWM control pin is connected to pin 9. Blue wire on Noctua fans. 

#define PWM_PIN 9

// Define the measurement interval 

#define SENSOR_THRESHOLD 500


// Initialize library
FanController fan(SENSOR_PIN, SENSOR_THRESHOLD, PWM_PIN);

/*
   The setup function.
*/
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Starting fan control");

  // Start up the library
  fan.begin();
}

/*
   Main function, get and show the temperature
*/
void loop(void)
{
  // Call fan.getSpeed() to get fan RPM.
  Serial.print("Current speed: ");
  unsigned int rpms = fan.getSpeed(); // Send the command to get RPM
  Serial.print(rpms);
  Serial.println("RPM");

  
  // Parse speed
  int input = analogRead(Pot);

  // Map the analog read result to a 0-100% duty cycle range. Using 32-100% here - which just about turns the fan off at the lowest setting with the NF-A14 iPPC 3000 fan. 
  
  byte target = map(input, 0, 1023, 32, 100);


  // Set fan duty cycle
  fan.setDutyCycle(target);

  // Get duty cycle
  byte dutyCycle = fan.getDutyCycle();
  Serial.print("Duty cycle: ");
  Serial.println(dutyCycle, DEC);
  

  // Not really needed, just avoiding spamming the monitor,
  // readings will be performed no faster than once every THRESHOLD ms anyway
  delay(500.);
}
