#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/*
 * File: app_config.h
 * Chuc nang:
 * - Luu cac cau hinh chung cua do an
 *
 * Ly do tao file nay:
 * - Gom cac thong so hay thay doi vao mot cho
 * - Khi can doi chan LED, kich thuoc buffer, timeout...
 *   chi can sua trong file nay
 */

#include "main.h"

/*
 * Cau hinh LED
 * LED hien tai duoc noi voi chan PH4.
 */
#define APP_LED_GPIO_PORT      GPIOH
#define APP_LED_GPIO_PIN       GPIO_PIN_4

/*
 * Cau hinh UART command buffer
 * Gia tri 50 nghia la moi lenh toi da 49 ky tu + 1 ky tu '\0'.
 */
#define APP_UART_BUFFER_SIZE   50

/*
 * Timeout khi nhan 1 byte UART.
 * Don vi: ms
 */
#define APP_UART_RX_TIMEOUT    10

/*
 * Timeout khi gui UART.
 * Don vi: ms
 */
#define APP_UART_TX_TIMEOUT    1000

#endif
