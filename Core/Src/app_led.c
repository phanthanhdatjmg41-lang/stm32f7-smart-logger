#include "app_led.h"
#include "app_config.h"

/*
 * Ham LED_On:
 * Chuc nang:
 * - Bat LED ngoai.
 */
void LED_On(void)
{
    HAL_GPIO_WritePin(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN, GPIO_PIN_SET);
}

/*
 * Ham LED_Off:
 * Chuc nang:
 * - Tat LED ngoai.
 */
void LED_Off(void)
{
    HAL_GPIO_WritePin(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN, GPIO_PIN_RESET);
}

/*
 * Ham LED_Toggle:
 * Chuc nang:
 * - Dao trang thai LED.
 */
void LED_Toggle(void)
{
    HAL_GPIO_TogglePin(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN);
}

/*
 * Ham LED_GetState:
 * Chuc nang:
 * - Doc trang thai hien tai cua LED.
 */
GPIO_PinState LED_GetState(void)
{
    return HAL_GPIO_ReadPin(APP_LED_GPIO_PORT, APP_LED_GPIO_PIN);
}
