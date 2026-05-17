#ifndef APP_LOG_H
#define APP_LOG_H

/*
 * File: app_log.h
 * Chuc nang:
 * - Khai bao cac ham ghi log cua he thong
 *
 * Ly do tao file nay:
 * - Gom cac thong bao log vao mot module rieng
 * - Giup code gon hon va de quan ly hon
 */

#include "main.h"

/*
 * Log_Info:
 * Gui thong bao muc INFO.
 */
void Log_Info(char *msg);

/*
 * Log_Warning:
 * Gui thong bao muc WARNING.
 */
void Log_Warning(char *msg);

/*
 * Log_Error:
 * Gui thong bao muc ERROR.
 */
void Log_Error(char *msg);

#endif
