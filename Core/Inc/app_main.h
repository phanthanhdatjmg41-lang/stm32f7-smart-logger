#ifndef APP_MAIN_H
#define APP_MAIN_H

/*
 * File: app_main.h
 * Chuc nang:
 * - Khai bao ham khoi tao va ham lap chinh cua ung dung
 *
 * Ly do tao file nay:
 * - Giup main.c gon hon
 * - Giam code tu viet trong file main.c sinh tu CubeIDE
 */

#include "main.h"

/*
 * App_Main_Init:
 * Khoi tao cac module cua ung dung.
 */
void App_Main_Init(void);

/*
 * App_Main_Loop:
 * Ham lap chinh cua ung dung.
 * Ham nay se duoc goi lien tuc trong while(1).
 */
void App_Main_Loop(void);

#endif
