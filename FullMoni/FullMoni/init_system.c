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
// filename		:	initsystem.c
// brief		:	FullMoni rev.C システム初期化
// author		:	Tomoya Sato
// update		:	2021/02/21
// version		:	1.06
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// システムヘッダファイル
// --------------------------------------------------------------------
#include <machine.h>

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "iodefine.h"
#include "TFTLCD35.h"
#include "CAN2515.h"
#include "dataregister.h"
#include "state_control.h"

// --------------------------------------------------------------------
// CPG初期化
// --------------------------------------------------------------------
void Init_CPG(void)
{
	//-----------------------------------------
	// Set All Internal Clocks in Maximum Speed
	//-----------------------------------------
	// ICLK = EXTAL x 4 (48MHz)
	// PCLK = EXTAL x 2 (24MHz)
	// BCLK = EXTAL x 4 (48MHz)
	SCKCR.WORD = (0 << 8) + (1 << 4) + (0 << 0);
}

// --------------------------------------------------------------------
// INTC初期化
// --------------------------------------------------------------------
void Init_INTC(void)
{
	//-------------------
	// Interrupt Mode = 2
	//-------------------
	INTC.INTCR.BIT.INTM = 2;
	//--------------------------------
	// Set Current Interrupt Level = 0
	//--------------------------------
 	set_imask_exr(0);
	
	// MCP2515 CANIRQ 指定
	P1.ICR.BIT.B3			=    1;
	PFC.PFCRC.BIT.ITS3		=    0;
	INTC.IPRA.BIT._IRQ3		=    5;
	INTC.ISCR_L.BIT.IRQ3SC  = 0x01;
	INTC.IER.BIT.IRQ3E		=    1;
	INTC.ISR.BIT.IRQ3F		=    0;
	
}

// --------------------------------------------------------------------
// MSTP初期化
// --------------------------------------------------------------------
void Init_MSTP(void)
{
	//-------------------------------------------
	// Clear Module Stop for All Internal Modules
	//-------------------------------------------
	MSTP.CRA.BIT.ACSE		= 0;
	MSTP.CRA.BIT._EXDMAC	= 0;
	MSTP.CRA.BIT._DMAC		= 0;
	MSTP.CRA.BIT._DTC		= 0;
	MSTP.CRA.BIT._TMR23		= 0;
	MSTP.CRA.BIT._TMR01		= 0;
	MSTP.CRA.BIT._DA		= 0;
	MSTP.CRA.BIT._AD0		= 0;
	MSTP.CRA.BIT._TPUU		= 0;
	MSTP.CRA.BIT._TPUL		= 0;
	
	MSTP.CRB.BIT._PPG0		= 0;
	MSTP.CRB.BIT._SCI4		= 0;
	MSTP.CRB.BIT._SCI2		= 0;
	MSTP.CRB.BIT._SCI1		= 0;
	MSTP.CRB.BIT._SCI0		= 0;
	MSTP.CRB.BIT._IIC1		= 0;
	MSTP.CRB.BIT._IIC0		= 0;
	MSTP.CRB.BIT._UBC		= 0;
	
	MSTP._CRC.BIT._SCI5		= 0;
	MSTP._CRC.BIT._SCI6		= 0;
	MSTP._CRC.BIT._TMR45	= 0;
	MSTP._CRC.BIT._TMR67	= 0;
	MSTP._CRC.BIT._USB		= 0;
	MSTP._CRC.BIT._CRC		= 0;
	MSTP._CRC.BIT._AD1		= 0;
	MSTP._CRC.BIT._PPG1		= 0;
	MSTP._CRC.BIT._RAM_4	= 0;
	MSTP._CRC.BIT._RAM32	= 0;
	MSTP._CRC.BIT._RAM10	= 0;
}

