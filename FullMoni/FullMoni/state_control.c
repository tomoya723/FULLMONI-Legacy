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
// filename		:	state_control.c
// brief		:	FullMoni rev.C ステート管理
// author		:	Tomoya Sato
// update		:	2021/02/21
// version		:	1.06
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "dataregister.h"
#include "iodefine.h"
#include "state_control.h"
#include "init_system.h"
#include "TFTLCD35.h"
#include "CAN2515.h"
#include "iic.h"

// --------------------------------------------------------------------
// define宣言
// --------------------------------------------------------------------
#define ChartBufNum 201

// --------------------------------------------------------------------
// グローバル変数宣言
// --------------------------------------------------------------------
//volatile unsigned int	g_fps;
//volatile unsigned int	g_fps_cnt;
//volatile unsigned int	g_fps_max;
volatile unsigned int	g_beep_oneshotmin_flg;
volatile unsigned int	g_beep_oneshotmax_flg;
volatile unsigned int	g_beep_twoshotmin_flg;
volatile unsigned int	g_master_warning_flg1;
volatile unsigned int	g_master_warning_flg2;
volatile unsigned int	g_master_warning_flg3;
volatile unsigned int	g_master_warning_flg4;
volatile unsigned int	g_master_warning_flg5;
volatile unsigned int	g_master_warning_flg6;
volatile unsigned int	g_shift_timing_flg;
volatile unsigned int	backlight_dimmer_flg;
volatile unsigned int	Onetime_Peakclear_cnt;
static unsigned int		Onetime_Peakclear_done;
static unsigned long	chart_buf1[ChartBufNum];
static unsigned long	chart_buf2[ChartBufNum];
static unsigned long	chart_buf3[ChartBufNum];
static unsigned long	chart_buf4[ChartBufNum];
static unsigned int		chart_onoff;
static int				rev_peak, num1_peak, num2_peak, num3_peak, num4_peak, num5_peak, num6_peak;
static unsigned int		Acc;
static unsigned int		num_page;
static unsigned int		num_control;
static unsigned int		preset_no;
static unsigned int		ChartX = 314, ChartY = 0;

// --------------------------------------------------------------------
// 状態別処理実行及び状態遷移処理
// --------------------------------------------------------------------
void state_control(void)
{
	switch(g_state)
	{
		default:
		case S001:	funcS001();
								switch(E001())
								{
									case   1:	A002();	break;
									case 999:	A990();	break;
								}
								break;
		case S002:	funcS002();
								switch(E002())
								{
									case   1:	A100();	break;
								}
								break;
		case S010:	funcS010();
								switch(E010())
								{
									case  1:	A011();	break;
									case  2:	A012();	break;
									case  3:	A102();	break;
									case  4:	A014();	break;
									case  5:	A013();	break;
//									case  6:	A016();	break;
//									case  7:	A017();	break;
//									case  8:	A018();	break;
//									case  9:	A019();	break;
//									case 10:	A020();	break;
//									case 11:	A021();	break;
//									case 12:	A022();	break;
//									case 13:	A023();	break;
//									case 14:	A022();	break;
//									case 15:	A023();	break;
								}
								break;
		case S020:	funcS020();
								switch(E020())
								{
									case  1:	A011();	break;
									case  2:	A123();	break;
									case  3:	A013();	break;
									case  4:	A024();	break;
//									case  5:	A015();	break;
//									case  6:	A016();	break;
//									case  7:	A017();	break;
//									case  8:	A018();	break;
//									case  9:	A019();	break;
//									case 10:	A020();	break;
//									case 11:	A021();	break;
//									case 12:	A022();	break;
//									case 13:	A023();	break;
								}
								break;
		case S110:	funcS110();
								switch(E110())
								{
									case  1:	A101();	break;
									case  2:	A102();	break;
									case  3:	A103();	break;
									case  4:	A104();	break;
									case  5:	A123();	break;
								}
								break;
		case S120:	funcS120();
								switch(E100())
								{
									case  1:	A121();	break;
									case  2:	A122();	break;
									case  3:	A133();	break;
								}
								break;
		case S130:	funcS130();
								switch(E130())
								{
									case  1:	A130();	break;
									case  2:	A131();	break;
									case  3:	A132();	break;
									case  4:	A123();	break;
									case  5:	A104();	break;
								}
								break;
		case S210:	funcS210();
								switch(E200())
								{
									case  1:	A201();	break;
									case  2:	A202();	break;
								}
								break;
		case S999:	funcS999();
								switch(E990())
								{
									case  1:	A991();	break;
								}
								break;
	}
}

// --------------------------------------------------------------------
// タッチ・長押しエリア判定関数
// --------------------------------------------------------------------
unsigned int area_judge(unsigned int X, unsigned int X1, unsigned int X2, unsigned int Y, unsigned int Y1, unsigned int Y2)
{
	if((X >= X1) && (X <= X2) && (Y >= Y1) && (Y <= Y2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
} 

// --------------------------------------------------------------------
// イベント処理：ステート遷移条件を定義
// --------------------------------------------------------------------
unsigned int E001(void)
{
	static unsigned int init_cnt;
	
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		init_cnt ++;
	}
	
	if(init_cnt >= 5)
	{
		return 999;
	}
	
	if(g_int50mscnt >= 0)
	{
		return 1;	// 初期画面描画待機終了判断
	}
	else
	{
		return 0;
	}
}

unsigned int E002(void)
{
	if(g_int50mscnt >= 0)
	{
		switch(g_e2p_data.E2P_1.model)
		{
			case 0xFF:		return 999; break;
			default:		return   1; break;
		}
	}
	else
	{
		return 0;
	}
}

unsigned int E010(void)
{
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 保存アイコン押下判定
		// --------------------------------------------------------------------
		if		(area_judge(g_PressX, 130, 193, g_PressY, 215, 238))									{						return 1;	}
		// --------------------------------------------------------------------
		// 左カーソルアイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX,  46, 139, g_PressY, 215, 238))									{						return 2;	}
		// --------------------------------------------------------------------
		// 右カーソルアイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 214, 277, g_PressY, 215, 238))
		{
			if(g_e2p_data.E2P_1.model == CAN_std)	// CAN_stdモードの時のみCAN ID設定画面に遷移
			{
				return 3;
			}
			else
			{
				return 5;
			}
		}
		// --------------------------------------------------------------------
		// モデル変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 2), ( 24 * 2 + 24 - 1)))	{	num_control = 1; 	return 4;	}
		// --------------------------------------------------------------------
		// モデル変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 2), ( 24 * 2 + 24 - 1)))	{	num_control = 2;	return 4;	}
		// --------------------------------------------------------------------
		// ブザー変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1)))	{	num_control = 3; 	return 4;	}
		// --------------------------------------------------------------------
		// ブザー変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1)))	{	num_control = 4; 	return 4;	}
		// --------------------------------------------------------------------
		// マスターワーニング変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1)))	{	num_control = 5;	return 4;	}
		// --------------------------------------------------------------------
		// マスターワーニング変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1)))	{	num_control = 6;	return 4;	}
		// --------------------------------------------------------------------
		// FClogger使用変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1)))	{	num_control = 7; 	return 4;	}
		// --------------------------------------------------------------------
		// FClogger使用変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1)))	{	num_control = 8;	return 4;	}
		// --------------------------------------------------------------------
		// プリセット変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1)))	{	num_control = 9;	return 4;	}
		// --------------------------------------------------------------------
		// プリセット変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1)))	{	num_control = 10;	return 4;	}
	}
	return 0;
}

unsigned int E020(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	static unsigned int drag_cnt;
	
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg | touch_drag_flg)			// タッチパネル押下判定あり
	{
		// --------------------------------------------------------------------
		// 保存アイコン押下判定
		// --------------------------------------------------------------------
		if		((touch_done_flg) && (area_judge(g_PressX, 130, 193, g_PressY, 215, 238)))	{	touch_done_flg = 0;	return 1;	}
		// --------------------------------------------------------------------
		// 左カーソルアイコン押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  46, 139, g_PressY, 215, 238)))	{	touch_done_flg = 0;	return 2;	}
		// --------------------------------------------------------------------
		// 右カーソルアイコン押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX, 214, 277, g_PressY, 215, 238)))	{	touch_done_flg = 0;	return 3;	}
		// --------------------------------------------------------------------
		// CAN ID1 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 2), ( 24 * 2 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 1;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID2 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 2;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID3 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 3;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID4 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 4;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID5 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 5;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID6 有効無効押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX,  60, (60 + 32 - 1 ), g_PressY, ( 24 * 7), ( 24 * 7 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 6;	return 4;	}
		// --------------------------------------------------------------------
		// CAN Baudrate 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 1), ( 24 * 1 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 7;	return 4;	}
		// --------------------------------------------------------------------
		// CAN Baudrate 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	((touch_done_flg) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 1), ( 24 * 1 + 24 - 1))))	{	touch_done_flg = 0;	num_control = 8;	return 4;	}
		// --------------------------------------------------------------------
		// CAN ID1 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 2), ( 24 * 2 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 9;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 9;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID1 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 2), ( 24 * 2 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 10;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 10;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID2 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 11;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 11;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID2 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 12;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 12;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID3 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 13;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 13;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID3 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 14;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 14;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID4 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 15;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 15;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID4 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 16;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 16;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID5 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 17;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 17;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID5 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 18;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 18;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID6 上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1 ), g_PressY, ( 24 * 7), ( 24 * 7 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 19;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 19;
					return 4;
				}
			}
		}
		// --------------------------------------------------------------------
		// CAN ID6 下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1 ), g_PressY, ( 24 * 7), ( 24 * 7 + 24 - 1))) && (g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 20;
				return 4;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 20;
					return 4;
				}
			}
		}
		else
		{
			touch_done_flg = 0;
			touch_drag_flg = 0;
			drag_cnt = 0;
		}
	}
	else
	{
		drag_cnt = 0;
		Acc = 1;
	}
	return 0;
}

unsigned int E100(void)
{
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 中央コマンドアイコン押下判定
		// --------------------------------------------------------------------
		if		(area_judge(g_PressX, 130, 193, g_PressY, 215, 238))	{	return 1;	}
		// --------------------------------------------------------------------
		// 左コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX,  46, 139, g_PressY, 215, 238))	{	return 2;	}
		// --------------------------------------------------------------------
		// 右コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX, 214, 277, g_PressY, 215, 238))	{	return 3;	}
	}
	return 0;
}

unsigned int E110(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	static unsigned int drag_cnt;
	
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 中央コマンドアイコン押下判定
		// --------------------------------------------------------------------
		if		(area_judge(g_PressX, 130, 193, g_PressY, 215, 238))	{	return 1;	}
		// --------------------------------------------------------------------
		// 左コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX,  46, 139, g_PressY, 215, 238))
		{
			if(g_e2p_data.E2P_1.model == CAN_std)	// CAN_stdモードの時のみCAN ID設定画面に遷移
			{
				return 2;
			}
			else
			{
				return 5;
			}
		}
		// --------------------------------------------------------------------
		// 右コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX, 214, 277, g_PressY, 215, 238))	{	return 3;	}
	}
	if(touch_drag_flg)			// タッチパネル長押し判定あり
	{
		touch_drag_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 数値表示1長押し判定
		// --------------------------------------------------------------------
		if		(area_judge(g_DragX,   1, 140, g_DragY, 144, 167))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 1;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 数値表示2長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX,   1, 140, g_DragY, 168, 191))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 2;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 数値表示3長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX,   1, 140, g_DragY, 192, 215))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 3;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 数値表示4長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 161, 300, g_DragY, 144, 167))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 4;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 数値表示5長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 161, 300, g_DragY, 168, 191))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 5;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 数値表示6長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 161, 300, g_DragY, 192, 215))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 6;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 回転数表示長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 194, 309, g_DragY,  72,  95))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 7;
				return 4;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// 空燃比表示長押し判定
		// --------------------------------------------------------------------
		else if	((g_DragX >=  92) && (g_DragX <= 219) && (g_DragY >=  96) && (g_DragY <= 143))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 8;
				return 4;
			}
			else
			{
				//
			}
		}
		else
		{
			drag_cnt = 0;
		}
	}
	else
	{
		drag_cnt = 0;
	}
	return 0;
}

unsigned int E130(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	static unsigned int drag_cnt;
	
	if((g_master_warning_flg1 == 1)
	|| (g_master_warning_flg2 == 1)
	|| (g_master_warning_flg3 == 1)
	|| (g_master_warning_flg4 == 1)
	|| (g_master_warning_flg5 == 1)
	|| (g_master_warning_flg6 == 1))
	{
		return 1;
	}
	
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 中央コマンドアイコン押下判定
		// --------------------------------------------------------------------
		if		(area_judge(g_PressX, 130, 193, g_PressY, 215, 238))	{	return 2;	}
		// --------------------------------------------------------------------
		// 左コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX,  46, 139, g_PressY, 215, 238))	{	return 3;	}
		// --------------------------------------------------------------------
		// 右コマンドアイコン押下判定
		// --------------------------------------------------------------------
		else if (area_judge(g_PressX, 214, 277, g_PressY, 215, 238))	{	return 4;	}
	}
	if(touch_drag_flg)			// タッチパネル長押し判定あり
	{
		touch_drag_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// チャートドラッグ判定
		// --------------------------------------------------------------------
		if		(area_judge(g_DragX, 114, 314, g_DragY,   5, 141))	{	ChartX = g_DragX;	ChartY = g_DragY;	}
		// --------------------------------------------------------------------
		// チャート数値表示1長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX,   1, 100, g_DragY, 144, 167))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 9;
				return 5;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// チャート数値表示2長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX,   1, 100, g_DragY, 192, 215))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 10;
				return 5;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// ゲージ1長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 113, 316, g_DragY, 146, 176))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 11;
				return 5;
			}
			else
			{
				//
			}
		}
		// --------------------------------------------------------------------
		// ゲージ2長押し判定
		// --------------------------------------------------------------------
		else if (area_judge(g_DragX, 113, 316, g_DragY, 179, 209))
		{
			drag_cnt ++;
			if(drag_cnt > 20)
			{
				Beep_TwoShotMin();
				num_page = 12;
				return 5;
			}
			else
			{
				//
			}
		}
		else
		{
			drag_cnt = 0;
		}
	}
	else
	{
		drag_cnt = 0;
	}
	return 0;
}

unsigned int E200(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	static unsigned int drag_cnt;
	
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg | touch_drag_flg)			// タッチパネル押下判定あり
	{
		// --------------------------------------------------------------------
		// 保存アイコン押下判定
		// --------------------------------------------------------------------
		if		((touch_done_flg) && (area_judge(g_PressX, 130, 193, g_PressY, 215, 238)))	{	touch_done_flg = 0;	return 1;	}
		// --------------------------------------------------------------------
		// データ変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 1), ( 24 * 1 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 1;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 1;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// データ変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 1), ( 24 * 1 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 2;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 2;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// ゲイン変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 3;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 3;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// ゲイン変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 3), ( 24 * 3 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 4;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 4;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// バイアス変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 5;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 5;
					return 2;
				}
			}	
		}
		// --------------------------------------------------------------------
		// バイアス変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 4), ( 24 * 4 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 6;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 6;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// 小数点位置変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 7;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 7;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// 小数点位置変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 5), ( 24 * 5 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 8;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 8;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// タグ変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 9;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 9;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// タグ変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 6), ( 24 * 6 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 10;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 10;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// 単位変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 7), ( 24 * 7 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 11;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 11;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// 単位変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 7), ( 24 * 7 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 12;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 12;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// リミット変更上アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 230, (230 + 32 - 1), g_PressY, ( 24 * 8), ( 24 * 8 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 13;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 13;
					return 2;
				}
			}
		}
		// --------------------------------------------------------------------
		// リミット変更下アイコン押下判定
		// --------------------------------------------------------------------
		else if	(((touch_done_flg) || (touch_drag_flg)) && (area_judge(g_PressX, 270, (270 + 32 - 1), g_PressY, ( 24 * 8), ( 24 * 8 + 24 - 1))))
		{
			if(touch_done_flg)
			{
				touch_done_flg = 0;		// フラグクリア
				num_control = 14;
				return 2;
			}
			else if(touch_drag_flg)
			{
				touch_drag_flg = 0;		// フラグクリア
				drag_cnt ++;
				if(drag_cnt > 5)
				{
					drag_cnt = 4;
					num_control = 14;
					return 2;
				}
			}
		}
		else
		{
			touch_done_flg = 0;
			touch_drag_flg = 0;
			drag_cnt = 0;
		}
	}
	else
	{
		drag_cnt = 0;
		Acc = 1;
	}
	return 0;
}

unsigned int E990(void)
{
	// --------------------------------------------------------------------
	// タッチ操作処理
	// --------------------------------------------------------------------
	if(touch_done_flg)			// タッチパネル押下判定あり
	{
		touch_done_flg = 0;		// フラグクリア
		
		// --------------------------------------------------------------------
		// 保存アイコン押下判定
		// --------------------------------------------------------------------
		if		(area_judge(g_PressX, 130, 193, g_PressY, 215, 238))
		{
			return 1;
		}
	}
	return 0;
}

// --------------------------------------------------------------------
// アクション処理：ステート開始時1度のみ実行
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// 初期化→初期画面描画
// --------------------------------------------------------------------
void A001(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S001;
//	g_int50mscnt = -100;		// ピリオド50ms x 100 = 5.0s 待機
	g_int50mscnt =  -60;		// ピリオド50ms x  60 = 3.0s 待機
//	g_int50mscnt =  -20;		// ピリオド50ms x  20 = 1.0s 待機
//	g_int50mscnt =  -10;		// ピリオド50ms x  10 = 0.5s 待機
	
	// --------------------------------------------------------------------
	// LCDリフレッシュ変数初期化
	// --------------------------------------------------------------------
	g_drawbuff_flg = 1;
	g_refresh_done = 1;
	
	// --------------------------------------------------------------------
	// オープニング画面描画
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_WHITE);
	LCD_locate(  0,  0);	LCD_Gcopy(  0,   0, 320,240, (volatile unsigned int    *)TITLE);
	
	LCD_Refresh();
	
	// --------------------------------------------------------------------
	// タイマスタート
	// --------------------------------------------------------------------
	TPU.TSTR.BIT.CST0 = 1;		// タイマスタートレジスタ	Start TPU0 for TFT LCD Refresh Cycle
	TPU.TSTR.BIT.CST3 = 1;		// タイマスタートレジスタ	Start TPU3 for BEEP
	TPU.TSTR.BIT.CST4 = 1;		// タイマスタートレジスタ	Start TPU4 for TFT LCD Back Light PWM
	TPU.TSTRB.BIT.CST0 = 1;		// タイマスタートレジスタ	Start TPU0 for LED Dimmer Cycle
	
	while(g_oneshot_flg <= 1);	// 1画面描写完了まで待機
	
	// --------------------------------------------------------------------
	// バックライト点灯
	// --------------------------------------------------------------------
	LCD_FadeIN();
}

// --------------------------------------------------------------------
// 画面消去→起動音
// --------------------------------------------------------------------
void A002(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S002;
	g_int50mscnt =   -2;		// ピリオド50ms x   2 = 0.1s 待機
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// EEPROMデータ読み込み
	// --------------------------------------------------------------------
	mrandrd_start((const unsigned char *)&g_e2p_data, 0x00, sizeof(g_e2p_data));
	
	// --------------------------------------------------------------------
	// 起動音
	// --------------------------------------------------------------------
	Beep_TwoShotMin();
}

