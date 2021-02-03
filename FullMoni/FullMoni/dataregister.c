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
// filename		:	dataregister.c
// brief		:	FullMoni rev.C データ管理
// author		:	Tomoya Sato
// update		:	2021/02/02
// version		:	1.05
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
	g_e2p_data.E2P_1.control.BIT.FC_mode		=      0;
	g_e2p_data.E2P_1.control.BIT.defi_on		=      0;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch1		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch2		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch3		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch4		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch5		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.CAN_ch6		=      1;
	g_e2p_data.E2P_1.CANcontrol.BIT.BAUD		=      1;
	g_e2p_data.E2P_1.CAN_ID1					=   1000;
	g_e2p_data.E2P_1.CAN_ID2					=   1001;
	g_e2p_data.E2P_1.CAN_ID3					=   1002;
	g_e2p_data.E2P_1.CAN_ID4					=   1003;
	g_e2p_data.E2P_1.CAN_ID5					=   1004;
	g_e2p_data.E2P_1.CAN_ID6					=   1005;
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
	g_e2p_data.E2P_3.t_afr_data_select			=      0;
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
	g_e2p_data.E2P_8.cht1_data_select			=      0;
	g_e2p_data.E2P_8.cht1_gain					= 0x0000;
	g_e2p_data.E2P_8.cht1_bias					= 0x0000;
	g_e2p_data.E2P_8.cht1_dp					=      0;
	g_e2p_data.E2P_8.cht1_label					=      0;
	g_e2p_data.E2P_8.cht2_data_select			=      0;
	g_e2p_data.E2P_8.cht2_gain					= 0x0000;
	g_e2p_data.E2P_8.cht2_bias					= 0x0000;
	g_e2p_data.E2P_8.cht2_dp					=      0;
	g_e2p_data.E2P_8.cht2_label					=      0;
	g_e2p_data.E2P_9.cht1_guage_gain			= 0x0000;
	g_e2p_data.E2P_9.cht1_guage_bias			= 0x0000;
	g_e2p_data.E2P_9.cht1_guage_grid			=      0;
	g_e2p_data.E2P_9.cht2_guage_gain			= 0x0000;
	g_e2p_data.E2P_9.cht2_guage_bias			= 0x0000;
	g_e2p_data.E2P_9.cht2_guage_grid			=      0;
}

// --------------------------------------------------------------------
// 標準CANデータ 初期化
// --------------------------------------------------------------------
void Init_CAN_data(void)
{
	g_CAN_data.ID1.DATA1					= 2500;
	g_CAN_data.ID1.DATA2					=  800;
	g_CAN_data.ID1.DATA3					=  500;
	g_CAN_data.ID1.DATA4					=  200;
	g_CAN_data.ID2.DATA1					=  800;
	g_CAN_data.ID2.DATA2					= 1000;
	g_CAN_data.ID2.DATA3					= 1000;
	g_CAN_data.ID2.DATA4					=  500;
	g_CAN_data.ID3.DATA1					=   50;
	g_CAN_data.ID3.DATA2					=  700;
	g_CAN_data.ID3.DATA3					=   30;
	g_CAN_data.ID3.DATA4					= 1000;
	g_CAN_data.ID4.DATA1					=   40;
	g_CAN_data.ID4.DATA2					=  950;
	g_CAN_data.ID4.DATA3					=  950;
	g_CAN_data.ID4.DATA4					= 1250;
	g_CAN_data.ID5.DATA1					=  400;
	g_CAN_data.ID5.DATA2					=  200;
	g_CAN_data.ID5.DATA3					=  850;
	g_CAN_data.ID5.DATA4					= 1000;
	g_CAN_data.ID6.DATA1					=  200;
	g_CAN_data.ID6.DATA2					=   10;
	g_CAN_data.ID6.DATA3					=    1;
	g_CAN_data.ID6.DATA4					=    1;
}

