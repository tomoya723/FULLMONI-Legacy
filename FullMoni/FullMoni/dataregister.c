// --------------------------------------------------------------------
// Copylight (C) 2013, Tomoya Sato( http://pub.ne.jp/nacci_tomoya )
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
// filename		:	dataregister.c
// brief		:	FullMoni rev.B データ管理
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "dataregister.h"

// --------------------------------------------------------------------
// EEPROMデータ 初期化
// --------------------------------------------------------------------
void Init_e2p_data(void)
{
	g_e2p_data.E2P_1.E2Pmanage.BIT.WROK			=      0;
	g_e2p_data.E2P_1.model						=   0x00;
	g_e2p_data.E2P_1.control.BIT.beep_on		=      0;
	g_e2p_data.E2P_1.control.BIT.ms_on			=      0;
	g_e2p_data.E2P_1.control.BIT.fclogger_on	=      0;
	g_e2p_data.E2P_1.control.BIT.defi_on		=      0;
	g_e2p_data.E2P_1.tp_Xmin					=   0x00;
	g_e2p_data.E2P_1.tp_Xmax					=   0x00;
	g_e2p_data.E2P_1.tp_Ymin					=   0x00;
	g_e2p_data.E2P_1.tp_Ymax					=   0x00;
	g_e2p_data.E2P_1.dimmer1					=   0x00;
	g_e2p_data.E2P_1.dimmer2					=   0x00;
	g_e2p_data.E2P_2.rev_timing_rmp1			=   6250;
	g_e2p_data.E2P_2.rev_timing_rmp2			=   6500;
	g_e2p_data.E2P_2.rev_timing_rmp3			=   6750;
	g_e2p_data.E2P_3.rev_data_select			=      0;
	g_e2p_data.E2P_3.rev_gain					= 0x0000;
	g_e2p_data.E2P_3.rev_bias					= 0x0000;
	g_e2p_data.E2P_3.afr_data_select			=      0;
	g_e2p_data.E2P_3.afr_gain					= 0x0000;
	g_e2p_data.E2P_3.afr_bias					= 0x0000;
	g_e2p_data.E2P_3.afr_dp						=      0;
	g_e2p_data.E2P_3.afr_label					=      0;
	g_e2p_data.E2P_4.num1_data_select			=      0;
	g_e2p_data.E2P_4.num1_gain					= 0x0000;
	g_e2p_data.E2P_4.num1_bias					= 0x0000;
	g_e2p_data.E2P_4.num1_dp					=      0;
	g_e2p_data.E2P_4.num1_label					=      0;
	g_e2p_data.E2P_4.num1_unit					=      0;
	g_e2p_data.E2P_4.num2_data_select			=      0;
	g_e2p_data.E2P_4.num2_gain					= 0x0000;
	g_e2p_data.E2P_4.num2_bias					= 0x0000;
	g_e2p_data.E2P_4.num2_dp					=      0;
	g_e2p_data.E2P_4.num2_label					=      0;
	g_e2p_data.E2P_4.num2_unit					=      0;
	g_e2p_data.E2P_5.num3_data_select			=      0;
	g_e2p_data.E2P_5.num3_gain					= 0x0000;
	g_e2p_data.E2P_5.num3_bias					= 0x0000;
	g_e2p_data.E2P_5.num3_dp					=      0;
	g_e2p_data.E2P_5.num3_label					=      0;
	g_e2p_data.E2P_5.num3_unit					=      0;
	g_e2p_data.E2P_5.num4_data_select			=      0;
	g_e2p_data.E2P_5.num4_gain					= 0x0000;
	g_e2p_data.E2P_5.num4_bias					= 0x0000;
	g_e2p_data.E2P_5.num4_dp					=      0;
	g_e2p_data.E2P_5.num4_label					=      0;
	g_e2p_data.E2P_5.num4_unit					=      0;
	g_e2p_data.E2P_6.num5_data_select			=      0;
	g_e2p_data.E2P_6.num5_gain					= 0x0000;
	g_e2p_data.E2P_6.num5_bias					= 0x0000;
	g_e2p_data.E2P_6.num5_dp					=      0;
	g_e2p_data.E2P_6.num5_label					=      0;
	g_e2p_data.E2P_6.num5_unit					=      0;
	g_e2p_data.E2P_6.num6_data_select			=      0;
	g_e2p_data.E2P_6.num6_gain					= 0x0000;
	g_e2p_data.E2P_6.num6_bias					= 0x0000;
	g_e2p_data.E2P_6.num6_dp					=      0;
	g_e2p_data.E2P_6.num6_label					=      0;
	g_e2p_data.E2P_6.num6_unit					=      0;
	g_e2p_data.E2P_7.num1_warning				= 0xFFFF;
	g_e2p_data.E2P_7.num2_warning				= 0xFFFF;
	g_e2p_data.E2P_7.num3_warning				= 0xFFFF;
	g_e2p_data.E2P_7.num4_warning				= 0xFFFF;
	g_e2p_data.E2P_7.num5_warning				= 0xFFFF;
	g_e2p_data.E2P_7.num6_warning				= 0xFFFF;
}
// --------------------------------------------------------------------
// MoTeC m#00系データ 初期化
// --------------------------------------------------------------------
void Init_MoTeC1_data(void)
{
	g_MoTeC1_data.RPM						= 2500;
	g_MoTeC1_data.GroundSpeed				=  200;
	g_MoTeC1_data.OilPressure				=   40;
	g_MoTeC1_data.EngineTemp				=  800;
	g_MoTeC1_data.FuelPressure				=   30;
	g_MoTeC1_data.BatteryVoltage			= 1250;
	g_MoTeC1_data.ThrottlePosition			=  800;
	g_MoTeC1_data.ManifoldPressure			=  500;
	g_MoTeC1_data.InletAirTemp				=  200;
	g_MoTeC1_data.Lambda					= 1000;
	g_MoTeC1_data.IgnitionAdvance			=  200;
	g_MoTeC1_data.Gear						=    1;
	g_MoTeC1_data.InjectorDuty				=   10;
}

