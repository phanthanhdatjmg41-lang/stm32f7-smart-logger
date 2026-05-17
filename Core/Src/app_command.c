#include "app_command.h"
#include "app_uart.h"
#include "app_system.h"
#include "app_led.h"
#include "app_log.h"
#include <string.h>
#include <stdio.h>

/*
 * Command_Process:
 * Chuc nang:
 * - Nhan chuoi lenh tu UART
 * - So sanh lenh
 * - Goi ham xu ly phu hop
 */
void Command_Process(char *cmd)
{
    /*
     * strcmp:
     * - Dung de so sanh chuoi
     * - Neu hai chuoi giong nhau thi tra ve 0
     */
    if (strcmp(cmd, "help") == 0)
    {
        UART_Send("\r\nAvailable commands:\r\n");
        UART_Send("help\r\n");
        UART_Send("status\r\n");
        UART_Send("start\r\n");
        UART_Send("stop\r\n");
        UART_Send("led on\r\n");
        UART_Send("led off\r\n");
        UART_Send("led toggle\r\n");
        UART_Send("led status\r\n");
        UART_Send("reset\r\n");
        UART_Send("uptime\r\n");
    }
    else if (strcmp(cmd, "status") == 0)
    {
        UART_Send("\r\nSystem status: ");
        UART_Send(System_GetStateString());
        UART_Send("\r\n");
    }
    else if (strcmp(cmd, "start") == 0)
    {
        System_SetState(SYSTEM_RUNNING);
        Log_Info("System started");
    }
    else if (strcmp(cmd, "stop") == 0)
    {
        System_SetState(SYSTEM_IDLE);
        Log_Info("System stopped");
    }
    else if (strcmp(cmd, "led on") == 0)
    {
        LED_On();
        Log_Info("LED ON");
    }
    else if (strcmp(cmd, "led off") == 0)
    {
        LED_Off();
        Log_Info("LED OFF");
    }
    else if (strcmp(cmd, "led toggle") == 0)
    {
        LED_Toggle();
        Log_Info("LED TOGGLE");
    }
    else if (strcmp(cmd, "led status") == 0)
    {
        if (LED_GetState() == GPIO_PIN_SET)
        {
            UART_Send("\r\nLED status: ON\r\n");
        }
        else
        {
            UART_Send("\r\nLED status: OFF\r\n");
        }
    }
    else if (strcmp(cmd, "reset") == 0)
    {
        System_Reset();
        LED_Off();
        Log_Warning("System reset");
    }
    else if (strcmp(cmd, "uptime") == 0)
    {
        char msg[50];

        /*
         * Tao chuoi thong bao uptime.
         * %lu dung de in so kieu unsigned long.
         */
        sprintf(msg, "\r\nSystem uptime: %lu s\r\n", System_GetUptimeSeconds());

        UART_Send(msg);
    }
    else
    {
        Log_Error("Unknown command. Type help");
    }

    /*
     * In lai dau > de nguoi dung biet co the nhap lenh moi.
     */
    UART_Send("\r\n> ");
}/*
 * app_command.c
 *
 *  Created on: May 17, 2026
 *      Author: phant
 */


