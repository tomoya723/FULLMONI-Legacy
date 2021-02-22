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
// filename		:	dataregister.h
// brief		:	FullMoni rev.C データ管理
// author		:	Tomoya Sato
// update		:	2021/02/21
// version		:	1.06
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _DATAREGISTER_H_
#define _DATAREGISTER_H_

// --------------------------------------------------------------------
// define宣言
// --------------------------------------------------------------------
#define num_data_select_value	103
//#define rev_data_select_value	4
//#define afr_data_select_value	6
//#define t_afr_data_select_value	5
#define num_dp_value			3
#define num_grid_value			9
#define num_label_value			49
#define afr_label_value			2
#define num_unit_value			8

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_e2p_data(void);
void Init_CAN_data(void);
void Init_MoTeC1_data(void);
//void Init_MoTeC2_data(void);
void Init_Haltech1_data(void);
void Init_Haltech2_data(void);
void Init_Freedom2_data(void);
//unsigned int rev_data_select(unsigned char rev_data_select);
//unsigned int afr_data_select(unsigned char afr_data_select);
//unsigned int t_afr_data_select(unsigned char t_afr_data_select);
unsigned int num_data_select(unsigned char num_data_select);
//void rev_data_select_draw(unsigned char rev_data_select_draw);
//void afr_data_select_draw(unsigned char afr_data_select_draw);
void num_data_select_draw(unsigned char num_data_select_draw);
void num_dp_draw(unsigned char num_dp);
void num_grid_draw(unsigned char num_grid);
void num_label_draw(unsigned char num_tag);
void num_unit_draw(unsigned char num_unit);

#pragma pack 1
// --------------------------------------------------------------------
// 標準CANデータレジスタ
// --------------------------------------------------------------------
typedef struct {
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x0000	数値1上限値					*/
										/*	0x0001								*/
		unsigned int  DATA2;			/*	0x0002	数値2上限値					*/
										/*	0x0003								*/
		unsigned int  DATA3;			/*	0x0004	数値3上限値					*/
										/*	0x0005								*/
		unsigned int  DATA4;			/*	0x0006	数値4上限値					*/
	} ID1;								/* 										*/
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x0007	数値1上限値					*/
										/*	0x0008								*/
		unsigned int  DATA2;			/*	0x0009	数値2上限値					*/
										/*	0x000A								*/
		unsigned int  DATA3;			/*	0x000B	数値3上限値					*/
										/*	0x000C								*/
		unsigned int  DATA4;			/*	0x000D	数値4上限値					*/
	} ID2;								/* 										*/
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x000E	数値1上限値					*/
										/*	0x000F								*/
		unsigned int  DATA2;			/*	0x0010	数値2上限値					*/
										/*	0x0011								*/
		unsigned int  DATA3;			/*	0x0012	数値3上限値					*/
										/*	0x0013								*/
		unsigned int  DATA4;			/*	0x0014	数値4上限値					*/
	} ID3;								/* 										*/
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x0015	数値1上限値					*/
										/*	0x0016								*/
		unsigned int  DATA2;			/*	0x0017	数値2上限値					*/
										/*	0x0018								*/
		unsigned int  DATA3;			/*	0x0019	数値3上限値					*/
										/*	0x001A								*/
		unsigned int  DATA4;			/*	0x001B	数値4上限値					*/
	} ID4;								/* 										*/
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x001C	数値1上限値					*/
										/*	0x001D								*/
		unsigned int  DATA2;			/*	0x001E	数値2上限値					*/
										/*	0x001F								*/
		unsigned int  DATA3;			/*	0x0020	数値3上限値					*/
										/*	0x0021								*/
		unsigned int  DATA4;			/*	0x0022	数値4上限値					*/
	} ID5;								/* 									*/
	struct {							/*										*/
		unsigned int  DATA1;			/*	0x0023	数値1上限値					*/
										/*	0x0024								*/
		unsigned int  DATA2;			/*	0x0025	数値2上限値					*/
										/*	0x0026								*/
		unsigned int  DATA3;			/*	0x0027	数値3上限値					*/
										/*	0x0028								*/
		unsigned int  DATA4;			/*	0x0029	数値4上限値					*/
	} ID6;								/* 										*/
} CAN_data_t;
#pragma unpack


