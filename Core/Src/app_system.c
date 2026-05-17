#include "app_system.h"


/*
 * commandCount:
 * Dem so lenh hop le da duoc xu ly.
 */
static uint32_t commandCount = 0;

/*
 * systemState:
 * Bien static chi duoc dung ben trong file app_system.c.
 *
 * Ly do dung static:
 * - Khong cho file khac sua truc tiep bien nay
 * - Muon thay doi trang thai thi phai goi ham System_SetState()
 * - Giup code an toan va de quan ly hon
 */
static SystemState_t systemState = SYSTEM_IDLE;

/*
 * System_Init:
 * Ham khoi tao he thong.
 *
 * Hien tai:
 * - Dat trang thai ban dau la SYSTEM_IDLE
 *
 * Sau nay co the mo rong:
 * - Khoi tao cam bien
 * - Khoi tao bo dem
 * - Khoi tao thong so do an
 */
void System_Init(void)
{
    /*
     * Dua he thong ve trang thai ban dau.
     */
    systemState = SYSTEM_IDLE;


    /*
     * Reset bien dem lenh ve 0 khi he thong khoi dong.
     */
    commandCount = 0;
}

/*
 * System_SetState:
 * Ham thay doi trang thai he thong.
 *
 * Tham so:
 * - newState: trang thai moi muon gan cho he thong
 */
void System_SetState(SystemState_t newState)
{
    systemState = newState;
}

/*
 * System_GetState:
 * Ham doc trang thai hien tai cua he thong.
 *
 * Gia tri tra ve:
 * - SYSTEM_IDLE
 * - SYSTEM_RUNNING
 * - SYSTEM_ERROR
 */
SystemState_t System_GetState(void)
{
    return systemState;
}

/*
 * System_GetStateString:
 * Ham chuyen trang thai tu enum sang chuoi.
 *
 * Ly do can ham nay:
 * - UART khong in duoc enum truc tiep
 * - Can chuyen trang thai thanh chuoi de gui ra Tera Term
 */
char* System_GetStateString(void)
{
    if (systemState == SYSTEM_IDLE)
    {
        return "IDLE";
    }
    else if (systemState == SYSTEM_RUNNING)
    {
        return "RUNNING";
    }
    else
    {
        return "ERROR";
    }
}



/*
 * System_Reset:
 * Chuc nang:
 * - Dua he thong ve trang thai ban dau
 *
 * Hien tai:
 * - Trang thai he thong quay ve SYSTEM_IDLE
 *
 * Ly do tao ham rieng:
 * - Khi can reset he thong, cac file khac chi can goi System_Reset()
 * - Sau nay neu reset them cam bien, bien dem, bo nho dem...
 *   thi chi can sua trong ham nay
 */
void System_Reset(void)
{
    systemState = SYSTEM_IDLE;
}


/*
 * System_GetUptimeSeconds:
 * Chuc nang:
 * - Lay thoi gian he thong da chay
 * - Don vi tra ve la giay
 *
 * HAL_GetTick:
 * - Tra ve thoi gian tinh bang mili giay
 * - Vi vay chia 1000 de doi sang giay
 */
uint32_t System_GetUptimeSeconds(void)
{
    return HAL_GetTick() / 1000;
}

/*
 * System_IncrementCommandCount:
 * Chuc nang:
 * - Tang bien dem moi khi co mot lenh duoc xu ly.
 *
 * Ly do:
 * - Giup he thong biet nguoi dung da gui bao nhieu lenh.
 * - Lam cho project dung tinh chat logger/giam sat hon.
 */
void System_IncrementCommandCount(void)
{
    commandCount++;
}

/*
 * System_GetCommandCount:
 * Chuc nang:
 * - Tra ve so lenh da duoc xu ly.
 */
uint32_t System_GetCommandCount(void)
{
    return commandCount;
}