// --------------------------------------------------------------------
// MoTeC m#00系データ 初期化
// --------------------------------------------------------------------
void Init_MoTeC1_data(void)
{
	g_MoTeC1_data.RPM						= 2500;
	g_MoTeC1_data.ThrottlePosition			=  800;
	g_MoTeC1_data.ManifoldPressure			=  500;
	g_MoTeC1_data.InletAirTemp				=  200;
	g_MoTeC1_data.EngineTemp				=  800;
	g_MoTeC1_data.Lambda1					= 1000;
	g_MoTeC1_data.Lambda2					= 1000;
	g_MoTeC1_data.ExhaustPressure			=  500;
	g_MoTeC1_data.MassAirFlow				=   50;
	g_MoTeC1_data.FuelTemp					=  700;
	g_MoTeC1_data.FuelPressure				=   30;
	g_MoTeC1_data.OilTemp					= 1000;
	g_MoTeC1_data.OilPressure				=   40;
	g_MoTeC1_data.ExhaustTemp1				=  950;
	g_MoTeC1_data.ExhaustTemp2				=  950;
	g_MoTeC1_data.BatteryVoltage			= 1250;
	g_MoTeC1_data.ECUTemp					=  400;
	g_MoTeC1_data.GroundSpeed				=  200;
	g_MoTeC1_data.AimLambda1				=  850;
	g_MoTeC1_data.AimLambda2				= 1000;
	g_MoTeC1_data.IgnitionAdvance			=  200;
	g_MoTeC1_data.InjectorDuty				=   10;
	g_MoTeC1_data.Gear						=    1;
}

// --------------------------------------------------------------------
// Haltech E8/E11データ初期化
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
	g_Haltech2_data.BatteryVoltage			= 1250;
	g_Haltech2_data.InletAirTemp2			= 2931;
	g_Haltech2_data.BaroPressure			=  980;
	g_Haltech2_data.EGT						= 1100;
	g_Haltech2_data.EngineTemp				= 3531;
	g_Haltech2_data.InletAirTemp1			= 2931;
	g_Haltech2_data.FuelTemp				=  700;
	g_Haltech2_data.OilTemp					= 1200;
}
// --------------------------------------------------------------------
// Freedom Ver3.XXデータ初期化
// --------------------------------------------------------------------
void Init_Freedom2_data(void)
{
	g_Freedom2_data.RPM					= 2500;
	g_Freedom2_data.ManifoldPressure	=  500;
	g_Freedom2_data.EngineTemp			=  800;
	g_Freedom2_data.InletAirTemp		=  200;
	g_Freedom2_data.BarometricPressure	=  980;
	g_Freedom2_data.ThrottlePosition	=  800;
	g_Freedom2_data.BatteryVoltage		=  125;
	g_Freedom2_data.ValidFuelTime		=  500;
	g_Freedom2_data.InvalidFuelTime		=  500;
	g_Freedom2_data.IgnitionAdvance		=   20;
	g_Freedom2_data.Status				=    0;
	g_Freedom2_data.GroundSpeed			= 2000;
	g_Freedom2_data.AFR					=  123;
	g_Freedom2_data.TargetAFR			=  147;
	g_Freedom2_data.IATCorrection		=    0;
	g_Freedom2_data.ETCorrection		=    0;
	g_Freedom2_data.EStartCorrection	=    0;
	g_Freedom2_data.AccelCorrection		=    0;
	g_Freedom2_data.PowerCorrection		=    0;
	g_Freedom2_data.FeedbackCorrection	=    0;
	g_Freedom2_data.IdolCorrection		=    0;
	g_Freedom2_data.DecelCutCorrection	=    0;
	g_Freedom2_data.BaroCorrection		=    0;
	g_Freedom2_data.IdolIGCorrection	=    0;
	g_Freedom2_data.RetardCorrection	=    0;
}