// --------------------------------------------------------------------
// 初期化
// --------------------------------------------------------------------
void A100(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int i;
	
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S110;
	
	// --------------------------------------------------------------------
	// 通信初期化
	// --------------------------------------------------------------------
	switch(g_e2p_data.E2P_1.model)
	{
		case CAN_std:	Init_CAN();			break;
		case MoTeC1:	Init_MoTeC1();		break;
		case MoTeC2:	Init_MoTeC2();		break;
		case Haltech1:	Init_Haltech1();	break;
		case Haltech2:	Init_Haltech2();	break;
		case Freedom2:	Init_Freedom2();	break;
//		case MSquirt1:	Init_MSquirt1();	break;
	}
	g_MoTeC1_data.ThrottlePosition			=  800;

	// --------------------------------------------------------------------
	// ピークホールド値初回限定更新クリアフラグリセット
	// --------------------------------------------------------------------
	Onetime_Peakclear_done = 0;
	Onetime_Peakclear_cnt = 10;
	
	// --------------------------------------------------------------------
	// チャートバッファクリア
	// --------------------------------------------------------------------
	for(i = 0; i < ChartBufNum; i++ )
	{
		chart_buf1[i] =    0;
		chart_buf2[i] =    0;
		chart_buf3[i] =    0;
		chart_buf4[i] =    0;
	}
}

