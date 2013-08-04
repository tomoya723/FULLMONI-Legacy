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
// filename		:	ADS7843.h
// brief		:	FullMoni rev.B タッチパネル管理
// author		:	Tomoya Sato
// update		:	2013/08/05
// version		:	1.04
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _ADS7843_H_
#define _ADS7843_H_

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_ADS7843(void);
void Start_ADS7843(void);
unsigned int Touch_SampX(void);
unsigned int Touch_SampY(void);
void Touch_Read(void);

// --------------------------------------------------------------------
// SPIポート定義
// --------------------------------------------------------------------
#define TP_SPI_SO_BIT   	0
#define TP_SPI_SI_BIT   	1
#define TP_SPI_SCK_BIT  	2
#define TP_SPI_CS_BIT   	3

#define TP_SPI_SO_DDR   	P6.DDR
#define TP_SPI_SI_DDR   	P6.DDR
#define TP_SPI_SCK_DDR  	P6.DDR
#define TP_SPI_CS_DDR   	P6.DDR

#define TP_SPI_SO_PORT   	P6.DR.BYTE
#define TP_SPI_SI_PORT   	P6.PORT.BYTE
#define TP_SPI_SCK_PORT   	P6.DR.BYTE
#define TP_SPI_CS_PORT   	P6.DR.BYTE

// --------------------------------------------------------------------
// SPIポート ビット操作
// --------------------------------------------------------------------
#define TP_SPI_CS_H			TP_SPI_CS_PORT	|=	(1<<TP_SPI_CS_BIT)
#define TP_SPI_SO_H			TP_SPI_SO_PORT	|=	(1<<TP_SPI_SO_BIT)
#define TP_SPI_SCK_H		TP_SPI_SCK_PORT	|=	(1<<TP_SPI_SCK_BIT)

#define TP_SPI_CS_L			TP_SPI_CS_PORT	&=~	(1<<TP_SPI_CS_BIT)
#define TP_SPI_SO_L			TP_SPI_SO_PORT	&=~	(1<<TP_SPI_SO_BIT)
#define TP_SPI_SCK_L		TP_SPI_SCK_PORT	&=~	(1<<TP_SPI_SCK_BIT)

#define TP_SPI_SI			(TP_SPI_SI_PORT	&	(1<<TP_SPI_SI_BIT))

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _ADS7843_H_ */