/*
// --------------------------------------------------------------------
// MegaSquirt(MS2/Extra) データ初期化
// --------------------------------------------------------------------
void Init_MSquirt1_data(void)
{
	g_Megasquirt1_data.rpm				= 2500;
	g_Megasquirt1_data.advance			=  200;
	g_Megasquirt1_data.afrtgt1			=  147;
	g_Megasquirt1_data.afrtgt2			=  147;
	g_Megasquirt1_data.barometer		= 9800;
	g_Megasquirt1_data.map				=  500;
	g_Megasquirt1_data.mat				=  680;
	g_Megasquirt1_data.coolant			= 1760;
	g_Megasquirt1_data.tps				=  800;
	g_Megasquirt1_data.batteryVoltage	= 1250;
	g_Megasquirt1_data.afr1				=  147;
	g_Megasquirt1_data.afr2				=  147;
}
*/

/*
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
		case  2:	return g_Haltech2_data.RPM;					break;
		case  3:	return g_Freedom2_data.RPM;					break;
		case  4:	return g_Megasquirt1_data.rpm;				break;
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
		case  0:	return g_MoTeC1_data.Lambda1;				break;
		case  1:	return g_MoTeC1_data.Lambda2;				break;
		case  2:	return g_Haltech1_data.Lambda;				break;
		case  3:	return g_Haltech2_data.Lambda;				break;
		case  4:	return g_Freedom2_data.AFR;					break;
		case  5:	return g_Megasquirt1_data.afr1;				break;
		case  6:	return g_Megasquirt1_data.afr2;				break;
	}
}

// --------------------------------------------------------------------
// 目標空燃比ゲージデータ選択
// --------------------------------------------------------------------
unsigned int t_afr_data_select(unsigned char t_afr_data_select)
{
	switch(t_afr_data_select)
	{
		default:
		case  0:	return 1;									break;
		case  1:	return g_MoTeC1_data.AimLambda1;			break;
		case  2:	return g_MoTeC1_data.AimLambda2;			break;
		case  3:	return g_Freedom2_data.TargetAFR;			break;
		case  4:	return g_Megasquirt1_data.afrtgt1;			break;
		case  5:	return g_Megasquirt1_data.afrtgt1;			break;
	}
}
*/

