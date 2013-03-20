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
// filename		:	dataregister.h
// brief		:	FullMoni rev.B データ管理
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _DATAREGISTER_H_
#define _DATAREGISTER_H_

// --------------------------------------------------------------------
// define宣言
// --------------------------------------------------------------------
#define num_data_select_value	43
#define rev_data_select_value	2
#define afr_data_select_value	2
#define num_dp_value			3
#define num_label_value			16
#define afr_label_value			2
#define num_unit_value			4

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_e2p_data(void);
void Init_MoTeC1_data(void);
void Init_Haltech1_data(void);
void Init_Haltech2_data(void);
void Init_Freedom2_data(void);
unsigned int rev_data_select(unsigned char rev_data_select);
unsigned int afr_data_select(unsigned char afr_data_select);
unsigned int num_data_select(unsigned char num_data_select);
void rev_data_select_draw(unsigned char rev_data_select_draw);
void afr_data_select_draw(unsigned char afr_data_select_draw);
void num_data_select_draw(unsigned char num_data_select_draw);
void num_dp_draw(unsigned char num_dp);
void num_label_draw(unsigned char num_tag);
void num_unit_draw(unsigned char num_unit);

// --------------------------------------------------------------------
// MoTeC m#00系データレジスタ
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
} MoTeC1_data_t;

// --------------------------------------------------------------------
// Haltech E8データレジスタ
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
	unsigned int InletAirTemp2;			/* 吸気温2				*/
	unsigned int BatteryVoltage;		/* バッテリー電圧		*/
	unsigned int BaroPressure;			/* 大気圧				*/
	unsigned int EGT;					/* 排気温				*/
	unsigned int OilTemp;				/* 油温					*/
	unsigned int EngineTemp;			/* エンジン温度			*/
	unsigned int InletAirTemp1;			/* 吸気温1				*/
	unsigned int FuelTemp;				/* 燃温					*/
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
	unsigned int Lambda;				/* ラムダ値				*/
} Freedom2_data_t;

