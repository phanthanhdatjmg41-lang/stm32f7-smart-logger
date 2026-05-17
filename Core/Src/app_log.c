#include "app_log.h"
#include "app_uart.h"

/*
 * Log_Info:
 * Chuc nang:
 * - Gui thong bao muc INFO ra UART.
 *
 * INFO:
 * - Dung cho cac thong bao binh thuong.
 */
void Log_Info(char *msg)
{
    UART_Send("\r\n[INFO] ");
    UART_Send(msg);
    UART_Send("\r\n");
}

/*
 * Log_Error:
 * Chuc nang:
 * - Gui thong bao muc ERROR ra UART.
 *
 * ERROR:
 * - Dung khi he thong gap loi hoac lenh sai.
 */
void Log_Error(char *msg)
{
    UART_Send("\r\n[ERROR] ");
    UART_Send(msg);
    UART_Send("\r\n");
}

/*
 * Log_Warning:
 * Chuc nang:
 * - Gui thong bao muc WARNING ra UART.
 *
 * WARNING:
 * - Dung cho canh bao, chua phai loi nghiem trong.
 */
void Log_Warning(char *msg)
{
    UART_Send("\r\n[WARNING] ");
    UART_Send(msg);
    UART_Send("\r\n");
}