// --------------------------------------------------------------------
// 数値ゲージデータ選択
// --------------------------------------------------------------------
unsigned int num_data_select(unsigned char num_data_select)
{
	switch(num_data_select)
	{
		default:
		case   0:	return g_CAN_data.ID1.DATA1;				break;
		case   1:	return g_CAN_data.ID1.DATA2;				break;
		case   2:	return g_CAN_data.ID1.DATA3;				break;
		case   3:	return g_CAN_data.ID1.DATA4;				break;
		case   4:	return g_CAN_data.ID2.DATA1;				break;
		case   5:	return g_CAN_data.ID2.DATA2;				break;
		case   6:	return g_CAN_data.ID2.DATA3;				break;
		case   7:	return g_CAN_data.ID2.DATA4;				break;
		case   8:	return g_CAN_data.ID3.DATA1;				break;
		case   9:	return g_CAN_data.ID3.DATA2;				break;
		case  10:	return g_CAN_data.ID3.DATA3;				break;
		case  11:	return g_CAN_data.ID3.DATA4;				break;
		case  12:	return g_CAN_data.ID4.DATA1;				break;
		case  13:	return g_CAN_data.ID4.DATA2;				break;
		case  14:	return g_CAN_data.ID4.DATA3;				break;
		case  15:	return g_CAN_data.ID4.DATA4;				break;
		case  16:	return g_CAN_data.ID5.DATA1;				break;
		case  17:	return g_CAN_data.ID5.DATA2;				break;
		case  18:	return g_CAN_data.ID5.DATA3;				break;
		case  19:	return g_CAN_data.ID5.DATA4;				break;
		case  20:	return g_CAN_data.ID6.DATA1;				break;
		case  21:	return g_CAN_data.ID6.DATA2;				break;
		case  22:	return g_CAN_data.ID6.DATA3;				break;
		case  23:	return g_CAN_data.ID6.DATA4;				break;
		case  24:	return g_MoTeC1_data.RPM;					break;
		case  25:	return g_MoTeC1_data.ThrottlePosition;		break;
		case  26:	return g_MoTeC1_data.ManifoldPressure;		break;
		case  27:	return g_MoTeC1_data.InletAirTemp;			break;
		case  28:	return g_MoTeC1_data.EngineTemp;			break;
		case  29:	return g_MoTeC1_data.Lambda1;				break;
		case  30:	return g_MoTeC1_data.Lambda2;				break;
		case  31:	return g_MoTeC1_data.ExhaustPressure;		break;
		case  32:	return g_MoTeC1_data.MassAirFlow;			break;
		case  33:	return g_MoTeC1_data.FuelTemp;				break;
		case  34:	return g_MoTeC1_data.FuelPressure;			break;
		case  35:	return g_MoTeC1_data.OilTemp;				break;
		case  36:	return g_MoTeC1_data.OilPressure;			break;
		case  37:	return g_MoTeC1_data.ExhaustTemp1;			break;
		case  38:	return g_MoTeC1_data.ExhaustTemp2;			break;
		case  39:	return g_MoTeC1_data.BatteryVoltage;		break;
		case  40:	return g_MoTeC1_data.ECUTemp;				break;
		case  41:	return g_MoTeC1_data.GroundSpeed;			break;
		case  42:	return g_MoTeC1_data.AimLambda1;			break;
		case  43:	return g_MoTeC1_data.AimLambda2;			break;
		case  44:	return g_MoTeC1_data.IgnitionAdvance;		break;
		case  45:	return g_MoTeC1_data.InjectorDuty;			break;
		case  46:	return g_MoTeC1_data.Gear;					break;
		case  47:	return g_Haltech1_data.RPM;					break;
		case  48:	return g_Haltech1_data.GroundSpeed;			break;
		case  49:	return g_Haltech1_data.OilPressure;			break;
		case  50:	return g_Haltech1_data.EngineTemp;			break;
		case  51:	return g_Haltech1_data.FuelPressure;		break;
		case  52:	return g_Haltech1_data.BatteryVoltage;		break;
		case  53:	return g_Haltech1_data.ThrottlePosition;	break;
		case  54:	return g_Haltech1_data.ManifoldPressure;	break;
		case  55:	return g_Haltech1_data.InletAirTemp;		break;
		case  56:	return g_Haltech1_data.Lambda;				break;
		case  57:	return g_Haltech1_data.IgnitionAdvance;		break;
		case  58:	return g_Haltech1_data.Gear;				break;
		case  59:	return g_Haltech1_data.InjectorDuty;		break;
		case  60:	return g_Haltech2_data.RPM;					break;
		case  61:	return g_Haltech2_data.ManifoldPressure;	break;
		case  62:	return g_Haltech2_data.ThrottlePosition;	break;
		case  63:	return g_Haltech2_data.FuelPressure;		break;
		case  64:	return g_Haltech2_data.OilPressure;			break;
		case  65:	return g_Haltech2_data.InjectorDuty;		break;
		case  66:	return g_Haltech2_data.IgnitionAdvance1;	break;
		case  67:	return g_Haltech2_data.IgnitionAdvance2;	break;
		case  68:	return g_Haltech2_data.Lambda;				break;
		case  69:	return g_Haltech2_data.GroundSpeed;			break;
		case  70:	return g_Haltech2_data.Gear;				break;
		case  71:	return g_Haltech2_data.BatteryVoltage;		break;
		case  72:	return g_Haltech2_data.InletAirTemp2;		break;
		case  73:	return g_Haltech2_data.BaroPressure;		break;
		case  74:	return g_Haltech2_data.EGT;					break;
		case  75:	return g_Haltech2_data.EngineTemp;			break;
		case  76:	return g_Haltech2_data.InletAirTemp1;		break;
		case  77:	return g_Haltech2_data.FuelTemp;			break;
		case  78:	return g_Haltech2_data.OilTemp;				break;
		case  79:	return g_Freedom2_data.RPM;					break;
		case  80:	return g_Freedom2_data.ManifoldPressure;	break;
		case  81:	return g_Freedom2_data.EngineTemp;			break;
		case  82:	return g_Freedom2_data.InletAirTemp;		break;
		case  83:	return g_Freedom2_data.BarometricPressure;	break;
		case  84:	return g_Freedom2_data.ThrottlePosition;	break;
		case  85:	return g_Freedom2_data.BatteryVoltage;		break;
		case  86:	return g_Freedom2_data.ValidFuelTime;		break;
		case  87:	return g_Freedom2_data.InvalidFuelTime;		break;
		case  88:	return g_Freedom2_data.IgnitionAdvance;		break;
		case  89:	return g_Freedom2_data.Status;				break;
		case  90:	return g_Freedom2_data.GroundSpeed;			break;
		case  91:	return g_Freedom2_data.AFR;					break;
		case  92:	return g_Freedom2_data.TargetAFR;			break;
		case  93:	return g_Freedom2_data.IATCorrection;		break;
		case  94:	return g_Freedom2_data.ETCorrection;		break;
		case  95:	return g_Freedom2_data.EStartCorrection;	break;
		case  96:	return g_Freedom2_data.AccelCorrection;		break;
		case  97:	return g_Freedom2_data.PowerCorrection;		break;
		case  98:	return g_Freedom2_data.FeedbackCorrection;	break;
		case  99:	return g_Freedom2_data.IdolCorrection;		break;
		case 100:	return g_Freedom2_data.DecelCutCorrection;	break;
		case 101:	return g_Freedom2_data.BaroCorrection;		break;
		case 102:	return g_Freedom2_data.IdolIGCorrection;	break;
		case 103:	return g_Freedom2_data.RetardCorrection;	break;
	}
}