#pragma pack 1
// --------------------------------------------------------------------
// MegaSquirt(MS2/Extra) データレジスタ
// --------------------------------------------------------------------
typedef struct {						/* 						*/
	unsigned int	seconds;			/* 						*/
	unsigned int	pulseWidth1;		/* 						*/
	unsigned int	pulseWidth2;		/* 						*/
	unsigned int	rpm;				/* 						*/
	int				advance;			/* 						*/
	union {								/* 						*/
		unsigned char	BYTE;			/* 						*/
		struct {						/* 						*/
			unsigned firing1	:1;		/* 	b0					*/
			unsigned firing2	:1;		/* 	b1					*/
			unsigned sched1		:1;		/*	b2					*/
			unsigned inj1		:1;		/*	b3					*/
			unsigned sched2		:1;		/*	b4					*/
			unsigned inj2		:1;		/*	b5					*/
			unsigned tentative	:1;		/*	b6					*/
			unsigned 			:1;		/*	b7					*/
		} BIT;							/*						*/
	} squirt;							/*						*/
	union {								/* 						*/
		unsigned char	BYTE;			/* 						*/
		struct {						/* 						*/
			unsigned running	:1;		/* 	b0					*/
			unsigned cranking	:1;		/* 	b1					*/
			unsigned ASE		:1;		/*	b2					*/
			unsigned warmup		:1;		/*	b3					*/
			unsigned accaen		:1;		/*	b4					*/
			unsigned accden		:1;		/*	b5					*/
			unsigned 			:1;		/*	b6					*/
			unsigned idleon		:1;		/*	b7					*/
		} BIT;							/*						*/
	} engine;							/*						*/
	unsigned char	afrtgt1;			/* 						*/
	unsigned char	afrtgt2;			/* 						*/
	unsigned char	wbo2_en1;			/* 						*/
	unsigned char	wbo2_en2;			/* 						*/
	int				barometer;			/* 						*/
	int				map;				/* 						*/
	int				mat;				/* 						*/
	int				coolant;			/* 						*/
	int				tps;				/* 						*/
	int				batteryVoltage;		/* 						*/
	int				afr1;				/* 						*/
	int				afr2;				/* 						*/
	int				knock;				/* 						*/
	int				egoCorrection1;		/* 						*/
	int				egoCorrection2;		/* 						*/
	int				airCorrection;		/* 						*/
	int				warmupEnrich;		/* 						*/
	int				accelEnrich;		/* 						*/
	int				tpsfuelcut;			/* 						*/
	int				baroCorrection;		/* 						*/
	int				gammaEnrich;		/* 						*/
	int				veCurr1;			/* 						*/
	int				veCurr2;			/* 						*/
	int				iacstep;			/* 						*/
	int				coldAdvDeg;			/* 						*/
	int				tpsDOT;				/* 						*/
	int				mapDOT;				/* 						*/
	unsigned int	dwell;				/* 						*/
	int				maf;				/* 						*/
	int				fuelload;			/* 						*/
	int				fuelCorrection;		/* 						*/
	unsigned char	portStatus;			/* 						*/
	unsigned char	knockRetard;		/* 						*/
	unsigned int	EAEFuleCorr;		/* 						*/
	int				egoV;				/* 						*/
	int				egoV2;				/* 						*/
	unsigned char	status1;			/* 						*/
	unsigned char	status2;			/* 						*/
	unsigned char	status3;			/* 						*/
	unsigned char	status4;			/* 						*/
	unsigned int	looptime;			/* 						*/
	unsigned char	status5;			/* 						*/
	unsigned int	tpsADC;				/* 						*/
	unsigned int	fuelload2;			/* 						*/
	unsigned int	ignload;			/* 						*/
	unsigned int	ignload2;			/* 						*/
	unsigned char	dummy;				/* 						*/
	long			deltaT;				/* 						*/
	unsigned long	wallfuel;			/* 						*/
	unsigned int	gpioadc0;			/* 						*/
	unsigned int	gpioadc1;			/* 						*/
	unsigned int	gpioadc2;			/* 						*/
	unsigned int	gpioadc3;			/* 						*/
	unsigned int	gpioadc4;			/* 						*/
	unsigned int	gpioadc5;			/* 						*/
	unsigned int	gpioadc6;			/* 						*/
	unsigned int	gpioadc7;			/* 						*/
	unsigned int	gpiopwmin0;			/* 						*/
	unsigned int	gpiopwmin1;			/* 						*/
	unsigned int	gpiopwmin2;			/* 						*/
	unsigned int	gpiopwmin3;			/* 						*/
	unsigned char	gpioport0;			/* 						*/
	unsigned char	gpioport1;			/* 						*/
	unsigned char	gpioport2;			/* 						*/
	unsigned int	adc6;				/* 						*/
	unsigned int	adc7;				/* 						*/
	unsigned long	wallfuel2;			/* 						*/
	unsigned int	EAEFuelCorr2;		/* 						*/
	unsigned char	boostduty;			/* 						*/
	unsigned char	checksum;			/* 						*/
	unsigned char	ochBlockSize;		/* 						*/
} Megasquirt1_data_t;
#pragma unpack

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
				unsigned fclogger_on:1;	/*		b2	FC-Logger併用 on/off		*/
				unsigned defi_on	:1;	/*		b3	Defi受信 on/off				*/
				unsigned 			:1;	/*		b4								*/
				unsigned 			:1;	/*		b5								*/
				unsigned 			:1;	/*		b6								*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} control;						/*										*/
		unsigned char tp_Xmin;			/*	0x0003	タッチパネルX軸下限校正値	*/
		unsigned char tp_Xmax;			/*	0x0004	タッチパネルX軸上限校正値	*/
		unsigned char tp_Ymin;			/*	0x0005	タッチパネルY軸下限校正値	*/
		unsigned char tp_Ymax;			/*	0x0006	タッチパネルY軸上限校正値	*/
		unsigned char dimmer1;			/*	0x0007	バックライトディマー調整1	*/
		unsigned char dimmer2;			/*	0x0008	バックライトディマー調整2	*/
		unsigned char dummy1;			/*	0x0009								*/
		unsigned char dummy2;			/*	0x000A								*/
		unsigned char dummy3;			/*	0x000B								*/
		unsigned char dummy4;			/*	0x000C								*/
		unsigned char dummy5;			/*	0x000D								*/
		unsigned char dummy6;			/*	0x000E								*/
		unsigned char dummy7;			/*	0x000F								*/
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
		unsigned char dummy4;			/*	0x002F								*/
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
		unsigned char dummy0;			/*	0x0070								*/
		unsigned char dummy1;			/*	0x0071								*/
		unsigned char dummy2;			/*	0x0072								*/
		unsigned char dummy3;			/*	0x0073								*/
		unsigned char dummy4;			/*	0x0074								*/
		unsigned char dummy5;			/*	0x0075								*/
		unsigned char dummy6;			/*	0x0076								*/
		unsigned char dummy7;			/*	0x0077								*/
		unsigned char dummy8;			/*	0x0078								*/
		unsigned char dummy9;			/*	0x0079								*/
		unsigned char dummyA;			/*	0x007A								*/
		unsigned char dummyB;			/*	0x007B								*/
		unsigned char dummyC;			/*	0x007C								*/
		unsigned char dummyD;			/*	0x007D								*/
		unsigned char dummyE;			/*	0x007E								*/
		unsigned char dummyF;			/*	0x007F								*/
	} E2P_8;							/* 										*/
} e2p_data_t;
#pragma unpack

// --------------------------------------------------------------------
// extern宣言
// --------------------------------------------------------------------
extern volatile e2p_data_t		g_e2p_data;
extern volatile MoTeC1_data_t	g_MoTeC1_data;
extern volatile Haltech1_data_t	g_Haltech1_data;
extern volatile Haltech2_data_t	g_Haltech2_data;
extern volatile Freedom2_data_t	g_Freedom2_data;

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _DATAREGISTER_H_ */
