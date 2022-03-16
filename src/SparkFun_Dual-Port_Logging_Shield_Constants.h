/*!
 * @file SparkFun_Dual-Port_Logging_Shield_Constants.h
 *
 * SparkFun Dual-Port Logging Shield Arduino Library
 * 
 * This library facilitates communication with the Thing Plus Dual-Port Logging Shield over I<sup>2</sup>C.
 * 
 * Want to support open source hardware? Buy a board from SparkFun!
 * <br>SparkFun Thing Plus Dual-Port Logging Shield (DEV-19217): https://www.sparkfun.com/products/19217
 * 
 * This library was written by:
 * Paul Clark
 * SparkFun Electronics
 * March 2022
 * 
 * Please see LICENSE.md for the license information
 * 
 */

#ifndef __SFE_DUAL_PORT_LOGGING_CONSTANTS__
#define __SFE_DUAL_PORT_LOGGING_CONSTANTS__

//Platform specific configurations

#if !defined(I2C_BUFFER_LENGTH) && !defined(ARDUINO_ARCH_ESP32)

//The catch-all default is 32
#define I2C_BUFFER_LENGTH 32

#endif

#define SFE_DUAL_PORT_LOGGING_DEFAULT_I2C_ADDRESS 0x51

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/** delay durations for the eeprom update */
#define SFE_DUAL_PORT_LOGGING_EEPROM_UPDATE_DELAY  6  ///< The eeprom update takes ~4ms to complete at 4MHz. 6ms provides margin.

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/** The addresses of the registers within the ATtiny43U's memory */
typedef enum 
{
  SFE_DUAL_PORT_LOGGING_REGISTER_I2C_ADDRESS = 0x00,
  SFE_DUAL_PORT_LOGGING_REGISTER_FIRMWARE_VERSION,
  SFE_DUAL_PORT_LOGGING_REGISTER_DEFAULT_MODE,
  SFE_DUAL_PORT_LOGGING_REGISTER_SLEEP,
  SFE_DUAL_PORT_LOGGING_REGISTER_SPI_MODE,
  SFE_DUAL_PORT_LOGGING_REGISTER_SDIO_MODE
} sfe_dual_port_logging_registers_e;

/** The default modes */
typedef enum 
{
  SFE_DUAL_PORT_LOGGING_MODE_SPI = 0x00,
  SFE_DUAL_PORT_LOGGING_MODE_SDIO,
  SFE_DUAL_PORT_LOGGING_MODE_UNKNOWN
} sfe_dual_port_logging_mode_e;

#endif // /__SFE_DUAL_PORT_LOGGING_CONSTANTS__