// --------------------------------------------------------------------
// MoTeC m#00系データレジスタ
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* エンジン回転数		*/
	unsigned int ThrottlePosition;		/* スロポジ				*/
	unsigned int ManifoldPressure;		/* 吸気圧				*/
	unsigned int InletAirTemp;			/* 吸気温				*/
	unsigned int EngineTemp;			/* エンジン温度			*/
	unsigned int Lambda1;				/* ラムダ値1			*/
	unsigned int Lambda2;				/* ラムダ値2			*/
	unsigned int ExhaustPressure;		/* 排気圧				*/
	unsigned int MassAirFlow;			/* エアフロ				*/
	unsigned int FuelTemp;				/* 燃温					*/
	unsigned int FuelPressure;			/* 燃圧					*/
	unsigned int OilTemp;				/* 油温					*/
	unsigned int OilPressure;			/* 油圧					*/
//	unsigned int GearVoltage;			/* ギア電圧				*/
//	unsigned int KnockVoltage;			/* ノック電圧			*/
//	unsigned int GearShiftForce;		/* ギアシフトフォース	*/
	unsigned int ExhaustTemp1;			/* 排気温1				*/
	unsigned int ExhaustTemp2;			/* 排気温2				*/
//	unsigned int UserChannel1;			/* ユーザチャンネル1	*/
//	unsigned int UserChannel2;			/* ユーザチャンネル2	*/
//	unsigned int UserChannel3;			/* ユーザチャンネル3	*/
//	unsigned int UserChannel4;			/* ユーザチャンネル4	*/
	unsigned int BatteryVoltage;		/* バッテリー電圧		*/
	unsigned int ECUTemp;				/* ECU内部温度			*/
//	unsigned int Dig1Speed;				/* Dig1速度				*/
//	unsigned int Dig2Speed;				/* Dig2速度				*/
//	unsigned int Dig3Speed;				/* Dig3速度				*/
//	unsigned int Dig4Speed;				/* Dig4速度				*/
//	unsigned int DriveSpeed;			/* ドライブ速度			*/
	unsigned int GroundSpeed;			/* 車速					*/
//	unsigned int Slip;					/* スリップ速度			*/
//	unsigned int AimSlip;				/* 目標スリップ速度		*/
//	unsigned int LaunchRPM;				/* ローンチ回転数		*/
//	unsigned int La1ShortTrim;			/* ラムダ1短時間補正	*/
//	unsigned int La2ShortTrim;			/* ラムダ2短時間補正	*/
//	unsigned int La1LongTrim;			/* ラムダ1長時間補正	*/
//	unsigned int La2LongTrim;			/* ラムダ2長時間補正	*/
	unsigned int AimLambda1;			/* 目標ラムダ値1		*/
	unsigned int AimLambda2;			/* 目標ラムダ値2		*/
//	unsigned int FuelCutLevel;			/* 燃料カットレベル		*/
//	unsigned int IGCutLevel;			/* 点火カットレベル		*/
	unsigned int IgnitionAdvance;		/* 点火時期				*/
