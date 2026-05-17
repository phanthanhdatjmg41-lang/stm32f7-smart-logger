#ifndef APP_SYSTEM_H
#define APP_SYSTEM_H

/*
 * File: app_system.h
 * Chuc nang:
 * - Khai bao kieu du lieu trang thai he thong
 * - Khai bao cac ham dieu khien trang thai he thong
 *
 * Ly do tao file nay:
 * - Tach phan quan ly trang thai ra khoi UART
 * - Giup project gon hon, de bao tri hon
 */

#include "main.h"

/*
 * SystemState_t:
 * Kieu enum dung de bieu dien trang thai cua he thong.
 */
typedef enum
{
    SYSTEM_IDLE = 0,     // He thong dang cho
    SYSTEM_RUNNING,      // He thong dang chay
    SYSTEM_ERROR         // He thong gap loi
} SystemState_t;

/*
 * System_Init:
 * Khoi tao trang thai ban dau cho he thong.
 */
void System_Init(void);

/*
 * System_SetState:
 * Thay doi trang thai he thong.
 */
void System_SetState(SystemState_t newState);

/*
 * System_GetState:
 * Doc trang thai hien tai cua he thong.
 */
SystemState_t System_GetState(void);

/*
 * System_GetStateString:
 * Tra ve chuoi mo ta trang thai he thong.
 * Vi du: "IDLE", "RUNNING", "ERROR".
 */
char* System_GetStateString(void);


/*
 * System_Reset:
 * Dua he thong ve trang thai ban dau.
 */
void System_Reset(void);


/*
 * System_GetUptimeSeconds:
 * Tra ve thoi gian he thong da chay, tinh bang giay.
 */
uint32_t System_GetUptimeSeconds(void);

/*
 * System_IncrementCommandCount:
 * Tang bien dem so lenh da duoc xu ly.
 */
void System_IncrementCommandCount(void);

/*
 * System_GetCommandCount:
 * Tra ve so lenh da duoc xu ly.
 */
uint32_t System_GetCommandCount(void);



#endif
