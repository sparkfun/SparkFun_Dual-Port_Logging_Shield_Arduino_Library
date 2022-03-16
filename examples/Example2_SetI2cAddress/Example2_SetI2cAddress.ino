/*
  SparkFun Thing Plus Dual-Port Logging Shield Code Example
  By: Paul Clark
  Date: March 2022

  This code example demonstrates how to use the Dual-Port Logging Shield.

  The Shield's default I2C address is 0x51.

  Want to support open source hardware? Buy a board from SparkFun!
  SparkFun Thing Plus Dual-Port Logging Shield (DEV-19217): https://www.sparkfun.com/products/19217

*/

#include <SparkFun_Dual-Port_Logging_Shield.h> //Click here to get the library: http://librarymanager/All#SparkFun_Dual-Port_Logging

sfeDualPortLoggingShield myShield;

void setup()
{
  
  Serial.begin(115200); // Start the Serial port
  Serial.println(F("Dual-Port microSD Shield Code Example"));

  delay(1000); // Let the shield start up - it takes a full second

  Wire.begin(); // Start I2C

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Begin communication with the Dual-Port Logging Shield
  
  bool success = myShield.begin(); // Use the default I2C address and Wire port

  //bool success = myShield.begin(0x51, Wire); // Use a custom I2C address and/or port

  if (!success)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the I2C Address
  //
  // This function is essentially redundant since we need to know the Shield's address before we can read from it!
  // But it proves the Shield is connected and communicating.
  //
  // getI2cAddress returns zero if the read failed
  
  byte i2cAddress = myShield.getI2cAddress();

  if (i2cAddress == 0)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }
  else
  {
    Serial.print(F("The Shield's I2C Address is 0x"));
    Serial.println(i2cAddress, HEX);
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Set (write) the I2C Address

  Serial.println(F("Setting the Shield's I2C Address to 0x52"));
  
  bool result = myShield.setI2cAddress(0x52);

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }
  else
  {
    Serial.println(F("The Shield's I2C Address has been changed"));
  }

  delay(1000); // Allow time for the shield to restart its I2C interface

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Begin communication with the Dual-Port Logging Shield
  
  success = myShield.begin(0x52);

  if (!success)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the I2C Address
  
  i2cAddress = myShield.getI2cAddress();

  if (i2cAddress == 0)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }
  else
  {
    Serial.print(F("The Shield's I2C Address is 0x"));
    Serial.println(i2cAddress, HEX);
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Set (write) the I2C Address

  Serial.println(F("Setting the Shield's I2C Address back to 0x51"));
  
  result = myShield.setI2cAddress(0x51);

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }
  else
  {
    Serial.println(F("The Shield's I2C Address has been changed"));
  }

  delay(1000); // Allow time for the shield to restart its I2C interface

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Begin communication with the Dual-Port Logging Shield
  
  success = myShield.begin(0x51);

  if (!success)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the I2C Address
  
  i2cAddress = myShield.getI2cAddress();

  if (i2cAddress == 0)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ; // Do nothing more
  }
  else
  {
    Serial.print(F("The Shield's I2C Address is 0x"));
    Serial.println(i2cAddress, HEX);
  }

}

void loop()
{
  
  // Nothing to do here...

}
