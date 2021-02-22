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
// filename		:	spi.c
// brief		:	FullMoni rev.C SPI通信処理
// author		:	Tomoya Sato
// update		:	2021/02/21
// version		:	1.06
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "iodefine.h"
#include "spi.h"

// --------------------------------------------------------------------
// 初期ボーレート
// --------------------------------------------------------------------
#define SPI_INITIAL_BAUD_RATE 6000 // kbps

// --------------------------------------------------------------------
// Initialize SPI (SCI0)
// --------------------------------------------------------------------
void Init_SPI(void)
{
	//----------------------------
	// Disable Interrupt
	//----------------------------
	INTC.IPRK.BIT._SCI0 = 0;
	//------------------------
	// Start SCI0 System Clock
	//------------------------
//	MSTP.CRB.BIT._SCI0 = 0;
	//----------------------------
	// P22 : TxD0 MOSI(MCP2515)
	// P21 : RxD0 MISO(MCP2515)
	// P20 : SCK0 SCK (MCP2515)
	//----------------------------
	SCI0.SCR.BIT.TE = 0;
	SCI0.SCR.BIT.RE = 0;
	//----------------------------
	// Clocked Serial Mode
	//----------------------------
	SCI0.SMR.BYTE	  = 0x80; // 10000000
	SCI0.SCMR.BIT.SDIR = 1;	// MSB first
	//----------------------------
	//Baud Rate
	//----------------------------
	SPI_Set_BaudRate(SPI_INITIAL_BAUD_RATE);
	//----------------------------
	// Set TE & RE
	//----------------------------
	SCI0.SCR.BIT.TE = 1;
	SCI0.SCR.BIT.RE = 1;
}

// --------------------------------------------------------------------
// Set SPI Baud Rate
// --------------------------------------------------------------------
void SPI_Set_BaudRate(unsigned int kbps)
{
//	unsigned short brr;
	unsigned long i;

	//--------------
	// Wait for Tx
	//--------------
	while(SCI0.SSR.BIT.TDRE == 0);	// Wait for TDRE = 1
	while(SCI0.SSR.BIT.TEND == 0);	// Wait for TEND = 1
	
	//----------------
	// Clear TE & RE
	//----------------
	SCI0.SCR.BIT.TE = 0;
	SCI0.SCR.BIT.RE = 0;
	
	for(i = 0; i < 100000; i++);	// Wait for 1bit period
	
	//---------------
	// Clear Flags
	//---------------
	SCI0.SSR.BIT.RDRF = 0;
	SCI0.SSR.BIT.ORER = 0;
	SCI0.SSR.BIT.FER  = 0;
	SCI0.SSR.BIT.PER  = 0;
	//----------------------------
	// Set Baud Rate
	//   PCLK = 24MHz
	//   CKS  = 0
	//   BRR = 24 * 1000 * 1000 / (8 * (2^0-1) * 1000 * kbps) - 1
	//----------------------------
//	brr = (6000 / (unsigned short) kbps) - 1; //(24 * 1000) / (8 / 2 * kbps) - 1;
//	if(brr <   0) brr = 0;
//	if(brr > 255) brr = 255;
	//
	SCI0.SCR.BIT.CKE = 0;
	SCI0.SMR.BIT.CKS = 0;
//	SCI0.BRR = (unsigned char) brr;
	SCI0.BRR = 0;
	//----------------------------
	// Wait for 1bit period
	//----------------------------
	for(i = 0; i < 100000; i++);
	//----------------
	// Set TE & RE
	//----------------
//	SCI0.SCR.BIT.TE = 1;
//	SCI0.SCR.BIT.RE = 1;
}

// --------------------------------------------------------------------
// SPI Tx and Rx a Byte
// --------------------------------------------------------------------
unsigned char SPI_TxRx(unsigned int byte_tx)
{
	unsigned char byte_rx;
	
	// Tx
	while(SCI0.SSR.BIT.TDRE == 0);		// Wait for TDRE = 1

	SCI0.TDR = byte_tx;					// Set TDR
										// Clear TDRE
	SCI0.SSR.BIT.TDRE = 0;				// read 1 and write 0

	while(SCI0.SSR.BIT.TEND == 0);		// Wait for TEND = 1
										// Clear TEND
	SCI0.SSR.BIT.TEND = 0;				// read 1 and write 0
	
	// Rx
	while(SCI0.SSR.BIT.RDRF == 0);		// Wait for RDRF = 1
	if(SCI0.SSR.BIT.ORER) SCI0.SSR.BIT.ORER = 0;	// If Over Run found, Clear ORER
	byte_rx = SCI0.RDR;					// Get RDR
										// Clear RDRF
	SCI0.SSR.BIT.RDRF = 0;				// read 1 and write 0

	return byte_rx;
}
