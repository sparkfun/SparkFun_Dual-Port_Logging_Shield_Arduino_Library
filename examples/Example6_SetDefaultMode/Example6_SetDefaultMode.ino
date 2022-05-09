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

#define myWire Wire // Define which Wire port to use. Change this to Wire1 if you are using the Artemis Thing Plus or the expLoRaBLE

void setup()
{
  
  Serial.begin(115200); // Start the Serial port
  Serial.println(F("Dual-Port Logging Shield Code Example"));

  delay(1000); // Let the shield start up - it takes a full second

  myWire.begin(); // Start I2C

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Begin communication with the Dual-Port Logging Shield
  
  //bool success = myShield.begin(); // Use the default I2C address and Wire port

  bool success = myShield.begin(0x51, myWire); // Use a custom I2C address and/or port

  if (!success)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield!"));
    Serial.println(F("Please try powering the board off and on again..."));
    while (1)
      ; // Do nothing more
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

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Set the default mode
  //
  // The choices are:
  // SFE_DUAL_PORT_LOGGING_MODE_SPI  = Thing Plus / Arduino (SPI) mode
  // SFE_DUAL_PORT_LOGGING_MODE_SDIO = USB "thumb drive" (SDIO) mode

  bool result = myShield.setDefaultMode(SFE_DUAL_PORT_LOGGING_MODE_SDIO);

  if (!result)
    Serial.println(F("An error has occurred! Could not communicate with the Shield!"));
  else
  {
    Serial.println(F("The Shield's Default Mode has been set"));
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Get (read) the default mode
  //
  // Returns SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN if the read failed
  // SFE_DUAL_PORT_LOGGING_MODE_SPI  = Thing Plus / Arduino (SPI) mode
  // SFE_DUAL_PORT_LOGGING_MODE_SDIO = USB "thumb drive" (SDIO) mode

  defaultMode = myShield.getDefaultMode();

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
  
  // Nothing to do here

} // /loop
