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

#include <SD.h>

#define chipSelect A5 // ** Change this to match the chip slect pin on your board **

//const int chipSelect = 24; // ** On the Artemis Thing Plus: A5 is D24 **

File root;

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

  // Wake the shield and put it into Thing Plus / Arduino (SPI) mode

  Serial.println(F("Putting the shield into SPI (Thing Plus / Arduino) mode"));

  result = myShield.spiMode();

  if (!result)
  {
    Serial.println(F("An error has occurred! Could not communicate with the Shield! Freezing..."));
    while (1)
      ;
  }

  delay(1000); // Let the shield start up - it takes a full second

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

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Serial.print(F("Waiting 5 seconds"));
  for (int i = 0; i < 5; i++)
  {
    delay(1000);
    Serial.print(F("."));
  }
  Serial.println();

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
