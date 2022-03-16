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

#include <SD.h>

//const int chipSelect = 10; // ** Change this to match the chip slect pin on your board **
#define chipSelect A5 // ** Change this to match the chip slect pin on your board **

File root;

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
  
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Put the shield into USB "thumb drive" (SDIO) mode

  Serial.println(F("Putting the shield into SDIO (USB \"thumb drive\") mode"));

  bool result = myShield.sdioMode();

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ;
  }

  delay(2000); // Be kind. Wait two seconds
  
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

  // Put the shield into Thing Plus / Arduino (SPI) mode

  Serial.println(F("Putting the shield into SPI (Thing Plus / Arduino) mode"));

  result = myShield.spiMode();

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ;
  }

  delay(2000); // Be kind. Wait two seconds
  
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  // Use the SD Library to print the directory of files on SD card
  // https://www.arduino.cc/en/Tutorial/LibraryExamples/Listfiles

  Serial.println(F("Initializing SD card..."));

  if (!SD.begin(chipSelect))
  {
    Serial.println("microSD card initialization failed! Freezing...");
    while (1)
      ;
  }

  Serial.println("Initialization complete.");

  root = SD.open("/");

  printDirectory(root, 0);

  delay(2000); // Be kind. Wait two seconds

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

} // /loop

void printDirectory(File dir, int numTabs) // https://www.arduino.cc/en/Tutorial/LibraryExamples/Listfiles
{

  while (true)
  {
    File entry =  dir.openNextFile();

    if (! entry)
    {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++)
    {
      Serial.print('\t');
    }

    Serial.print(entry.name());

    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }

    entry.close();
  }
  
} // /printDirectory
