//
//Date: 6/16/17
//Version: 1.0
//
//Comments:
//This sketch reads an analog temperature sensor and writes the temperature in F to the serial monitor
//
// Analog Temperature Sensor Connection:
// Vout Pin: Connect to analog input 0.
//

// The AREF pin is tied to the 3.3V output pin to be used as an external reference for the ADC
#define aref_ext_voltage 3.3
// Assign Arduino analog input pin to be connected to temp sensor 
int tempPin = 0;
// Assign a variable to hold the temperature sensor reading 
int tempVal; // the analog reading from the sensor


void setup() {
  // put your setup code here, to run once:
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 

  // Need to tell Arduino that we are using an external voltage reference for ADC
  // Always have to set this first before calling analogRead() or else you could short out your board
  analogReference(EXTERNAL);
  // Allow voltage on ADC to settle out before reading
  analogRead(0);

}

//Returns the ambient temperature
float ReadTemp(bool DegC)
{
// Read the temperature sensor and store the value
tempVal = analogRead(tempPin); 
// debug - print raw along reading to serial monitor
//Serial.print(tempReading); 

// Convert the digitized number 0-1023 from the ADC into a voltage based on the reference voltage
// For an external reference voltage of 3.3V => (ADC value) * (3.3V/1024)
float voltageConvert = tempVal * aref_ext_voltage;
voltageConvert /= 1024.0; 
// debug - print out the voltage
//Serial.print(" - ");
//Serial.print(voltageConvert); Serial.println(" volts");

// Convert the voltage into temperature using the linear graph data from the TMP36 datasheet
// TMP36 has 500mV offset and 10mV/C degree scale
// Temp in C = (Voltage - 500mV)/10
// Voltage is in Volts so multiply by 100 instead of divide by 10 to get correct result (1000mV=1V)
float tempC = (voltageConvert - 0.5) * 100 ; 

// Convert C to F
float tempF = (tempC * 9.0 / 5.0) + 32.0;
// Print temperature in F to serial monitor
Serial.print(tempF); Serial.println(" degrees F");

if(DegC)
  return tempC;

return tempF;  
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadTemp(true);
}