// --------------------------------------------------------------------
// GPIO初期化
// --------------------------------------------------------------------
void Init_GPIO(void)
{
	//---------------------
	// Enable External Bus
	//---------------------
	SYSCR.BIT.EXPE			= 1;		// 外部バスモード選択
	//-------------
	// P1
	//-------------
	// P10 : O : TFT LCD Command/Data Switch
	// P11 : I : ADS7843E INT
	// P12 : O : MCP2515 CS
	// P13 : I : MCP2515 INT
	// P14 : O : MAX3232ID TxD5
	// P15 : I : MAX3232ID RxD5
	// P16 : I/O : BR24L04F-W SDA0
	// P17 : O : BR24L04F-W SDL0
	P1.DDR = 0x95;
	P1.ICR.BIT.B4 = 1;
	P1.ICR.BIT.B5 = 1;
	P1.ICR.BIT.B6 = 1;
	P1.ICR.BIT.B7 = 1;
	P1.DR.BIT.B6 = 1;
	P1.DR.BIT.B7 = 1;
	//-------------
	// P2
	//-------------
	// P20 : O : MCP2515 SCK0
	// P21 : I : MCP2515 RxD0
	// P22 : O : MCP2515 TxD0
	// P23 : O : BEEP OUT
	// P24 : O : TFT LCD Reset
	// P25 : O : TFT LCD Back Light Control PWM
	// P26 : I : Reserve
	// P27 : O : MAX3232ID FC-Logger select Switch
	P2.DR.BIT.B3 = 0;
	P2.DDR = 0xBD;
	P2.ICR.BIT.B1 = 1;
	P2.DR.BIT.B7 = 1;
	//-------------
	// P5
	//-------------
	// P50 : I : Reserve
	// P51 : I : Reserve
	// P52 : I : Reserve
	// P53 : I : Reserve
	// P54 : I : Reserve
	// P55 : I : Reserve
	// P56 : I : Reserve
	// P57 : I : Reserve
	//-------------
	// P6
	//-------------
	// P60 : O : ADS7843E TxD4
	// P61 : I : ADS7843E RxD4
	// P62 : O : ADS7843E SCK4
	// P63 : O : ADS7843E CS
	// P64 : I : Reserve
	// P65 : I : Reserve
	P6.DDR = 0x0D;
//	P6.ICR.BIT.B1 = 1;
	//-------------
	// PA
	//-------------
	// PA0 : I : Reserve
	// PA1 : O : RD/WR
	// PA2 : I : Reserve
	// PA3 : O : LLWR
	// PA4 : O : LHWR
	// PA5 : O : RD
	// PA6 : I : Reserve
	// PA7 : I : Reserve
	PA.DDR = 0x3A;
	//-------------
	// PB
	//-------------
	// PB0 : I : Reserve
	// PB1 : O : CS1
	// PB2 : O : CS2-A
	// PB3 : O : LED(Red)
	PB.DDR = 0x0E;
	//-------------
	// PD
	//-------------
	// BSC Address
	PD.DDR = 0xFF; // Enable  A7-A0 Output
	//-------------
	// PE
	//-------------
	// BSC Address
	PE.DDR = 0xFF; // Enable A15-A8 Output
	//-------------
	// PF
	//-------------
	// BSC Address
	PF.DDR = 0x1F; // Enable A18-A16 Output
	//-------------
	// PH
	//-------------
	PH.DDR = 0xFF; // Enable D7-D0 Output
	//-------------
	// PI
	//-------------
	PI.DDR = 0xFF; // Enable D15-D8 Output
	//----------------------
	// PJ (Single Chip Mode)
	//----------------------
	//----------------------
	// PK
	//----------------------
	//-------------
	// PM
	//-------------
	// PM0 : O : LED(Yellow)
	// PM1 : I : TC7W125FU RxD6
	// PM2 : I : Reserve
	PM.DDR = 0x01;
}


