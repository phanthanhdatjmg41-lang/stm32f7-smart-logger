#ifndef APP_COMMAND_H
#define APP_COMMAND_H

/*
 * File: app_command.h
 * Chuc nang:
 * - Khai bao ham xu ly lenh nguoi dung
 *
 * Ly do tao file nay:
 * - Tach phan xu ly lenh ra khoi app_uart.c
 * - Giup app_uart.c chi tap trung vao viec gui/nhan UART
 */

#include "main.h"

/*
 * Command_Process:
 * Ham xu ly lenh nguoi dung nhap tu Tera Term.
 *
 * Vi du lenh:
 * - help
 * - status
 * - start
 * - stop
 * - led on
 * - led off
 * - led toggle
 * - led status
 * - reset
 * - uptime
 */
void Command_Process(char *cmd);

#endif
