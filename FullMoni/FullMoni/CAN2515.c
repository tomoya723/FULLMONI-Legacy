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
// filename		:	CAN2515.c
// brief		:	FullMoni rev.B CAN管理
// author		:	Tomoya Sato
// update		:	2013/03/31
// version		:	1.02
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "iodefine.h"
#include "CAN2515.h"
#include "spi.h"

// --------------------------------------------------------------------
// MPC2515初期化
// --------------------------------------------------------------------
void CANInit(unsigned char brp)
{
	unsigned char reg;
	
	CAN_SPI_CS_H;
	
	CANReset();
	
	CANSetOpMode(CAM_MODE_CONFIG);
	
	reg = 64 + brp;
	CANWriteReg(CAN_CNF1, reg);
	
	reg = 0x92;
	CANWriteReg(CAN_CNF2, reg);
	
	reg = 0x02;
	CANWriteReg(CAN_CNF3, reg);
	
//	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
}


// --------------------------------------------------------------------
// CAN受信チェック
// --------------------------------------------------------------------
unsigned char CANRxCheck(unsigned char rxbnum)
{
	unsigned char rxstat;
	
	rxstat = CANReadRXStat();			// 受信ステータス取得
	
	if(rxbnum == 0)
	{
		return rxstat & 1<<MsgInRXB0;
	}
	else if(rxbnum == 1)
	{
		return rxstat & 1<<MsgInRXB1;
	}
	
	return rxstat & ( (1<<MsgInRXB0) | (1<<MsgInRXB1) );
}


// --------------------------------------------------------------------
// CANリセット
// --------------------------------------------------------------------
void CANReset(void)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_RESET);		// リセット
	
	CAN_SPI_CS_H;
}


// --------------------------------------------------------------------
// CANレジスタ バイト・ライト
// --------------------------------------------------------------------
void CANWriteReg(unsigned char adrs, unsigned char data)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_WRITE);		// バイト・ライト
	SPI_TxRx(adrs);
	SPI_TxRx(data);
	
	CAN_SPI_CS_H;
}

// --------------------------------------------------------------------
// CANレジスタ・リード
// ステータス・リード
// 受信ステータス・リード  (3機能兼用ルーチン)
// --------------------------------------------------------------------
unsigned char CANRegRead2B(unsigned char inst, unsigned char adrs)
{
	unsigned char dat;
	
	CAN_SPI_CS_L;
	
	// 2バイト出力(データ入力は無視)
	SPI_TxRx(inst);			// インストラクション
	SPI_TxRx(adrs);
	
	// データ入力(ステータスの場合は、2回目のリピートデータ)
	dat = 0;
	dat = SPI_TxRx(0xFF);
	
	CAN_SPI_CS_H;
	
	return dat;
}

#ifndef CANSetSidFilteMask
// --------------------------------------------------------------------
// CAN SID フィルタ、マスク設定 (兼用ルーチン)
// --------------------------------------------------------------------
void CANSetSidFilteMask(unsigned char adrs, unsigned int sid)
{
	CANWriteReg(adrs, (unsigned char)(sid>>3));			// HIGH
	CANWriteReg(adrs + 1, (unsigned char)(sid<<5));		// LOW
}
#endif


// --------------------------------------------------------------------
// CANビット・モデファイ・コマンド
// --------------------------------------------------------------------
void CANBitModCmd(unsigned char adrs, unsigned char mask, unsigned char data)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_BIT_MOD);			// ビット・モデファイ
	SPI_TxRx(adrs);
	SPI_TxRx(mask);
	SPI_TxRx(data);
	
	CAN_SPI_CS_H;
}


// --------------------------------------------------------------------
// CAN送／受信バッファ シーケンシャル・リード／ライト (兼用ルーチン)
// --------------------------------------------------------------------
void CANTxRxBufRW(unsigned char inst, unsigned char readop, unsigned char *data, unsigned char cnt)
{
	unsigned char dat;
	unsigned char p;
	
	CAN_SPI_CS_L;
	
	// インストラクションの送信
	SPI_TxRx(inst);
	
	// =============== 送信/受信バッファ内容の送受信 =================
	if(readop)
	{
		// データ受信
		for(p = 0; p < cnt; p++)
		{
			dat = 0;
			dat = SPI_TxRx(0xFF);
			data[p] = dat;
		}
	}
	else
	{
		// データ送信
		for(p = 0; p < cnt; p++)
		{
			dat = data[p];
			SPI_TxRx(dat);
		}
	}
	
	CAN_SPI_CS_H;
}