// --------------------------------------------------------------------
// Haltech E8データ初期化
// --------------------------------------------------------------------
void Init_Haltech1_data(void)
{
	g_Haltech1_data.RPM						= 2500;
	g_Haltech1_data.GroundSpeed				=  200;
	g_Haltech1_data.OilPressure				=   40;
	g_Haltech1_data.EngineTemp				=  800;
	g_Haltech1_data.FuelPressure			=   30;
	g_Haltech1_data.BatteryVoltage			= 1250;
	g_Haltech1_data.ThrottlePosition		=  800;
	g_Haltech1_data.ManifoldPressure		=  500;
	g_Haltech1_data.InletAirTemp			=  200;
	g_Haltech1_data.Lambda					= 1000;
	g_Haltech1_data.IgnitionAdvance			=  200;
	g_Haltech1_data.Gear					=    1;
	g_Haltech1_data.InjectorDuty			=   10;
}

// --------------------------------------------------------------------
// Haltech SPORT系データ初期化
// --------------------------------------------------------------------
void Init_Haltech2_data(void)
{
	g_Haltech2_data.RPM						= 2500;
	g_Haltech2_data.ManifoldPressure		=  500;
	g_Haltech2_data.ThrottlePosition		=  800;
	g_Haltech2_data.FuelPressure			=   30;
	g_Haltech2_data.OilPressure				=   40;
	g_Haltech2_data.InjectorDuty			=   10;
	g_Haltech2_data.IgnitionAdvance1		=  200;
	g_Haltech2_data.IgnitionAdvance2		=  200;
	g_Haltech2_data.Lambda					= 1000;
	g_Haltech2_data.GroundSpeed				=  200;
	g_Haltech2_data.Gear					=    1;
	g_Haltech2_data.InletAirTemp2			=  200;
	g_Haltech2_data.BatteryVoltage			= 1250;
	g_Haltech2_data.BaroPressure			=  980;
	g_Haltech2_data.EGT						= 1100;
	g_Haltech2_data.OilTemp					= 1200;
	g_Haltech2_data.EngineTemp				=  800;
	g_Haltech2_data.InletAirTemp1			=  200;
	g_Haltech2_data.FuelTemp				=  700;
}
// --------------------------------------------------------------------
// Freedom Ver3.XXデータ初期化
// --------------------------------------------------------------------
void Init_Freedom2_data(void)
{
	g_Freedom2_data.RPM					= 2500;
	g_Freedom2_data.ManifoldPressure	=  200;
	g_Freedom2_data.EngineTemp			=  800;
	g_Freedom2_data.InletAirTemp		=  200;
	g_Freedom2_data.BarometricPressure	= 1080;
	g_Freedom2_data.ThrottlePosition	=  800;
	g_Freedom2_data.BatteryVoltage		=  125;
	g_Freedom2_data.ValidFuelTime		=  500;
	g_Freedom2_data.InvalidFuelTime		=  500;
	g_Freedom2_data.IgnitionAdvance		=   20;
	g_Freedom2_data.Status				=    0;
	g_Freedom2_data.GroundSpeed			= 2000;
	g_Freedom2_data.Lambda				=   10;
}