//	unsigned int LoadPoint;				/* 負荷軸値				*/
//	unsigned int EffPoint;				/* 負荷軸値				*/
//	unsigned int FuelUsed;				/* 						*/
//	unsigned int Aux1Duty;				/* Aux1デューティ		*/
//	unsigned int Aux2Duty;				/* Aux2デューティ		*/
//	unsigned int Aux3Duty;				/* Aux3デューティ		*/
//	unsigned int Aux4Duty;				/* Aux4デューティ		*/
//	unsigned int Aux5Duty;				/* Aux5デューティ		*/
//	unsigned int Aux6Duty;				/* Aux6デューティ		*/
//	unsigned int Aux7Duty;				/* Aux7デューティ		*/
//	unsigned int Aux8Duty;				/* Aux8デューティ		*/
//	unsigned int FuelActualWidth;		/* 						*/
//	unsigned int FuelEffPulseWidth;		/* 						*/
	unsigned int InjectorDuty;			/* 開弁率				*/
	unsigned int Gear;					/* ギアポジション		*/
//	unsigned int SyncPosition;			/* 						*/
//	unsigned int FuelComp1;				/* 						*/
//	unsigned int FuelComp2;				/* 						*/
} MoTeC1_data_t;

// --------------------------------------------------------------------
// Haltech E8/E11データレジスタ
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* エンジン回転数		*/
	unsigned int GroundSpeed;			/* 車速					*/
	unsigned int OilPressure;			/* 油圧					*/
	unsigned int EngineTemp;			/* エンジン温度			*/
	unsigned int FuelPressure;			/* 燃圧					*/
	unsigned int BatteryVoltage;		/* バッテリー電圧		*/
	unsigned int ThrottlePosition;		/* スロポジ				*/
	unsigned int ManifoldPressure;		/* 吸気圧				*/
	unsigned int InletAirTemp;			/* 吸気温				*/
	unsigned int Lambda;				/* ラムダ値				*/
	unsigned int IgnitionAdvance;		/* 点火時期				*/
	unsigned int Gear;					/* ギアポジション		*/
	unsigned int InjectorDuty;			/* 開弁率				*/
} Haltech1_data_t;

// --------------------------------------------------------------------
// Haltech SPORT系データレジスタ
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* エンジン回転数		*/
	unsigned int ManifoldPressure;		/* 吸気圧				*/
	unsigned int ThrottlePosition;		/* スロポジ				*/
	unsigned int FuelPressure;			/* 燃圧					*/
	unsigned int OilPressure;			/* 油圧					*/
	unsigned int InjectorDuty;			/* 開弁率				*/
	unsigned int IgnitionAdvance1;		/* 点火時期1			*/
	unsigned int IgnitionAdvance2;		/* 点火時期2			*/
	unsigned int Lambda;				/* ラムダ値				*/
	unsigned int GroundSpeed;			/* 車速					*/
	unsigned int Gear;					/* ギアポジション		*/
	unsigned int BatteryVoltage;		/* バッテリー電圧		*/
	unsigned int InletAirTemp2;			/* 吸気温2				*/
	unsigned int BaroPressure;			/* 大気圧				*/
	unsigned int EGT;					/* 排気温				*/
	unsigned int EngineTemp;			/* エンジン温度			*/
	unsigned int InletAirTemp1;			/* 吸気温1				*/
	unsigned int FuelTemp;				/* 燃温					*/
	unsigned int OilTemp;				/* 油温					*/
} Haltech2_data_t;