// --------------------------------------------------------------------
// BSC初期化
// --------------------------------------------------------------------
void Init_BSC(void)
{
	// --------------------------------------------------------------------
	// PFC
	// --------------------------------------------------------------------
	PFC.PFCR0.BIT.CS1E		= 1;		// 出力選択		CS1		SRAMチップセレクト
	PFC.PFCR0.BIT.CS2E		= 1;		// 出力選択		CS2-A	LCDチップセレクト
	PFC.PFCR2.BIT.RDWRE		= 1;		// 出力設定		RD/^WR
	PFC.PFCR4.BIT.A18E		= 1;		// 出力設定		A18
	PFC.PFCR4.BIT.A17E		= 1;		// 出力設定		A17
	PFC.PFCR4.BIT.A16E		= 1;		// 出力設定		A16
	PFC.PFCR6.BIT.LHWROE	= 1;		// 出力設定		PA4=LHWR
	PFC.PFCR8.BYTE			= 0x00;		// EXDMAC1制御端子 P14-P17
	PFC.PFCR9.BIT.TPUMS4	= 1;		// TIOCA4 P25アウトプトコンペア
	PFC.PFCR9.BIT.TPUMS4	= 1;		// TIOCA4 P25アウトプトコンペア
	
	// --------------------------------------------------------------------
	// BSC
	// --------------------------------------------------------------------
	BSC.ABWCR.BIT.ABWH1		= 0;		// 16bit幅設定H	CS1
	BSC.ABWCR.BIT.ABWL1		= 1;		// 16bit幅設定L	CS1
	BSC.ABWCR.BIT.ABWH2		= 0;		// 16bit幅設定H	CS2
	BSC.ABWCR.BIT.ABWL2		= 1;		// 16bit幅設定L	CS2
	BSC.ASTCR.WORD			= 0x0000;	// 外部バスウェイトステート挿入許可
	BSC.WTCRA.WORD			= 0x0000;	// 外部バスウェイトステート数(1)
	BSC.WTCRB.WORD			= 0x0000;	// 外部バスウェイトステート数(2)
	BSC.RDNCR.WORD			= 0x0000;	// 外部バスリードストローブタイミング
	BSC.CSACR.WORD			= 0x0000;	// 外部バスCSアサート期間拡張
	BSC.IDLCR.WORD			= 0x0000;	// 外部バスアイドルサイクル
	BSC.BCR1.WORD			= 0x0000;	// バスコントロールレジスタ1
	BSC.BCR2.BYTE			= 0x02;		// バスコントロールレジスタ2
	BSC.ENDIANCR.BYTE		= 0x00;		// エンディアンコントロールレジスタ
	BSC.SRAMCR.WORD			= 0x0600;	// SRAMモードコントロールレジスタ
	BSC.BROMCR.WORD			= 0x0000;	// バーストROMインターフェースコントロールレジスタ
	BSC.MPXCR.WORD			= 0x0000;	// アドレスデータMPXコントロールレジスタ
}

// --------------------------------------------------------------------
// EXDMAC初期化
// --------------------------------------------------------------------
void Init_EXDMAC(void)
{
	//=========================================
	// Configure EXDMAC0 for TFT LCD Refresh Cycle
	//=========================================
	//--------------------------
	// Start EXDMAC0
	//--------------------------
//	MSTP.CRA.BIT._EXDMAC  = 0;
	//------------------------
	// Initialize EXDMAC0
	//------------------------
	EXDMAC0.EDSAR			= 0x200000;		//*ADATA		// EXDMA ソースアドレスレジスタ
	EXDMAC0.EDDAR			= 0x400000;		//LCD_D			// EXDMA デスティネーションアドレスレジスタ
	EXDMAC0.EDOFR			= 0x00000000;					// EXDMA オフセットレジスタ
	EXDMAC0.EDTCR			= 0x00025800;					// EXDMA 転送カウントレジスタ 320*240*2=0x00025800
//	EXDMAC0.EDBSR			= (320 << 16) + (320 << 0);		// EXDMA ブロックサイズレジスタ
	EXDMAC0.EDMDR.LONG		= 0x00004006;					// EXDMA モードコントロールレジスタ
	EXDMAC0.EDACR.LONG		= 0x00200000;					// EXDMA アドレスコントロールレジスタ
}

// --------------------------------------------------------------------
// DMA初期化
// --------------------------------------------------------------------
void Init_DMAC(void)
{
	//=========================================
	// Configure DMAC0 for TFT LCD Graphic Copy
	//=========================================
	//--------------------------
	// Start DMAC0
	//--------------------------
//	MSTP.CRA.BIT._DMAC = 0;
	//------------------------
	// Initialize DMAC0
	//------------------------
	DMAC0.DOFR			= 0x00000000;	// DMA オフセットレジスタ
	DMAC0.DMDR.LONG		= 0x00004005;	// DMA モードコントロールレジスタ
	DMAC0.DACR.LONG		= 0x00220000;	// DMA アドレスコントロールレジスタ
	
	//=========================================
	// Configure DMAC1 for TFT LCD Paint
	//=========================================
	//------------------------
	// Initialize DMAC1
	//------------------------
	DMAC1.DOFR			= 0x00000000;	// DMA オフセットレジスタ
	DMAC1.DMDR.LONG		= 0x00004005;	// DMA モードコントロールレジスタ
	DMAC1.DACR.LONG		= 0x00020000;	// DMA アドレスコントロールレジスタ
	
	//=========================================
	// Configure DMAC2 for TFT LCD Graphic Copy Large
	//=========================================
	//------------------------
	// Initialize DMAC2
	//------------------------
	DMAC2.DOFR			= 0x00000004;	// DMA オフセットレジスタ
	DMAC2.DMDR.LONG		= 0x00004005;	// DMA モードコントロールレジスタ
	DMAC2.DACR.LONG		= 0x00210000;	// DMA アドレスコントロールレジスタ

}

