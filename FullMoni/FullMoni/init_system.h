// --------------------------------------------------------------------
// Copylight (C) 2021, Tomoya Sato( https://blog.goo.ne.jp/nacci_tomoya )
//
// This file is part of FullMoni firmwere.
//
// FullMoni is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option ) any later version.
//
// FullMoni is distributed in the hope that it will be useful,
// but WITHIOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FullMoni. if not, see <http:/www.gnu.org/licenses/>.
//
// filename		:	init_system.h
// brief		:	FullMoni rev.C システム初期化管理
// author		:	Tomoya Sato
// update		:	2021/02/02
// version		:	1.05
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _INIT_SYSTEM_H_
#define _INIT_SYSTEM_H_

// --------------------------------------------------------------------
// extern宣言
// --------------------------------------------------------------------
extern volatile unsigned int	g_TouchX, g_TouchY;
extern volatile unsigned int	g_drawbuff_flg;
extern volatile unsigned int	g_fps;
extern volatile unsigned int	g_fps_cnt;
extern volatile unsigned int	g_fps_max;
extern volatile unsigned int	g_beep_oneshotmin_flg;
extern volatile unsigned int	g_beep_oneshotmax_flg;
extern volatile unsigned int	g_beep_twoshotmin_flg;
extern volatile unsigned char	g_CANMsgBuf[4][14];
extern volatile unsigned int	g_refresh_done;
extern volatile unsigned int	g_led_o_max_flg;
extern volatile unsigned int	g_led_o_min_flg;
extern volatile unsigned int	g_led_r_max_flg;
extern volatile unsigned int	g_led_r_min_flg;
extern volatile unsigned int	g_master_warning_flg1;
extern volatile unsigned int	g_master_warning_flg2;
extern volatile unsigned int	g_master_warning_flg3;
extern volatile unsigned int	g_master_warning_flg4;
extern volatile unsigned int	g_master_warning_flg5;
extern volatile unsigned int	g_master_warning_flg6;
extern volatile unsigned int	g_shift_timing_flg;
extern volatile unsigned int	backlight_dimmer_flg;
extern volatile unsigned int	Onetime_Peakclear_cnt;
extern volatile unsigned int	sci_rcv_pointer;
extern volatile unsigned int	sci_rcv_command;
extern volatile unsigned int	g_can_rcv_timer;

// --------------------------------------------------------------------
// define関数
// --------------------------------------------------------------------
#define COLOR_WHITE		0xFFFF
#define COLOR_BLACK		0x0000
#define COLOR_RED		0xF800
#define COLOR_GREEN		0x07E0
#define COLOR_BLUE		0x001F

#define Beep_OneShotMin() g_beep_oneshotmin_flg = 1
#define Beep_OneShotMax() g_beep_oneshotmax_flg = 1
#define Beep_TwoShotMin() g_beep_twoshotmin_flg = 1

#define Led_O_Max_ON()  g_led_o_max_flg = 1
#define Led_O_Max_OFF() g_led_o_max_flg = 0
#define Led_R_Max_ON()  g_led_r_max_flg = 1
#define Led_R_Max_OFF() g_led_r_max_flg = 0

#define Led_O_Min_ON()  g_led_o_min_flg = 1
#define Led_O_Min_OFF() g_led_o_min_flg = 0
#define Led_R_Min_ON()  g_led_r_min_flg = 1
#define Led_R_Min_OFF() g_led_r_min_flg = 0

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_CPG(void);
void Init_INTC(void);
void Init_MSTP(void);
void Init_GPIO(void);
void Init_BSC(void);
void Init_EXDMAC(void);
void Init_DMAC(void);
void Init_TPU(void);
unsigned char UART_Tx_Possible(void);
unsigned char UART_Tx(unsigned char byte);
void UART_Tx_Char(unsigned char byte);
void Int_Handler_UART_Tx(void);
void Int_Handler_UART_Rx(void);
void Int_Handler_UART_Tx_END(void);
void Int_Handler_UART_Rx_ERR(void);
void Int_CAN2515(void);
void Int_50msFunc(void);
void Int_1msFunc(void);

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _INIT_SYSTEM_H_ */
