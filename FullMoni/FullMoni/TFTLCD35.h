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
// filename		:	TFTLCD35.h
// brief		:	FullMoni rev.B TFT液晶管理
// author		:	Tomoya Sato
// update		:	2013/06/16
// version		:	1.03
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#ifndef _TFTLCD35_H_
#define _TFTLCD35_H_

// --------------------------------------------------------------------
// extern宣言
// --------------------------------------------------------------------
extern volatile unsigned int g_refresh_done;

// --------------------------------------------------------------------
// プロトタイプ宣言
// --------------------------------------------------------------------
void delay(unsigned int t);
void write_comm(unsigned int);
void write_data(unsigned int);
void Init_TFTLCD(void);
void Display_Home(void);
void LCD_Refresh(void);
void LCD_locate(unsigned int x, unsigned int y);
void LCD_pset(unsigned int x, unsigned int y, unsigned int color);
void LCD_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
void LCD_line2(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
void swap(int *x0, int *x1);
void LCD_FadeIn(void);
void LCD_FadeOUT(void);
void FONT_open(void);
void LCD_CLR(unsigned int color);
void LCD_PAINT(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
void LCD_Gcopy(unsigned int p, unsigned int q, unsigned int w, unsigned int h, volatile unsigned int *sorce);
void LCD_textout(char chr[]);//, unsigned int color);
void LCD_CHR_Copy_Smallfont(unsigned char chr);
//void LCD_CHR_Alpha_Smallfont(unsigned char chr, unsigned int color);
void LCD_CHR_copyBN(unsigned char chr);
void LCD_CHR_copyBNR(unsigned char chr);
void LCD_CHR_copyBN2(unsigned char chr);
//void LCD_CHR_drawBN(unsigned char chr[]);
void LCD_INT_draw(int num, unsigned int figure, unsigned int dp);
void LCD_INT_drawBN(int num, unsigned int figure, unsigned int dp);
void LCD_INT_drawBNR(int num, unsigned int figure, unsigned int dp);
void LCD_INT_drawBN2(int num, unsigned int figure, unsigned int dp);
//void LCD_NUM_drawBN(int num, unsigned int figure);
//void LCD_NUM_drawBNF(int num, unsigned int figure, unsigned int f);
//void LCD_CHR_copyBN2(unsigned char chr);
//void LCD_CHR_drawBN2(unsigned char chr[]);
//void LCD_NUM_drawBN2(int num, unsigned int figure);
//void LCD_NUM_drawBN2F(int num, unsigned int figure, unsigned int f);
//void LCD_CHR_copyB(unsigned int x, unsigned int y, unsigned char chr, unsigned int color);
//void LCD_CHR_drawB(unsigned int x, unsigned int y, unsigned char chr[], unsigned int color);

// --------------------------------------------------------------------
// 多重インクルード防止
// --------------------------------------------------------------------
#endif /* _TFTLCD35_H_ */