// --------------------------------------------------------------------
// TPU初期化
// --------------------------------------------------------------------
void Init_TPU(void)
{
	TPU.TSTR.BYTE			= 0x00;		// タイマスタートレジスタクリア
	
	//--------------------------
	// Module Start TPU0-5
	//--------------------------
//	MSTP.CRA.BIT._TPUL  = 0;
	//=========================================
	// Configure TPU0 for TFT LCD Refresh Cycle
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRF.BIT._TPU0 = 4;
	//----------------------------
	// Initialize TPU0
	//----------------------------
	TPU0.TCR.BYTE			= 0x2B;		// タイマコントロールレジスタ(TGRAでクリア/立上り/φ／64)
	TPU0.TIOR.BYTE.H		= 0x00;		// タイマI/Oコントロールレジスタ(H)
	TPU0.TIOR.BYTE.L		= 0x00;		// タイマI/Oコントロールレジスタ(L)
	TPU0.TIER.BYTE			= 0x41;		// タイマインタラプトイネーブルレジスタ
	TPU0.TSR.BYTE			= 0xC0;		// タイマステータスレジスタ
	TPU0.TCNT				= 0x0000;	// タイマカウンタ
//	TPU0.TGRA				= 0x249F;	// タイマジェネラルレジスタA(fps40)
//	TPU0.TGRA				= 0x30D4;	// タイマジェネラルレジスタA(fps30)
	TPU0.TGRA				= 0x493E;	// タイマジェネラルレジスタA(fps20)
//	TPU0.TGRA				= 0x927C;	// タイマジェネラルレジスタA(fps10)
	TPU0.TGRB				= 0;		// タイマジェネラルレジスタB
	TPU0.TGRC				= 0;		// タイマジェネラルレジスタC
	TPU0.TGRD				= 0;		// タイマジェネラルレジスタD
	TPU0.TMDR.BYTE			= 0xC0;		// タイマモードレジスタ(すべて通常動作)
	
	//=========================================
	// Configure TPU3 for BEEP
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRG.BIT._TPU3 = 3;
	//----------------------------
	// Initialize TPU3
	//----------------------------
	TPU3.TCR.BYTE			= 0xA8;		// タイマコントロールレジスタ(TGRAでクリア/立上り/φ／1)
	TPU3.TIOR.BYTE.H		= 0x00;		// タイマI/Oコントロールレジスタ(H)
	TPU3.TIOR.BYTE.L		= 0x21;		// タイマI/Oコントロールレジスタ(L)
	TPU3.TIER.BYTE			= 0x40;		// タイマインタラプトイネーブルレジスタ
	TPU3.TSR.BYTE			= 0xC0;		// タイマステータスレジスタ
	TPU3.TCNT				= 0x0000;	// タイマカウンタ
	TPU3.TGRC				= 0x1770;	// タイマジェネラルレジスタA(4KHz)
//	TPU3.TGRD				= 0x0BB8;	// タイマジェネラルレジスタB(50%)	(最大音)
	TPU3.TGRD				= 0x0000;	// タイマジェネラルレジスタB(0%)	(消音)
	TPU3.TMDR.BYTE			= 0xC3;		// タイマモードレジスタ(PWMモード2)
	
	//=========================================
	// Configure TPU4 for TFT LCD Back Light PWM
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRG.BIT._TPU4 = 3;
	//----------------------------
	// Initialize TPU4
	//----------------------------
	TPU4.TCR.BYTE			= 0x28;		// タイマコントロールレジスタ(TGRAでクリア/立上り/φ／1)
	TPU4.TIOR.BYTE			= 0x21;		// タイマI/Oコントロールレジスタ
	TPU4.TIER.BYTE			= 0x40;		// タイマインタラプトイネーブルレジスタ
	TPU4.TSR.BYTE			= 0xC0;		// タイマステータスレジスタ
	TPU4.TCNT				= 0x0000;	// タイマカウンタ
	TPU4.TGRA				= 0x2580;	// タイマジェネラルレジスタA(2.5KHz)
	TPU4.TGRB				= 0x2579;	// タイマジェネラルレジスタB(0%)
	TPU4.TMDR.BYTE			= 0xC2;		// タイマモードレジスタ(PWMモード1)
	
	//=========================================
	// Configure TPU6 for LED Dimmer Cycle
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRL.BIT._TPU6A = 6;
	//----------------------------
	// Initialize TPU6
	//----------------------------
	TPU6.TCR.BYTE			= 0x28;		// タイマコントロールレジスタ(TGRAでクリア/立上り/φ／1)
	TPU6.TIOR.BYTE.H		= 0x00;		// タイマI/Oコントロールレジスタ(H)
	TPU6.TIOR.BYTE.L		= 0x00;		// タイマI/Oコントロールレジスタ(L)
	TPU6.TIER.BYTE			= 0x41;		// タイマインタラプトイネーブルレジスタ
	TPU6.TSR.BYTE			= 0xC0;		// タイマステータスレジスタ
	TPU6.TCNT				= 0x0000;	// タイマカウンタ
	TPU6.TGRA				= 0x5DC0;	// タイマジェネラルレジスタA(1KHz)
	TPU6.TGRB				= 0;		// タイマジェネラルレジスタB
	TPU6.TGRC				= 0;		// タイマジェネラルレジスタC
	TPU6.TGRD				= 0;		// タイマジェネラルレジスタD
	TPU6.TMDR.BYTE			= 0xC0;		// タイマモードレジスタ(すべて通常動作)
	
//	TPU.TSTR.BYTE			= 0x00;		// タイマスタートレジスタ
	TPU.TSYR.BYTE			= 0x00;		// タイマシンクロレジスタ
}