// --------------------------------------------------------------------
// レブゲージデータ選択
// --------------------------------------------------------------------
unsigned int rev_data_select(unsigned char rev_data_select)
{
	switch(rev_data_select)
	{
		default:
		case  0:	return g_MoTeC1_data.RPM;					break;
		case  1:	return g_Haltech1_data.RPM;					break;
	}
}

// --------------------------------------------------------------------
// 空燃比ゲージデータ選択
// --------------------------------------------------------------------
unsigned int afr_data_select(unsigned char afr_data_select)
{
	switch(afr_data_select)
	{
		default:
		case  0:	return g_MoTeC1_data.Lambda;				break;
		case  1:	return g_Haltech1_data.Lambda;				break;
		case  2:	return g_Haltech2_data.Lambda;				break;
	}
}

// --------------------------------------------------------------------
// 数値ゲージデータ選択
// --------------------------------------------------------------------
unsigned int num_data_select(unsigned char num_data_select)
{
	switch(num_data_select)
	{
		default:
		case  0:	return g_MoTeC1_data.RPM;					break;
		case  1:	return g_MoTeC1_data.GroundSpeed;			break;
		case  2:	return g_MoTeC1_data.OilPressure;			break;
		case  3:	return g_MoTeC1_data.EngineTemp;			break;
		case  4:	return g_MoTeC1_data.FuelPressure;			break;
		case  5:	return g_MoTeC1_data.BatteryVoltage;		break;
		case  6:	return g_MoTeC1_data.ThrottlePosition;		break;
		case  7:	return g_MoTeC1_data.ManifoldPressure;		break;
		case  8:	return g_MoTeC1_data.InletAirTemp;			break;
		case  9:	return g_MoTeC1_data.Lambda;				break;
		case 10:	return g_MoTeC1_data.IgnitionAdvance;		break;
		case 11:	return g_MoTeC1_data.Gear;					break;
		case 12:	return g_MoTeC1_data.InjectorDuty;			break;
		case 13:	return g_Haltech1_data.RPM;					break;
		case 14:	return g_Haltech1_data.GroundSpeed;			break;
		case 15:	return g_Haltech1_data.OilPressure;			break;
		case 16:	return g_Haltech1_data.EngineTemp;			break;
		case 17:	return g_Haltech1_data.FuelPressure;		break;
		case 18:	return g_Haltech1_data.BatteryVoltage;		break;
		case 19:	return g_Haltech1_data.ThrottlePosition;	break;
		case 20:	return g_Haltech1_data.ManifoldPressure;	break;
		case 21:	return g_Haltech1_data.InletAirTemp;		break;
		case 22:	return g_Haltech1_data.Lambda;				break;
		case 23:	return g_Haltech1_data.IgnitionAdvance;		break;
		case 24:	return g_Haltech1_data.Gear;				break;
		case 25:	return g_Haltech1_data.InjectorDuty;		break;
		case 26:	return g_Haltech2_data.RPM;					break;
		case 27:	return g_Haltech2_data.ManifoldPressure;	break;
		case 28:	return g_Haltech2_data.ThrottlePosition;	break;
		case 29:	return g_Haltech2_data.FuelPressure;		break;
		case 30:	return g_Haltech2_data.OilPressure;			break;
		case 31:	return g_Haltech2_data.InjectorDuty;		break;
		case 32:	return g_Haltech2_data.IgnitionAdvance1;	break;
		case 33:	return g_Haltech2_data.IgnitionAdvance2;	break;
		case 34:	return g_Haltech2_data.Lambda;				break;
		case 35:	return g_Haltech2_data.GroundSpeed;			break;
		case 36:	return g_Haltech2_data.Gear;				break;
		case 37:	return g_Haltech2_data.InletAirTemp2;		break;
		case 38:	return g_Haltech2_data.BatteryVoltage;		break;
		case 39:	return g_Haltech2_data.BaroPressure;		break;
		case 40:	return g_Haltech2_data.EGT;					break;
		case 41:	return g_Haltech2_data.OilTemp;				break;
		case 42:	return g_Haltech2_data.EngineTemp;			break;
		case 43:	return g_Haltech2_data.InletAirTemp1;		break;
	}
}