/*
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
		case  3:	LCD_textout("< Freedom2.RPM             >");	break;
		case  4:	LCD_textout("< MSquirt1.rpm             >");	break;
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
		case  0:	LCD_textout("< MoTeC1.Lambda1           >");	break;
		case  1:	LCD_textout("< MoTeC1.Lambda2           >");	break;
		case  2:	LCD_textout("< Haltech1.Lambda          >");	break;
		case  3:	LCD_textout("< Haltech2.Lambda          >");	break;
		case  4:	LCD_textout("< Freedom2.AFR             >");	break;
		case  5:	LCD_textout("< MSquirt1.afr1            >");	break;
		case  6:	LCD_textout("< MSquirt1.afr2            >");	break;
	}
}

// --------------------------------------------------------------------
// 目標空燃比ゲージデータ選択描画
// --------------------------------------------------------------------
void t_afr_data_select_draw(unsigned char t_afr_data_select_draw)
{
	switch(t_afr_data_select_draw)
	{
		default:
		case  0:	LCD_textout("< none                     >");	break;
		case  1:	LCD_textout("< MoTeC1.AimLambda1        >");	break;
		case  2:	LCD_textout("< MoTeC1.AimLambda2        >");	break;
		case  3:	LCD_textout("< Freedom2.TargetAFR       >");	break;
		case  4:	LCD_textout("< MSquirt1.afrtgt1         >");	break;
		case  5:	LCD_textout("< MSquirt1.afrtgt2         >");	break;
	}
}
*/