// --------------------------------------------------------------------
// Freedom Ver3.XX データレジスタ
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* エンジン回転数		*/
	unsigned int ManifoldPressure;		/* 吸気圧				*/
	unsigned int EngineTemp;			/* エンジン温度			*/
	unsigned int InletAirTemp;			/* 吸気温				*/
	unsigned int BarometricPressure;	/* 外気圧				*/
	unsigned int ThrottlePosition;		/* スロットルポジション	*/
	unsigned int BatteryVoltage;		/* バッテリー電圧		*/
	unsigned int ValidFuelTime;			/* 有効噴射時間			*/
	unsigned int InvalidFuelTime;		/* 無効噴射時間			*/
	unsigned int IgnitionAdvance;		/* 点火時期				*/
	unsigned int Status;				/* ステータス			*/
	unsigned int GroundSpeed;			/* データ				*/
	unsigned int AFR;					/* AFR値				*/
	unsigned int TargetAFR;				/* 目標AFR値			*/
	unsigned int IATCorrection;			/* 吸気温補正			*/
	unsigned int ETCorrection;			/* 水温補正				*/
	unsigned int EStartCorrection;		/* 始動後増量補正		*/
	unsigned int AccelCorrection;		/* 加減速補正			*/
	unsigned int PowerCorrection;		/* 出力増量補正			*/
	unsigned int FeedbackCorrection;	/* フィードバック補正	*/
	unsigned int IdolCorrection;		/* アイドル安定化補正	*/
	unsigned int DecelCutCorrection;	/* 噴射復帰補正			*/
	unsigned int BaroCorrection;		/* 外気圧補正			*/
	unsigned int IdolIGCorrection;		/* アイドル安定化点火補正			*/
	unsigned int RetardCorrection;		/* 噴射復帰点火補正＆ノック遅角補正	*/
} Freedom2_data_t;

// --------------------------------------------------------------------
// MegaSquirt(MS2/Extra) データレジスタ
// --------------------------------------------------------------------
typedef struct {						/* 						*/
	unsigned int rpm;					/* 						*/
	unsigned int advance;				/* 						*/
	unsigned int afrtgt1;				/* 						*/
	unsigned int afrtgt2;				/* 						*/
	unsigned int barometer;				/* 						*/
	unsigned int map;					/* 						*/
	unsigned int mat;					/* 						*/
	unsigned int coolant;				/* 						*/
	unsigned int tps;					/* 						*/
	unsigned int batteryVoltage;		/* 						*/
	unsigned int afr1;					/* 						*/
	unsigned int afr2;					/* 						*/
} Megasquirt1_data_t;