//=============================
// Global : UART Software FIFO
//=============================
#define UART_FIFO_DEPTH 256         					 // UART FIFO Depth
volatile unsigned char gUART_FIFO_Tx[UART_FIFO_DEPTH]; // Tx FIFO Buffer
volatile unsigned long gUART_FIFO_Tx_WP;               // Tx FIFO Read Pointer
volatile unsigned long gUART_FIFO_Tx_RP;               // Tx FIFO Write Pointer
volatile unsigned long gUART_FIFO_Tx_DC;               // Tx FIFO Data Count;
volatile unsigned char	sci_rcv[154];
volatile unsigned int	sci_rcv_pointer;
volatile unsigned int	sci_rcv_command;

// --------------------------------------------------------------------
// UART 送信処理
// --------------------------------------------------------------------
unsigned char UART_Tx(unsigned char byte)
{
	unsigned char possible;
	unsigned char tie_bkup;
	
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRQ.BIT._SCI5 = 5;
	//----------------------------------------------
	// Disable Interrupt TXI (still TDRE flag is ON)
	//----------------------------------------------
	tie_bkup = SCI5.SCR.BIT.TIE;
	//------------------------
	// Check FIFO Tx
	//------------------------
	possible = (gUART_FIFO_Tx_DC < UART_FIFO_DEPTH)? 1 : 0;
	//------------------------
	// Set the Tx Data in FIFO
	//------------------------
	if (possible)
	{
		gUART_FIFO_Tx[gUART_FIFO_Tx_WP] = byte;
		gUART_FIFO_Tx_WP = (gUART_FIFO_Tx_WP + 1) % UART_FIFO_DEPTH;
		gUART_FIFO_Tx_DC = gUART_FIFO_Tx_DC + 1;
		tie_bkup = 1;
	}
	SCI5.SCR.BIT.TIE = tie_bkup;
	
	return possible;
}

// --------------------------------------------------------------------
// UART 送信処理
// --------------------------------------------------------------------
void UART_Tx_Char(unsigned char byte)
{
	while(UART_Tx(byte) == 0);
}

// --------------------------------------------------------------------
// UART 送信ハンドラ
// --------------------------------------------------------------------
void Int_Handler_UART_Tx(void)
{
	//------------------------
	// If FIFO Tx has Data
	//------------------------
	if (gUART_FIFO_Tx_DC > 0)
    {
		SCI5.TDR = gUART_FIFO_Tx[gUART_FIFO_Tx_RP];
		gUART_FIFO_Tx_RP = (gUART_FIFO_Tx_RP + 1) % UART_FIFO_DEPTH;
		gUART_FIFO_Tx_DC = gUART_FIFO_Tx_DC - 1;
		SCI5.SSR.BIT.TDRE = 0;
	}
	//-------------------------
	// If FIFO Tx has no Data
	//-------------------------
	else
	{
		SCI5.SCR.BIT.TIE = 0;
	}
}

