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
// filename		:	i2cEEPROM.h
// brief		:	FullMoni rev.B シリアルフラッシュROM管理
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _IIC_H_
#define _IIC_H_

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_IIC( void );
unsigned char mtrs_start(const unsigned char *dtadd, unsigned char mtbuf,unsigned short dtnum);
unsigned char mrcv_start(const unsigned char *dtadd, unsigned short dtnum);
unsigned char mrandrd_start(const unsigned char *mrbuf, unsigned char mtbuf, unsigned short dtnum);
void iici0_interrupt(void);
void receive_stop_condition(void);
void master_transfer(void);
void master_receive(void);
void master_randomread(void);

// --------------------------------------------------------------------
// define宣言
// --------------------------------------------------------------------
#define SLAVE_ADDR	  0xA0			// スレーブアドレス(0bit=0)

#define MT_ID		   0xA0			// Master transfer:Slave ID(0bit=0)
#define MR_ID		   0xA1			// Master receive :Slave ID(0bit=1)

// モード定義
#define MODE_MR_RAND	5			// Master random receive mode
#define MODE_MT			4			// Master transfer mode
#define MODE_MR			3			// Master receive mode
#define MODE_ST			2			// Slave transfer mode
#define MODE_SR			1			// Slave receive mode
#define MODE_IDLE		0			// I2C idle mode

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _IIC_H_ */
