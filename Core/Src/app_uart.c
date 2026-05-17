#include "app_uart.h"
#include "app_config.h"
#include <string.h>
/*
 * extern UART_HandleTypeDef huart1:
 * Bien huart1 da duoc tao trong main.c boi STM32CubeIDE.
 * O day dung extern de file app_uart.c co the su dung UART1.
 */
/*
 * Khong khai bao extern systemState o day nua.
 * Ly do:
 * - Trang thai he thong da duoc quan ly rieng trong app_system.c
 * - app_uart.c chi thay doi trang thai thong qua ham System_SetState()
 * - app_uart.c chi doc trang thai thong qua ham System_GetStateString()
 */
extern UART_HandleTypeDef huart1;



/*
 * Ham UART_Send:
 * Chuc nang:
 * - Gui mot chuoi ky tu ra UART1.
 *
 * Ly do viet ham rieng:
 * - De khong phai viet HAL_UART_Transmit dai nhieu lan.
 * - Code ngan gon hon, de doc hon.
 */
void UART_Send(char *msg)
{
    /*
     * HAL_UART_Transmit:
     * - &huart1: su dung UART1
     * - (uint8_t*)msg: ep chuoi ky tu ve kieu du lieu UART can gui
     * - strlen(msg): tinh do dai chuoi can gui
     * - 1000: timeout 1000 ms
     */
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), APP_UART_TX_TIMEOUT);
}