// --------------------------------------------------------------------
// レブゲージデータ選択描画
// --------------------------------------------------------------------
void rev_data_select_draw(unsigned char rev_data_select_draw)
{
	switch(rev_data_select_draw)
	{
		default:
		case  0:	LCD_textout("< MoTeC1.RPM               >");	break;
		case  1:	LCD_textout("< Haltech1.RPM             >");	break;
		case  2:	LCD_textout("< Haltech2.RPM             >");	break;
	}
}

// --------------------------------------------------------------------
// 空燃比ゲージデータ選択描画
// --------------------------------------------------------------------
void afr_data_select_draw(unsigned char afr_data_select_draw)
{
	switch(afr_data_select_draw)
	{
		default:
		case  0:	LCD_textout("< MoTeC1.Lambda            >");	break;
		case  1:	LCD_textout("< Haltech1.Lambda          >");	break;
		case  2:	LCD_textout("< Haltech2.Lambda          >");	break;
	}
}

// --------------------------------------------------------------------
// 数値ゲージデータ選択描画
// --------------------------------------------------------------------
void num_data_select_draw(unsigned char num_data_select_draw)
{
	switch(num_data_select_draw)
	{
		default:
		case  0:	LCD_textout("< MoTeC1.RPM               >");	break;
		case  1:	LCD_textout("< MoTeC1.GroundSpeed       >");	break;
		case  2:	LCD_textout("< MoTeC1.OilPressure       >");	break;
		case  3:	LCD_textout("< MoTeC1.EngineTemp        >");	break;
		case  4:	LCD_textout("< MoTeC1.FuelPressure      >");	break;
		case  5:	LCD_textout("< MoTeC1.BatteryVoltage    >");	break;
		case  6:	LCD_textout("< MoTeC1.ThrottlePosition  >");	break;
		case  7:	LCD_textout("< MoTeC1.ManifoldPressure  >");	break;
		case  8:	LCD_textout("< MoTeC1.InletAirTemp      >");	break;
		case  9:	LCD_textout("< MoTeC1.Lambda            >");	break;
		case 10:	LCD_textout("< MoTeC1.IgnitionAdvance   >");	break;
		case 11:	LCD_textout("< MoTeC1.Gear              >");	break;
		case 12:	LCD_textout("< MoTeC1.InjectorDuty      >");	break;
		case 13:	LCD_textout("< Haltech1.RPM             >");	break;
		case 14:	LCD_textout("< Haltech1.GroundSpeed     >");	break;
		case 15:	LCD_textout("< Haltech1.OilPressure     >");	break;
		case 16:	LCD_textout("< Haltech1.EngineTemp      >");	break;
		case 17:	LCD_textout("< Haltech1.FuelPressure    >");	break;
		case 18:	LCD_textout("< Haltech1.BatteryVoltage  >");	break;
		case 19:	LCD_textout("< Haltech1.ThrottlePosition>");	break;
		case 20:	LCD_textout("< Haltech1.ManifoldPressure>");	break;
		case 21:	LCD_textout("< Haltech1.InletAirTemp    >");	break;
		case 22:	LCD_textout("< Haltech1.Lambda          >");	break;
		case 23:	LCD_textout("< Haltech1.IgnitionAdvance >");	break;
		case 24:	LCD_textout("< Haltech1.Gear            >");	break;
		case 25:	LCD_textout("< Haltech1.InjectorDuty    >");	break;
		case 26:	LCD_textout("< Haltech2.RPM             >");	break;
		case 27:	LCD_textout("< Haltech2.ManifoldPressure>");	break;
		case 28:	LCD_textout("< Haltech2.ThrottlePosition>");	break;
		case 29:	LCD_textout("< Haltech2.FuelPressure    >");	break;
		case 30:	LCD_textout("< Haltech2.OilPressure     >");	break;
		case 31:	LCD_textout("< Haltech2.InjectorDuty    >");	break;
		case 32:	LCD_textout("< Haltech2.IgnitionAdvance1>");	break;
		case 33:	LCD_textout("< Haltech2.IgnitionAdvance2>");	break;
		case 34:	LCD_textout("< Haltech2.Lambda          >");	break;
		case 35:	LCD_textout("< Haltech2.GroundSpeed     >");	break;
		case 36:	LCD_textout("< Haltech2.Gear            >");	break;
		case 37:	LCD_textout("< Haltech2.InletAirTemp2   >");	break;
		case 38:	LCD_textout("< Haltech2.BatteryVoltage  >");	break;
		case 39:	LCD_textout("< Haltech2.BaroPressure    >");	break;
		case 40:	LCD_textout("< Haltech2.EGT             >");	break;
		case 41:	LCD_textout("< Haltech2.OilTemp         >");	break;
		case 42:	LCD_textout("< Haltech2.EngineTemp      >");	break;
		case 43:	LCD_textout("< Haltech2.InletAirTemp1   >");	break;
	}
}