#pragma pack 1
// --------------------------------------------------------------------
// EEPROMデータレジスタ
// --------------------------------------------------------------------
typedef struct {						/*										*/
	struct {							/*										*/
		union {							/*										*/
			unsigned char BYTE;			/*	0x0000	EEPROM管理					*/
			struct {					/*										*/
				unsigned WROK		:1;	/*		b0	書き込み正常/異常フラグ		*/
				unsigned 			:1;	/*		b1								*/
				unsigned 			:1;	/*		b2								*/
				unsigned 			:1;	/*		b3								*/
				unsigned 			:1;	/*		b4								*/
				unsigned 			:1;	/*		b5								*/
				unsigned 			:1;	/*		b6								*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} E2Pmanage;					/*										*/
		unsigned char model;			/*	0x0001	対応モデル選択番号			*/
		union {							/*										*/
			unsigned char BYTE;			/*	0x0002	フルモニ管理				*/
			struct {					/*										*/
				unsigned beep_on	:1;	/*		b0	ブザー on/off				*/
				unsigned ms_on		:1;	/*		b1	マスターワーニング on/off	*/
				unsigned FC_mode	:1;	/*		b2	フリーダムモード FAST/ALL	*/
				unsigned defi_on	:1;	/*		b3	Defi受信 on/off				*/
				unsigned 			:1;	/*		b4								*/
				unsigned 			:1;	/*		b5								*/
				unsigned 			:1;	/*		b6								*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} control;						/*										*/
		union {							/*										*/
			unsigned char BYTE;			/*	0x0003	CAN Stream管理				*/
			struct {					/*										*/
				unsigned CAN_ch1	:1;	/*		b0	CAN Stream Ch1 on/off		*/
				unsigned CAN_ch2	:1;	/*		b1	CAN Stream Ch2 on/off		*/
				unsigned CAN_ch3	:1;	/*		b2	CAN Stream Ch3 on/off		*/
				unsigned CAN_ch4	:1;	/*		b3	CAN Stream Ch4 on/off		*/
				unsigned CAN_ch5	:1;	/*		b4	CAN Stream Ch5 on/off		*/
				unsigned CAN_ch6	:1;	/*		b5	CAN Stream Ch6 on/off		*/
				unsigned BAUD		:1;	/*		b6	CAN ボーレート切り替え		*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} CANcontrol;					/*										*/
		int				CAN_ID1;		/*	0x0004	CAN Stream ID CH1			*/
										/*	0x0005								*/
		int				CAN_ID2;		/*	0x0006	CAN Stream ID CH2			*/
										/*	0x0007								*/
		int				CAN_ID3;		/*	0x0008	CAN Stream ID CH3			*/
										/*	0x0009								*/
		int				CAN_ID4;		/*	0x000A	CAN Stream ID CH4			*/
										/*	0x000B								*/
		int				CAN_ID5;		/*	0x000C	CAN Stream ID CH5			*/
										/*	0x000D								*/
		int				CAN_ID6;		/*	0x000E	CAN Stream ID CH6			*/
	} E2P_1;							/* 										*/
	struct {							/*										*/
		int           rev_timing_rmp1;	/*	0x0010	シフトランプ 橙作動回転数	*/
										/*	0x0011								*/
		int           rev_timing_rmp2;	/*	0x0012	シフトランプ 赤作動回転数	*/
										/*	0x0013								*/
		int           rev_timing_rmp3;	/*	0x0014	シフトランプ 橙+赤作動回転数*/
										/*	0x0015								*/
		unsigned char dummy1;			/*	0x0016								*/
		unsigned char dummy2;			/*	0x0017								*/
		unsigned char dummy3;			/*	0x0018								*/
		unsigned char dummy4;			/*	0x0019								*/
		unsigned char dummy5;			/*	0x001A								*/
		unsigned char dummy6;			/*	0x001B								*/
		unsigned char dummy7;			/*	0x001C								*/
		unsigned char dummy8;			/*	0x001D								*/
		unsigned char dummy9;			/*	0x001E								*/
		unsigned char dummyA;			/*	0x001F								*/
	} E2P_2;							/* 										*/
	struct {							/*										*/
		unsigned char rev_data_select;	/*	0x0020	回転数 データ選択			*/
		int           rev_gain;			/*	0x0021	回転数 ゲインH				*/
										/*	0x0022	回転数 ゲインL				*/
		int           rev_bias;			/*	0x0023	回転数 バイアスH			*/
										/*	0x0024	回転数 バイアスL			*/
		unsigned char dummy1;			/*	0x0025								*/
		unsigned char dummy2;			/*	0x0026								*/
		unsigned char dummy3;			/*	0x0027								*/
		unsigned char afr_data_select;	/*	0x0028	空燃比 データ選択			*/
		int           afr_gain;			/*	0x0029	空燃比 ゲインH				*/
										/*	0x002A	空燃比 ゲインL				*/
		int           afr_bias;			/*	0x002B	空燃比 バイアスH			*/
										/*	0x002C	空燃比 バイアスL			*/
		unsigned char afr_dp;			/*	0x002D	空燃比 小数点位置			*/
		unsigned char afr_label;		/*	0x002E	空燃比 ラベル選択			*/
		unsigned char t_afr_data_select;/*	0x0028	目標空燃比 データ選択		*/
	} E2P_3;							/* 										*/
	struct {							/*										*/
		unsigned char num1_data_select;	/*	0x0030	数値表示1 データ選択		*/
		int           num1_gain;		/*	0x0031	数値表示1 ゲインH			*/
										/*	0x0032	数値表示1 ゲインL			*/
		int           num1_bias;		/*	0x0033	数値表示1 バイアスH			*/
										/*	0x0034	数値表示1 バイアスL			*/
		unsigned char num1_dp;			/*	0x0035	数値表示1 小数点位置		*/
		unsigned char num1_label;		/*	0x0036	数値表示1 ラベル選択		*/
		unsigned char num1_unit;		/*	0x0037	数値表示1 単位選択			*/
		unsigned char num2_data_select;	/*	0x0038	数値表示2 データ選択		*/
		int           num2_gain;		/*	0x0039	数値表示2 ゲインH			*/
										/*	0x003A	数値表示2 ゲインL			*/
		int           num2_bias;		/*	0x003B	数値表示2 バイアスH			*/
										/*	0x003C	数値表示2 バイアスL			*/
		unsigned char num2_dp;			/*	0x003D	数値表示2 小数点位置		*/
		unsigned char num2_label;		/*	0x003E	数値表示2 タグ選択			*/
		unsigned char num2_unit;		/*	0x003F	数値表示2 単位選択			*/
	} E2P_4;							/* 										*/
	struct {							/*										*/
		unsigned char num3_data_select;	/*	0x0040	数値表示3 データ選択		*/
		int           num3_gain;		/*	0x0041	数値表示3 ゲインH			*/
										/*	0x0042	数値表示3 ゲインL			*/
		int           num3_bias;		/*	0x0043	数値表示3 バイアスH			*/
										/*	0x0044	数値表示3 バイアスL			*/
		unsigned char num3_dp;			/*	0x0045	数値表示3 小数点位置		*/
		unsigned char num3_label;		/*	0x0046	数値表示3 ラベル選択		*/
		unsigned char num3_unit;		/*	0x0047	数値表示3 単位選択			*/
		unsigned char num4_data_select;	/*	0x0048	数値表示4 データ選択		*/
		int           num4_gain;		/*	0x0049	数値表示4 ゲインH			*/
										/*	0x004A	数値表示4 ゲインL			*/
		int           num4_bias;		/*	0x004B	数値表示4 バイアスH			*/
										/*	0x003C	数値表示4 バイアスL			*/
		unsigned char num4_dp;			/*	0x004D	数値表示4 小数点位置		*/
		unsigned char num4_label;		/*	0x004E	数値表示4 ラベル選択		*/
		unsigned char num4_unit;		/*	0x004F	数値表示4 単位選択			*/
	} E2P_5;							/* 										*/
	struct {							/*										*/
		unsigned char num5_data_select;	/*	0x0050	数値表示5 データ選択		*/
		int           num5_gain;		/*	0x0051	数値表示5 ゲインH			*/
										/*	0x0052	数値表示5 ゲインL			*/
		int           num5_bias;		/*	0x0053	数値表示5 バイアスH			*/
										/*	0x0054	数値表示5 バイアスL			*/
		unsigned char num5_dp;			/*	0x0055	数値表示5 小数点位置		*/
		unsigned char num5_label;		/*	0x0056	数値表示5 ラベル選択		*/
		unsigned char num5_unit;		/*	0x0057	数値表示5 単位選択			*/
		unsigned char num6_data_select;	/*	0x0058	数値表示6 データ選択		*/
		int           num6_gain;		/*	0x0059	数値表示6 ゲインH			*/
										/*	0x005A	数値表示6 ゲインL			*/
		int           num6_bias;		/*	0x005B	数値表示6 バイアスH			*/
										/*	0x005C	数値表示6 バイアスL			*/
		unsigned char num6_dp;			/*	0x005D	数値表示6 小数点位置		*/
		unsigned char num6_label;		/*	0x005E	数値表示6 ラベル選択		*/
		unsigned char num6_unit;		/*	0x005F	数値表示6 単位選択			*/
	} E2P_6;							/* 										*/
	struct {							/*										*/
		int           num1_warning;		/*	0x0060	数値1上限値					*/
										/*	0x0061								*/
		int           num2_warning;		/*	0x0062	数値2上限値					*/
										/*	0x0063								*/
		int           num3_warning;		/*	0x0064	数値3上限値					*/
										/*	0x0065								*/
		int           num4_warning;		/*	0x0066	数値4上限値					*/
										/*	0x0067								*/
		int           num5_warning;		/*	0x0068	数値5上限値					*/
										/*	0x0069								*/
		int           num6_warning;		/*	0x006A	数値6上限値					*/
										/*	0x006B								*/
		unsigned char dummy1;			/*	0x006C								*/
		unsigned char dummy2;			/*	0x006D								*/
		unsigned char dummy3;			/*	0x006E								*/
		unsigned char dummy4;			/*	0x006F								*/
	} E2P_7;							/* 										*/
	struct {							/*										*/
		unsigned char cht1_data_select;	/*	0x0070	ゲージ数値表示1 データ選択	*/
		int           cht1_gain;		/*	0x0071	ゲージ数値表示1 ゲインH		*/
										/*	0x0072	ゲージ数値表示1 ゲインL		*/
		int           cht1_bias;		/*	0x0073	ゲージ数値表示1 バイアスH	*/
										/*	0x0074	ゲージ数値表示1 バイアスL	*/
		unsigned char cht1_dp;			/*	0x0075	ゲージ数値表示1 小数点位置	*/
		unsigned char cht1_label;		/*	0x0076	ゲージ数値表示1 ラベル選択	*/
		unsigned char dummy1;			/*	0x0077								*/
		unsigned char cht2_data_select;	/*	0x0078	ゲージ数値表示2 データ選択	*/
		int           cht2_gain;		/*	0x0079	ゲージ数値表示2 ゲインH		*/
										/*	0x007A	ゲージ数値表示2 ゲインL		*/
		int           cht2_bias;		/*	0x007B	ゲージ数値表示2 バイアスH	*/
										/*	0x007C	ゲージ数値表示2 バイアスL	*/
		unsigned char cht2_dp;			/*	0x007D	ゲージ数値表示2 小数点位置	*/
		unsigned char cht2_label;		/*	0x007E	ゲージ数値表示2 ラベル選択	*/
		unsigned char dummy2;			/*	0x007F								*/
	} E2P_8;							/* 										*/
	struct {							/*										*/
		int           cht1_guage_gain;	/*	0x0080	ゲージ1設定 ゲインH			*/
										/*	0x0081	ゲージ1設定 ゲインL			*/
		int           cht1_guage_bias;	/*	0x0082	ゲージ1設定 バイアスH		*/
										/*	0x0083	ゲージ1設定 バイアスL		*/
		unsigned char cht1_guage_grid;	/*	0x0084	ゲージ1設定 グリッド数		*/
		int           cht2_guage_gain;	/*	0x0085	ゲージ2設定 ゲインH			*/
										/*	0x0086	ゲージ2設定 ゲインL			*/
		int           cht2_guage_bias;	/*	0x0087	ゲージ2設定 バイアスH		*/
										/*	0x0088	ゲージ2設定 バイアスL		*/
		unsigned char cht2_guage_grid;	/*	0x0089	ゲージ2設定 グリッド数		*/
		unsigned char dummyA;			/*	0x008A								*/
		unsigned char dummyB;			/*	0x008B								*/
		unsigned char dummyC;			/*	0x008C								*/
		unsigned char dummyD;			/*	0x008D								*/
		unsigned char dummyE;			/*	0x008E								*/
		unsigned char dummyF;			/*	0x008F								*/
	} E2P_9;							/* 										*/
} e2p_data_t;
#pragma unpack

// --------------------------------------------------------------------
// extern宣言
// --------------------------------------------------------------------
extern volatile e2p_data_t			g_e2p_data;
extern volatile CAN_data_t			g_CAN_data;
extern volatile MoTeC1_data_t		g_MoTeC1_data;
extern volatile Haltech1_data_t		g_Haltech1_data;
extern volatile Haltech2_data_t		g_Haltech2_data;
extern volatile Freedom2_data_t		g_Freedom2_data;
//extern volatile Megasquirt1_data_t	g_Megasquirt1_data;

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _DATAREGISTER_H_ */
