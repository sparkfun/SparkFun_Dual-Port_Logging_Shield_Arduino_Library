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
  Serial.println(F("Dual-Port Logging Shield Code Example"));

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
    Serial.println(F("An error has occurred! Could not communicate with the Shield!"));
  else
  {
    Serial.print(F("The Shield's I2C Address is 0x"));
    Serial.println(i2cAddress, HEX);
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the firmware version
  //
  // getFirmwareVersion returns zero if the read failed
  // Version 1.0 = 0x10

  byte firmwareVersion = myShield.getFirmwareVersion();

  if (firmwareVersion == 0)
    Serial.println(F("An error has occurred! Could not communicate with the Shield!"));
  else
  {
    Serial.print(F("The Shield's Firmware Version is v"));
    Serial.print(firmwareVersion >> 4);
    Serial.print(F("."));
    Serial.println(firmwareVersion & 0x0F);
  }
  
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the default mode
  //
  // Returns SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN if the read failed
  // SFE_DUAL_PORT_LOGGING_MODE_SPI  = Thing Plus / Arduino (SPI) mode
  // SFE_DUAL_PORT_LOGGING_MODE_SDIO = USB "thumb drive" (SDIO) mode

  sfe_dual_port_logging_mode_e defaultMode = myShield.getDefaultMode();

  if (defaultMode == SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN)
    Serial.println(F("An error has occurred! Could not communicate with the Shield!"));
  else
  {
    Serial.print(F("The Shield's Default Mode is "));
    if (defaultMode == SFE_DUAL_PORT_LOGGING_MODE_SPI)
      Serial.println(F("SPI (Thing Plus / Arduino mode)"));
    else // if (defaultMode == SFE_DUAL_PORT_LOGGING_MODE_SDIO)
      Serial.println(F("SDIO (USB \"thumb drive\" mode)"));
  }
  
}

void loop()
{
  
  // Nothing to do here...

}
