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

#define chipSelect A5 // ** Change this to match the chip slect pin on your board **

//const int chipSelect = 24; // ** On the Artemis Thing Plus: A5 is D24 **

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

}

void loop()
{
  
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Put the shield into deep sleep

  Serial.println(F("Putting the shield into deep sleep"));

  bool result = myShield.sleep();

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ;
  }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Serial.print(F("Waiting 30 seconds"));
  for (int i = 0; i < 30; i++)
  {
    delay(1000);
    Serial.print(F("."));
  }
  Serial.println();

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Wake the shield and put it into USB "thumb drive" (SDIO) mode

  Serial.println(F("Putting the shield into SDIO (USB \"thumb drive\") mode"));

  result = myShield.sdioMode();

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ;
  }

  delay(1000); // Let the shield start up - it takes a full second

  Serial.println(F("The shield should now appear as a USB device"));

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Serial.print(F("Waiting 30 seconds"));
  for (int i = 0; i < 30; i++)
  {
    delay(1000);
    Serial.print(F("."));
  }
  Serial.println();

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

} // /loop