// --------------------------------------------------------------------
// UART 受信ハンドラ
// --------------------------------------------------------------------
void Int_Handler_UART_Rx(void)
{
    unsigned char byte;
	unsigned int lambda;
	
	if		(g_e2p_data.E2P_1.model == Freedom2)
	{
		sci_rcv[sci_rcv_pointer] = SCI5.RDR - 0x30;
		sci_rcv_pointer ++;
		
		if(sci_rcv_pointer >= 55)
		{
			sci_rcv_pointer = 0;
			if		(sci_rcv_command == 0)
			{
				g_Freedom2_data.RPM					= sci_rcv[0]  * 10000 + sci_rcv[1]  * 1000 + sci_rcv[2]  * 100 + sci_rcv[3]  * 10 + sci_rcv[4] ;
				g_Freedom2_data.ManifoldPressure	=                       sci_rcv[5]  * 1000 + sci_rcv[6]  * 100 + sci_rcv[7]  * 10 + sci_rcv[8] ;
				g_Freedom2_data.EngineTemp			= sci_rcv[9]  * 10000 + sci_rcv[10] * 1000 + sci_rcv[11] * 100 + sci_rcv[12] * 10 + sci_rcv[13];
				g_Freedom2_data.InletAirTemp		= sci_rcv[14] * 10000 + sci_rcv[15] * 1000 + sci_rcv[16] * 100 + sci_rcv[17] * 10 + sci_rcv[18];
				g_Freedom2_data.BarometricPressure	=                       sci_rcv[19] * 1000 + sci_rcv[20] * 100 + sci_rcv[21] * 10 + sci_rcv[22];
				g_Freedom2_data.ThrottlePosition	=                       sci_rcv[23] * 1000 + sci_rcv[24] * 100 + sci_rcv[25] * 10 + sci_rcv[26];
				g_Freedom2_data.BatteryVoltage		=                                            sci_rcv[27] * 100 + sci_rcv[28] * 10 + sci_rcv[29];
				g_Freedom2_data.ValidFuelTime		=                       sci_rcv[30] * 1000 + sci_rcv[31] * 100 + sci_rcv[32] * 10 + sci_rcv[33];
				g_Freedom2_data.InvalidFuelTime		=                       sci_rcv[34] * 1000 + sci_rcv[35] * 100 + sci_rcv[36] * 10 + sci_rcv[37];
				g_Freedom2_data.IgnitionAdvance		=                                                                sci_rcv[38] * 10 + sci_rcv[39];
				g_Freedom2_data.Status				= sci_rcv[40] * 10000 + sci_rcv[41] * 1000 + sci_rcv[42] * 100 + sci_rcv[43] * 10 + sci_rcv[44];
				g_Freedom2_data.GroundSpeed			= sci_rcv[45] * 10000 + sci_rcv[46] * 1000 + sci_rcv[47] * 100 + sci_rcv[48] * 10 + sci_rcv[49];
				lambda								= sci_rcv[50] * 10000 + sci_rcv[51] * 1000 + sci_rcv[52] * 100 + sci_rcv[53] * 10 + sci_rcv[54];
				g_Freedom2_data.AFR					= (lambda & 0xFF00) >> 8;
				g_Freedom2_data.TargetAFR			= (lambda & 0x00FF);
			}
			else if	(sci_rcv_command == 1)
			{
				g_Freedom2_data.IATCorrection		= sci_rcv[0]  * 10000 + sci_rcv[1]  * 1000 + sci_rcv[2]  * 100 + sci_rcv[3]  * 10 + sci_rcv[4] ;
				g_Freedom2_data.ETCorrection		= sci_rcv[5]  * 10000 + sci_rcv[6]  * 1000 + sci_rcv[7]  * 100 + sci_rcv[8]  * 10 + sci_rcv[9] ;
				g_Freedom2_data.EStartCorrection	= sci_rcv[10] * 10000 + sci_rcv[11] * 1000 + sci_rcv[12] * 100 + sci_rcv[13] * 10 + sci_rcv[14];
				g_Freedom2_data.AccelCorrection		= sci_rcv[15] * 10000 + sci_rcv[16] * 1000 + sci_rcv[17] * 100 + sci_rcv[18] * 10 + sci_rcv[19];
				g_Freedom2_data.PowerCorrection		= sci_rcv[20] * 10000 + sci_rcv[21] * 1000 + sci_rcv[22] * 100 + sci_rcv[23] * 10 + sci_rcv[24];
				g_Freedom2_data.FeedbackCorrection	= sci_rcv[25] * 10000 + sci_rcv[26] * 1000 + sci_rcv[27] * 100 + sci_rcv[28] * 10 + sci_rcv[29];
				g_Freedom2_data.IdolCorrection		= sci_rcv[30] * 10000 + sci_rcv[31] * 1000 + sci_rcv[32] * 100 + sci_rcv[33] * 10 + sci_rcv[34];
				g_Freedom2_data.DecelCutCorrection	= sci_rcv[35] * 10000 + sci_rcv[36] * 1000 + sci_rcv[37] * 100 + sci_rcv[38] * 10 + sci_rcv[39];
				g_Freedom2_data.BaroCorrection		= sci_rcv[40] * 10000 + sci_rcv[41] * 1000 + sci_rcv[42] * 100 + sci_rcv[43] * 10 + sci_rcv[44];
				g_Freedom2_data.IdolIGCorrection	= sci_rcv[45] * 10000 + sci_rcv[46] * 1000 + sci_rcv[47] * 100 + sci_rcv[48] * 10 + sci_rcv[49];
				g_Freedom2_data.RetardCorrection	= sci_rcv[50] * 10000 + sci_rcv[51] * 1000 + sci_rcv[52] * 100 + sci_rcv[53] * 10 + sci_rcv[54];
			}
			else
			{
				//
			}
		}
		else
		{
			//
		}
/*	}
	else if	(g_e2p_data.E2P_1.model == MSquirt1)
	{
		sci_rcv[sci_rcv_pointer] = SCI5.RDR;
		sci_rcv_pointer ++;
//		if(sci_rcv_pointer >= 154)
		if(sci_rcv_pointer >32)
		{
			sci_rcv_pointer = 0;
			g_Megasquirt1_data.rpm				= ((unsigned int) sci_rcv[6]  << 8) + sci_rcv[7] ;
			g_Megasquirt1_data.advance			= ((unsigned int) sci_rcv[8]  << 8) + sci_rcv[9] ;
//			g_Megasquirt1_data.afrtgt1			=        				              sci_rcv[12];
//			g_Megasquirt1_data.afrtgt2			=        				              sci_rcv[13];
//			g_Megasquirt1_data.barometer		= ((unsigned int) sci_rcv[16] << 8) + sci_rcv[17];
//			g_Megasquirt1_data.map				= ((unsigned int) sci_rcv[18] << 8) + sci_rcv[19];
//			g_Megasquirt1_data.mat				= ((unsigned int) sci_rcv[20] << 8) + sci_rcv[21];
//			g_Megasquirt1_data.coolant			= ((unsigned int) sci_rcv[22] << 8) + sci_rcv[23];
//			g_Megasquirt1_data.tps				= ((unsigned int) sci_rcv[24] << 8) + sci_rcv[25];
//			g_Megasquirt1_data.batteryVoltage	= ((unsigned int) sci_rcv[26] << 8) + sci_rcv[27];
//			g_Megasquirt1_data.afr1				= ((unsigned int) sci_rcv[28] << 8) + sci_rcv[29];
//			g_Megasquirt1_data.afr2				= ((unsigned int) sci_rcv[30] << 8) + sci_rcv[31];
		}
		else
		{
			//
		}*/
	}
	else
	{
		//
	}
	
	SCI5.SSR.BIT.RDRF = 0;
}

// --------------------------------------------------------------------
// UART 受信エラーハンドラ
// --------------------------------------------------------------------
void Int_Handler_UART_Rx_ERR(void)
{
	SCI5.SSR.BIT.FER = 0;
	SCI5.SSR.BIT.ORER = 0;
	SCI5.SSR.BIT.PER = 0;
	SCI5.SSR.BIT.RDRF = 0;
}

// --------------------------------------------------------------------
// UART 送信終了ハンドラ
// --------------------------------------------------------------------
void Int_Handler_UART_Tx_END(void)
{
	SCI5.SSR.BIT.TEND = 0;
}
