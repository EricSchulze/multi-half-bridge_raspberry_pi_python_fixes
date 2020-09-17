/**
 * @file        gpio-rpi.cpp
 * @brief       Raspberry Pi PAL for the GPIO
 * @date        September 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio-rpi.hpp"
#include <wiringPiSPI.h>
#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_RPI)

// #include <Arduino.h>

/**
 * @brief Constructor of the Raspberry Pi GPIO class
 *
 * This function is setting the basics for a GPIO.
 *
 */
GPIORpi::GPIORpi() : pin(0), mode(OUTPUT), logic(POSITIVE) //Woher weiß ich welcher Pin? Bei Hall Switch Pin 4
{ 
}

/**
 * @brief Constructor of the Raspberry Pi GPIO class
 *
 * This function is setting the basics for a GPIO. It allows to set the pin number,
 * mode of the pin and the logic level.
 *
 * @param[in]   pin     Number of the desired pin
 * @param[in]   mode    Defines the mode of the pin (INPUT, OUTPUT, etc.)
 * @param[in]   logic   Defines the logic level of the pin
 */
GPIORpi::GPIORpi(uint8_t pin, uint8_t mode, VLogic_t logic): pin(pin), mode(mode), logic(logic)
{
}

/**
 * @brief Initialize the GPIO
 *
 * This function is initializing the chosen pin.
 *
 * @return      GPIORpi::Error_t
 */
GPIORpi::Error_t GPIORpi::init()
{
	GPIORpi::Error_t err = GPIORpi::OK;
	if (wiringPiSetup() < 0)
	{
		err = GPIORpi::INTF_ERROR; //gibts das in WiringPi?
	}
	
	pinMode(this->pin, this->mode);

	return err;
	
}

/**
 * @brief Deinitialize the GPIO
 *
 * This function is deinitializing the chosen pin.
 *
 * @return      GPIORpi::Error_t
 */
GPIORpi::Error_t GPIORpi::deinit()
{
	return OK;
}

/**
 * @brief Read GPIO logic level
 *
 * This function reads the logic level of the chosen pin and
 * returns the logic level value.
 *
 * @return      GPIORpi::VLevel_t
 * @retval      0    = GPIO_LOW
 * @retval      1    = GPIO_HIGH
 */
GPIORpi::VLevel_t GPIORpi::read()
{
	return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief Set GPIO logic level
 *
 * This functions sets the logic level of the chosen pin.
 *
 * @param[in]   level   Desired logic level of the pin
 * @return      GPIORpi::Error_t
 */
GPIORpi::Error_t GPIORpi::write(VLevel_t level)
{
	digitalWrite(this->pin, level);
	return OK;
}

/**
 * @brief Enable the GPIO
 *
 * This functions enable the chosen pin. Depending on the chosen logic of the pin
 * it sets the right logic level of the pin.
 *
 * @return      GPIORpi::Error_t
 */
GPIORpi::Error_t GPIORpi::enable()
{
	if(this->logic == POSITIVE){
		digitalWrite(this->pin, GPIO_HIGH);
	}
	else if(this->logic == NEGATIVE){
		digitalWrite(this->pin, GPIO_LOW);;
	}
	return GPIORpi::OK;
}

/**
 * @brief Disable the GPIO
 *
 * This functions disables the chosen pin. Depending on the chosen logic of the pin
 * it sets the right logic level of the pin.
 *
 * @return      GPIOIno::Error_t
 */
GPIORpi::Error_t GPIORpi::disable()
{
	if(this->logic == POSITIVE){
		digitalWrite(this->pin, GPIO_LOW);
	}
	else if(this->logic == NEGATIVE){
		digitalWrite(this->pin, GPIO_HIGH);
	}
	return GPIORpi::OK;
}


#endif /** TLE94112_FRAMEWORK **/



