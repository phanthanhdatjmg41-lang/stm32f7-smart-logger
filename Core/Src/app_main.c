#include "app_main.h"
#include "app_uart.h"
#include "app_system.h"
#include "app_command.h"
#include "app_config.h"
#include <string.h>

/*
 * extern UART_HandleTypeDef huart1:
 * Bien huart1 duoc tao trong main.c boi CubeIDE.
 * File nay can dung huart1 de nhan UART.
 */
extern UART_HandleTypeDef huart1;

/*
 * Bien dung cho nhan UART.
 * Dung static de chi file app_main.c su dung duoc cac bien nay.
 */
static uint8_t rxByte;
static char rxBuffer[APP_UART_BUFFER_SIZE];
static uint8_t rxIndex = 0;

/*
 * App_Main_Init:
 * Chuc nang:
 * - Khoi tao module he thong
 * - Gui thong bao san sang ra Tera Term
 */
void App_Main_Init(void)
{
    System_Init();

    UART_Send("\r\nSTM32F7 Smart Logger Ready\r\n");
    UART_Send("Type help to see commands\r\n");
    UART_Send("> ");
}

/*
 * App_Main_Loop:
 * Chuc nang:
 * - Nhan tung ky tu UART
 * - Gom thanh lenh hoan chinh
 * - Khi nhan Enter thi goi Command_Process de xu ly lenh
 */
void App_Main_Loop(void)
{
    if (HAL_UART_Receive(&huart1, &rxByte, 1, APP_UART_RX_TIMEOUT) == HAL_OK)
    {
        /*
         * Neu nhan duoc Enter thi ket thuc lenh.
         */
        if (rxByte == '\r' || rxByte == '\n')
        {
            rxBuffer[rxIndex] = '\0';

            if (rxIndex > 0)
            {
                Command_Process(rxBuffer);
            }

            rxIndex = 0;
        }
        else
        {
            /*
             * Neu chua phai Enter thi luu ky tu vao buffer.
             */
            if (rxIndex < sizeof(rxBuffer) - 1)
            {
                rxBuffer[rxIndex++] = rxByte;

                /*
                 * Echo ky tu vua nhan.
                 */
                HAL_UART_Transmit(&huart1, &rxByte, 1, APP_UART_TX_TIMEOUT);
            }
        }
    }
}