// --------------------------------------------------------------------
// 数値ゲージ小数点位置選択描画
// --------------------------------------------------------------------
void num_dp_draw(unsigned char num_dp)
{
	switch(num_dp)
	{
		case  0:	LCD_textout("< 0         >");	break;
		case  1:	LCD_textout("< 1         >");	break;
		case  2:	LCD_textout("< 2         >");	break;
		case  3:	LCD_textout("< 3         >");	break;
	}
	
	return;
}

// --------------------------------------------------------------------
// 数値ゲージラベル選択描画
// --------------------------------------------------------------------
void num_label_draw(unsigned char num_tag)
{
	switch(num_tag)
	{
		default:
		case  0:	LCD_textout("      ");	break;
		case  1:	LCD_textout("A/F   ");	break;
		case  2:	LCD_textout("LAMBDA");	break;
		case  3:	LCD_textout("RPM   ");	break;
		case  4:	LCD_textout("Etemp ");	break;
		case  5:	LCD_textout("Atemp ");	break;
		case  6:	LCD_textout("Otemp ");	break;
		case  7:	LCD_textout("EXTemp");	break;
		case  8:	LCD_textout("BATT  ");	break;
		case  9:	LCD_textout("SPEED ");	break;
		case 10:	LCD_textout("TPS   ");	break;
		case 11:	LCD_textout("GEAR  ");	break;
		case 12:	LCD_textout("MAP   ");	break;
		case 13:	LCD_textout("Opress");	break;
		case 14:	LCD_textout("Fpress");	break;
		case 15:	LCD_textout("IJduty");	break;
		case 16:	LCD_textout("IGadv ");	break;
	}
	
	return;
}

// --------------------------------------------------------------------
// 数値ゲージ単位選択描画
// --------------------------------------------------------------------
void num_unit_draw(unsigned char num_unit)
{
	switch(num_unit)
	{
		default:
		case  0:	LCD_CHR_Copy_Smallfont(' ');	break;
		case  1:	LCD_CHR_Copy_Smallfont(0x7F);	break;
		case  2:	LCD_CHR_Copy_Smallfont('V');	break;
		case  3:	LCD_CHR_Copy_Smallfont('%');	break;
		case  4:	LCD_CHR_Copy_Smallfont('K');	break;
	}
}