// --------------------------------------------------------------------
// 設定保存処理
// --------------------------------------------------------------------
void A011(void)
{
	// --------------------------------------------------------------------
	// 保存アイコンタッチ描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// データプリセット保存
	// --------------------------------------------------------------------
	switch(preset_no)
	{
		case 1:	Preset_load_CAN();			break;
		case 2:	Preset_load_MoTeC1();		break;
//		case 3:	Preset_load_MoTeC2();		break;
		case 3:	Preset_load_Haltech1();		break;
		case 4:	Preset_load_Haltech2();		break;
		case 5:	Preset_load_Freedom1();		break;
		case 6:	Preset_load_Freedom2();		break;
//		case 7:	Preset_load_MegaSquirt1();	break;
		case 0:
		default:							break;
	}
	
	// --------------------------------------------------------------------
	// EEPROMデータ保存
	// --------------------------------------------------------------------
	Save_EEPROM_ALL();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A012(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int i;
	
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S130;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	switch(g_e2p_data.E2P_1.model)
	{
		case CAN_std:	Init_CAN();			break;
		case MoTeC1:	Init_MoTeC1();		break;
		case MoTeC2:	Init_MoTeC2();		break;
		case Haltech1:	Init_Haltech1();	break;
		case Haltech2:	Init_Haltech2();	break;
		case Freedom2:	Init_Freedom2();	break;
//		case MSquirt1:	Init_MSquirt1();	break;
	}
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// チャートバッファクリア
	// --------------------------------------------------------------------
	if(chart_onoff == 0)
	{
		for(i = 0; i < ChartBufNum; i++ )
		{
			chart_buf1[i] =    0;
			chart_buf2[i] =    0;
			chart_buf3[i] =    0;
			chart_buf4[i] =    0;
		}
	}
	else
	{
		//
	}
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A013(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S110;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	switch(g_e2p_data.E2P_1.model)
	{
		case CAN_std:	Init_CAN();			break;
		case MoTeC1:	Init_MoTeC1();		break;
		case MoTeC2:	Init_MoTeC2();		break;
		case Haltech1:	Init_Haltech1();	break;
		case Haltech2:	Init_Haltech2();	break;
		case Freedom2:	Init_Freedom2();	break;
//		case MSquirt1:	Init_MSquirt1();	break;
	}
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A014(void)
{
	if		(num_control == 1)
	{
		g_e2p_data.E2P_1.model --;
		g_e2p_data.E2P_1.model = ( g_e2p_data.E2P_1.model >= 255 ) ? 0 : g_e2p_data.E2P_1.model;
		
		LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 2)
	{
		g_e2p_data.E2P_1.model ++;
		g_e2p_data.E2P_1.model = (g_e2p_data.E2P_1.model > 6) ? 6 : g_e2p_data.E2P_1.model;
		
		LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 3)
	{
		if(g_e2p_data.E2P_1.control.BIT.beep_on)
		{
			g_e2p_data.E2P_1.control.BIT.beep_on = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.beep_on = 1;
		}
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 4)
	{
		if(g_e2p_data.E2P_1.control.BIT.beep_on)
		{
			g_e2p_data.E2P_1.control.BIT.beep_on = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.beep_on = 1;
		}
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 5)
	{
		if(g_e2p_data.E2P_1.control.BIT.ms_on)
		{
			g_e2p_data.E2P_1.control.BIT.ms_on = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.ms_on = 1;
		}
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 6)
	{
		if(g_e2p_data.E2P_1.control.BIT.ms_on)
		{
			g_e2p_data.E2P_1.control.BIT.ms_on = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.ms_on = 1;
		}
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 7)
	{
		if(g_e2p_data.E2P_1.control.BIT.FC_mode)
		{
			g_e2p_data.E2P_1.control.BIT.FC_mode = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.FC_mode = 1;
		}
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 8)
	{
		if(g_e2p_data.E2P_1.control.BIT.FC_mode)
		{
			g_e2p_data.E2P_1.control.BIT.FC_mode = 0;
		}
		else
		{
			g_e2p_data.E2P_1.control.BIT.FC_mode = 1;
		}
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 9)
	{
		preset_no --;
		preset_no = ( preset_no >= 255 ) ? 0 : preset_no;
		
		LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 10)
	{
		preset_no ++;
		preset_no = (preset_no > 6) ? 6 : preset_no;
		
		LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else
	{
		//
	}
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A024(void)
{


	if		(num_control == 1)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1 = 1;
		}

	}
	else if	(num_control == 2)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2 = 1;
		}

	}
	else if	(num_control == 3)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3 = 1;
		}

	}
	else if	(num_control == 4)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4 = 1;
		}

	}
	else if	(num_control == 5)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5 = 1;
		}

	}
	else if	(num_control == 6)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6 == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6 = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6 = 1;
		}

	}
	else if	(num_control == 7)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.BAUD == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.BAUD = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.BAUD = 1;
		}

	}
	else if	(num_control == 8)
	{
		if		(g_e2p_data.E2P_1.CANcontrol.BIT.BAUD == 1)
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.BAUD = 0;
		}
		else
		{
			g_e2p_data.E2P_1.CANcontrol.BIT.BAUD = 1;
		}

	}
	else if	(num_control == 9)
	{
		g_e2p_data.E2P_1.CAN_ID1 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID1 = (g_e2p_data.E2P_1.CAN_ID1 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID1;
		
		LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 10)
	{
		g_e2p_data.E2P_1.CAN_ID1 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID1 = (g_e2p_data.E2P_1.CAN_ID1 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID1;
		
		LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 11)
	{
		g_e2p_data.E2P_1.CAN_ID2 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID2 = (g_e2p_data.E2P_1.CAN_ID2 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID2;
		
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 12)
	{
		g_e2p_data.E2P_1.CAN_ID2 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID2 = (g_e2p_data.E2P_1.CAN_ID2 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID2;
		
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 13)
	{
		g_e2p_data.E2P_1.CAN_ID3 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID3 = (g_e2p_data.E2P_1.CAN_ID3 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID3;
		
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 14)
	{
		g_e2p_data.E2P_1.CAN_ID3 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID3 = (g_e2p_data.E2P_1.CAN_ID3 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID3;
		
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 15)
	{
		g_e2p_data.E2P_1.CAN_ID4 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID4 = (g_e2p_data.E2P_1.CAN_ID4 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID4;
		
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 16)
	{
		g_e2p_data.E2P_1.CAN_ID4 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID4 = (g_e2p_data.E2P_1.CAN_ID4 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID4;
		
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 17)
	{
		g_e2p_data.E2P_1.CAN_ID5 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID5 = (g_e2p_data.E2P_1.CAN_ID5 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID5;
		
		LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 18)
	{
		g_e2p_data.E2P_1.CAN_ID5 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID5 = (g_e2p_data.E2P_1.CAN_ID5 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID5;
		
		LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 19)
	{
		g_e2p_data.E2P_1.CAN_ID6 += Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID6 = (g_e2p_data.E2P_1.CAN_ID6 >   2047 ) ? 2047 : g_e2p_data.E2P_1.CAN_ID6;
		
		LCD_locate(230,24 * 7);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(230,24 * 7);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 20)
	{
		g_e2p_data.E2P_1.CAN_ID6 -= Acc; Acc ++;
		g_e2p_data.E2P_1.CAN_ID6 = (g_e2p_data.E2P_1.CAN_ID6 <=    -1 ) ?    0 : g_e2p_data.E2P_1.CAN_ID6;
		
		LCD_locate(270,24 * 7);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 7);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else
	{
		//
	}
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
	touch_drag_flg = 0;
}

/*void A015(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A016(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A017(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A018(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A019(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A020(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A021(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A022(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}
void A023(void)
{
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
}*/

// --------------------------------------------------------------------
// バックライトディマートグル処理
// --------------------------------------------------------------------
void A101(void)
{
	if(backlight_dimmer_flg)
	{
		TPU4.TGRB = 0x0010;
		backlight_dimmer_flg = 0;
	}
	else
	{
		TPU4.TGRB = 0x2000;
		backlight_dimmer_flg = 1;
	}
	// --------------------------------------------------------------------
	// バックライトディマーアイコン描画
	// --------------------------------------------------------------------
	if(backlight_dimmer_flg)
	{
		LCD_locate(130,215);	LCD_Gcopy(256,  24, 64, 24, (volatile unsigned int    *)FONTR);
	}
	else
	{
		LCD_locate(130,215);	LCD_Gcopy(256,   0, 64, 24, (volatile unsigned int    *)FONTR);
	}
	LCD_RefreshFast();
	if(backlight_dimmer_flg)
	{
		LCD_locate(130,215);	LCD_Gcopy(256,  24, 64, 24, (volatile unsigned int    *)FONTR);
	}
	else
	{
		LCD_locate(130,215);	LCD_Gcopy(256,   0, 64, 24, (volatile unsigned int    *)FONTR);
	}
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// ピークホールドクリア処理
// --------------------------------------------------------------------
void A121(void)
{
	// --------------------------------------------------------------------
	// ピークホールドクリアアイコンタッチ描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256,  96, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	LCD_locate(130,215);	LCD_Gcopy(256,  96, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	
	rev_peak  = 0;
	num1_peak = 0;
	num2_peak = 0;
	num3_peak = 0;
	num4_peak = 0;
	num5_peak = 0;
	num6_peak = 0;
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A130(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S110;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// チャートクリア処理
// --------------------------------------------------------------------
void A131(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int i;
	
	if(chart_onoff == 0)
	{
		chart_onoff = 1;
		
		// --------------------------------------------------------------------
		// チャート停止アイコンタッチ描画
		// --------------------------------------------------------------------
		LCD_locate(130,215);	LCD_Gcopy(256, 168, 64, 24, (volatile unsigned int    *)FONTR);	// ||
		LCD_Refresh();
		LCD_locate(130,215);	LCD_Gcopy(256, 168, 64, 24, (volatile unsigned int    *)FONTR);	// ||
		LCD_RefreshFast();
	}
	else
	{
		chart_onoff = 0;
		
		// --------------------------------------------------------------------
		// チャート再生アイコンタッチ描画
		// --------------------------------------------------------------------
		LCD_locate(130,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONTR);	// 右
		LCD_Refresh();
		LCD_locate(130,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONTR);	// 右
		LCD_RefreshFast();
		
		// --------------------------------------------------------------------
		// チャートバッファクリア
		// --------------------------------------------------------------------
		for(i = 0; i < ChartBufNum; i++ )
		{
			chart_buf1[i] =    0;
			chart_buf2[i] =    0;
			chart_buf3[i] =    0;
			chart_buf4[i] =    0;
		}
	}
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A102(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S020;
	
	// --------------------------------------------------------------------
	// プリセット変更初期化
	// --------------------------------------------------------------------
	preset_no = 0;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A103(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S120;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A104(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S210;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A133(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int i;
	
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S130;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// チャートバッファクリア
	// --------------------------------------------------------------------
	if(chart_onoff == 0)
	{
		for(i = 0; i < ChartBufNum; i++ )
		{
			chart_buf1[i] =    0;
			chart_buf2[i] =    0;
			chart_buf3[i] =    0;
			chart_buf4[i] =    0;
		}
	}
	else
	{
		//
	}
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A122(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S110;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A132(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S120;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void A123(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S010;
	
	// --------------------------------------------------------------------
	// プリセット変更初期化
	// --------------------------------------------------------------------
	preset_no = 0;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// 数値設定保存処理
// --------------------------------------------------------------------
void A201(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int i;
	
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	if((num_page == 9) || (num_page == 10) || (num_page == 11) || (num_page == 12))
	{
		g_state = S130;
	}
	else
	{
		g_state = S110;
	}
	
	// --------------------------------------------------------------------
	// チャート初期化
	// --------------------------------------------------------------------
	chart_onoff = 0;
	for(i = 0; i < ChartBufNum; i++ )
	{
		chart_buf1[i] =    0;
		chart_buf2[i] =    0;
		chart_buf3[i] =    0;
		chart_buf4[i] =    0;
	}
	
	// --------------------------------------------------------------------
	// 保存アイコンタッチ描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// EEPROMデータ保存
	// --------------------------------------------------------------------
	Save_EEPROM_ALL();
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
	touch_drag_flg = 0;
}

// --------------------------------------------------------------------
// 数値描画設定操作
// --------------------------------------------------------------------
void A202(void)
{
	if		(num_control == 1)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_data_select -= Acc; g_e2p_data.E2P_4.num1_data_select = ( g_e2p_data.E2P_4.num1_data_select >= 255 ) ? 0 : g_e2p_data.E2P_4.num1_data_select; break;
			case  2:	g_e2p_data.E2P_4.num2_data_select -= Acc; g_e2p_data.E2P_4.num2_data_select = ( g_e2p_data.E2P_4.num2_data_select >= 255 ) ? 0 : g_e2p_data.E2P_4.num2_data_select; break;
			case  3:	g_e2p_data.E2P_5.num3_data_select -= Acc; g_e2p_data.E2P_5.num3_data_select = ( g_e2p_data.E2P_5.num3_data_select >= 255 ) ? 0 : g_e2p_data.E2P_5.num3_data_select; break;
			case  4:	g_e2p_data.E2P_5.num4_data_select -= Acc; g_e2p_data.E2P_5.num4_data_select = ( g_e2p_data.E2P_5.num4_data_select >= 255 ) ? 0 : g_e2p_data.E2P_5.num4_data_select; break;
			case  5:	g_e2p_data.E2P_6.num5_data_select -= Acc; g_e2p_data.E2P_6.num5_data_select = ( g_e2p_data.E2P_6.num5_data_select >= 255 ) ? 0 : g_e2p_data.E2P_6.num5_data_select; break;
			case  6:	g_e2p_data.E2P_6.num6_data_select -= Acc; g_e2p_data.E2P_6.num6_data_select = ( g_e2p_data.E2P_6.num6_data_select >= 255 ) ? 0 : g_e2p_data.E2P_6.num6_data_select; break;
			case  7:	g_e2p_data.E2P_3.rev_data_select  -= Acc; g_e2p_data.E2P_3.rev_data_select  = ( g_e2p_data.E2P_3.rev_data_select  >= 255 ) ? 0 : g_e2p_data.E2P_3.rev_data_select;  break;
			case  8:	g_e2p_data.E2P_3.afr_data_select  -= Acc; g_e2p_data.E2P_3.afr_data_select  = ( g_e2p_data.E2P_3.afr_data_select  >= 255 ) ? 0 : g_e2p_data.E2P_3.afr_data_select;  break;
			case  9:	g_e2p_data.E2P_8.cht1_data_select -= Acc; g_e2p_data.E2P_8.cht1_data_select = ( g_e2p_data.E2P_8.cht1_data_select >= 255 ) ? 0 : g_e2p_data.E2P_8.cht1_data_select; break;
			case 10:	g_e2p_data.E2P_8.cht2_data_select -= Acc; g_e2p_data.E2P_8.cht2_data_select = ( g_e2p_data.E2P_8.cht2_data_select >= 255 ) ? 0 : g_e2p_data.E2P_8.cht2_data_select; break;
		}
		if((num_page != 11) && (num_page != 12))
		{
			LCD_locate(230,24 * 1);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
			LCD_locate(230,24 * 1);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 2)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_data_select += Acc; g_e2p_data.E2P_4.num1_data_select = (g_e2p_data.E2P_4.num1_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_4.num1_data_select; break;
			case  2:	g_e2p_data.E2P_4.num2_data_select += Acc; g_e2p_data.E2P_4.num2_data_select = (g_e2p_data.E2P_4.num2_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_4.num2_data_select; break;
			case  3:	g_e2p_data.E2P_5.num3_data_select += Acc; g_e2p_data.E2P_5.num3_data_select = (g_e2p_data.E2P_5.num3_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_5.num3_data_select; break;
			case  4:	g_e2p_data.E2P_5.num4_data_select += Acc; g_e2p_data.E2P_5.num4_data_select = (g_e2p_data.E2P_5.num4_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_5.num4_data_select; break;
			case  5:	g_e2p_data.E2P_6.num5_data_select += Acc; g_e2p_data.E2P_6.num5_data_select = (g_e2p_data.E2P_6.num5_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_6.num5_data_select; break;
			case  6:	g_e2p_data.E2P_6.num6_data_select += Acc; g_e2p_data.E2P_6.num6_data_select = (g_e2p_data.E2P_6.num6_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_6.num6_data_select; break;
//			case  7:	g_e2p_data.E2P_3.rev_data_select  += Acc; g_e2p_data.E2P_3.rev_data_select  = (g_e2p_data.E2P_3.rev_data_select  > rev_data_select_value) ? rev_data_select_value : g_e2p_data.E2P_3.rev_data_select;  break;
			case  7:	g_e2p_data.E2P_3.rev_data_select  += Acc; g_e2p_data.E2P_3.rev_data_select  = (g_e2p_data.E2P_3.rev_data_select  > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_3.rev_data_select;  break;
//			case  8:	g_e2p_data.E2P_3.afr_data_select  += Acc; g_e2p_data.E2P_3.afr_data_select  = (g_e2p_data.E2P_3.afr_data_select  > afr_data_select_value) ? afr_data_select_value : g_e2p_data.E2P_3.afr_data_select;  break;
			case  8:	g_e2p_data.E2P_3.afr_data_select  += Acc; g_e2p_data.E2P_3.afr_data_select  = (g_e2p_data.E2P_3.afr_data_select  > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_3.afr_data_select;  break;
			case  9:	g_e2p_data.E2P_8.cht1_data_select += Acc; g_e2p_data.E2P_8.cht1_data_select = (g_e2p_data.E2P_8.cht1_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_8.cht1_data_select; break;
			case 10:	g_e2p_data.E2P_8.cht2_data_select += Acc; g_e2p_data.E2P_8.cht2_data_select = (g_e2p_data.E2P_8.cht2_data_select > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_8.cht2_data_select; break;
		}
		if((num_page != 11) && (num_page != 12))
		{
			LCD_locate(270,24 * 1);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
			LCD_locate(270,24 * 1);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 3)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_gain += Acc; Acc ++; g_e2p_data.E2P_4.num1_gain = (g_e2p_data.E2P_4.num1_gain > 10000) ? 10000 : g_e2p_data.E2P_4.num1_gain; break;
			case  2:	g_e2p_data.E2P_4.num2_gain += Acc; Acc ++; g_e2p_data.E2P_4.num2_gain = (g_e2p_data.E2P_4.num2_gain > 10000) ? 10000 : g_e2p_data.E2P_4.num2_gain; break;
			case  3:	g_e2p_data.E2P_5.num3_gain += Acc; Acc ++; g_e2p_data.E2P_5.num3_gain = (g_e2p_data.E2P_5.num3_gain > 10000) ? 10000 : g_e2p_data.E2P_5.num3_gain; break;
			case  4:	g_e2p_data.E2P_5.num4_gain += Acc; Acc ++; g_e2p_data.E2P_5.num4_gain = (g_e2p_data.E2P_5.num4_gain > 10000) ? 10000 : g_e2p_data.E2P_5.num4_gain; break;
			case  5:	g_e2p_data.E2P_6.num5_gain += Acc; Acc ++; g_e2p_data.E2P_6.num5_gain = (g_e2p_data.E2P_6.num5_gain > 10000) ? 10000 : g_e2p_data.E2P_6.num5_gain; break;
			case  6:	g_e2p_data.E2P_6.num6_gain += Acc; Acc ++; g_e2p_data.E2P_6.num6_gain = (g_e2p_data.E2P_6.num6_gain > 10000) ? 10000 : g_e2p_data.E2P_6.num6_gain; break;
			case  7:	g_e2p_data.E2P_3.rev_gain  += Acc; Acc ++; g_e2p_data.E2P_3.rev_gain  = (g_e2p_data.E2P_3.rev_gain  > 10000) ? 10000 : g_e2p_data.E2P_3.rev_gain;  break;
			case  8:	g_e2p_data.E2P_3.afr_gain  += Acc; Acc ++; g_e2p_data.E2P_3.afr_gain  = (g_e2p_data.E2P_3.afr_gain  > 10000) ? 10000 : g_e2p_data.E2P_3.afr_gain;  break;
			case  9:	g_e2p_data.E2P_8.cht1_gain += Acc; Acc ++; g_e2p_data.E2P_8.cht1_gain = (g_e2p_data.E2P_8.cht1_gain > 10000) ? 10000 : g_e2p_data.E2P_8.cht1_gain; break;
			case 10:	g_e2p_data.E2P_8.cht2_gain += Acc; Acc ++; g_e2p_data.E2P_8.cht2_gain = (g_e2p_data.E2P_8.cht2_gain > 10000) ? 10000 : g_e2p_data.E2P_8.cht2_gain; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_gain += Acc; Acc ++; g_e2p_data.E2P_9.cht1_guage_gain = (g_e2p_data.E2P_9.cht1_guage_gain > 10000) ? 10000 : g_e2p_data.E2P_9.cht1_guage_gain; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_gain += Acc; Acc ++; g_e2p_data.E2P_9.cht2_guage_gain = (g_e2p_data.E2P_9.cht2_guage_gain > 10000) ? 10000 : g_e2p_data.E2P_9.cht2_guage_gain; break;
		}
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 4)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_gain -= Acc; Acc ++; g_e2p_data.E2P_4.num1_gain = (g_e2p_data.E2P_4.num1_gain < -10000) ? -10000 : g_e2p_data.E2P_4.num1_gain; break;
			case  2:	g_e2p_data.E2P_4.num2_gain -= Acc; Acc ++; g_e2p_data.E2P_4.num2_gain = (g_e2p_data.E2P_4.num2_gain < -10000) ? -10000 : g_e2p_data.E2P_4.num2_gain; break;
			case  3:	g_e2p_data.E2P_5.num3_gain -= Acc; Acc ++; g_e2p_data.E2P_5.num3_gain = (g_e2p_data.E2P_5.num3_gain < -10000) ? -10000 : g_e2p_data.E2P_5.num3_gain; break;
			case  4:	g_e2p_data.E2P_5.num4_gain -= Acc; Acc ++; g_e2p_data.E2P_5.num4_gain = (g_e2p_data.E2P_5.num4_gain < -10000) ? -10000 : g_e2p_data.E2P_5.num4_gain; break;
			case  5:	g_e2p_data.E2P_6.num5_gain -= Acc; Acc ++; g_e2p_data.E2P_6.num5_gain = (g_e2p_data.E2P_6.num5_gain < -10000) ? -10000 : g_e2p_data.E2P_6.num5_gain; break;
			case  6:	g_e2p_data.E2P_6.num6_gain -= Acc; Acc ++; g_e2p_data.E2P_6.num6_gain = (g_e2p_data.E2P_6.num6_gain < -10000) ? -10000 : g_e2p_data.E2P_6.num6_gain; break;
			case  7:	g_e2p_data.E2P_3.rev_gain  -= Acc; Acc ++; g_e2p_data.E2P_3.rev_gain  = (g_e2p_data.E2P_3.rev_gain  < -10000) ? -10000 : g_e2p_data.E2P_3.rev_gain;  break;
			case  8:	g_e2p_data.E2P_3.afr_gain  -= Acc; Acc ++; g_e2p_data.E2P_3.afr_gain  = (g_e2p_data.E2P_3.afr_gain  < -10000) ? -10000 : g_e2p_data.E2P_3.afr_gain;  break;
			case  9:	g_e2p_data.E2P_8.cht1_gain -= Acc; Acc ++; g_e2p_data.E2P_8.cht1_gain = (g_e2p_data.E2P_8.cht1_gain < -10000) ? -10000 : g_e2p_data.E2P_8.cht1_gain; break;
			case 10:	g_e2p_data.E2P_8.cht2_gain -= Acc; Acc ++; g_e2p_data.E2P_8.cht2_gain = (g_e2p_data.E2P_8.cht2_gain < -10000) ? -10000 : g_e2p_data.E2P_8.cht2_gain; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_gain -= Acc; Acc ++; g_e2p_data.E2P_9.cht1_guage_gain = (g_e2p_data.E2P_9.cht1_guage_gain < -10000) ? -10000 : g_e2p_data.E2P_9.cht1_guage_gain; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_gain -= Acc; Acc ++; g_e2p_data.E2P_9.cht2_guage_gain = (g_e2p_data.E2P_9.cht2_guage_gain < -10000) ? -10000 : g_e2p_data.E2P_9.cht2_guage_gain; break;
		}
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 5)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_bias += Acc; Acc ++; g_e2p_data.E2P_4.num1_bias = (g_e2p_data.E2P_4.num1_bias > 10000) ? 10000 : g_e2p_data.E2P_4.num1_bias; break;
			case  2:	g_e2p_data.E2P_4.num2_bias += Acc; Acc ++; g_e2p_data.E2P_4.num2_bias = (g_e2p_data.E2P_4.num2_bias > 10000) ? 10000 : g_e2p_data.E2P_4.num2_bias; break;
			case  3:	g_e2p_data.E2P_5.num3_bias += Acc; Acc ++; g_e2p_data.E2P_5.num3_bias = (g_e2p_data.E2P_5.num3_bias > 10000) ? 10000 : g_e2p_data.E2P_5.num3_bias; break;
			case  4:	g_e2p_data.E2P_5.num4_bias += Acc; Acc ++; g_e2p_data.E2P_5.num4_bias = (g_e2p_data.E2P_5.num4_bias > 10000) ? 10000 : g_e2p_data.E2P_5.num4_bias; break;
			case  5:	g_e2p_data.E2P_6.num5_bias += Acc; Acc ++; g_e2p_data.E2P_6.num5_bias = (g_e2p_data.E2P_6.num5_bias > 10000) ? 10000 : g_e2p_data.E2P_6.num5_bias; break;
			case  6:	g_e2p_data.E2P_6.num6_bias += Acc; Acc ++; g_e2p_data.E2P_6.num6_bias = (g_e2p_data.E2P_6.num6_bias > 10000) ? 10000 : g_e2p_data.E2P_6.num6_bias; break;
			case  7:	g_e2p_data.E2P_3.rev_bias  += Acc; Acc ++; g_e2p_data.E2P_3.rev_bias  = (g_e2p_data.E2P_3.rev_bias  > 10000) ? 10000 : g_e2p_data.E2P_3.rev_bias;  break;
			case  8:	g_e2p_data.E2P_3.afr_bias  += Acc; Acc ++; g_e2p_data.E2P_3.afr_bias  = (g_e2p_data.E2P_3.afr_bias  > 10000) ? 10000 : g_e2p_data.E2P_3.afr_bias;  break;
			case  9:	g_e2p_data.E2P_8.cht1_bias += Acc; Acc ++; g_e2p_data.E2P_8.cht1_bias = (g_e2p_data.E2P_8.cht1_bias > 10000) ? 10000 : g_e2p_data.E2P_8.cht1_bias; break;
			case 10:	g_e2p_data.E2P_8.cht2_bias += Acc; Acc ++; g_e2p_data.E2P_8.cht2_bias = (g_e2p_data.E2P_8.cht2_bias > 10000) ? 10000 : g_e2p_data.E2P_8.cht2_bias; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_bias += Acc; Acc ++; g_e2p_data.E2P_9.cht1_guage_bias = (g_e2p_data.E2P_9.cht1_guage_bias > 10000) ? 10000 : g_e2p_data.E2P_9.cht1_guage_bias; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_bias += Acc; Acc ++; g_e2p_data.E2P_9.cht2_guage_bias = (g_e2p_data.E2P_9.cht2_guage_bias > 10000) ? 10000 : g_e2p_data.E2P_9.cht2_guage_bias; break;
		}
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 6)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_bias -= Acc; Acc ++; g_e2p_data.E2P_4.num1_bias = (g_e2p_data.E2P_4.num1_bias < -10000) ? -10000 : g_e2p_data.E2P_4.num1_bias; break;
			case  2:	g_e2p_data.E2P_4.num2_bias -= Acc; Acc ++; g_e2p_data.E2P_4.num2_bias = (g_e2p_data.E2P_4.num2_bias < -10000) ? -10000 : g_e2p_data.E2P_4.num2_bias; break;
			case  3:	g_e2p_data.E2P_5.num3_bias -= Acc; Acc ++; g_e2p_data.E2P_5.num3_bias = (g_e2p_data.E2P_5.num3_bias < -10000) ? -10000 : g_e2p_data.E2P_5.num3_bias; break;
			case  4:	g_e2p_data.E2P_5.num4_bias -= Acc; Acc ++; g_e2p_data.E2P_5.num4_bias = (g_e2p_data.E2P_5.num4_bias < -10000) ? -10000 : g_e2p_data.E2P_5.num4_bias; break;
			case  5:	g_e2p_data.E2P_6.num5_bias -= Acc; Acc ++; g_e2p_data.E2P_6.num5_bias = (g_e2p_data.E2P_6.num5_bias < -10000) ? -10000 : g_e2p_data.E2P_6.num5_bias; break;
			case  6:	g_e2p_data.E2P_6.num6_bias -= Acc; Acc ++; g_e2p_data.E2P_6.num6_bias = (g_e2p_data.E2P_6.num6_bias < -10000) ? -10000 : g_e2p_data.E2P_6.num6_bias; break;
			case  7:	g_e2p_data.E2P_3.rev_bias  -= Acc; Acc ++; g_e2p_data.E2P_3.rev_bias  = (g_e2p_data.E2P_3.rev_bias  < -10000) ? -10000 : g_e2p_data.E2P_3.rev_bias;  break;
			case  8:	g_e2p_data.E2P_3.afr_bias  -= Acc; Acc ++; g_e2p_data.E2P_3.afr_bias  = (g_e2p_data.E2P_3.afr_bias  < -10000) ? -10000 : g_e2p_data.E2P_3.afr_bias;  break;
			case  9:	g_e2p_data.E2P_8.cht1_bias -= Acc; Acc ++; g_e2p_data.E2P_8.cht1_bias = (g_e2p_data.E2P_8.cht1_bias < -10000) ? -10000 : g_e2p_data.E2P_8.cht1_bias; break;
			case 10:	g_e2p_data.E2P_8.cht2_bias -= Acc; Acc ++; g_e2p_data.E2P_8.cht2_bias = (g_e2p_data.E2P_8.cht2_bias < -10000) ? -10000 : g_e2p_data.E2P_8.cht2_bias; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_bias -= Acc; Acc ++; g_e2p_data.E2P_9.cht1_guage_bias = (g_e2p_data.E2P_9.cht1_guage_bias < -10000) ? -10000 : g_e2p_data.E2P_9.cht1_guage_bias; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_bias -= Acc; Acc ++; g_e2p_data.E2P_9.cht2_guage_bias = (g_e2p_data.E2P_9.cht2_guage_bias < -10000) ? -10000 : g_e2p_data.E2P_9.cht2_guage_bias; break;
		}
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 7)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_dp += Acc; g_e2p_data.E2P_4.num1_dp = (g_e2p_data.E2P_4.num1_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_4.num1_dp; break;
			case  2:	g_e2p_data.E2P_4.num2_dp += Acc; g_e2p_data.E2P_4.num2_dp = (g_e2p_data.E2P_4.num2_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_4.num2_dp; break;
			case  3:	g_e2p_data.E2P_5.num3_dp += Acc; g_e2p_data.E2P_5.num3_dp = (g_e2p_data.E2P_5.num3_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_5.num3_dp; break;
			case  4:	g_e2p_data.E2P_5.num4_dp += Acc; g_e2p_data.E2P_5.num4_dp = (g_e2p_data.E2P_5.num4_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_5.num4_dp; break;
			case  5:	g_e2p_data.E2P_6.num5_dp += Acc; g_e2p_data.E2P_6.num5_dp = (g_e2p_data.E2P_6.num5_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_6.num5_dp; break;
			case  6:	g_e2p_data.E2P_6.num6_dp += Acc; g_e2p_data.E2P_6.num6_dp = (g_e2p_data.E2P_6.num6_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_6.num6_dp; break;
			case  7:	g_e2p_data.E2P_2.rev_timing_rmp1 += Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp1 = (g_e2p_data.E2P_2.rev_timing_rmp1 > (g_e2p_data.E2P_2.rev_timing_rmp2 - 1)) ? (g_e2p_data.E2P_2.rev_timing_rmp2 - 1) : g_e2p_data.E2P_2.rev_timing_rmp1; break;
			case  8:	g_e2p_data.E2P_3.afr_dp  += Acc; g_e2p_data.E2P_3.afr_dp  = (g_e2p_data.E2P_3.afr_dp  > num_dp_value) ? num_dp_value : g_e2p_data.E2P_3.afr_dp;  break;
			case  9:	g_e2p_data.E2P_8.cht1_dp += Acc; g_e2p_data.E2P_8.cht1_dp = (g_e2p_data.E2P_8.cht1_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_8.cht1_dp; break;
			case 10:	g_e2p_data.E2P_8.cht2_dp += Acc; g_e2p_data.E2P_8.cht2_dp = (g_e2p_data.E2P_8.cht2_dp > num_dp_value) ? num_dp_value : g_e2p_data.E2P_8.cht2_dp; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_grid += Acc; g_e2p_data.E2P_9.cht1_guage_grid = (g_e2p_data.E2P_9.cht1_guage_grid > num_grid_value) ? num_grid_value : g_e2p_data.E2P_9.cht1_guage_grid; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_grid += Acc; g_e2p_data.E2P_9.cht2_guage_grid = (g_e2p_data.E2P_9.cht2_guage_grid > num_grid_value) ? num_grid_value : g_e2p_data.E2P_9.cht2_guage_grid; break;
		}
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
		LCD_RefreshFast();
	}
	else if	(num_control == 8)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_dp -= Acc; g_e2p_data.E2P_4.num1_dp = (g_e2p_data.E2P_4.num1_dp >= 255) ? 0 : g_e2p_data.E2P_4.num1_dp; break;
			case  2:	g_e2p_data.E2P_4.num2_dp -= Acc; g_e2p_data.E2P_4.num2_dp = (g_e2p_data.E2P_4.num2_dp >= 255) ? 0 : g_e2p_data.E2P_4.num2_dp; break;
			case  3:	g_e2p_data.E2P_5.num3_dp -= Acc; g_e2p_data.E2P_5.num3_dp = (g_e2p_data.E2P_5.num3_dp >= 255) ? 0 : g_e2p_data.E2P_5.num3_dp; break;
			case  4:	g_e2p_data.E2P_5.num4_dp -= Acc; g_e2p_data.E2P_5.num4_dp = (g_e2p_data.E2P_5.num4_dp >= 255) ? 0 : g_e2p_data.E2P_5.num4_dp; break;
			case  5:	g_e2p_data.E2P_6.num5_dp -= Acc; g_e2p_data.E2P_6.num5_dp = (g_e2p_data.E2P_6.num5_dp >= 255) ? 0 : g_e2p_data.E2P_6.num5_dp; break;
			case  6:	g_e2p_data.E2P_6.num6_dp -= Acc; g_e2p_data.E2P_6.num6_dp = (g_e2p_data.E2P_6.num6_dp >= 255) ? 0 : g_e2p_data.E2P_6.num6_dp; break;
			case  7:	g_e2p_data.E2P_2.rev_timing_rmp1 -= Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp1 = (g_e2p_data.E2P_2.rev_timing_rmp1 < 2000) ? 2000 : g_e2p_data.E2P_2.rev_timing_rmp1; break;
			case  8:	g_e2p_data.E2P_3.afr_dp  -= Acc; g_e2p_data.E2P_3.afr_dp  = (g_e2p_data.E2P_3.afr_dp  >= 255) ? 0 : g_e2p_data.E2P_3.afr_dp;  break;
			case  9:	g_e2p_data.E2P_8.cht1_dp -= Acc; g_e2p_data.E2P_8.cht1_dp = (g_e2p_data.E2P_8.cht1_dp >= 255) ? 0 : g_e2p_data.E2P_8.cht1_dp; break;
			case 10:	g_e2p_data.E2P_8.cht2_dp -= Acc; g_e2p_data.E2P_8.cht2_dp = (g_e2p_data.E2P_8.cht2_dp >= 255) ? 0 : g_e2p_data.E2P_8.cht2_dp; break;
			case 11:	g_e2p_data.E2P_9.cht1_guage_grid -= Acc; g_e2p_data.E2P_9.cht1_guage_grid = (g_e2p_data.E2P_9.cht1_guage_grid >= 255) ? 0 : g_e2p_data.E2P_9.cht1_guage_grid; break;
			case 12:	g_e2p_data.E2P_9.cht2_guage_grid -= Acc; g_e2p_data.E2P_9.cht2_guage_grid = (g_e2p_data.E2P_9.cht2_guage_grid >= 255) ? 0 : g_e2p_data.E2P_9.cht2_guage_grid; break;
		}
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
		LCD_RefreshFast();
	}
	else if	(num_control == 9)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_label -= Acc; g_e2p_data.E2P_4.num1_label = (g_e2p_data.E2P_4.num1_label >= 255) ? 0 : g_e2p_data.E2P_4.num1_label; break;
			case  2:	g_e2p_data.E2P_4.num2_label -= Acc; g_e2p_data.E2P_4.num2_label = (g_e2p_data.E2P_4.num2_label >= 255) ? 0 : g_e2p_data.E2P_4.num2_label; break;
			case  3:	g_e2p_data.E2P_5.num3_label -= Acc; g_e2p_data.E2P_5.num3_label = (g_e2p_data.E2P_5.num3_label >= 255) ? 0 : g_e2p_data.E2P_5.num3_label; break;
			case  4:	g_e2p_data.E2P_5.num4_label -= Acc; g_e2p_data.E2P_5.num4_label = (g_e2p_data.E2P_5.num4_label >= 255) ? 0 : g_e2p_data.E2P_5.num4_label; break;
			case  5:	g_e2p_data.E2P_6.num5_label -= Acc; g_e2p_data.E2P_6.num5_label = (g_e2p_data.E2P_6.num5_label >= 255) ? 0 : g_e2p_data.E2P_6.num5_label; break;
			case  6:	g_e2p_data.E2P_6.num6_label -= Acc; g_e2p_data.E2P_6.num6_label = (g_e2p_data.E2P_6.num6_label >= 255) ? 0 : g_e2p_data.E2P_6.num6_label; break;
			case  7:	g_e2p_data.E2P_2.rev_timing_rmp2 += Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp2 = (g_e2p_data.E2P_2.rev_timing_rmp2 > (g_e2p_data.E2P_2.rev_timing_rmp3 - 1)) ? (g_e2p_data.E2P_2.rev_timing_rmp3 - 1) : g_e2p_data.E2P_2.rev_timing_rmp2; break;
			case  8:	g_e2p_data.E2P_3.afr_label  -= Acc; g_e2p_data.E2P_3.afr_label  = (g_e2p_data.E2P_3.afr_label  >= 255) ? 0 : g_e2p_data.E2P_3.afr_label;  break;
			case  9:	g_e2p_data.E2P_8.cht1_label -= Acc; g_e2p_data.E2P_8.cht1_label = (g_e2p_data.E2P_8.cht1_label >= 255) ? 0 : g_e2p_data.E2P_8.cht1_label; break;
			case 10:	g_e2p_data.E2P_8.cht2_label -= Acc; g_e2p_data.E2P_8.cht2_label = (g_e2p_data.E2P_8.cht2_label >= 255) ? 0 : g_e2p_data.E2P_8.cht2_label; break;
		}
		if((num_page != 11) && (num_page != 12))
		{
			LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
			LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 10)
	{
		switch(num_page)
		{
			case  1:	g_e2p_data.E2P_4.num1_label += Acc; g_e2p_data.E2P_4.num1_label = (g_e2p_data.E2P_4.num1_label > num_label_value) ? num_label_value : g_e2p_data.E2P_4.num1_label; break;
			case  2:	g_e2p_data.E2P_4.num2_label += Acc; g_e2p_data.E2P_4.num2_label = (g_e2p_data.E2P_4.num2_label > num_label_value) ? num_label_value : g_e2p_data.E2P_4.num2_label; break;
			case  3:	g_e2p_data.E2P_5.num3_label += Acc; g_e2p_data.E2P_5.num3_label = (g_e2p_data.E2P_5.num3_label > num_label_value) ? num_label_value : g_e2p_data.E2P_5.num3_label; break;
			case  4:	g_e2p_data.E2P_5.num4_label += Acc; g_e2p_data.E2P_5.num4_label = (g_e2p_data.E2P_5.num4_label > num_label_value) ? num_label_value : g_e2p_data.E2P_5.num4_label; break;
			case  5:	g_e2p_data.E2P_6.num5_label += Acc; g_e2p_data.E2P_6.num5_label = (g_e2p_data.E2P_6.num5_label > num_label_value) ? num_label_value : g_e2p_data.E2P_6.num5_label; break;
			case  6:	g_e2p_data.E2P_6.num6_label += Acc; g_e2p_data.E2P_6.num6_label = (g_e2p_data.E2P_6.num6_label > num_label_value) ? num_label_value : g_e2p_data.E2P_6.num6_label; break;
			case  7:	g_e2p_data.E2P_2.rev_timing_rmp2 -= Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp2 = (g_e2p_data.E2P_2.rev_timing_rmp2 < (g_e2p_data.E2P_2.rev_timing_rmp1 + 1)) ? (g_e2p_data.E2P_2.rev_timing_rmp1 + 1) : g_e2p_data.E2P_2.rev_timing_rmp2; break;
			case  8:	g_e2p_data.E2P_3.afr_label  += Acc; g_e2p_data.E2P_3.afr_label  = (g_e2p_data.E2P_3.afr_label  > afr_label_value) ? afr_label_value : g_e2p_data.E2P_3.afr_label;  break;
			case  9:	g_e2p_data.E2P_8.cht1_label += Acc; g_e2p_data.E2P_8.cht1_label = (g_e2p_data.E2P_8.cht1_label > num_label_value) ? num_label_value : g_e2p_data.E2P_8.cht1_label; break;
			case 10:	g_e2p_data.E2P_8.cht2_label += Acc; g_e2p_data.E2P_8.cht2_label = (g_e2p_data.E2P_8.cht2_label > num_label_value) ? num_label_value : g_e2p_data.E2P_8.cht2_label; break;
		}
		if((num_page != 11) && (num_page != 12))
		{
			LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
			LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 11)
	{
		switch(num_page)
		{
			case 1:	g_e2p_data.E2P_4.num1_unit -= Acc; g_e2p_data.E2P_4.num1_unit = (g_e2p_data.E2P_4.num1_unit >= 255) ? 0 : g_e2p_data.E2P_4.num1_unit; break;
			case 2:	g_e2p_data.E2P_4.num2_unit -= Acc; g_e2p_data.E2P_4.num2_unit = (g_e2p_data.E2P_4.num2_unit >= 255) ? 0 : g_e2p_data.E2P_4.num2_unit; break;
			case 3:	g_e2p_data.E2P_5.num3_unit -= Acc; g_e2p_data.E2P_5.num3_unit = (g_e2p_data.E2P_5.num3_unit >= 255) ? 0 : g_e2p_data.E2P_5.num3_unit; break;
			case 4:	g_e2p_data.E2P_5.num4_unit -= Acc; g_e2p_data.E2P_5.num4_unit = (g_e2p_data.E2P_5.num4_unit >= 255) ? 0 : g_e2p_data.E2P_5.num4_unit; break;
			case 5:	g_e2p_data.E2P_6.num5_unit -= Acc; g_e2p_data.E2P_6.num5_unit = (g_e2p_data.E2P_6.num5_unit >= 255) ? 0 : g_e2p_data.E2P_6.num5_unit; break;
			case 6:	g_e2p_data.E2P_6.num6_unit -= Acc; g_e2p_data.E2P_6.num6_unit = (g_e2p_data.E2P_6.num6_unit >= 255) ? 0 : g_e2p_data.E2P_6.num6_unit; break;
			case 7:	g_e2p_data.E2P_2.rev_timing_rmp3 += Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp3 = (g_e2p_data.E2P_2.rev_timing_rmp3 > 20000) ? 20000 : g_e2p_data.E2P_2.rev_timing_rmp3; break;
			case 8:	g_e2p_data.E2P_3.t_afr_data_select  -= Acc; g_e2p_data.E2P_3.t_afr_data_select  = ( g_e2p_data.E2P_3.t_afr_data_select  >= 255 ) ? 0 : g_e2p_data.E2P_3.t_afr_data_select;  break;
		}
		if((num_page != 9) && (num_page != 10) && (num_page != 11) && (num_page != 12))
		{
			LCD_locate(230,24 * 7);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
			LCD_locate(230,24 * 7);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 12)
	{
		switch(num_page)
		{
			case 1:	g_e2p_data.E2P_4.num1_unit += Acc; g_e2p_data.E2P_4.num1_unit = (g_e2p_data.E2P_4.num1_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_4.num1_unit; break;
			case 2:	g_e2p_data.E2P_4.num2_unit += Acc; g_e2p_data.E2P_4.num2_unit = (g_e2p_data.E2P_4.num2_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_4.num2_unit; break;
			case 3:	g_e2p_data.E2P_5.num3_unit += Acc; g_e2p_data.E2P_5.num3_unit = (g_e2p_data.E2P_5.num3_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_5.num3_unit; break;
			case 4:	g_e2p_data.E2P_5.num4_unit += Acc; g_e2p_data.E2P_5.num4_unit = (g_e2p_data.E2P_5.num4_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_5.num4_unit; break;
			case 5:	g_e2p_data.E2P_6.num5_unit += Acc; g_e2p_data.E2P_6.num5_unit = (g_e2p_data.E2P_6.num5_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_6.num5_unit; break;
			case 6:	g_e2p_data.E2P_6.num6_unit += Acc; g_e2p_data.E2P_6.num6_unit = (g_e2p_data.E2P_6.num6_unit > num_unit_value) ? num_unit_value : g_e2p_data.E2P_6.num6_unit; break;
			case 7:	g_e2p_data.E2P_2.rev_timing_rmp3 -= Acc; Acc ++; g_e2p_data.E2P_2.rev_timing_rmp3 = (g_e2p_data.E2P_2.rev_timing_rmp3 < (g_e2p_data.E2P_2.rev_timing_rmp2 + 1)) ? (g_e2p_data.E2P_2.rev_timing_rmp2 + 1) : g_e2p_data.E2P_2.rev_timing_rmp3; break;
//			case 8:	g_e2p_data.E2P_3.t_afr_data_select  += Acc; g_e2p_data.E2P_3.t_afr_data_select  = (g_e2p_data.E2P_3.t_afr_data_select  > t_afr_data_select_value) ? t_afr_data_select_value : g_e2p_data.E2P_3.t_afr_data_select;  break;
			case 8:	g_e2p_data.E2P_3.t_afr_data_select  += Acc; g_e2p_data.E2P_3.t_afr_data_select  = (g_e2p_data.E2P_3.t_afr_data_select  > num_data_select_value) ? num_data_select_value : g_e2p_data.E2P_3.t_afr_data_select;  break;
		}
		if((num_page != 9) && (num_page != 10) && (num_page != 11) && (num_page != 12))
		{
			LCD_locate(270,24 * 7);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
			LCD_locate(270,24 * 7);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 13)
	{
		switch(num_page)
		{
			case 1:	g_e2p_data.E2P_7.num1_warning += Acc; Acc ++; g_e2p_data.E2P_7.num1_warning = (g_e2p_data.E2P_7.num1_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num1_warning; break;
			case 2:	g_e2p_data.E2P_7.num2_warning += Acc; Acc ++; g_e2p_data.E2P_7.num2_warning = (g_e2p_data.E2P_7.num2_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num2_warning; break;
			case 3:	g_e2p_data.E2P_7.num3_warning += Acc; Acc ++; g_e2p_data.E2P_7.num3_warning = (g_e2p_data.E2P_7.num3_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num3_warning; break;
			case 4:	g_e2p_data.E2P_7.num4_warning += Acc; Acc ++; g_e2p_data.E2P_7.num4_warning = (g_e2p_data.E2P_7.num4_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num4_warning; break;
			case 5:	g_e2p_data.E2P_7.num5_warning += Acc; Acc ++; g_e2p_data.E2P_7.num5_warning = (g_e2p_data.E2P_7.num5_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num5_warning; break;
			case 6:	g_e2p_data.E2P_7.num6_warning += Acc; Acc ++; g_e2p_data.E2P_7.num6_warning = (g_e2p_data.E2P_7.num6_warning > 30000) ? 30000 : g_e2p_data.E2P_7.num6_warning; break;
		}
		if((num_page != 7) && (num_page != 8) && (num_page != 9) && (num_page != 10) && (num_page != 11) && (num_page != 12))
		{
			LCD_locate(230,24 * 8);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
			LCD_locate(230,24 * 8);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 上
			LCD_RefreshFast();
		}
	}
	else if	(num_control == 14)
	{
		switch(num_page)
		{
			case 1:	g_e2p_data.E2P_7.num1_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num1_warning = (g_e2p_data.E2P_7.num1_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num1_warning; break;
			case 2:	g_e2p_data.E2P_7.num2_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num2_warning = (g_e2p_data.E2P_7.num2_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num2_warning; break;
			case 3:	g_e2p_data.E2P_7.num3_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num3_warning = (g_e2p_data.E2P_7.num3_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num3_warning; break;
			case 4:	g_e2p_data.E2P_7.num4_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num4_warning = (g_e2p_data.E2P_7.num4_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num4_warning; break;
			case 5:	g_e2p_data.E2P_7.num5_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num5_warning = (g_e2p_data.E2P_7.num5_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num5_warning; break;
			case 6:	g_e2p_data.E2P_7.num6_warning -= Acc; Acc ++; g_e2p_data.E2P_7.num6_warning = (g_e2p_data.E2P_7.num6_warning < -30000) ? -30000 : g_e2p_data.E2P_7.num6_warning; break;
		}
		if((num_page != 7) && (num_page != 8) && (num_page != 9) && (num_page != 10) && (num_page != 11) && (num_page != 12))
		{
			LCD_locate(270,24 * 8);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
			LCD_locate(270,24 * 8);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONTR);	// 下
			LCD_RefreshFast();
		}
	}
	else
	{
		//
	}
	
	// --------------------------------------------------------------------
	// 2度押しキャンセル
	// --------------------------------------------------------------------
	touch_done_flg = 0;
	touch_drag_flg = 0;
}

// --------------------------------------------------------------------
// EEPROM初期状態遷移
// --------------------------------------------------------------------
void A990(void)
{
	// --------------------------------------------------------------------
	// 状態遷移処理
	// --------------------------------------------------------------------
	g_state = S999;
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	LCD_CLR(COLOR_BLACK);
	LCD_RefreshFast();
	
	touch_done_flg = 0;
	touch_drag_flg = 0;
}

// --------------------------------------------------------------------
// 設定保存処理
// --------------------------------------------------------------------
void A991(void)
{
	// --------------------------------------------------------------------
	// 保存アイコンタッチ描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Processing.......");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("                ");
	LCD_RefreshFast();
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Processing.......");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("                ");
	LCD_RefreshFast();
	
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	
	// --------------------------------------------------------------------
	// EEPROMデータ保存
	// --------------------------------------------------------------------
	Init_e2p_data();						// EEPROMデータレジスタ初期化
	Preset_load_MoTeC1();					// 初期データとしてMoTeC1データを読み込み
	// EEPROM初期データデータ書き込み
	Save_EEPROM_ALL();
	
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Save is complete.");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("Please restart!!");
	LCD_RefreshFast();
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONTR);
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Save is complete.");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("Please restart!!");
	LCD_RefreshFast();
}

// --------------------------------------------------------------------
// ステート定常処理 ステート中は常時実行
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void funcS001(void)
{
	// 定常処理なし
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void funcS002(void)
{
	// 定常処理なし
}

// --------------------------------------------------------------------
// 設定画面1描画
// --------------------------------------------------------------------
void funcS010(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	
	// --------------------------------------------------------------------
	// 設定項目描画
	// --------------------------------------------------------------------
	LCD_locate( 20, 24 * 0 + 6);	LCD_textout("<<SETTINGS>>");
	LCD_locate( 20, 24 * 2 + 6);	LCD_textout("Model   ");
	LCD_locate( 20, 24 * 3 + 6);	LCD_textout("Beep    ");
	LCD_locate( 20, 24 * 4 + 6);	LCD_textout("Mstr-W  ");
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("FCmode  ");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("Preset  ");
	LCD_locate(250, 24 * 0 + 6);	LCD_textout(version);
	
	switch(g_e2p_data.E2P_1.model)
	{
		case CAN_std:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< CAN STD  >");	break;
		case MoTeC1:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< MoTeC100 >");	break;
		case MoTeC2:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< MoTeC84  >");	break;
		case Haltech1:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< Haltech1 >");	break;
		case Haltech2:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< Haltech2 >");	break;
		case Freedom1:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< Freedom1 >");	break;
		case Freedom2:	LCD_locate(100, 24 * 2 + 6);	LCD_textout("< Freedom2 >");	break;
	}
	LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	switch(g_e2p_data.E2P_1.control.BIT.beep_on)
	{
		case 0:			LCD_locate(100, 24 * 3 + 6);	LCD_textout("< ON       >");	break;
		case 1:			LCD_locate(100, 24 * 3 + 6);	LCD_textout("< OFF      >");	break;
	}
	LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	switch(g_e2p_data.E2P_1.control.BIT.ms_on)
	{
		case 0:			LCD_locate(100, 24 * 4 + 6);	LCD_textout("< ON       >");	break;
		case 1:			LCD_locate(100, 24 * 4 + 6);	LCD_textout("< OFF      >");	break;
	}
	LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	switch(g_e2p_data.E2P_1.control.BIT.FC_mode)
	{
		case 0:			LCD_locate(100, 24 * 5 + 6);	LCD_textout("< FASTmode >");	break;
		case 1:			LCD_locate(100, 24 * 5 + 6);	LCD_textout("< ALLmode  >");	break;
	}
	LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	switch(preset_no)
	{
		case 0:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("<-nochange->");	break;
		case 1:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< CAN-STD  >");	break;
		case 2:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< MoTeC    >");	break;
//		case 3:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< MoTeC2   >");	break;
		case 3:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< Haltech1 >");	break;
		case 4:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< Haltech2 >");	break;
		case 5:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< Freedom1 >");	break;
		case 6:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< Freedom2 >");	break;
//		case 7:			LCD_locate(100, 24 * 6 + 6);	LCD_textout("< MSquirt1 >");	break;
	}
	LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	// --------------------------------------------------------------------
	// 保存アイコン描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONT);
	
	// --------------------------------------------------------------------
	// カーソルアイコン描画
	// --------------------------------------------------------------------
	LCD_locate( 46,215);	LCD_Gcopy(256,  48, 64, 24, (volatile unsigned int    *)FONT);	// 左
	LCD_locate(214,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONT);	// 右
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// 設定画面2描画
// --------------------------------------------------------------------
void funcS020(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	
	// --------------------------------------------------------------------
	// 画面クリア&切り替え
	// --------------------------------------------------------------------
	LCD_CLR(COLOR_BLACK);
	
	// --------------------------------------------------------------------
	// 設定項目描画
	// --------------------------------------------------------------------
	LCD_locate( 20, 24 * 0 + 6);	LCD_textout("<<CAN ID SETTINGS>>");
	
	LCD_locate( 20, 24 * 1 + 6);	LCD_textout("Baudrate");
	LCD_locate( 20, 24 * 2 + 6);	LCD_textout("Ch1     ");
	LCD_locate( 20, 24 * 3 + 6);	LCD_textout("Ch2     ");
	LCD_locate( 20, 24 * 4 + 6);	LCD_textout("Ch3     ");
	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Ch4     ");
	LCD_locate( 20, 24 * 6 + 6);	LCD_textout("Ch5     ");
	LCD_locate( 20, 24 * 7 + 6);	LCD_textout("Ch6     ");
	LCD_locate(250, 24 * 0 + 6);	LCD_textout(version);
	
	// ボーレート設定
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.BAUD == 0)
	{
		LCD_locate(100, 24 * 1 + 6);	LCD_textout("< 500kbps >");
		
	}
	else
	{
		LCD_locate(100, 24 * 1 + 6);	LCD_textout("< 1Mbps   >");

	}
	LCD_locate(230,24 * 1);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270,24 * 1);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	// ID1
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1 == 1)
	{
		LCD_locate(60,24 * 2);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 2 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID1, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 2);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 2);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 2);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 2 + 6);	LCD_textout("not in use.");
	}
	
	// ID2
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2 == 1)
	{
		LCD_locate(60,24 * 3);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 3 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID2, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 3);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 3);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 3);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 3 + 6);	LCD_textout("not in use.");
	}
	
	// ID3
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3 == 1)
	{
		LCD_locate(60,24 * 4);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 4 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID3, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 4);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 4);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 4);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 4 + 6);	LCD_textout("not in use.");
	}
	
	// ID4
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4 == 1)
	{
		LCD_locate(60,24 * 5);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 5 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID4, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 5);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 5);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 5);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 5 + 6);	LCD_textout("not in use.");
	}
	
	// ID5
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5 == 1)
	{
		LCD_locate(60,24 * 6);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 6 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID5, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 6);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 6);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 6);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 6 + 6);	LCD_textout("not in use.");
	}
	
	// ID6
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6 == 1)
	{
		LCD_locate(60,24 * 7);	LCD_Gcopy(256, 192, 32, 24, (volatile unsigned int    *)FONT);	// ○
		LCD_locate(100, 24 * 7 + 6);	LCD_textout("ID <");	LCD_INT_draw(g_e2p_data.E2P_1.CAN_ID6, 4, 0);	LCD_textout(" >");
		LCD_locate(230,24 * 7);	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270,24 * 7);	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	}
	else
	{
		LCD_locate(60,24 * 7);	LCD_Gcopy(288, 192, 32, 24, (volatile unsigned int    *)FONT);	// ×
		LCD_locate(100, 24 * 7 + 6);	LCD_textout("not in use. ");
	}
	
	// --------------------------------------------------------------------
	// 保存アイコン描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONT);
	
	// --------------------------------------------------------------------
	// カーソルアイコン描画
	// --------------------------------------------------------------------
	LCD_locate( 46,215);	LCD_Gcopy(256,  48, 64, 24, (volatile unsigned int    *)FONT);	// 左
	LCD_locate(214,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONT);	// 右
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// 定常描画
// --------------------------------------------------------------------
void funcS110(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int			RevPoint;
	int						rev, afr, num1, num2, num3, num4, num5, num6;
	
	// --------------------------------------------------------------------
	// 数値算出
	// --------------------------------------------------------------------
//	rev  = ((long)(rev_data_select(g_e2p_data.E2P_3.rev_data_select )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(afr_data_select(g_e2p_data.E2P_3.afr_data_select )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
	
//	rev  = ((long)(num_data_select(g_e2p_data.E2P_3.rev_data_select )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(num_data_select(g_e2p_data.E2P_3.afr_data_select )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
//	num1 = ((long)(num_data_select(g_e2p_data.E2P_4.num1_data_select)) + g_e2p_data.E2P_4.num1_bias) * g_e2p_data.E2P_4.num1_gain / 1000;
//	num2 = ((long)(num_data_select(g_e2p_data.E2P_4.num2_data_select)) + g_e2p_data.E2P_4.num2_bias) * g_e2p_data.E2P_4.num2_gain / 1000;
//	num3 = ((long)(num_data_select(g_e2p_data.E2P_5.num3_data_select)) + g_e2p_data.E2P_5.num3_bias) * g_e2p_data.E2P_5.num3_gain / 1000;
//	num4 = ((long)(num_data_select(g_e2p_data.E2P_5.num4_data_select)) + g_e2p_data.E2P_5.num4_bias) * g_e2p_data.E2P_5.num4_gain / 1000;
//	num5 = ((long)(num_data_select(g_e2p_data.E2P_6.num5_data_select)) + g_e2p_data.E2P_6.num5_bias) * g_e2p_data.E2P_6.num5_gain / 1000;
//	num6 = ((long)(num_data_select(g_e2p_data.E2P_6.num6_data_select)) + g_e2p_data.E2P_6.num6_bias) * g_e2p_data.E2P_6.num6_gain / 1000;
	
	rev  = num_calc(g_e2p_data.E2P_3.rev_data_select , g_e2p_data.E2P_3.rev_bias , g_e2p_data.E2P_3.rev_gain );
	afr  = num_calc(g_e2p_data.E2P_3.afr_data_select , g_e2p_data.E2P_3.afr_bias , g_e2p_data.E2P_3.afr_gain );
	num1 = num_calc(g_e2p_data.E2P_4.num1_data_select, g_e2p_data.E2P_4.num1_bias, g_e2p_data.E2P_4.num1_gain);
	num2 = num_calc(g_e2p_data.E2P_4.num2_data_select, g_e2p_data.E2P_4.num2_bias, g_e2p_data.E2P_4.num2_gain);
	num3 = num_calc(g_e2p_data.E2P_5.num3_data_select, g_e2p_data.E2P_5.num3_bias, g_e2p_data.E2P_5.num3_gain);
	num4 = num_calc(g_e2p_data.E2P_5.num4_data_select, g_e2p_data.E2P_5.num4_bias, g_e2p_data.E2P_5.num4_gain);
	num5 = num_calc(g_e2p_data.E2P_6.num5_data_select, g_e2p_data.E2P_6.num5_bias, g_e2p_data.E2P_6.num5_gain);
	num6 = num_calc(g_e2p_data.E2P_6.num6_data_select, g_e2p_data.E2P_6.num6_bias, g_e2p_data.E2P_6.num6_gain);

	// 算出値リミット
	rev  = (rev  >=  +9000) ? + 9000 : rev ;	rev  = (rev  <=      0) ?      0 : rev ;
	afr  = (afr  >= +32000) ? +32000 : afr ;	afr  = (afr  <= -32000) ? -32000 : afr ;
	num1 = (num1 >= +32000) ? +32000 : num1;	num1 = (num1 <= -32000) ? -32000 : num1;
	num2 = (num2 >= +32000) ? +32000 : num2;	num2 = (num2 <= -32000) ? -32000 : num2;
	num3 = (num3 >= +32000) ? +32000 : num3;	num3 = (num3 <= -32000) ? -32000 : num3;
	num4 = (num4 >= +32000) ? +32000 : num4;	num4 = (num4 <= -32000) ? -32000 : num4;
	num5 = (num5 >= +32000) ? +32000 : num5;	num5 = (num5 <= -32000) ? -32000 : num5;
	num6 = (num6 >= +32000) ? +32000 : num6;	num6 = (num6 <= -32000) ? -32000 : num6;
	
	// --------------------------------------------------------------------
	// ピークホールド値更新
	// --------------------------------------------------------------------
	if(rev_peak  < rev  ){rev_peak  = rev;}
	if(num1_peak < num1 ){num1_peak = num1;}
	if(num2_peak < num2 ){num2_peak = num2;}
	if(num3_peak < num3 ){num3_peak = num3;}
	if(num4_peak < num4 ){num4_peak = num4;}
	if(num5_peak < num5 ){num5_peak = num5;}
	if(num6_peak < num6 ){num6_peak = num6;}
	
	// --------------------------------------------------------------------
	// ピークホールド値初回限定更新
	// --------------------------------------------------------------------
	if( (Onetime_Peakclear_done == 0)
	&&	(Onetime_Peakclear_cnt == 0))
	{
		Onetime_Peakclear_done = 1;
		rev_peak  = rev;
		num1_peak = num1;
		num2_peak = num2;
		num3_peak = num3;
		num4_peak = num4;
		num5_peak = num5;
		num6_peak = num6;
	}
	
	// --------------------------------------------------------------------
	// マスターワーニング判定&解除
	// --------------------------------------------------------------------
	if(num1 >= g_e2p_data.E2P_7.num1_warning){ if(g_master_warning_flg1 == 0){g_master_warning_flg1 = 1;}} else { if((g_master_warning_flg1 == 2) && (num1 <= (g_e2p_data.E2P_7.num1_warning - 5))){g_master_warning_flg1 = 0;}}
	if(num2 >= g_e2p_data.E2P_7.num2_warning){ if(g_master_warning_flg2 == 0){g_master_warning_flg2 = 1;}} else { if((g_master_warning_flg2 == 2) && (num2 <= (g_e2p_data.E2P_7.num2_warning - 5))){g_master_warning_flg2 = 0;}}
	if(num3 >= g_e2p_data.E2P_7.num3_warning){ if(g_master_warning_flg3 == 0){g_master_warning_flg3 = 1;}} else { if((g_master_warning_flg3 == 2) && (num3 <= (g_e2p_data.E2P_7.num3_warning - 5))){g_master_warning_flg3 = 0;}}
	if(num4 >= g_e2p_data.E2P_7.num4_warning){ if(g_master_warning_flg4 == 0){g_master_warning_flg4 = 1;}} else { if((g_master_warning_flg4 == 2) && (num4 <= (g_e2p_data.E2P_7.num4_warning - 5))){g_master_warning_flg4 = 0;}}
	if(num5 >= g_e2p_data.E2P_7.num5_warning){ if(g_master_warning_flg5 == 0){g_master_warning_flg5 = 1;}} else { if((g_master_warning_flg5 == 2) && (num5 <= (g_e2p_data.E2P_7.num5_warning - 5))){g_master_warning_flg5 = 0;}}
	if(num6 >= g_e2p_data.E2P_7.num6_warning){ if(g_master_warning_flg6 == 0){g_master_warning_flg6 = 1;}} else { if((g_master_warning_flg6 == 2) && (num6 <= (g_e2p_data.E2P_7.num6_warning - 5))){g_master_warning_flg6 = 0;}}
	
	// --------------------------------------------------------------------
	// シフトタイミングランプ判定
	// --------------------------------------------------------------------
	if		 (rev >= g_e2p_data.E2P_2.rev_timing_rmp3)												{ g_shift_timing_flg = 3;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp2) && (rev < g_e2p_data.E2P_2.rev_timing_rmp3))	{ g_shift_timing_flg = 2;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp1) && (rev < g_e2p_data.E2P_2.rev_timing_rmp2))	{ g_shift_timing_flg = 1;	}
	else																							{ g_shift_timing_flg = 0;	}
	
	// --------------------------------------------------------------------
	// レブゲージ描画
	// --------------------------------------------------------------------
	RevPoint = rev * 3 / 100;
	LCD_locate( 0				, 10);	LCD_Gcopy( 0				,   0, (RevPoint + 23)			,119, (volatile unsigned int    *)BASE);
	LCD_locate((RevPoint + 23)	, 10);	LCD_Gcopy((RevPoint + 23)	, 120, 320 - (RevPoint + 23)	,119, (volatile unsigned int    *)BASE);
	
	// --------------------------------------------------------------------
	// CAN 受信エラー表示
	// --------------------------------------------------------------------
	if(g_can_error_cnt != 0)
	{
		LCD_locate(  1, 24 * 0 + 6);	LCD_textout("CAN ERROR");
	}
	else
	{
		LCD_locate(  1, 24 * 0 + 6);	LCD_textout("          ");
	}
	
	// --------------------------------------------------------------------
	// 数値メータ描画
	// --------------------------------------------------------------------
	LCD_locate(178, 24 * 3);	LCD_INT_drawBN (rev , 5, 0);
	LCD_locate( 60, 24 * 4);	LCD_INT_drawBN2(afr	, 4, g_e2p_data.E2P_3.afr_dp );
	LCD_locate( 45, 24 * 6);	if(num1 >= g_e2p_data.E2P_7.num1_warning){ LCD_INT_drawBNR(num1, 5, g_e2p_data.E2P_4.num1_dp);} else {LCD_INT_drawBN (num1, 5, g_e2p_data.E2P_4.num1_dp);}
	LCD_locate( 45, 24 * 7);	if(num2 >= g_e2p_data.E2P_7.num2_warning){ LCD_INT_drawBNR(num2, 5, g_e2p_data.E2P_4.num2_dp);} else {LCD_INT_drawBN (num2, 5, g_e2p_data.E2P_4.num2_dp);}
	LCD_locate( 45, 24 * 8);	if(num3 >= g_e2p_data.E2P_7.num3_warning){ LCD_INT_drawBNR(num3, 5, g_e2p_data.E2P_5.num3_dp);} else {LCD_INT_drawBN (num3, 5, g_e2p_data.E2P_5.num3_dp);}
	LCD_locate(205, 24 * 6);	if(num4 >= g_e2p_data.E2P_7.num4_warning){ LCD_INT_drawBNR(num4, 5, g_e2p_data.E2P_5.num4_dp);} else {LCD_INT_drawBN (num4, 5, g_e2p_data.E2P_5.num4_dp);}
	LCD_locate(205, 24 * 7);	if(num5 >= g_e2p_data.E2P_7.num5_warning){ LCD_INT_drawBNR(num5, 5, g_e2p_data.E2P_6.num5_dp);} else {LCD_INT_drawBN (num5, 5, g_e2p_data.E2P_6.num5_dp);}
	LCD_locate(205, 24 * 8);	if(num6 >= g_e2p_data.E2P_7.num6_warning){ LCD_INT_drawBNR(num6, 5, g_e2p_data.E2P_6.num6_dp);} else {LCD_INT_drawBN (num6, 5, g_e2p_data.E2P_6.num6_dp);}
	
	// --------------------------------------------------------------------
	// ベース描画
	// --------------------------------------------------------------------
	LCD_locate(280, 24 * 3 + 6);	LCD_textout("RPM");
	LCD_locate( 20, 24 * 5 + 6);	num_label_draw(g_e2p_data.E2P_3.afr_label);
	LCD_locate(  1, 24 * 6 + 6);	num_label_draw(g_e2p_data.E2P_4.num1_label);
	LCD_locate(  1, 24 * 7 + 6);	num_label_draw(g_e2p_data.E2P_4.num2_label);
	LCD_locate(  1, 24 * 8 + 6);	num_label_draw(g_e2p_data.E2P_5.num3_label);
	LCD_locate(161, 24 * 6 + 6);	num_label_draw(g_e2p_data.E2P_5.num4_label);
	LCD_locate(161, 24 * 7 + 6);	num_label_draw(g_e2p_data.E2P_6.num5_label);
	LCD_locate(161, 24 * 8 + 6);	num_label_draw(g_e2p_data.E2P_6.num6_label);
	
	// --------------------------------------------------------------------
	// 単位描画
	// --------------------------------------------------------------------
	LCD_locate(145, 24 * 6 + 6);	num_unit_draw(g_e2p_data.E2P_4.num1_unit);
	LCD_locate(145, 24 * 7 + 6);	num_unit_draw(g_e2p_data.E2P_4.num2_unit);
	LCD_locate(145, 24 * 8 + 6);	num_unit_draw(g_e2p_data.E2P_5.num3_unit);
	LCD_locate(305, 24 * 6 + 6);	num_unit_draw(g_e2p_data.E2P_5.num4_unit);
	LCD_locate(305, 24 * 7 + 6);	num_unit_draw(g_e2p_data.E2P_6.num5_unit);
	LCD_locate(305, 24 * 8 + 6);	num_unit_draw(g_e2p_data.E2P_6.num6_unit);
	
	// --------------------------------------------------------------------
	// バックライトディマーアイコン描画
	// --------------------------------------------------------------------
	if(backlight_dimmer_flg)
	{
		LCD_locate(130,215);	LCD_Gcopy(256,  24, 64, 24, (volatile unsigned int    *)FONT);
	}
	else
	{
		LCD_locate(130,215);	LCD_Gcopy(256,   0, 64, 24, (volatile unsigned int    *)FONT);
	}
	
	// --------------------------------------------------------------------
	// カーソルアイコン描画
	// --------------------------------------------------------------------
	LCD_locate( 46,215);	LCD_Gcopy(256,  48, 64, 24, (volatile unsigned int    *)FONT);	// 左
	LCD_locate(214,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONT);	// 右

/*	
	// --------------------------------------------------------------------
	// FPS描画
	// --------------------------------------------------------------------
	g_fps ++;
	LCD_locate(  0,  0);	LCD_INT_drawBN (g_fps_max, 3, 0);
	LCD_locate( 64,  6);	LCD_textout("fps");
*/
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// ピークホールド描画
// --------------------------------------------------------------------
void funcS120(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int			RevPoint;
	int						rev, afr, num1, num2, num3, num4, num5, num6;
	
	// --------------------------------------------------------------------
	// 数値算出
	// --------------------------------------------------------------------
//	rev  = ((long)(rev_data_select(g_e2p_data.E2P_3.rev_data_select )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(afr_data_select(g_e2p_data.E2P_3.afr_data_select )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
	
//	rev  = ((long)(num_data_select(g_e2p_data.E2P_3.rev_data_select )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(num_data_select(g_e2p_data.E2P_3.afr_data_select )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
//	num1 = ((long)(num_data_select(g_e2p_data.E2P_4.num1_data_select)) + g_e2p_data.E2P_4.num1_bias) * g_e2p_data.E2P_4.num1_gain / 1000;
//	num2 = ((long)(num_data_select(g_e2p_data.E2P_4.num2_data_select)) + g_e2p_data.E2P_4.num2_bias) * g_e2p_data.E2P_4.num2_gain / 1000;
//	num3 = ((long)(num_data_select(g_e2p_data.E2P_5.num3_data_select)) + g_e2p_data.E2P_5.num3_bias) * g_e2p_data.E2P_5.num3_gain / 1000;
//	num4 = ((long)(num_data_select(g_e2p_data.E2P_5.num4_data_select)) + g_e2p_data.E2P_5.num4_bias) * g_e2p_data.E2P_5.num4_gain / 1000;
//	num5 = ((long)(num_data_select(g_e2p_data.E2P_6.num5_data_select)) + g_e2p_data.E2P_6.num5_bias) * g_e2p_data.E2P_6.num5_gain / 1000;
//	num6 = ((long)(num_data_select(g_e2p_data.E2P_6.num6_data_select)) + g_e2p_data.E2P_6.num6_bias) * g_e2p_data.E2P_6.num6_gain / 1000;
	
	rev  = num_calc(g_e2p_data.E2P_3.rev_data_select , g_e2p_data.E2P_3.rev_bias , g_e2p_data.E2P_3.rev_gain );
	afr  = num_calc(g_e2p_data.E2P_3.afr_data_select , g_e2p_data.E2P_3.afr_bias , g_e2p_data.E2P_3.afr_gain );
	num1 = num_calc(g_e2p_data.E2P_4.num1_data_select, g_e2p_data.E2P_4.num1_bias, g_e2p_data.E2P_4.num1_gain);
	num2 = num_calc(g_e2p_data.E2P_4.num2_data_select, g_e2p_data.E2P_4.num2_bias, g_e2p_data.E2P_4.num2_gain);
	num3 = num_calc(g_e2p_data.E2P_5.num3_data_select, g_e2p_data.E2P_5.num3_bias, g_e2p_data.E2P_5.num3_gain);
	num4 = num_calc(g_e2p_data.E2P_5.num4_data_select, g_e2p_data.E2P_5.num4_bias, g_e2p_data.E2P_5.num4_gain);
	num5 = num_calc(g_e2p_data.E2P_6.num5_data_select, g_e2p_data.E2P_6.num5_bias, g_e2p_data.E2P_6.num5_gain);
	num6 = num_calc(g_e2p_data.E2P_6.num6_data_select, g_e2p_data.E2P_6.num6_bias, g_e2p_data.E2P_6.num6_gain);
	
	// 算出値リミット
	rev  = (rev  >=  +9000) ? + 9000 : rev ;	rev  = (rev  <=      0) ?      0 : rev ;
	afr  = (afr  >= +32767) ? +32767 : afr ;	afr  = (afr  <= -32767) ? -32767 : afr ;
	num1 = (num1 >= +32767) ? +32767 : num1;	num1 = (num1 <= -32767) ? -32767 : num1;
	num2 = (num2 >= +32767) ? +32767 : num2;	num2 = (num2 <= -32767) ? -32767 : num2;
	num3 = (num3 >= +32767) ? +32767 : num3;	num3 = (num3 <= -32767) ? -32767 : num3;
	num4 = (num4 >= +32767) ? +32767 : num4;	num4 = (num4 <= -32767) ? -32767 : num4;
	num5 = (num5 >= +32767) ? +32767 : num5;	num5 = (num5 <= -32767) ? -32767 : num5;
	num6 = (num6 >= +32767) ? +32767 : num6;	num6 = (num6 <= -32767) ? -32767 : num6;
	
	// --------------------------------------------------------------------
	// ピークホールド値更新
	// --------------------------------------------------------------------
	if(rev_peak  < rev  ){rev_peak  = rev;}
	if(num1_peak < num1 ){num1_peak = num1;}
	if(num2_peak < num2 ){num2_peak = num2;}
	if(num3_peak < num3 ){num3_peak = num3;}
	if(num4_peak < num4 ){num4_peak = num4;}
	if(num5_peak < num5 ){num5_peak = num5;}
	if(num6_peak < num6 ){num6_peak = num6;}
	
	// --------------------------------------------------------------------
	// ピークホールド値初回限定更新
	// --------------------------------------------------------------------
	if( (Onetime_Peakclear_done == 0)
	&&	(Onetime_Peakclear_cnt == 0))
	{
		Onetime_Peakclear_done = 1;
		rev_peak  = rev;
		num1_peak = num1;
		num2_peak = num2;
		num3_peak = num3;
		num4_peak = num4;
		num5_peak = num5;
		num6_peak = num6;
	}
	
	// --------------------------------------------------------------------
	// マスターワーニング判定&解除
	// --------------------------------------------------------------------
	if(num1 >= g_e2p_data.E2P_7.num1_warning){ if(g_master_warning_flg1 == 0){g_master_warning_flg1 = 1;}} else { if((g_master_warning_flg1 == 2) && (num1 <= (g_e2p_data.E2P_7.num1_warning - 5))){g_master_warning_flg1 = 0;}}
	if(num2 >= g_e2p_data.E2P_7.num2_warning){ if(g_master_warning_flg2 == 0){g_master_warning_flg2 = 1;}} else { if((g_master_warning_flg2 == 2) && (num2 <= (g_e2p_data.E2P_7.num2_warning - 5))){g_master_warning_flg2 = 0;}}
	if(num3 >= g_e2p_data.E2P_7.num3_warning){ if(g_master_warning_flg3 == 0){g_master_warning_flg3 = 1;}} else { if((g_master_warning_flg3 == 2) && (num3 <= (g_e2p_data.E2P_7.num3_warning - 5))){g_master_warning_flg3 = 0;}}
	if(num4 >= g_e2p_data.E2P_7.num4_warning){ if(g_master_warning_flg4 == 0){g_master_warning_flg4 = 1;}} else { if((g_master_warning_flg4 == 2) && (num4 <= (g_e2p_data.E2P_7.num4_warning - 5))){g_master_warning_flg4 = 0;}}
	if(num5 >= g_e2p_data.E2P_7.num5_warning){ if(g_master_warning_flg5 == 0){g_master_warning_flg5 = 1;}} else { if((g_master_warning_flg5 == 2) && (num5 <= (g_e2p_data.E2P_7.num5_warning - 5))){g_master_warning_flg5 = 0;}}
	if(num6 >= g_e2p_data.E2P_7.num6_warning){ if(g_master_warning_flg6 == 0){g_master_warning_flg6 = 1;}} else { if((g_master_warning_flg6 == 2) && (num6 <= (g_e2p_data.E2P_7.num6_warning - 5))){g_master_warning_flg6 = 0;}}
	
	// --------------------------------------------------------------------
	// シフトタイミングランプ判定
	// --------------------------------------------------------------------
	if		 (rev >= g_e2p_data.E2P_2.rev_timing_rmp3)												{ g_shift_timing_flg = 3;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp2) && (rev < g_e2p_data.E2P_2.rev_timing_rmp3))	{ g_shift_timing_flg = 2;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp1) && (rev < g_e2p_data.E2P_2.rev_timing_rmp2))	{ g_shift_timing_flg = 1;	}
	else																							{ g_shift_timing_flg = 0;	}
	
	// --------------------------------------------------------------------
	// レブゲージ描画
	// --------------------------------------------------------------------
	RevPoint = rev_peak * 3 / 100;
	LCD_locate( 0				, 10);	LCD_Gcopy( 0				,   0, (RevPoint + 23)			,119, (volatile unsigned int    *)BASE);
	LCD_locate((RevPoint + 23)	, 10);	LCD_Gcopy((RevPoint + 23)	, 120, 320 - (RevPoint + 23)	,119, (volatile unsigned int    *)BASE);
	
	// --------------------------------------------------------------------
	// 数値メータ描画
	// --------------------------------------------------------------------
	LCD_locate(178, 24 * 3);	LCD_INT_drawBN (rev_peak , 5, 0);
	LCD_locate( 45, 24 * 6);	if(num1_peak >= g_e2p_data.E2P_7.num1_warning){ LCD_INT_drawBNR(num1_peak, 5, g_e2p_data.E2P_4.num1_dp);} else {LCD_INT_drawBN (num1_peak, 5, g_e2p_data.E2P_4.num1_dp);}
	LCD_locate( 45, 24 * 7);	if(num2_peak >= g_e2p_data.E2P_7.num2_warning){ LCD_INT_drawBNR(num2_peak, 5, g_e2p_data.E2P_4.num2_dp);} else {LCD_INT_drawBN (num2_peak, 5, g_e2p_data.E2P_4.num2_dp);}
	LCD_locate( 45, 24 * 8);	if(num3_peak >= g_e2p_data.E2P_7.num3_warning){ LCD_INT_drawBNR(num3_peak, 5, g_e2p_data.E2P_5.num3_dp);} else {LCD_INT_drawBN (num3_peak, 5, g_e2p_data.E2P_5.num3_dp);}
	LCD_locate(205, 24 * 6);	if(num4_peak >= g_e2p_data.E2P_7.num4_warning){ LCD_INT_drawBNR(num4_peak, 5, g_e2p_data.E2P_5.num4_dp);} else {LCD_INT_drawBN (num4_peak, 5, g_e2p_data.E2P_5.num4_dp);}
	LCD_locate(205, 24 * 7);	if(num5_peak >= g_e2p_data.E2P_7.num5_warning){ LCD_INT_drawBNR(num5_peak, 5, g_e2p_data.E2P_6.num5_dp);} else {LCD_INT_drawBN (num5_peak, 5, g_e2p_data.E2P_6.num5_dp);}
	LCD_locate(205, 24 * 8);	if(num6_peak >= g_e2p_data.E2P_7.num6_warning){ LCD_INT_drawBNR(num6_peak, 5, g_e2p_data.E2P_6.num6_dp);} else {LCD_INT_drawBN (num6_peak, 5, g_e2p_data.E2P_6.num6_dp);}
	
	// --------------------------------------------------------------------
	// ベース描画
	// --------------------------------------------------------------------
	LCD_locate( 20, 24 * 1    );	LCD_textout("PEAK");
	LCD_locate(280, 24 * 3 + 6);	LCD_textout("RPM");
	LCD_locate(  1, 24 * 6 + 6);	num_label_draw(g_e2p_data.E2P_4.num1_label);
	LCD_locate(  1, 24 * 7 + 6);	num_label_draw(g_e2p_data.E2P_4.num2_label);
	LCD_locate(  1, 24 * 8 + 6);	num_label_draw(g_e2p_data.E2P_5.num3_label);
	LCD_locate(161, 24 * 6 + 6);	num_label_draw(g_e2p_data.E2P_5.num4_label);
	LCD_locate(161, 24 * 7 + 6);	num_label_draw(g_e2p_data.E2P_6.num5_label);
	LCD_locate(161, 24 * 8 + 6);	num_label_draw(g_e2p_data.E2P_6.num6_label);
	
	// --------------------------------------------------------------------
	// 単位描画
	// --------------------------------------------------------------------
	LCD_locate(145, 24 * 6 + 6);	num_unit_draw(g_e2p_data.E2P_4.num1_unit);
	LCD_locate(145, 24 * 7 + 6);	num_unit_draw(g_e2p_data.E2P_4.num2_unit);
	LCD_locate(145, 24 * 8 + 6);	num_unit_draw(g_e2p_data.E2P_5.num3_unit);
	LCD_locate(305, 24 * 6 + 6);	num_unit_draw(g_e2p_data.E2P_5.num4_unit);
	LCD_locate(305, 24 * 7 + 6);	num_unit_draw(g_e2p_data.E2P_6.num5_unit);
	LCD_locate(305, 24 * 8 + 6);	num_unit_draw(g_e2p_data.E2P_6.num6_unit);
	
	// --------------------------------------------------------------------
	// ピークホールドクリアアイコン描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256,  96, 64, 24, (volatile unsigned int    *)FONT);
	
	// --------------------------------------------------------------------
	// カーソルアイコン描画
	// --------------------------------------------------------------------
	LCD_locate( 46,215);	LCD_Gcopy(256,  48, 64, 24, (volatile unsigned int    *)FONT);	// 左
	LCD_locate(214,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONT);	// 右
	
/*
	// --------------------------------------------------------------------
	// FPS描画
	// --------------------------------------------------------------------
	g_fps ++;
	LCD_locate(  0,  0);	LCD_INT_drawBN (g_fps_max, 3, 0);
	LCD_locate( 64,  6);	LCD_textout("fps");
*/
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// A/Fチャート描画
// --------------------------------------------------------------------
void funcS130(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	unsigned int			i;
	int						chart_line0, chart_line1, chart_line2, chart_line3;
	int						rev, afr, tafr, num1, num2, num3, num4, num5, num6, cht1, cht2;
	long					chart1_point, chart2_point;
	
	// --------------------------------------------------------------------
	// チャート部　画面クリア&ベース描画
	// --------------------------------------------------------------------
	//チャート面クリア
	LCD_PAINT( 113,   4, 203, 139, COLOR_WHITE);
	//縦罫線
	LCD_line ( 114,   5, 114, 141, 0xCE59);
	LCD_line ( 164,   5, 164, 141, 0xCE59);
	LCD_line ( 214,   5, 214, 141, 0xCE59);
	LCD_line ( 264,   5, 264, 141, 0xCE59);
	LCD_line ( 314,   5, 314, 141, 0xCE59);
	//横罫線
	LCD_line ( 114,   5, 314,   5, 0xCE59);
	LCD_line ( 114,  22, 314,  22, 0xCE59);
	LCD_line ( 114,  39, 314,  39, 0xCE59);
	LCD_line ( 114,  56, 314,  56, 0xCE59);
	LCD_line ( 114,  73, 314,  73, 0xCE59);
	LCD_line ( 114,  90, 314,  90, 0xCE59);
	LCD_line ( 114, 107, 314, 107, 0xCE59);
	LCD_line ( 114, 124, 314, 124, 0xCE59);
	LCD_line ( 114, 141, 314, 141, 0xCE59);
	//空燃比罫線
	LCD_line2( 114,  95 - 51, 314,  95 - 51, 0xFE50);	// 14.7
	LCD_line2( 114, 132 - 51, 314, 132 - 51, 0x865F);	// 12.5
	//ゲージ1
	LCD_PAINT( 113, 146, 203,  30, COLOR_WHITE);
	//ゲージ2
	LCD_PAINT( 113, 179, 203,  30, COLOR_WHITE);
	
	// --------------------------------------------------------------------
	// 数値算出
	// --------------------------------------------------------------------
//	rev  = ((long)(rev_data_select(g_e2p_data.E2P_3.rev_data_select    )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(afr_data_select(g_e2p_data.E2P_3.afr_data_select    )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
//	rev  = ((long)(num_data_select(g_e2p_data.E2P_3.rev_data_select    )) + g_e2p_data.E2P_3.rev_bias ) * g_e2p_data.E2P_3.rev_gain  / 1000;
//	afr  = ((long)(num_data_select(g_e2p_data.E2P_3.afr_data_select    )) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
	rev  = num_calc(g_e2p_data.E2P_3.rev_data_select , g_e2p_data.E2P_3.rev_bias , g_e2p_data.E2P_3.rev_gain );
	afr  = num_calc(g_e2p_data.E2P_3.afr_data_select , g_e2p_data.E2P_3.afr_bias , g_e2p_data.E2P_3.afr_gain );
	if(g_e2p_data.E2P_3.t_afr_data_select != 0)
	{
//		tafr = ((long)(t_afr_data_select(g_e2p_data.E2P_3.t_afr_data_select)) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
		tafr = ((long)(num_data_select(g_e2p_data.E2P_3.t_afr_data_select)) + g_e2p_data.E2P_3.afr_bias ) * g_e2p_data.E2P_3.afr_gain  / 1000;
	}
	else
	{
		tafr = 0;
	}
	num1 = ((long)(num_data_select(g_e2p_data.E2P_4.num1_data_select   )) + g_e2p_data.E2P_4.num1_bias) * g_e2p_data.E2P_4.num1_gain / 1000;
	num2 = ((long)(num_data_select(g_e2p_data.E2P_4.num2_data_select   )) + g_e2p_data.E2P_4.num2_bias) * g_e2p_data.E2P_4.num2_gain / 1000;
	num3 = ((long)(num_data_select(g_e2p_data.E2P_5.num3_data_select   )) + g_e2p_data.E2P_5.num3_bias) * g_e2p_data.E2P_5.num3_gain / 1000;
	num4 = ((long)(num_data_select(g_e2p_data.E2P_5.num4_data_select   )) + g_e2p_data.E2P_5.num4_bias) * g_e2p_data.E2P_5.num4_gain / 1000;
	num5 = ((long)(num_data_select(g_e2p_data.E2P_6.num5_data_select   )) + g_e2p_data.E2P_6.num5_bias) * g_e2p_data.E2P_6.num5_gain / 1000;
	num6 = ((long)(num_data_select(g_e2p_data.E2P_6.num6_data_select   )) + g_e2p_data.E2P_6.num6_bias) * g_e2p_data.E2P_6.num6_gain / 1000;
	cht1 = ((long)(num_data_select(g_e2p_data.E2P_8.cht1_data_select   )) + g_e2p_data.E2P_8.cht1_bias) * g_e2p_data.E2P_8.cht1_gain / 1000;
	cht2 = ((long)(num_data_select(g_e2p_data.E2P_8.cht2_data_select   )) + g_e2p_data.E2P_8.cht2_bias) * g_e2p_data.E2P_8.cht2_gain / 1000;
	// 算出値リミット
	rev  = (rev  >=  +9000) ? + 9000 : rev ;	rev  = (rev  <=      0) ?      0 : rev ;
	afr  = (afr  >= +32767) ? +32767 : afr ;	afr  = (afr  <= -32767) ? -32767 : afr ;
	tafr = (tafr >= +32767) ? +32767 : tafr;	tafr = (tafr <= -32767) ? -32767 : tafr;
	num1 = (num1 >= +32767) ? +32767 : num1;	num1 = (num1 <= -32767) ? -32767 : num1;
	num2 = (num2 >= +32767) ? +32767 : num2;	num2 = (num2 <= -32767) ? -32767 : num2;
	num3 = (num3 >= +32767) ? +32767 : num3;	num3 = (num3 <= -32767) ? -32767 : num3;
	num4 = (num4 >= +32767) ? +32767 : num4;	num4 = (num4 <= -32767) ? -32767 : num4;
	num5 = (num5 >= +32767) ? +32767 : num5;	num5 = (num5 <= -32767) ? -32767 : num5;
	num6 = (num6 >= +32767) ? +32767 : num6;	num6 = (num6 <= -32767) ? -32767 : num6;
	
	// --------------------------------------------------------------------
	// ピークホールド値更新
	// --------------------------------------------------------------------
	if(rev_peak  < rev  ){rev_peak  = rev;}
	if(num1_peak < num1 ){num1_peak = num1;}
	if(num2_peak < num2 ){num2_peak = num2;}
	if(num3_peak < num3 ){num3_peak = num3;}
	if(num4_peak < num4 ){num4_peak = num4;}
	if(num5_peak < num5 ){num5_peak = num5;}
	if(num6_peak < num6 ){num6_peak = num6;}
	
	// --------------------------------------------------------------------
	// ピークホールド値初回限定更新
	// --------------------------------------------------------------------
	if( (Onetime_Peakclear_done == 0)
	&&	(Onetime_Peakclear_cnt == 0))
	{
		Onetime_Peakclear_done = 1;
		rev_peak  = rev;
		num1_peak = num1;
		num2_peak = num2;
		num3_peak = num3;
		num4_peak = num4;
		num5_peak = num5;
		num6_peak = num6;
	}
	
	// --------------------------------------------------------------------
	// マスターワーニング判定&解除
	// --------------------------------------------------------------------
	if(num1 >= g_e2p_data.E2P_7.num1_warning){ if(g_master_warning_flg1 == 0){g_master_warning_flg1 = 1;}} else { if((g_master_warning_flg1 == 2) && (num1 <= (g_e2p_data.E2P_7.num1_warning - 5))){g_master_warning_flg1 = 0;}}
	if(num2 >= g_e2p_data.E2P_7.num2_warning){ if(g_master_warning_flg2 == 0){g_master_warning_flg2 = 1;}} else { if((g_master_warning_flg2 == 2) && (num2 <= (g_e2p_data.E2P_7.num2_warning - 5))){g_master_warning_flg2 = 0;}}
	if(num3 >= g_e2p_data.E2P_7.num3_warning){ if(g_master_warning_flg3 == 0){g_master_warning_flg3 = 1;}} else { if((g_master_warning_flg3 == 2) && (num3 <= (g_e2p_data.E2P_7.num3_warning - 5))){g_master_warning_flg3 = 0;}}
	if(num4 >= g_e2p_data.E2P_7.num4_warning){ if(g_master_warning_flg4 == 0){g_master_warning_flg4 = 1;}} else { if((g_master_warning_flg4 == 2) && (num4 <= (g_e2p_data.E2P_7.num4_warning - 5))){g_master_warning_flg4 = 0;}}
	if(num5 >= g_e2p_data.E2P_7.num5_warning){ if(g_master_warning_flg5 == 0){g_master_warning_flg5 = 1;}} else { if((g_master_warning_flg5 == 2) && (num5 <= (g_e2p_data.E2P_7.num5_warning - 5))){g_master_warning_flg5 = 0;}}
	if(num6 >= g_e2p_data.E2P_7.num6_warning){ if(g_master_warning_flg6 == 0){g_master_warning_flg6 = 1;}} else { if((g_master_warning_flg6 == 2) && (num6 <= (g_e2p_data.E2P_7.num6_warning - 5))){g_master_warning_flg6 = 0;}}
	
	// --------------------------------------------------------------------
	// シフトタイミングランプ判定
	// --------------------------------------------------------------------
	if		 (rev >= g_e2p_data.E2P_2.rev_timing_rmp3)												{ g_shift_timing_flg = 3;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp2) && (rev < g_e2p_data.E2P_2.rev_timing_rmp3))	{ g_shift_timing_flg = 2;	}
	else if	((rev >= g_e2p_data.E2P_2.rev_timing_rmp1) && (rev < g_e2p_data.E2P_2.rev_timing_rmp2))	{ g_shift_timing_flg = 1;	}
	else																							{ g_shift_timing_flg = 0;	}
	
	// --------------------------------------------------------------------
	// AFチャートデータ更新
	// --------------------------------------------------------------------
	if(g_int50mscnt >= 1)
	{
		if(chart_onoff == 0)
		{
			for(i = 1; i < ChartBufNum; i++ )
			{
				chart_buf1[i - 1] = chart_buf1[i];
				chart_buf2[i - 1] = chart_buf2[i];
				chart_buf3[i - 1] = chart_buf3[i];
				chart_buf4[i - 1] = chart_buf4[i];
			}
			chart_buf1[ChartBufNum - 1] = tafr;
			chart_buf2[ChartBufNum - 1] = afr;
			chart_buf3[ChartBufNum - 1] = cht1;
			chart_buf4[ChartBufNum - 1] = cht2;
		}
		
		g_int50mscnt = 0;
	}
	else
	{
		//
	}
	
	// --------------------------------------------------------------------
	// AFチャート描画
	// --------------------------------------------------------------------
	if(g_e2p_data.E2P_3.t_afr_data_select != 0)
	{
		for(i = 1; i < ChartBufNum; i++ )
		{
			// 目標空燃比座標算出
			chart_line0 = ((chart_buf1[i - 1] * 13926) >> 13) * (-1) + 293;
			chart_line0 = (chart_line0 > 140) ? 140 : chart_line0;
			chart_line0 = (chart_line0 <   6) ?   6 : chart_line0;
			
			chart_line1 = ((chart_buf1[i    ] * 13926) >> 13) * (-1) + 293;
			chart_line1 = (chart_line1 > 140) ? 140 : chart_line1;
			chart_line1 = (chart_line1 <   6) ?   6 : chart_line1;
			
			// 目標空燃比プロット
			LCD_line2((i - 1 + 114), chart_line0, ( i + 114), chart_line1, COLOR_RED);
		}
	}
	else
	{
		// 描画なし
	}
		
	for(i = 1; i < ChartBufNum; i++ )
	{
		// 実空燃比座標算出
		chart_line2 = ((chart_buf2[i - 1] * 13926) >> 13) * (-1) + 293;
		chart_line2 = (chart_line2 > 140) ? 140 : chart_line2;
		chart_line2 = (chart_line2 <   6) ?   6 : chart_line2;
		
		chart_line3 = ((chart_buf2[i    ] * 13926) >> 13) * (-1) + 293;
		chart_line3 = (chart_line3 > 140) ? 140 : chart_line3;
		chart_line3 = (chart_line3 <   6) ?   6 : chart_line3;
		
		// 実空燃比プロット
		LCD_line2((i - 1 + 114), chart_line2, ( i + 114), chart_line3, COLOR_BLUE);
	}
	
	// --------------------------------------------------------------------
	// ベース描画
	// --------------------------------------------------------------------
	LCD_locate(  0, 24 * 1 + 6);	num_label_draw(g_e2p_data.E2P_3.afr_label);
	if(g_e2p_data.E2P_3.t_afr_data_select != 0)
	{
		LCD_locate(  0, 24 * 3 + 6);	LCD_textout("TARGET");
	}
	else
	{
		// 描画なし
	}
	LCD_locate(  0, 24 * 5 + 6);	num_label_draw(g_e2p_data.E2P_8.cht1_label);
	LCD_locate(  0, 24 * 7 + 6);	num_label_draw(g_e2p_data.E2P_8.cht2_label);
	LCD_locate( 93,  68 - 51);		LCD_textout("16");
	LCD_locate( 93, 102 - 51);		LCD_textout("14");
	LCD_locate( 93, 136 - 51);		LCD_textout("12");
	LCD_locate( 93, 170 - 51);		LCD_textout("10");
	
	if(chart_onoff == 0)
	{
		// --------------------------------------------------------------------
		// 数値メータ描画
		// --------------------------------------------------------------------
		LCD_locate(  0, 24 * 2);	LCD_INT_drawBN (afr	, 5, g_e2p_data.E2P_3.afr_dp );
		if(g_e2p_data.E2P_3.t_afr_data_select != 0)
		{
			LCD_locate(  0, 24 * 4);	LCD_INT_drawBN (tafr, 5, g_e2p_data.E2P_3.afr_dp );
		}
		else
		{
			// 描画なし
		}
		LCD_locate(  0, 24 * 6);	LCD_INT_drawBN (cht1, 5, g_e2p_data.E2P_8.cht1_dp);
		LCD_locate(  0, 24 * 8);	LCD_INT_drawBN (cht2, 5, g_e2p_data.E2P_8.cht2_dp);
		
		// ゲージ1描画
		chart1_point = ((long)(cht1 + g_e2p_data.E2P_9.cht1_guage_bias) * g_e2p_data.E2P_9.cht1_guage_gain / 1000);
		chart1_point = (chart1_point  >=  200) ? + 200 : chart1_point;
		chart1_point = (chart1_point  <=    0) ?     0 : chart1_point;
		chart1_point ++;
		LCD_PAINT( 114, 148, chart1_point,  26, COLOR_BLUE);
		
		// ゲージ2描画
		chart2_point = ((long)(cht2 + g_e2p_data.E2P_9.cht2_guage_bias) * g_e2p_data.E2P_9.cht2_guage_gain / 1000);
		chart2_point = (chart2_point  >=  200) ? + 200 : chart2_point;
		chart2_point = (chart2_point  <=    0) ?     0 : chart2_point;
		chart2_point ++;
		LCD_PAINT( 114, 181, chart2_point,  26, COLOR_BLUE);
		
		// --------------------------------------------------------------------
		// チャート停止アイコン描画
		// --------------------------------------------------------------------
		LCD_locate(130,215);	LCD_Gcopy(256, 168, 64, 24, (volatile unsigned int    *)FONT);	// ||
	}
	else
	{
		// --------------------------------------------------------------------
		// 数値メータ描画
		// --------------------------------------------------------------------
		LCD_locate(  0, 24 * 2);	LCD_INT_drawBNR( chart_buf2[ChartX - 114] , 5, g_e2p_data.E2P_3.afr_dp );
		if(g_e2p_data.E2P_3.t_afr_data_select != 0)
		{
			LCD_locate(  0, 24 * 4);	LCD_INT_drawBNR( chart_buf1[ChartX - 114] , 5, g_e2p_data.E2P_3.afr_dp );
		}
		else
		{
			// 描画なし
		}
		LCD_locate(  0, 24 * 6);	LCD_INT_drawBNR( chart_buf3[ChartX - 114] , 5, g_e2p_data.E2P_8.cht1_dp);
		LCD_locate(  0, 24 * 8);	LCD_INT_drawBNR( chart_buf4[ChartX - 114] , 5, g_e2p_data.E2P_8.cht2_dp);
		
		// チャートドラッググリッド線描画
		LCD_line ( ChartX,   5,  ChartX, 141, COLOR_RED);
		
		// ゲージ1描画
		chart1_point = ((long)(chart_buf3[ChartX - 114] + g_e2p_data.E2P_9.cht1_guage_bias) * g_e2p_data.E2P_9.cht1_guage_gain / 1000);
		chart1_point = (chart1_point  >=  200) ? + 200 : chart1_point;
		chart1_point = (chart1_point  <=    0) ?     0 : chart1_point;
		chart1_point ++;
		LCD_PAINT( 114, 148, chart1_point,  26, COLOR_BLUE);
		
		// ゲージ2描画
		chart2_point = ((long)(chart_buf4[ChartX - 114] + g_e2p_data.E2P_9.cht2_guage_bias) * g_e2p_data.E2P_9.cht2_guage_gain / 1000);
		chart2_point = (chart2_point  >=  200) ? + 200 : chart2_point;
		chart2_point = (chart2_point  <=    0) ?     0 : chart2_point;
		chart2_point ++;
		LCD_PAINT( 114, 181, chart2_point,  26, COLOR_BLUE);
		
		// --------------------------------------------------------------------
		// チャート再生アイコン描画
		// --------------------------------------------------------------------
		LCD_locate(130,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONTR);	// 右
	}
		
	// --------------------------------------------------------------------
	// 罫線描画
	// --------------------------------------------------------------------
	for(i = 0; i <= 200 ; i = i + (200 / (g_e2p_data.E2P_9.cht1_guage_grid + 1)))
	{
		// 縦罫線
		LCD_line ( 114 + i, 148, 114 + i, 173, 0xCE59);
	}
	//横罫線
	LCD_line ( 114, 147, 114 + (i - (200 / (g_e2p_data.E2P_9.cht1_guage_grid + 1))), 147, 0xCE59);
	LCD_line ( 114, 174, 114 + (i - (200 / (g_e2p_data.E2P_9.cht1_guage_grid + 1))), 174, 0xCE59);
	for(i = 0; i <= 200 ; i = i + (200 / (g_e2p_data.E2P_9.cht2_guage_grid + 1)))
	{
		// 縦罫線
		LCD_line ( 114 + i, 181, 114 + i, 206, 0xCE59);
	}
	//横罫線
	LCD_line ( 114, 180, 114 + (i - (200 / (g_e2p_data.E2P_9.cht2_guage_grid + 1))), 180, 0xCE59);
	LCD_line ( 114, 207, 114 + (i - (200 / (g_e2p_data.E2P_9.cht2_guage_grid + 1))), 207, 0xCE59);
	
	// --------------------------------------------------------------------
	// カーソルアイコン描画
	// --------------------------------------------------------------------
	LCD_locate( 46,215);	LCD_Gcopy(256,  48, 64, 24, (volatile unsigned int    *)FONT);	// 左
	LCD_locate(214,215);	LCD_Gcopy(256,  72, 64, 24, (volatile unsigned int    *)FONT);	// 右
	
/*
	// --------------------------------------------------------------------
	// FPS描画
	// --------------------------------------------------------------------
	g_fps ++;
	LCD_locate(  0,  0);	LCD_INT_drawBN (g_fps_max, 3, 0);
	LCD_locate( 64,  6);	LCD_textout("fps");
*/
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// 数値描画設定画面描画
// --------------------------------------------------------------------
void funcS210(void)
{
	// --------------------------------------------------------------------
	// 設定項目描画
	// --------------------------------------------------------------------
	LCD_locate( 20, 24 * 0 + 6);
	switch(num_page)
	{
		case  1:		LCD_textout("<<NUM 1 SETTINGS>>");			break;
		case  2:		LCD_textout("<<NUM 2 SETTINGS>>");			break;
		case  3:		LCD_textout("<<NUM 3 SETTINGS>>");			break;
		case  4:		LCD_textout("<<NUM 4 SETTINGS>>");			break;
		case  5:		LCD_textout("<<NUM 5 SETTINGS>>");			break;
		case  6:		LCD_textout("<<NUM 6 SETTINGS>>");			break;
		case  7:		LCD_textout("<<REV SETTINGS>>");			break;
		case  8:		LCD_textout("<<AFR SETTINGS>>");			break;
		case  9:		LCD_textout("<<CHART NUM 1 SETTINGS>>");	break;
		case 10:		LCD_textout("<<CHART NUM 2 SETTINGS>>");	break;
		case 11:		LCD_textout("<<CHART GUAGE 1 SETTINGS>>");	break;
		case 12:		LCD_textout("<<CHART GUAGE 2 SETTINGS>>");	break;
	}
	
	if((num_page != 11)
	&&( num_page != 12)){	LCD_locate( 20, 24 * 1 + 6);	LCD_textout("Data Select");}
							LCD_locate( 20, 24 * 3 + 6);	LCD_textout("Gain  ");
							LCD_locate( 20, 24 * 4 + 6);	LCD_textout("Bias  ");
	if((num_page != 7)
	&&( num_page != 11)
	&&( num_page != 12)){	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("DP    ");
							LCD_locate( 20, 24 * 6 + 6);	LCD_textout("Label ");}
	if((num_page == 11)
	||( num_page == 12)){	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("Grid  ");}
	
	if((num_page != 7)
	&&( num_page != 8)
	&&( num_page != 9)
	&&( num_page != 10)
	&&( num_page != 11)
	&&( num_page != 12)){	LCD_locate( 20, 24 * 7 + 6);	LCD_textout("Unit  ");
							LCD_locate( 20, 24 * 8 + 6);	LCD_textout("Limit ");}
	
	if( num_page == 7) {	LCD_locate( 20, 24 * 5 + 6);	LCD_textout("REV-1 ");
							LCD_locate( 20, 24 * 6 + 6);	LCD_textout("REV-2 ");
							LCD_locate( 20, 24 * 7 + 6);	LCD_textout("REV-3 ");}
	if( num_page == 8) {	LCD_locate( 20, 24 * 7 + 6);	LCD_textout("TARGET AFR Select");}

	LCD_locate( 20, 24 * 2 + 6);
	switch(num_page)
	{
		case  1:		num_data_select_draw(g_e2p_data.E2P_4.num1_data_select);	break;
		case  2:		num_data_select_draw(g_e2p_data.E2P_4.num2_data_select);	break;
		case  3:		num_data_select_draw(g_e2p_data.E2P_5.num3_data_select);	break;
		case  4:		num_data_select_draw(g_e2p_data.E2P_5.num4_data_select);	break;
		case  5:		num_data_select_draw(g_e2p_data.E2P_6.num5_data_select);	break;
		case  6:		num_data_select_draw(g_e2p_data.E2P_6.num6_data_select);	break;
//		case  7:		rev_data_select_draw(g_e2p_data.E2P_3.rev_data_select );	break;
//		case  8:		afr_data_select_draw(g_e2p_data.E2P_3.afr_data_select );	break;
		case  7:		num_data_select_draw(g_e2p_data.E2P_3.rev_data_select );	break;
		case  8:		num_data_select_draw(g_e2p_data.E2P_3.afr_data_select );	break;
		case  9:		num_data_select_draw(g_e2p_data.E2P_8.cht1_data_select);	break;
		case 10:		num_data_select_draw(g_e2p_data.E2P_8.cht2_data_select);	break;
	}
	switch(num_page)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:	case 9:	case 10:
		LCD_locate(230, 24 * 1    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270, 24 * 1    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
		break;
	}
	
	LCD_locate( 80, 24 * 3 + 6);	LCD_textout("< x ");
	switch(num_page)
	{
		case  1:		LCD_INT_draw(g_e2p_data.E2P_4.num1_gain, 6, 3);	break;
		case  2:		LCD_INT_draw(g_e2p_data.E2P_4.num2_gain, 6, 3);	break;
		case  3:		LCD_INT_draw(g_e2p_data.E2P_5.num3_gain, 6, 3);	break;
		case  4:		LCD_INT_draw(g_e2p_data.E2P_5.num4_gain, 6, 3);	break;
		case  5:		LCD_INT_draw(g_e2p_data.E2P_6.num5_gain, 6, 3);	break;
		case  6:		LCD_INT_draw(g_e2p_data.E2P_6.num6_gain, 6, 3);	break;
		case  7:		LCD_INT_draw(g_e2p_data.E2P_3.rev_gain , 6, 3);	break;
		case  8:		LCD_INT_draw(g_e2p_data.E2P_3.afr_gain , 6, 3);	break;
		case  9:		LCD_INT_draw(g_e2p_data.E2P_8.cht1_gain, 6, 3);	break;
		case 10:		LCD_INT_draw(g_e2p_data.E2P_8.cht2_gain, 6, 3);	break;
		case 11:		LCD_INT_draw(g_e2p_data.E2P_9.cht1_guage_gain, 6, 3);	break;
		case 12:		LCD_INT_draw(g_e2p_data.E2P_9.cht2_guage_gain, 6, 3);	break;
	}
	LCD_locate(200, 24 * 3 + 6);	LCD_textout(">");
	LCD_locate(230, 24 * 3    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270, 24 * 3    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	LCD_locate( 80, 24 * 4 + 6);	LCD_textout("< + ");
	switch(num_page)
	{
		case  1:		LCD_INT_draw(g_e2p_data.E2P_4.num1_bias, 6, 0);	break;
		case  2:		LCD_INT_draw(g_e2p_data.E2P_4.num2_bias, 6, 0);	break;
		case  3:		LCD_INT_draw(g_e2p_data.E2P_5.num3_bias, 6, 0);	break;
		case  4:		LCD_INT_draw(g_e2p_data.E2P_5.num4_bias, 6, 0);	break;
		case  5:		LCD_INT_draw(g_e2p_data.E2P_6.num5_bias, 6, 0);	break;
		case  6:		LCD_INT_draw(g_e2p_data.E2P_6.num6_bias, 6, 0);	break;
		case  7:		LCD_INT_draw(g_e2p_data.E2P_3.rev_bias , 6, 0);	break;
		case  8:		LCD_INT_draw(g_e2p_data.E2P_3.afr_bias , 6, 0);	break;
		case  9:		LCD_INT_draw(g_e2p_data.E2P_8.cht1_bias, 6, 0);	break;
		case 10:		LCD_INT_draw(g_e2p_data.E2P_8.cht2_bias, 6, 0);	break;
		case 11:		LCD_INT_draw(g_e2p_data.E2P_9.cht1_guage_bias, 6, 0);	break;
		case 12:		LCD_INT_draw(g_e2p_data.E2P_9.cht2_guage_bias, 6, 0);	break;
	}
	LCD_locate(200, 24 * 4 + 6);	LCD_textout(">");
	LCD_locate(230, 24 * 4    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270, 24 * 4    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	LCD_locate( 80, 24 * 5 + 6);
	switch(num_page)
	{
		case  1:		num_dp_draw(g_e2p_data.E2P_4.num1_dp);	break;
		case  2:		num_dp_draw(g_e2p_data.E2P_4.num2_dp);	break;
		case  3:		num_dp_draw(g_e2p_data.E2P_5.num3_dp);	break;
		case  4:		num_dp_draw(g_e2p_data.E2P_5.num4_dp);	break;
		case  5:		num_dp_draw(g_e2p_data.E2P_6.num5_dp);	break;
		case  6:		num_dp_draw(g_e2p_data.E2P_6.num6_dp);	break;
		case  7:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_2.rev_timing_rmp1, 6, 0);	LCD_textout(">");	break;
		case  8:		num_dp_draw(g_e2p_data.E2P_3.afr_dp );	break;
		case  9:		num_dp_draw(g_e2p_data.E2P_8.cht1_dp);	break;
		case 10:		num_dp_draw(g_e2p_data.E2P_8.cht2_dp);	break;
		case 11:		num_grid_draw(g_e2p_data.E2P_9.cht1_guage_grid);	break;
		case 12:		num_grid_draw(g_e2p_data.E2P_9.cht2_guage_grid);	break;
	}
	LCD_locate(230, 24 * 5    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
	LCD_locate(270, 24 * 5    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
	
	LCD_locate( 80, 24 * 6 + 6);	
	switch(num_page)
	{
		case  1:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_4.num1_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  2:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_4.num2_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  3:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_5.num3_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  4:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_5.num4_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  5:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_6.num5_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  6:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_6.num6_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  7:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_2.rev_timing_rmp2, 6, 0);	LCD_textout(">");						break;
		case  8:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_3.afr_label );	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case  9:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_8.cht1_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
		case 10:		LCD_textout("< ");	num_label_draw(g_e2p_data.E2P_8.cht2_label);	LCD_locate(200, 24 * 6 + 6);	LCD_textout(">");	break;
	}
	switch(num_page)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:	case 9:	case 10:
		LCD_locate(230, 24 * 6    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270, 24 * 6    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
		break;
	}
	
	LCD_locate( 80, 24 * 7 + 6);
	switch(num_page)
	{
		case 1:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_4.num1_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 2:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_4.num2_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 3:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_5.num3_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 4:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_5.num4_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 5:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_6.num5_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 6:		LCD_textout("< ");	num_unit_draw(g_e2p_data.E2P_6.num6_unit);	LCD_locate(200, 24 * 7 + 6);	LCD_textout(">");	break;
		case 7:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_2.rev_timing_rmp3, 6, 0);	LCD_textout(">");					break;
//		case 8:		LCD_locate( 20, 24 * 8 + 6);t_afr_data_select_draw(g_e2p_data.E2P_3.t_afr_data_select );							break;
		case 8:		LCD_locate( 20, 24 * 8 + 6);num_data_select_draw(g_e2p_data.E2P_3.t_afr_data_select );							break;
	}
	switch(num_page)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:
		LCD_locate(230, 24 * 7    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270, 24 * 7    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
		break;
	}
	
	LCD_locate( 80, 24 * 8 + 6);
	switch(num_page)
	{
		case 1:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num1_warning, 6, g_e2p_data.E2P_4.num1_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
		case 2:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num2_warning, 6, g_e2p_data.E2P_4.num2_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
		case 3:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num3_warning, 6, g_e2p_data.E2P_5.num3_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
		case 4:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num4_warning, 6, g_e2p_data.E2P_5.num4_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
		case 5:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num5_warning, 6, g_e2p_data.E2P_6.num5_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
		case 6:		LCD_textout("<   ");	LCD_INT_draw(g_e2p_data.E2P_7.num6_warning, 6, g_e2p_data.E2P_6.num6_dp);	LCD_locate(200, 24 * 8 + 6);	LCD_textout(">");	break;
	}
	switch(num_page)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:
		LCD_locate(230, 24 * 8    );	LCD_Gcopy(256, 144, 32, 24, (volatile unsigned int    *)FONT);	// 上
		LCD_locate(270, 24 * 8    );	LCD_Gcopy(288, 144, 32, 24, (volatile unsigned int    *)FONT);	// 下
		break;
	}
	
	// --------------------------------------------------------------------
	// 保存アイコン描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONT);
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// 初期設定画面描画
// --------------------------------------------------------------------
void funcS999(void)
{
	// --------------------------------------------------------------------
	// 初期設定項目描画
	// --------------------------------------------------------------------
	LCD_locate( 20, 24 * 0 + 6);	LCD_textout("<<INITIALIZATION>>");
	LCD_locate(250, 24 * 0 + 6);	LCD_textout(version);
	LCD_locate( 20, 24 * 2 + 6);	LCD_textout("Initialize the SETUP DATA.");
	LCD_locate( 20, 24 * 3 + 6);	LCD_textout("Press to SAVE.");
	
	// --------------------------------------------------------------------
	// 保存アイコン描画
	// --------------------------------------------------------------------
	LCD_locate(130,215);	LCD_Gcopy(256, 120, 64, 24, (volatile unsigned int    *)FONT);
	
	LCD_Refresh();			// フレームバッファ更新
}

// --------------------------------------------------------------------
// 標準CAN初期化
// --------------------------------------------------------------------
static void Init_CAN(void)
{
	// --------------------------------------------------------------------
	// CAN割り込み禁止
	// --------------------------------------------------------------------
	RX0IE_Disable;
	RX1IE_Disable;
//	ERRIE_Disable;
//	WAKIE_Disable;
//	MERRE_Disable;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	if		(g_e2p_data.E2P_1.CANcontrol.BIT.BAUD == 0)
	{
		CANInit(CAN_BRP_20MHz_500KBPS);
	}
	else
	{
		CANInit(CAN_BRP_20MHz_1MBPS);
	}
	
	// --------------------------------------------------------------------
	// CANフィルター設定
	// --------------------------------------------------------------------
	CANSetSidFilter0(0x0000);
	CANSetSidFilter1(0x0000);
	CANSetSidFilter2(0x0000);
	CANSetSidFilter3(0x0000);
	CANSetSidFilter4(0x0000);
	CANSetSidFilter5(0x0000);
	CANSetSidMask0(0x0800);
	CANSetSidMask1(0x0800);
	
	CANSetFilterRxB0(1);
	CANSetFilterRxB1(1);
	
	// --------------------------------------------------------------------
	// CANモード切替
	// --------------------------------------------------------------------
	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
	
	// --------------------------------------------------------------------
	// CAN割り込み許可
	// --------------------------------------------------------------------
	RX0IE_Enable;
	RX1IE_Enable;
//	ERRIE_Enable;
//	WAKIE_Enable;
//	MERRE_Enable;
	
	// --------------------------------------------------------------------
	// CAN 時分割処理用タイマー初期化
	// --------------------------------------------------------------------
	g_can_rcv_timer = 10;
}

// --------------------------------------------------------------------
// MoTeC1初期化
// --------------------------------------------------------------------
static void Init_MoTeC1(void)
{
	// --------------------------------------------------------------------
	// CAN割り込み禁止
	// --------------------------------------------------------------------
	RX0IE_Disable;
	RX1IE_Disable;
//	ERRIE_Disable;
//	WAKIE_Disable;
//	MERRE_Disable;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	CANInit(CAN_BRP_20MHz_1MBPS);
	
	// --------------------------------------------------------------------
	// CANフィルター設定
	// --------------------------------------------------------------------
	CANSetSidFilter0(0x05F0);
	CANSetSidFilter1(0x05F0);
	CANSetSidFilter2(0x05F0);
	CANSetSidFilter3(0x05F0);
	CANSetSidFilter4(0x05F0);
	CANSetSidFilter5(0x05F0);
	CANSetSidMask0(0xFFF0);
	CANSetSidMask1(0xFFF0);
	
	CANSetFilterRxB0(1);
	CANSetFilterRxB1(1);
	
	// --------------------------------------------------------------------
	// CANモード切替
	// --------------------------------------------------------------------
	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
	
	// --------------------------------------------------------------------
	// CAN割り込み許可
	// --------------------------------------------------------------------
	RX0IE_Enable;
	RX1IE_Enable;
//	ERRIE_Enable;
//	WAKIE_Enable;
//	MERRE_Enable;
	
	// --------------------------------------------------------------------
	// CAN 時分割処理用タイマー初期化
	// --------------------------------------------------------------------
	g_can_rcv_timer = 10;
}


// --------------------------------------------------------------------
// MoTeC2初期化
// --------------------------------------------------------------------
static void Init_MoTeC2(void)
{
	// --------------------------------------------------------------------
	// CAN割り込み禁止
	// --------------------------------------------------------------------
	RX0IE_Disable;
	RX1IE_Disable;
//	ERRIE_Disable;
//	WAKIE_Disable;
//	MERRE_Disable;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	CANInit(CAN_BRP_20MHz_1MBPS);
	
	// --------------------------------------------------------------------
	// CANフィルター設定
	// --------------------------------------------------------------------
	CANSetSidFilter0(0x00E8);
	CANSetSidFilter1(0x00E8);
	CANSetSidFilter2(0x00E8);
	CANSetSidFilter3(0x00E8);
	CANSetSidFilter4(0x00E8);
	CANSetSidFilter5(0x00E8);
	CANSetSidMask0(0xFFF0);
	CANSetSidMask1(0xFFF0);
	
	CANSetFilterRxB0(1);
	CANSetFilterRxB1(1);
	
	// --------------------------------------------------------------------
	// CANモード切替
	// --------------------------------------------------------------------
	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
	
	// --------------------------------------------------------------------
	// CAN割り込み許可
	// --------------------------------------------------------------------
	RX0IE_Enable;
	RX1IE_Enable;
//	ERRIE_Enable;
//	WAKIE_Enable;
//	MERRE_Enable;
}

// --------------------------------------------------------------------
// Haltech1初期化
// --------------------------------------------------------------------
static void Init_Haltech1(void)
{
	// --------------------------------------------------------------------
	// SCI5停止
	// --------------------------------------------------------------------
	SCI5.SCR.BIT.TE  = 0;
	SCI5.SCR.BIT.RE  = 0;
	
	// --------------------------------------------------------------------
	// CAN割り込み禁止
	// --------------------------------------------------------------------
	RX0IE_Disable;
	RX1IE_Disable;
//	ERRIE_Disable;
//	WAKIE_Disable;
//	MERRE_Disable;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	CANInit(CAN_BRP_20MHz_1MBPS);
	
	// --------------------------------------------------------------------
	// CANフィルター設定
	// --------------------------------------------------------------------
	CANSetSidFilter0(0x0010);
	CANSetSidFilter1(0x0010);
	CANSetSidFilter2(0x0010);
	CANSetSidFilter3(0x0010);
	CANSetSidFilter4(0x0010);
	CANSetSidFilter5(0x0010);
	CANSetSidMask0(0xFFF0);
	CANSetSidMask1(0xFFF0);
	
	CANSetFilterRxB0(1);
	CANSetFilterRxB1(1);
	
	// --------------------------------------------------------------------
	// CANモード切替
	// --------------------------------------------------------------------
	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
	
	// --------------------------------------------------------------------
	// CAN割り込み許可
	// --------------------------------------------------------------------
	RX0IE_Enable;
	RX1IE_Enable;
//	ERRIE_Enable;
//	WAKIE_Enable;
//	MERRE_Enable;
}

// --------------------------------------------------------------------
// Haltech2初期化
// --------------------------------------------------------------------
static void Init_Haltech2(void)
{
	// --------------------------------------------------------------------
	// SCI5停止
	// --------------------------------------------------------------------
	SCI5.SCR.BIT.TE  = 0;
	SCI5.SCR.BIT.RE  = 0;
	
	// --------------------------------------------------------------------
	// CAN割り込み禁止
	// --------------------------------------------------------------------
	RX0IE_Disable;
	RX1IE_Disable;
//	ERRIE_Disable;
//	WAKIE_Disable;
//	MERRE_Disable;
	
	// --------------------------------------------------------------------
	// CAN初期化
	// --------------------------------------------------------------------
	CANInit(CAN_BRP_20MHz_1MBPS);
	
	// --------------------------------------------------------------------
	// CANフィルター設定
	// --------------------------------------------------------------------
	CANSetSidFilter0(0x0300);
	CANSetSidFilter1(0x0300);
	CANSetSidFilter2(0x0300);
	CANSetSidFilter3(0x0300);
	CANSetSidFilter4(0x0300);
	CANSetSidFilter5(0x0300);
	CANSetSidMask0(0xFF00);
	CANSetSidMask1(0xFF00);
	
	CANSetFilterRxB0(1);
	CANSetFilterRxB1(1);
	
	// --------------------------------------------------------------------
	// CANモード切替
	// --------------------------------------------------------------------
	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
	
	// --------------------------------------------------------------------
	// CAN割り込み許可
	// --------------------------------------------------------------------
	RX0IE_Enable;
	RX1IE_Enable;
//	ERRIE_Enable;
//	WAKIE_Enable;
//	MERRE_Enable;
}

// --------------------------------------------------------------------
// Freedom2初期化
// --------------------------------------------------------------------
static void Init_Freedom2(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	volatile unsigned long i;
	
	// --------------------------------------------------------------------
	// 送信FIFO変数初期化
	// --------------------------------------------------------------------
	gUART_FIFO_Tx_WP = 0;
	gUART_FIFO_Tx_RP = 0;
	gUART_FIFO_Tx_DC = 0;
	
	// --------------------------------------------------------------------
	// 受信一時レジスタ初期化
	// --------------------------------------------------------------------
	for(i = 0; i < 154; i++ ) sci_rcv[i] = 0x00;
	sci_rcv_pointer = 0;
	
	INTC.IPRQ.BIT._SCI5 = 6;
	
	SCI5.SCR.BIT.TE  = 0;
	SCI5.SCR.BIT.RE  = 0;
	SCI5.SCR.BIT.CKE = 0;
	SCI5.SMR.BYTE = 0x60;  //01100000
	SCI5.SEMR.BIT.ABCS = 0;
	SCI5.BRR = 77;
	
	for (i = 0; i < 30000 / 20; i++);
	
	SCI5.SCR.BIT.RIE = 1;
	
	// --------------------------------------------------------------------
	// SCI5開始
	// --------------------------------------------------------------------
	SCI5.SCR.BIT.TE  = 1;
	SCI5.SCR.BIT.RE  = 1;
}

// --------------------------------------------------------------------
// MSquirt1初期化
// --------------------------------------------------------------------
static void Init_MSquirt1(void)
{
	// --------------------------------------------------------------------
	// ローカル変数宣言
	// --------------------------------------------------------------------
	volatile unsigned long i;
	
	// --------------------------------------------------------------------
	// 送信FIFO変数初期化
	// --------------------------------------------------------------------
	gUART_FIFO_Tx_WP = 0;
	gUART_FIFO_Tx_RP = 0;
	gUART_FIFO_Tx_DC = 0;
	
	// --------------------------------------------------------------------
	// 受信一時レジスタ初期化
	// --------------------------------------------------------------------
	for(i = 0; i < 154; i++ ) sci_rcv[i] = 0x00;
	sci_rcv_pointer = 0;
	
	INTC.IPRQ.BIT._SCI5 = 6;
	
	SCI5.SCR.BIT.TE  = 0;
	SCI5.SCR.BIT.RE  = 0;
	SCI5.SCR.BIT.CKE = 0;
	SCI5.SMR.BYTE = 0x00;  //00000000
//	SCI5.SEMR.BIT.ABCS = 1;
//	SCI5.BRR = 12;
	SCI5.SEMR.BIT.ABCS = 0;
	SCI5.BRR = 19;
	
	for (i = 0; i < 30000 / 20; i++);
	
	SCI5.SCR.BIT.RIE = 1;
	
	// --------------------------------------------------------------------
	// SCI5開始
	// --------------------------------------------------------------------
	SCI5.SCR.BIT.TE  = 1;
	SCI5.SCR.BIT.RE  = 1;
}

// --------------------------------------------------------------------
// 標準CANプリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_CAN(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      0; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=      5; g_e2p_data.E2P_3.afr_gain  =    147; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=     18;
	g_e2p_data.E2P_4.num1_data_select			=      4; g_e2p_data.E2P_4.num1_gain =   1000; g_e2p_data.E2P_4.num1_bias =      0; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=      3; g_e2p_data.E2P_4.num2_gain =   1000; g_e2p_data.E2P_4.num2_bias =      0; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     15; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 2; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=      2; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=      1; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     21; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 1; g_e2p_data.E2P_6.num6_label = 15; g_e2p_data.E2P_6.num6_unit =  3;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=    900;
	g_e2p_data.E2P_8.cht1_data_select			=      0; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=      1; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}

// --------------------------------------------------------------------
// MoTeC1プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_MoTeC1(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=     24; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=     29; g_e2p_data.E2P_3.afr_gain  =    147; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=     42;
	g_e2p_data.E2P_4.num1_data_select			=     28; g_e2p_data.E2P_4.num1_gain =   1000; g_e2p_data.E2P_4.num1_bias =      0; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=     27; g_e2p_data.E2P_4.num2_gain =   1000; g_e2p_data.E2P_4.num2_bias =      0; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     39; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 2; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=     26; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=     25; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     45; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 1; g_e2p_data.E2P_6.num6_label = 15; g_e2p_data.E2P_6.num6_unit =  3;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=    900;
	g_e2p_data.E2P_8.cht1_data_select			=     24; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=     25; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}

/*
// --------------------------------------------------------------------
// MoTeC2プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_MoTeC2(void)
{
	//
}
*/

// --------------------------------------------------------------------
// Haltech1プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_Haltech1(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      1; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=      2; g_e2p_data.E2P_3.afr_gain  =    147; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=      0;
	g_e2p_data.E2P_4.num1_data_select			=     26; g_e2p_data.E2P_4.num1_gain =   1000; g_e2p_data.E2P_4.num1_bias =      0; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=     31; g_e2p_data.E2P_4.num2_gain =   1000; g_e2p_data.E2P_4.num2_bias =      0; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     28; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 2; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=     30; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=     29; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     35; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 0; g_e2p_data.E2P_6.num6_label = 15; g_e2p_data.E2P_6.num6_unit =  3;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=    900;
	g_e2p_data.E2P_8.cht1_data_select			=     23; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=     29; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}

// --------------------------------------------------------------------
// Haltech2プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_Haltech2(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      2; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=      3; g_e2p_data.E2P_3.afr_gain  =    147; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=      0;
	g_e2p_data.E2P_4.num1_data_select			=     51; g_e2p_data.E2P_4.num1_gain =   1000; g_e2p_data.E2P_4.num1_bias =  -2731; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=     52; g_e2p_data.E2P_4.num2_gain =   1000; g_e2p_data.E2P_4.num2_bias =  -2731; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     47; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 2; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=     37; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=     38; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     41; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 1; g_e2p_data.E2P_6.num6_label = 15; g_e2p_data.E2P_6.num6_unit =  3;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=    900;
	g_e2p_data.E2P_8.cht1_data_select			=     36; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=     38; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}

// --------------------------------------------------------------------
// Freedom1プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_Freedom1(void)
{
	//
}

// --------------------------------------------------------------------
// Freedom2プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_Freedom2(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      3; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=      4; g_e2p_data.E2P_3.afr_gain  =   1000; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=      3;
	g_e2p_data.E2P_4.num1_data_select			=     57; g_e2p_data.E2P_4.num1_gain =   1000; g_e2p_data.E2P_4.num1_bias =      0; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=     58; g_e2p_data.E2P_4.num2_gain =   1000; g_e2p_data.E2P_4.num2_bias =      0; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     61; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 1; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=     56; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=     60; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     64; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 0; g_e2p_data.E2P_6.num6_label = 16; g_e2p_data.E2P_6.num6_unit =  0;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=     45;
	g_e2p_data.E2P_8.cht1_data_select			=     55; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=     60; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}

/*
// --------------------------------------------------------------------
// MegaSquirt1プリセット読み込み
// --------------------------------------------------------------------
static void Preset_load_MegaSquirt1(void)
{
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      4; g_e2p_data.E2P_3.rev_gain  =   1000; g_e2p_data.E2P_3.rev_bias  =      0;
	g_e2p_data.E2P_3.afr_data_select			=      5; g_e2p_data.E2P_3.afr_gain  =   1000; g_e2p_data.E2P_3.afr_bias  =      0; g_e2p_data.E2P_3.afr_dp  = 1; g_e2p_data.E2P_3.afr_label  =  1;
	g_e2p_data.E2P_3.t_afr_data_select			=      4;
	g_e2p_data.E2P_4.num1_data_select			=     87; g_e2p_data.E2P_4.num1_gain =    556; g_e2p_data.E2P_4.num1_bias =   -320; g_e2p_data.E2P_4.num1_dp = 1; g_e2p_data.E2P_4.num1_label =  4; g_e2p_data.E2P_4.num1_unit =  1;
	g_e2p_data.E2P_4.num2_data_select			=     88; g_e2p_data.E2P_4.num2_gain =    556; g_e2p_data.E2P_4.num2_bias =   -320; g_e2p_data.E2P_4.num2_dp = 1; g_e2p_data.E2P_4.num2_label =  5; g_e2p_data.E2P_4.num2_unit =  1;
	g_e2p_data.E2P_5.num3_data_select			=     89; g_e2p_data.E2P_5.num3_gain =   1000; g_e2p_data.E2P_5.num3_bias =      0; g_e2p_data.E2P_5.num3_dp = 1; g_e2p_data.E2P_5.num3_label =  8; g_e2p_data.E2P_5.num3_unit =  2;
	g_e2p_data.E2P_5.num4_data_select			=     85; g_e2p_data.E2P_5.num4_gain =   1000; g_e2p_data.E2P_5.num4_bias =      0; g_e2p_data.E2P_5.num4_dp = 0; g_e2p_data.E2P_5.num4_label = 12; g_e2p_data.E2P_5.num4_unit =  4;
	g_e2p_data.E2P_6.num5_data_select			=     88; g_e2p_data.E2P_6.num5_gain =   1000; g_e2p_data.E2P_6.num5_bias =      0; g_e2p_data.E2P_6.num5_dp = 1; g_e2p_data.E2P_6.num5_label = 10; g_e2p_data.E2P_6.num5_unit =  3;
	g_e2p_data.E2P_6.num6_data_select			=     81; g_e2p_data.E2P_6.num6_gain =   1000; g_e2p_data.E2P_6.num6_bias =      0; g_e2p_data.E2P_6.num6_dp = 1; g_e2p_data.E2P_6.num6_label = 16; g_e2p_data.E2P_6.num6_unit =  0;
	g_e2p_data.E2P_7.num1_warning				=   1050;
	g_e2p_data.E2P_7.num2_warning				=    700;
	g_e2p_data.E2P_7.num3_warning				=   1600;
	g_e2p_data.E2P_7.num4_warning				=   1500;
	g_e2p_data.E2P_7.num5_warning				=   1100;
	g_e2p_data.E2P_7.num6_warning				=    450;
	g_e2p_data.E2P_8.cht1_data_select			=     80; g_e2p_data.E2P_8.cht1_gain =   1000; g_e2p_data.E2P_8.cht1_bias =      0; g_e2p_data.E2P_8.cht1_dp = 0; g_e2p_data.E2P_8.cht1_label =  3;
	g_e2p_data.E2P_8.cht2_data_select			=     88; g_e2p_data.E2P_8.cht2_gain =   1000; g_e2p_data.E2P_8.cht2_bias =      0; g_e2p_data.E2P_8.cht2_dp = 1; g_e2p_data.E2P_8.cht2_label = 10;
	g_e2p_data.E2P_9.cht1_guage_gain			=     25; g_e2p_data.E2P_9.cht1_guage_bias = 0; g_e2p_data.E2P_9.cht1_guage_grid = 7;
	g_e2p_data.E2P_9.cht2_guage_gain			=    200; g_e2p_data.E2P_9.cht2_guage_bias = 0; g_e2p_data.E2P_9.cht2_guage_grid = 9;
}
*/

// --------------------------------------------------------------------
// EEPROM 全書き込み
// --------------------------------------------------------------------
static void Save_EEPROM_ALL(void)
{
	mtrs_start((const unsigned char *)&g_e2p_data + 0x00, 0x00, 16);	// E2P_1
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x10, 0x10, 16);	// E2P_2
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x20, 0x20, 16);	// E2P_3
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x30, 0x30, 16);	// E2P_4
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x40, 0x40, 16);	// E2P_5
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x50, 0x50, 16);	// E2P_6
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x60, 0x60, 16);	// E2P_7
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x70, 0x70, 16);	// E2P_8
	g_int50mscnt =  -4;		// ピリオド50ms x   6 = 0.2s 待機
	while(g_int50mscnt < 0);
	mtrs_start((const unsigned char *)&g_e2p_data + 0x80, 0x80, 16);	// E2P_9

}
// --------------------------------------------------------------------
// 表示数値計算
// --------------------------------------------------------------------
static int num_calc(unsigned char num_calc_data_select, int num_calc_bias, int num_calc_gain)
{
	int val;
	
	val = ((long)(num_data_select(num_calc_data_select)) + num_calc_bias ) * num_calc_gain  / 1000;
	
	return val;

}
