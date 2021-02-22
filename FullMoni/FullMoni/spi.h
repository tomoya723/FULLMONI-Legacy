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
// filename		:	spi.h
// brief		:	FullMoni rev.C SPI通信処理
// author		:	Tomoya Sato
// update		:	2021/02/21
// version		:	1.06
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _SPI_H_
#define _SPI_H_

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void Init_SPI(void);
void SPI_Set_BaudRate(unsigned int kbps);
unsigned char SPI_TxRx(unsigned int byte_tx);

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _SPI_H_ */
