#ifndef APP_LED_H
#define APP_LED_H

/*
 * File: app_led.h
 * Chuc nang:
 * - Khai bao cac ham dieu khien LED
 */

#include "main.h"

/*
 * LED_On:
 * Bat LED.
 */
void LED_On(void);

/*
 * LED_Off:
 * Tat LED.
 */
void LED_Off(void);

/*
 * LED_Toggle:
 * Dao trang thai LED.
 */
void LED_Toggle(void);

/*
 * LED_GetState:
 * Doc trang thai hien tai cua LED.
 *
 * Gia tri tra ve:
 * - GPIO_PIN_SET
 * - GPIO_PIN_RESET
 */
GPIO_PinState LED_GetState(void);

#endif