// --------------------------------------------------------------------
// 数値ゲージデータ選択描画
// --------------------------------------------------------------------
void num_data_select_draw(unsigned char num_data_select_draw)
{
	switch(num_data_select_draw)
	{
		default:
		case   0:	LCD_textout("< CAN-STD.ID1.DATA1        >");	break;
		case   1:	LCD_textout("< CAN-STD.ID1.DATA2        >");	break;
		case   2:	LCD_textout("< CAN-STD.ID1.DATA3        >");	break;
		case   3:	LCD_textout("< CAN-STD.ID1.DATA4        >");	break;
		case   4:	LCD_textout("< CAN-STD.ID2.DATA1        >");	break;
		case   5:	LCD_textout("< CAN-STD.ID2.DATA2        >");	break;
		case   6:	LCD_textout("< CAN-STD.ID2.DATA3        >");	break;
		case   7:	LCD_textout("< CAN-STD.ID2.DATA4        >");	break;
		case   8:	LCD_textout("< CAN-STD.ID3.DATA1        >");	break;
		case   9:	LCD_textout("< CAN-STD.ID3.DATA2        >");	break;
		case  10:	LCD_textout("< CAN-STD.ID3.DATA3        >");	break;
		case  11:	LCD_textout("< CAN-STD.ID3.DATA4        >");	break;
		case  12:	LCD_textout("< CAN-STD.ID4.DATA1        >");	break;
		case  13:	LCD_textout("< CAN-STD.ID4.DATA2        >");	break;
		case  14:	LCD_textout("< CAN-STD.ID4.DATA3        >");	break;
		case  15:	LCD_textout("< CAN-STD.ID4.DATA4        >");	break;
		case  16:	LCD_textout("< CAN-STD.ID5.DATA1        >");	break;
		case  17:	LCD_textout("< CAN-STD.ID5.DATA2        >");	break;
		case  18:	LCD_textout("< CAN-STD.ID5.DATA3        >");	break;
		case  19:	LCD_textout("< CAN-STD.ID5.DATA4        >");	break;
		case  20:	LCD_textout("< CAN-STD.ID6.DATA1        >");	break;
		case  21:	LCD_textout("< CAN-STD.ID6.DATA2        >");	break;
		case  22:	LCD_textout("< CAN-STD.ID6.DATA3        >");	break;
		case  23:	LCD_textout("< CAN-STD.ID6.DATA4        >");	break;
		case  24:	LCD_textout("< MoTeC1.RPM               >");	break;
		case  25:	LCD_textout("< MoTeC1.ThrottlePosition  >");	break;
		case  26:	LCD_textout("< MoTeC1.ManifoldPressure  >");	break;
		case  27:	LCD_textout("< MoTeC1.InletAirTemp      >");	break;
		case  28:	LCD_textout("< MoTeC1.EngineTemp        >");	break;
		case  29:	LCD_textout("< MoTeC1.Lambda1           >");	break;
		case  30:	LCD_textout("< MoTeC1.Lambda2           >");	break;
		case  31:	LCD_textout("< MoTeC1.ExhaustPressure   >");	break;
		case  32:	LCD_textout("< MoTeC1.MassAirFlow       >");	break;
		case  33:	LCD_textout("< MoTeC1.FuelTemp          >");	break;
		case  34:	LCD_textout("< MoTeC1.FuelPressure      >");	break;
		case  35:	LCD_textout("< MoTeC1.OilTemp           >");	break;
		case  36:	LCD_textout("< MoTeC1.OilPressure       >");	break;
		case  37:	LCD_textout("< MoTeC1.ExhaustTemp1      >");	break;
		case  38:	LCD_textout("< MoTeC1.ExhaustTemp2      >");	break;
		case  39:	LCD_textout("< MoTeC1.BatteryVoltage    >");	break;
		case  40:	LCD_textout("< MoTeC1.ECUTemp           >");	break;
		case  41:	LCD_textout("< MoTeC1.GroundSpeed       >");	break;
		case  42:	LCD_textout("< MoTeC1.AimLambda1        >");	break;
		case  43:	LCD_textout("< MoTeC1.AimLambda2        >");	break;
		case  44:	LCD_textout("< MoTeC1.IgnitionAdvance   >");	break;
		case  45:	LCD_textout("< MoTeC1.InjectorDuty      >");	break;
		case  46:	LCD_textout("< MoTeC1.Gear              >");	break;
		case  47:	LCD_textout("< Haltech1.RPM             >");	break;
		case  48:	LCD_textout("< Haltech1.GroundSpeed     >");	break;
		case  49:	LCD_textout("< Haltech1.OilPressure     >");	break;
		case  50:	LCD_textout("< Haltech1.EngineTemp      >");	break;
		case  51:	LCD_textout("< Haltech1.FuelPressure    >");	break;
		case  52:	LCD_textout("< Haltech1.BatteryVoltage  >");	break;
		case  53:	LCD_textout("< Haltech1.ThrottlePosition>");	break;
		case  54:	LCD_textout("< Haltech1.ManifoldPressure>");	break;
		case  55:	LCD_textout("< Haltech1.InletAirTemp    >");	break;
		case  56:	LCD_textout("< Haltech1.Lambda          >");	break;
		case  57:	LCD_textout("< Haltech1.IgnitionAdvance >");	break;
		case  58:	LCD_textout("< Haltech1.Gear            >");	break;
		case  59:	LCD_textout("< Haltech1.InjectorDuty    >");	break;
		case  60:	LCD_textout("< Haltech2.RPM             >");	break;
		case  61:	LCD_textout("< Haltech2.ManifoldPressure>");	break;
		case  62:	LCD_textout("< Haltech2.ThrottlePosition>");	break;
		case  63:	LCD_textout("< Haltech2.FuelPressure    >");	break;
		case  64:	LCD_textout("< Haltech2.OilPressure     >");	break;
		case  65:	LCD_textout("< Haltech2.InjectorDuty    >");	break;
		case  66:	LCD_textout("< Haltech2.IgnitionAdvance1>");	break;
		case  67:	LCD_textout("< Haltech2.IgnitionAdvance2>");	break;
		case  68:	LCD_textout("< Haltech2.Lambda          >");	break;
		case  69:	LCD_textout("< Haltech2.GroundSpeed     >");	break;
		case  70:	LCD_textout("< Haltech2.Gear            >");	break;
		case  71:	LCD_textout("< Haltech2.BatteryVoltage  >");	break;
		case  72:	LCD_textout("< Haltech2.InletAirTemp2   >");	break;
		case  73:	LCD_textout("< Haltech2.BaroPressure    >");	break;
		case  74:	LCD_textout("< Haltech2.EGT             >");	break;
		case  75:	LCD_textout("< Haltech2.EngineTemp      >");	break;
		case  76:	LCD_textout("< Haltech2.InletAirTemp1   >");	break;
		case  77:	LCD_textout("< Haltech2.FuelTemp        >");	break;
		case  78:	LCD_textout("< Haltech2.OilTemp         >");	break;
		case  79:	LCD_textout("< Freedom2.RPM             >");	break;
		case  80:	LCD_textout("< Freedom2.ManifoldPressure>");	break;
		case  81:	LCD_textout("< Freedom2.EngineTemp      >");	break;
		case  82:	LCD_textout("< Freedom2.InletAirTemp    >");	break;
		case  83:	LCD_textout("< Freedom2.BaroPressure    >");	break;
		case  84:	LCD_textout("< Freedom2.ThrottlePosition>");	break;
		case  85:	LCD_textout("< Freedom2.BatteryVoltage  >");	break;
		case  86:	LCD_textout("< Freedom2.ValidFuelTime   >");	break;
		case  87:	LCD_textout("< Freedom2.InvalidFuelTime >");	break;
		case  88:	LCD_textout("< Freedom2.IgnitionAdvance >");	break;
		case  89:	LCD_textout("< Freedom2.Status          >");	break;
		case  90:	LCD_textout("< Freedom2.GroundSpeed     >");	break;
		case  91:	LCD_textout("< Freedom2.AFR             >");	break;
		case  92:	LCD_textout("< Freedom2.TargetAFR       >");	break;
		case  93:	LCD_textout("< Freedom2.IATCorrection   >");	break;
		case  94:	LCD_textout("< Freedom2.ETCorrection    >");	break;
		case  95:	LCD_textout("< Freedom2.EStartCorrection>");	break;
		case  96:	LCD_textout("< Freedom2.AccelCorrection >");	break;
		case  97:	LCD_textout("< Freedom2.PowerCorrection >");	break;
		case  98:	LCD_textout("< Freedom2.FeedbackCorrect >");	break;
		case  99:	LCD_textout("< Freedom2.IdolCorrection  >");	break;
		case 100:	LCD_textout("< Freedom2.DecelCutCorrect >");	break;
		case 101:	LCD_textout("< Freedom2.BaroCorrection  >");	break;
		case 102:	LCD_textout("< Freedom2.IdolIGCorrect   >");	break;
		case 103:	LCD_textout("< Freedom2.RetardCorrect   >");	break;
/*		case 80:	LCD_textout("< MSquirt1.rpm             >");	break;
		case 81:	LCD_textout("< MSquirt1.advance         >");	break;
		case 82:	LCD_textout("< MSquirt1.afrtgt1         >");	break;
		case 83:	LCD_textout("< MSquirt1.afrtgt2         >");	break;
		case 84:	LCD_textout("< MSquirt1.barometer       >");	break;
		case 85:	LCD_textout("< MSquirt1.map             >");	break;
		case 86:	LCD_textout("< MSquirt1.mat             >");	break;
		case 87:	LCD_textout("< MSquirt1.coolant         >");	break;
		case 88:	LCD_textout("< MSquirt1.tps             >");	break;
		case 89:	LCD_textout("< MSquirt1.batteryVoltage  >");	break;
		case 90:	LCD_textout("< MSquirt1.afr1            >");	break;
		case 91:	LCD_textout("< MSquirt1.afr2            >");	break;*/
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
// チャートゲージグリッド数選択描画
// --------------------------------------------------------------------
void num_grid_draw(unsigned char num_grid)
{
	switch(num_grid)
	{
		case  0:	LCD_textout("< 0         >");	break;
		case  1:	LCD_textout("< 1         >");	break;
		case  2:	LCD_textout("< 2         >");	break;
		case  3:	LCD_textout("< 3         >");	break;
		case  4:	LCD_textout("< 4         >");	break;
		case  5:	LCD_textout("< 5         >");	break;
		case  6:	LCD_textout("< 6         >");	break;
		case  7:	LCD_textout("< 7         >");	break;
		case  8:	LCD_textout("< 8         >");	break;
		case  9:	LCD_textout("< 9         >");	break;
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
		case 17:	LCD_textout("MAF   ");	break;
		case 18:	LCD_textout("TARGET");	break;
		case 19:	LCD_textout("Baro-P");	break;
		case 20:	LCD_textout("S-0   ");	break;
		case 21:	LCD_textout("S-1   ");	break;
		case 22:	LCD_textout("S-2   ");	break;
		case 23:	LCD_textout("S-3   ");	break;
		case 24:	LCD_textout("S-4   ");	break;
		case 25:	LCD_textout("S-5   ");	break;
		case 26:	LCD_textout("S-6   ");	break;
		case 27:	LCD_textout("S-7   ");	break;
		case 28:	LCD_textout("S-8   ");	break;
		case 29:	LCD_textout("S-9   ");	break;
		case 30:	LCD_textout("V-0   ");	break;
		case 31:	LCD_textout("V-1   ");	break;
		case 32:	LCD_textout("V-2   ");	break;
		case 33:	LCD_textout("V-3   ");	break;
		case 34:	LCD_textout("V-4   ");	break;
		case 35:	LCD_textout("V-5   ");	break;
		case 36:	LCD_textout("V-6   ");	break;
		case 37:	LCD_textout("V-7   ");	break;
		case 38:	LCD_textout("V-8   ");	break;
		case 39:	LCD_textout("V-9   ");	break;
		case 40:	LCD_textout("T-0   ");	break;
		case 41:	LCD_textout("T-1   ");	break;
		case 42:	LCD_textout("T-2   ");	break;
		case 43:	LCD_textout("T-3   ");	break;
		case 44:	LCD_textout("T-4   ");	break;
		case 45:	LCD_textout("T-5   ");	break;
		case 46:	LCD_textout("T-6   ");	break;
		case 47:	LCD_textout("T-7   ");	break;
		case 48:	LCD_textout("T-8   ");	break;
		case 49:	LCD_textout("T-9   ");	break;
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
		case  5:	LCD_CHR_Copy_Smallfont('g');	break;
		case  6:	LCD_CHR_Copy_Smallfont('m');	break;
		case  7:	LCD_CHR_Copy_Smallfont('s');	break;
		case  8:	LCD_CHR_Copy_Smallfont('d');	break;
	}
}
