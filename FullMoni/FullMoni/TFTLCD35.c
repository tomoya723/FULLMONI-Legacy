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
// filename		:	TFTLCD35.c
// brief		:	FullMoni rev.B TFT液晶管理
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
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

// --------------------------------------------------------------------
// defineマクロ宣言
// --------------------------------------------------------------------
#define	LCD_RS	P1.DR.BIT.B0		//  コマンド信号 (RS for Parallel Interface)
#define	LCD_RES	P2.DR.BIT.B4		//  リセット信号

// --------------------------------------------------------------------
// グローバル変数宣言
// --------------------------------------------------------------------
volatile unsigned int g_LCD_x;
volatile unsigned int g_LCD_y;
volatile unsigned int g_drawbuff_flg;
volatile unsigned int g_oneshot_flg;

// --------------------------------------------------------------------
// ソフトディレイ関数
// --------------------------------------------------------------------
void delay(unsigned int t)
{
	unsigned int t1;
	while(t --)
	for(t1 = 11000; t1 > 0; t1 --)
	{
		nop();
	}
}
// --------------------------------------------------------------------
// TFT LCD バス コマンド出力
// --------------------------------------------------------------------
void write_comm(unsigned int command)
{
	LCD_RS = 0;		// CLR_RS;
	LCD_D = command;
}

// --------------------------------------------------------------------
// TFT LCD バス データ出力
// --------------------------------------------------------------------
void write_data(unsigned int data)
{
	LCD_RS = 1;		// SET_RS;
	LCD_D = data;
}
// --------------------------------------------------------------------
// TFT LCD 初期化
// --------------------------------------------------------------------
void Init_TFTLCD()
{
	
	LCD_RS = 1;		// SET_RS;
	LCD_RES = 0;	//	CLR_RESET;
	delay(200);
	LCD_RES = 1;	//	SET_RESET;
	delay(500);
	
	write_comm(0x0028);		// VCOM OTP
	write_data(0x0006);		// Page 55-56 of SSD2119 datasheet
	
	write_comm(0x0000);		// start Oscillator
	write_data(0x0001);		// Page 36 of SSD2119 datasheet
	
	write_comm(0x0010);		// Sleep mode
	write_data(0x0000);		// Page 49 of SSD2119 datasheet
	
	write_comm(0x0001);		// Driver Output Control
//	write_data(0x32EF);		// Page 36-39 of SSD2119 datasheet
	write_data(0x7AEF);		// Page 36-39 of SSD2119 datasheet
	
	write_comm(0x0002);		// LCD Driving Waveform Control
	write_data(0x0600);		// Page 40-42 of SSD2119 datasheet
	
	write_comm(0x0003);		// Power Control 1
	write_data(0x6A38);		// Page 43-44 of SSD2119 datasheet
	
	write_comm(0x0011);		// Entry Mode
	write_data(0x6870);		// Page 50-52 of SSD2119 datasheet
//	write_data(0x6860);		// Page 50-52 of SSD2119 datasheet	// 左右反転対策
	
	write_comm(0X000F);		// Gate Scan Position
	write_data(0x0000);		// Page 49 of SSD2119 datasheet
	
	write_comm(0X000B);		// Frame Cycle Control
	write_data(0x5308);		// Page 45 of SSD2119 datasheet
	
	write_comm(0x000C);		// Power Control 2
	write_data(0x0003);		// Page 47 of SSD2119 datasheet
	
	write_comm(0x000D);		// Power Control 3
	write_data(0x000A);		// Page 48 of SSD2119 datasheet
	
	write_comm(0x000E);		// Power Control 4
	write_data(0x2E00);		// Page 48 of SSD2119 datasheet
	
	write_comm(0x001E);		// Power Control 5
	write_data(0x00BE);		// Page 53 of SSD2119 datasheet
	
	write_comm(0x0025);		// Frame Frequency Control
	write_data(0x8000);		// Page 53 of SSD2119 datasheet
	
	write_comm(0x0026);		// Analog setting
	write_data(0x7800);		// Page 54 of SSD2119 datasheet
	
	write_comm(0x004E);		// Ram Address Set
	write_data(0x0000);		// Page 58 of SSD2119 datasheet
	
	write_comm(0x004F);		// Ram Address Set
	write_data(0x0000);		// Page 58 of SSD2119 datasheet
	
	write_comm(0x0012);		// Sleep mode
	write_data(0x08D9);		// Page 49 of SSD2119 datasheet
	
	// Gamma Control (R30h to R3Bh)
	// Page 56 of SSD2119 datasheet
	write_comm(0x0030);
	write_data(0x0000);
	
	write_comm(0x0031);
	write_data(0x0104);
	
	write_comm(0x0032);
	write_data(0x0100);
	
	write_comm(0x0033);
	write_data(0x0305);
	
	write_comm(0x0034);
	write_data(0x0505);
	
	write_comm(0x0035);
	write_data(0x0305);
	
	write_comm(0x0036);
	write_data(0x0707);
	
	write_comm(0x0037);
	write_data(0x0300);
	
	write_comm(0x003A);
	write_data(0x1200);
	
	write_comm(0x003B);
	write_data(0x0800);		 
	
	write_comm(0x0007);		// Display Control 
	write_data(0x0033);		// Page 45 of SSD2119 datasheet
	
	delay(150);
	//_delay_ms(150);
	
	write_comm(0x0022);		// RAM data write/read
}

// --------------------------------------------------------------------
// TDT LCD リフレッシュ処理
// --------------------------------------------------------------------
void Display_Home()
{
	long i;
	
	for(i = 0; i <= 1000; i++);	// 50ms割り込み安定の為ダミー
	
	write_comm(0x004E);		// RAM address set
	write_data(0x0000);		// Page 58 of SSD2119 datasheet
	write_comm(0x004F);		// RAM address set
	write_data(0x0000);		// Page 58 of SSD2119 datasheet
	
	write_comm(0x0044);		// Vertical RAM address position
	write_data(0xEF00);		// Page 57 of SSD2119 datasheet
	write_comm(0x0045);		// Horizontal RAM address position 
	write_data(0x0000);		// Page 57 of SSD2119 datasheet
	write_comm(0x0046);		// Horizontal RAM address position
	write_data(0x013F);		// Page 57 of SSD2119 datasheet
	
	write_comm(0x0022);		// RAM data write/read
	
	LCD_RS = 1;		// SET_RS;
	
	g_oneshot_flg ++;
	
	// フレームバッファの切り替え
	if(g_drawbuff_flg == 0)
	{
		EXDMAC0.EDSAR		= 0x200000;		//*ADATA		// EXDMA ソースアドレスレジスタ1
	}
	else
	{
		EXDMAC0.EDSAR		= 0x225800;		//*BDATA		// EXDMA ソースアドレスレジスタ2
	}
	EXDMAC0.EDDAR			= 0x400000;		//LCD_D			// EXDMA デスティネーションアドレスレジスタ
	EXDMAC0.EDTCR			= 0x00025800;					// EXDMA 転送カウントレジスタ 320*240*2=0x00025800
	
	EXDMAC0.EDMDR.BIT.DTE	= 1;
}

// --------------------------------------------------------------------
// TDT LCD リフレッシュ同期フレームバッファ更新処理
// --------------------------------------------------------------------
void LCD_Refresh(void)
{
	while(g_refresh_done == 0);
	g_refresh_done = 0;
	if(g_drawbuff_flg == 0){g_drawbuff_flg=1;}else{g_drawbuff_flg=0;}
}

// --------------------------------------------------------------------
// TFT LCD 描画座標設定
// --------------------------------------------------------------------
void LCD_locate(unsigned int x, unsigned int y)
{
	g_LCD_x = x;
	g_LCD_y = y;
}

// --------------------------------------------------------------------
// TFT LCD バックライト点灯
// --------------------------------------------------------------------
void LCD_FadeIN(void)
{
	static unsigned long y, z;
	
	for(z = 0x2579; z >= 0x10; z -- )
	{
		for(y = 0; y <= 100; y ++ )
		{
			TPU4.TGRB = z & 0xFFFF;
		}
	}
}

// --------------------------------------------------------------------
// TFT LCD バックライト消灯
// --------------------------------------------------------------------
void LCD_FadeOUT(void)
{
	static unsigned long y, z;
	
	for(z = 0x10; z <= 0x2579; z ++ )
	{
		for(y = 0; y <= 100; y ++ )
		{
			TPU4.TGRB = z & 0xFFFF;
		}
	}
}

// --------------------------------------------------------------------
// FONTデータ展開(Flash→内部RAM)
// --------------------------------------------------------------------
void FONT_open(void)
{
	static unsigned long icnt;
	
	for(icnt = 0; icnt < 0x00012C00; icnt ++ )
	{
//		*(FONTR + icnt) = *(FONT + icnt) & 0xF800;	// 白文字→青文字で転送
//		*(FONTR + icnt) = *(FONT + icnt) & 0x07E0;	// 白文字→緑文字で転送
		*(FONTR + icnt) = *(FONT + icnt) & 0x001F;	// 白文字→赤文字で転送
	}
}

// --------------------------------------------------------------------
// TFT LCD 点描画
// --------------------------------------------------------------------
void LCD_pset(unsigned int x, unsigned int y, unsigned int color)
{
	unsigned long z;
	
	z = y;
	
	if(g_drawbuff_flg)
	{
		*(ADATA + (x + z * 320)) = color;
	}
	else
	{
		*(BDATA + (x + z * 320)) = color;
	}
}

// --------------------------------------------------------------------
// TFT LCD 線描画
// --------------------------------------------------------------------
void LCD_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
	unsigned int st;
	int sx0, sx1, sy0, sy1;
	int dx, dy;
	int err;
	int ystep;
	unsigned long x, y;
	
	sx0 = (int) x0;
	sx1 = (int) x1;
	sy0 = (int) y0;
	sy1 = (int) y1;
	
	st = abs(sy1 - sy0) > abs(sx1 - sx0);
	
	if(st)
	{
		swap(&sx0, &sy0);
		swap(&sx1, &sy1);
	}
	
	if(sx0 > sx1)
	{
		swap(&sx0, &sx1);
		swap(&sy0, &sy1);
	}
	
	dx = sx1 - sx0;
	dy = abs(sy1 - sy0);
	err = dx >> 1;
	ystep = (sy0 < sy1)? +1 : -1;
	y = sy0;
	
	for(x = sx0; x <= sx1; x++)
	{
		if(st)
		{
			if((y >= 0) && (x >= 0) && (y < 320) && (x < 240))
			{
				if(g_drawbuff_flg)
				{
					*(ADATA + (y + x * 320)) = color;
				}
				else
				{
					*(BDATA + (y + x * 320)) = color;
				}
			}
		}
		else
		{
			if((x >= 0) && (y >= 0) && (x < 320) && (y < 240))
			{
				if(g_drawbuff_flg)
				{
					*(ADATA + (x + y * 320)) = color;
				}
				else
				{
					*(BDATA + (x + y * 320)) = color;
				}
			}
		}
		
		err = err - dy;
		if(err < 0)
		{
			y = y + ystep;
			err = err + dx;
		}
	}
}

// --------------------------------------------------------------------
// TFT LCD 線描画 2倍寸
// --------------------------------------------------------------------
void LCD_line2(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
	unsigned int st;
	int sx0, sx1, sy0, sy1;
	int dx, dy;
	int err;
	int ystep;
	unsigned long x, y;
	
	sx0 = (int) x0;
	sx1 = (int) x1;
	sy0 = (int) y0;
	sy1 = (int) y1;
	
	st = abs(sy1 - sy0) > abs(sx1 - sx0);
	
	if(st)
	{
		swap(&sx0, &sy0);
		swap(&sx1, &sy1);
	}
	
	if(sx0 > sx1)
	{
		swap(&sx0, &sx1);
		swap(&sy0, &sy1);
	}
	
	dx = sx1 - sx0;
	dy = abs(sy1 - sy0);
	err = dx >> 1;
	ystep = (sy0 < sy1)? +1 : -1;
	y = sy0;
	
	for(x = sx0; x < sx1; x++)
	{
		if(st)
		{
			if((y >= 0) && (x >= 0) && (y < 320) && (x < 240))
			{
				if(g_drawbuff_flg)
				{
					*(ADATA + (y + x       * 320)) = color;
					*(ADATA + ((y - 1) + x * 320)) = color;
					*(ADATA + ((y + 1) + x * 320)) = color;
					*(ADATA + (y + (x - 1) * 320)) = color;
					*(ADATA + (y + (x + 1) * 320)) = color;
				}
				else
				{
					*(BDATA + (y + x       * 320)) = color;
					*(BDATA + ((y - 1) + x * 320)) = color;
					*(BDATA + ((y + 1) + x * 320)) = color;
					*(BDATA + (y + (x - 1) * 320)) = color;
					*(BDATA + (y + (x + 1) * 320)) = color;
				}
			}
		}
		else
		{
			if((x >= 0) && (y >= 0) && (x < 320) && (y < 240))
			{
				if(g_drawbuff_flg)
				{
					*(ADATA + (x + y       * 320)) = color;
					*(ADATA + ((x - 1) + y * 320)) = color;
					*(ADATA + ((x + 1) + y * 320)) = color;
					*(ADATA + (x + (y - 1) * 320)) = color;
					*(ADATA + (x + (y + 1) * 320)) = color;
				}
				else
				{
					*(BDATA + (x + y       * 320)) = color;
					*(BDATA + ((x - 1) + y * 320)) = color;
					*(BDATA + ((x + 1) + y * 320)) = color;
					*(BDATA + (x + (y - 1) * 320)) = color;
					*(BDATA + (x + (y + 1) * 320)) = color;
				}
			}
		}
		
		err = err - dy;
		if(err < 0)
		{
			y = y + ystep;
			err = err + dx;
		}
	}
}

void swap(int *x0, int *x1)
{
	int temp;
	temp = *x0;
	*x0 = *x1;
	*x1 = temp;
}

/*
// --------------------------------------------------------------------
// TFT LCD 画面クリア(ソフトウェア転送版)
// --------------------------------------------------------------------
void LCD_CLR(unsigned int color)
{
	static unsigned long icnt;
	
	for(icnt = 0; icnt < 0x00012C00; icnt ++ )
	{
		if(g_drawbuff_flg)
		{
			*(ADATA + icnt) = color;
		}
		else
		{
			*(BDATA + icnt) = color;
		}
	}
}
*/

// --------------------------------------------------------------------
// TFT LCD 画面クリア(ハードウェアDMA1転送版)
// --------------------------------------------------------------------
void LCD_CLR(unsigned int color)
{
	unsigned int	*color_p;
	color_p = &color;
	
	DMAC1.DTCR = 0x00012C00 * 2;
	DMAC1.DSAR = color_p;
	if(g_drawbuff_flg)
	{
		DMAC1.DDAR = ADATA;
	}
	else
	{
		DMAC1.DDAR = BDATA;
	}
	DMAC1.DMDR.BIT.DTE	= 1;
	while(DMAC1.DMDR.BIT.DTIF == 0);
}

/*
// --------------------------------------------------------------------
// TFT LCD 画面塗りつぶし(ソフトウェア転送版)
// --------------------------------------------------------------------
void LCD_PAINT(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
	unsigned long	i, j;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i++)
		{
			if(g_drawbuff_flg)
			{
				*(ADATA + ((x + i) + (y + j) * 320)) = color;
			}
			else
			{
				*(BDATA + ((x + i) + (y + j) * 320)) = color;
			}
		}
	}
}
*/

// --------------------------------------------------------------------
// TFT LCD 画面塗りつぶし(ハードウェアDMA1転送版)
// --------------------------------------------------------------------
void LCD_PAINT(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
	unsigned long	j;
	unsigned int	*color_p;
	color_p = &color;
	
	for(j = 0; j < h; j++)
	{
		DMAC1.DTCR = w * 2;
		DMAC1.DSAR = color_p;
		if(g_drawbuff_flg)
		{
			DMAC1.DDAR = (ADATA + ((x) + (y + j) * 320));
		}
		else
		{
			DMAC1.DDAR = (BDATA + ((x) + (y + j) * 320));
		}
		DMAC1.DMDR.BIT.DTE	= 1;
		while(DMAC1.DMDR.BIT.DTIF == 0);
	}
}

/*
// --------------------------------------------------------------------
// TFT LCD 画像コピー描画(ソフトウェア転送版)
// --------------------------------------------------------------------
void LCD_Gcopy(unsigned int p, unsigned int q, unsigned int w, unsigned int h, volatile unsigned int *sorce)
{
	unsigned long	i, j;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i++)
		{
			if(g_drawbuff_flg)
			{
				*(ADATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320)) = *(sorce + ((p + i) + (q + j) * 320));
			}
			else
			{
				*(BDATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320)) = *(sorce + ((p + i) + (q + j) * 320));
			}
		}
	}
}
*/

// --------------------------------------------------------------------
// TFT LCD 画像コピー描画(ハードウェアDMA0転送版)
// --------------------------------------------------------------------
void LCD_Gcopy(unsigned int p, unsigned int q, unsigned int w, unsigned int h, volatile unsigned int *sorce)
{
	unsigned long	j;
	
	for(j = 0; j < h; j++)
	{
		DMAC0.DTCR = w * 2;
		DMAC0.DSAR = (sorce + ((p) + (q + j) * 320));
		if(g_drawbuff_flg)
		{
			DMAC0.DDAR = (ADATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		else
		{
			DMAC0.DDAR = (BDATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		DMAC0.DMDR.BIT.DTE	= 1;
		while(DMAC0.DMDR.BIT.DTIF == 0);
	}
}

// --------------------------------------------------------------------
// TFT LCD 文字列出力（小さめ文字）
// --------------------------------------------------------------------
void LCD_textout(char chr[])//, unsigned int color)
{
	unsigned int i;
	
	for(i = 0; i <= 32; i++)
	{
		if(chr[i] == '\0') return;
		LCD_CHR_Copy_Smallfont(chr[i]);			// 単純コピー出力を選択(高速)
//		LCD_CHR_Alpha_Smallfont(chr[i], color);	// 色指定アンチエイリアス出力を選択(低速)
	}
}

/*
// --------------------------------------------------------------------
// TFT LCD 文字単出力（小さめ文字・単純コピー出力）(ソフトウェア転送版)
// --------------------------------------------------------------------
void LCD_CHR_Copy_Smallfont(unsigned char chr)
{
	unsigned long i, j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 16) * 320) + ((((chr - 0x20) & 0x0000000F) * 10)) + 46080;
	
	for(j = 0; j < 16; j++)
	{
		for(i = 0; i < 10; i++)
		{
			if(g_drawbuff_flg)
			{
				(*(ADATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = *(FONT + font_addr + i + j * 320);
			}
			else
			{
				(*(BDATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = *(FONT + font_addr + i + j * 320);
			}
		}
	}
	g_LCD_x = g_LCD_x  + 10;
}
*/

// --------------------------------------------------------------------
// TFT LCD 文字単出力（小さめ文字・単純コピー出力）(ハードウェアDMA0転送版)
// --------------------------------------------------------------------
void LCD_CHR_Copy_Smallfont(unsigned char chr)
{
	unsigned long j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 16) * 320) + ((((chr - 0x20) & 0x0000000F) * 10)) + 46080;
	
	for(j = 0; j < 16; j++)
	{
		DMAC0.DTCR = 10 * 2;
		DMAC0.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC0.DDAR = (ADATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		else
		{
			DMAC0.DDAR = (BDATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		DMAC0.DMDR.BIT.DTE	= 1;
		while(DMAC0.DMDR.BIT.DTIF == 0);
	}
	g_LCD_x = g_LCD_x  + 10;
}

/*
// --------------------------------------------------------------------
// TFT LCD 文字単出力（小さめ文字・色指定アンチエイリアス出力）
// --------------------------------------------------------------------
void LCD_CHR_Alpha_Smallfont(unsigned char chr, unsigned int color)
{
	unsigned long	i, j, font_addr;
	unsigned long	dst_data, font_data;
	unsigned long	rd, gd, bd,rs, gs, bs, alpha;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 16) * 320) + ((((chr - 0x20) & 0x0000000F) * 10)) + 46080;
	
	for(j = 0; j < 16; j++)
	{
		for(i = 0; i < 10; i++)
		{
			if(g_drawbuff_flg)
			{
				dst_data	= (*(ADATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320)));	// 貼り付け先データの該当ピクセルデータの算出
			}
			else
			{
				dst_data	= (*(BDATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320)));	// 貼り付け先データの該当ピクセルデータの算出
			}
			font_data	= (*(FONT + font_addr + i + j * 320));						// フォントテーブルデータの該当ピクセルデータの算出(アルファデータ)
			rd			= ((dst_data >> 11) & 0x001F);								// 貼り付け先データのR要素の算出
			gd			= ((dst_data >>  5) & 0x003F);								// 貼り付け先データのG要素の算出
			bd			= ((dst_data      ) & 0x001F);								// 貼り付け先データのB要素の算出
			rs			= ((color         ) & 0x001F);								// フォント指定色のR要素の算出
			gs			= ((color    >>  5) & 0x003F);								// フォント指定色のG要素の算出
			bs			= ((color    >> 11) & 0x001F);								// フォント指定色のB要素の算出
			alpha		= font_data & 0x1F;											// フォントテーブルデータからアルファ量を算出
			rd			= (rd *  alpha       + rs * (0x1F -  alpha      )) / 0x1F;	// R要素のアルファブレンド
			gd			= (gd * (alpha << 1) + gs * (0x3F - (alpha << 1))) / 0x3F;	// G要素のアルファブレンド
			bd			= (bd *  alpha       + bs * (0x1F -  alpha      )) / 0x1F;	// B要素のアルファブレンド
			dst_data	= (rd << 11) | (gd << 5) | bd;	
			if(g_drawbuff_flg)
			{
				(*(ADATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = dst_data;
			}
			else
			{
				(*(BDATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = dst_data;
			}
		}
	}
	g_LCD_x = g_LCD_x + 10;
}
*/

/*
// --------------------------------------------------------------------
// TFT LCD 文字単出力（大き目）(ソフトウェア転送版)
// --------------------------------------------------------------------
void LCD_CHR_copyBN(unsigned char chr)
{
	unsigned long i, j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j++)
	{
		for(i = 0; i < 16; i++)
		{
			if(g_drawbuff_flg)
			{
				(*(ADATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = *(FONT + font_addr + i + j * 320);
			}
			else
			{
				(*(BDATA + ((g_LCD_x + i) + (g_LCD_y + j) * 320))) = *(FONT + font_addr + i + j * 320);
			}
		}
	}
	g_LCD_x = g_LCD_x  + 16;
}
*/

// --------------------------------------------------------------------
// TFT LCD 文字単出力（大き目）(ハードウェアDMA0転送版)
// --------------------------------------------------------------------
void LCD_CHR_copyBN(unsigned char chr)
{
	unsigned long j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j++)
	{
		DMAC0.DTCR = 16 * 2;
		DMAC0.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC0.DDAR = (ADATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		else
		{
			DMAC0.DDAR = (BDATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		DMAC0.DMDR.BIT.DTE	= 1;
		while(DMAC0.DMDR.BIT.DTIF == 0);
	}
	g_LCD_x = g_LCD_x  + 16;
}

// --------------------------------------------------------------------
// TFT LCD 文字単出力（大き目）(ハードウェアDMA0転送版) 展開FONT対象
// --------------------------------------------------------------------
void LCD_CHR_copyBNR(unsigned char chr)
{
	unsigned long j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j++)
	{
		DMAC0.DTCR = 16 * 2;
		DMAC0.DSAR = (FONTR + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC0.DDAR = (ADATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		else
		{
			DMAC0.DDAR = (BDATA + ((g_LCD_x) + (g_LCD_y + j) * 320));
		}
		DMAC0.DMDR.BIT.DTE	= 1;
		while(DMAC0.DMDR.BIT.DTIF == 0);
	}
	g_LCD_x = g_LCD_x  + 16;
}

// --------------------------------------------------------------------
// TFT LCD 文字単出力（大き目2倍）(ハードウェアDMA2転送版)
// --------------------------------------------------------------------
void LCD_CHR_copyBN2(unsigned char chr)
{
	unsigned long j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j++)
	{
		DMAC2.DTCR = 16 * 2;
		DMAC2.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC2.DDAR = (ADATA + ((g_LCD_x    ) + (g_LCD_y + j * 2    ) * 320));
		}
		else
		{
			DMAC2.DDAR = (BDATA + ((g_LCD_x    ) + (g_LCD_y + j * 2    ) * 320));
		}
		DMAC2.DMDR.BIT.DTE	= 1;
		while(DMAC2.DMDR.BIT.DTIF == 0);
		
		
		DMAC2.DTCR = 16 * 2;
		DMAC2.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC2.DDAR = (ADATA + ((g_LCD_x + 1) + (g_LCD_y + j * 2    ) * 320));
		}
		else
		{
			DMAC2.DDAR = (BDATA + ((g_LCD_x + 1) + (g_LCD_y + j * 2    ) * 320));
		}
		DMAC2.DMDR.BIT.DTE	= 1;
		while(DMAC2.DMDR.BIT.DTIF == 0);
		DMAC2.DTCR = 16 * 2;
		DMAC2.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC2.DDAR = (ADATA + ((g_LCD_x    ) + (g_LCD_y + j * 2 + 1) * 320));
		}
		else
		{
			DMAC2.DDAR = (BDATA + ((g_LCD_x    ) + (g_LCD_y + j * 2 + 1) * 320));
		}
		DMAC2.DMDR.BIT.DTE	= 1;
		while(DMAC2.DMDR.BIT.DTIF == 0);
		
		
		DMAC2.DTCR = 16 * 2;
		DMAC2.DSAR = (FONT + font_addr + j * 320);
		if(g_drawbuff_flg)
		{
			DMAC2.DDAR = (ADATA + ((g_LCD_x + 1) + (g_LCD_y + j * 2 + 1) * 320));
		}
		else
		{
			DMAC2.DDAR = (BDATA + ((g_LCD_x + 1) + (g_LCD_y + j * 2 + 1) * 320));
		}
		DMAC2.DMDR.BIT.DTE	= 1;
		while(DMAC2.DMDR.BIT.DTIF == 0);

	}
	g_LCD_x = g_LCD_x  + 32;
}

/*
// --------------------------------------------------------------------
// TFT LCD 文字列出力（大き目）
// --------------------------------------------------------------------
void LCD_CHR_drawBN(unsigned char chr[])
{
	unsigned int i;
	
	for(i = 0; i <= 19; i++)
	{
		if(chr[i] == '\0') return;
		LCD_CHR_copyBN(chr[i]);
	}
}
*/

// --------------------------------------------------------------------
// TFT LCD 整数値出力（小さ目）
// --------------------------------------------------------------------
void LCD_INT_draw(int num, unsigned int figure, unsigned int dp)
{
	int i, j, k, l, numw;
	unsigned char chr[6], temp, sign;
	
	if( figure > 8 ) return;
	
	if( num < 0)
	{
		num = (~num) + 1;
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	
	numw = num;
	if(dp > 0)
	{
		for(i = 1; i <= dp; i ++ )
		{
			numw = numw / 10;
		}
	}
	
	i = 0;
	l = 0;
	if(numw >= 10)
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			chr[i ++ ] = '.';			// 小数点を格納
		} while (( num /= 10 ) != 0);	// 数値の桁数までループ
	}
	else
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			{
			chr[i ++ ] = '.';			// 小数点を格納
			l = 1;
			}
			num /= 10;
		} while (i != (dp + 1 + l));		// 数値の桁数までループ
	}
	
	i --;
	
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == 1)
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{
			chr[i] = ' ';				//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == 1)
				{
					LCD_CHR_Copy_Smallfont('-');	//頭桁に-記号付加
				}
				else
				{
					LCD_CHR_Copy_Smallfont(' ');	//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
				}
			}
			else
			{
				LCD_CHR_Copy_Smallfont(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_Copy_Smallfont(chr[k]);
	}
}

// --------------------------------------------------------------------
// TFT LCD 整数値出力（大き目）
// --------------------------------------------------------------------
void LCD_INT_drawBN(int num, unsigned int figure, unsigned int dp)
{
	int i, j, k, l, numw;
	unsigned char chr[6], temp, sign;
	
	if( figure > 8 ) return;
	
	if( num < 0)
	{
		num = (~num) + 1;
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	
	numw = num;
	if(dp > 0)
	{
		for(i = 1; i <= dp; i ++ )
		{
			numw = numw / 10;
		}
	}
	
	i = 0;
	l = 0;
	if(numw >= 10)
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			chr[i ++ ] = '.';			// 小数点を格納
		} while (( num /= 10 ) != 0);	// 数値の桁数までループ
	}
	else
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			{
			chr[i ++ ] = '.';			// 小数点を格納
			l = 1;
			}
			num /= 10;
		} while (i != (dp + 1 + l));		// 数値の桁数までループ
	}
	
	i --;
	
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == 1)
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{
			chr[i] = ' ';				//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == 1)
				{
					LCD_CHR_copyBN('-');	//頭桁に-記号付加
				}
				else
				{
					LCD_CHR_copyBN(' ');	//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
				}
			}
			else
			{
				LCD_CHR_copyBN(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_copyBN(chr[k]);
	}
}

// --------------------------------------------------------------------
// TFT LCD 整数値出力（大き目）展開FONT対象
// --------------------------------------------------------------------
void LCD_INT_drawBNR(int num, unsigned int figure, unsigned int dp)
{
	int i, j, k, l, numw;
	unsigned char chr[6], temp, sign;
	
	if( figure > 8 ) return;
	
	if( num < 0)
	{
		num = (~num) + 1;
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	
	numw = num;
	if(dp > 0)
	{
		for(i = 1; i <= dp; i ++ )
		{
			numw = numw / 10;
		}
	}
	
	i = 0;
	l = 0;
	if(numw >= 10)
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			chr[i ++ ] = '.';			// 小数点を格納
		} while (( num /= 10 ) != 0);	// 数値の桁数までループ
	}
	else
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			{
			chr[i ++ ] = '.';			// 小数点を格納
			l = 1;
			}
			num /= 10;
		} while (i != (dp + 1 + l));		// 数値の桁数までループ
	}
	
	i --;
	
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == 1)
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{
			chr[i] = ' ';				//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == 1)
				{
					LCD_CHR_copyBNR('-');	//頭桁に-記号付加
				}
				else
				{
					LCD_CHR_copyBNR(' ');	//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
				}
			}
			else
			{
				LCD_CHR_copyBNR(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_copyBNR(chr[k]);
	}
}

// --------------------------------------------------------------------
// TFT LCD 整数値出力（大き目2倍）
// --------------------------------------------------------------------
void LCD_INT_drawBN2(int num, unsigned int figure, unsigned int dp)
{
	int i, j, k, l, numw;
	unsigned char chr[6], temp, sign;
	
	if( figure > 8 ) return;
	
	if( num < 0)
	{
		num = (~num) + 1;
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	
	numw = num;
	if(dp > 0)
	{
		for(i = 1; i <= dp; i ++ )
		{
			numw = numw / 10;
		}
	}
	
	i = 0;
	l = 0;
	if(numw >= 10)
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			chr[i ++ ] = '.';			// 小数点を格納
		} while (( num /= 10 ) != 0);	// 数値の桁数までループ
	}
	else
	{
		do								// 各桁数値の抽出ループ
		{
			temp = num % 10;			// 下位の桁から数字を抽出
			chr[i ++ ] = temp + '0';	// 数字を文字コードに変換
			if(i == dp)					// 小数点位置の場合
			{
			chr[i ++ ] = '.';			// 小数点を格納
			l = 1;
			}
			num /= 10;
		} while (i != (dp + 1 + l));		// 数値の桁数までループ
	}
	
	i --;
	
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == 1)
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{
			chr[i] = ' ';				//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == 1)
				{
					LCD_CHR_copyBN2('-');	//頭桁に-記号付加
				}
				else
				{
					LCD_CHR_copyBN2(' ');	//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
				}
			}
			else
			{
				LCD_CHR_copyBN2(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_copyBN2(chr[k]);
	}
}

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_NUM_drawBN(int num, unsigned int figure)
{
	int i, j, k, sign;
	unsigned char chr[6], temp;
	
	if( figure > 8 )
	{
		return;
	}
	
	if(num < 0)
	{
		num = (~num) + 1;
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	
	
	i = 0;
	do									// 各桁数値の抽出ループ
	{
		temp = num % 10;				// 下位の桁から数字を抽出
		chr[i ++] = temp + '0';		// 数字を文字コードに変換
	} while (( num /= 10 ) != 0);		// 数値の桁数までループ
	i --;
		
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == -1)					//負数の場合
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{								//正数の場合
			chr[i] = ' ';				//頭桁に-ｽﾍﾟｰｽ記号付加(+記号は付けない)
	//		chr[i] = '+';				//
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == -1)			//負数の場合
				{
					LCD_CHR_copyBN('-');//頭桁に-記号付加
                }
				else					//正数の場合
				{
					LCD_CHR_copyBN(' ');//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
	//        		LCD_CHR_copyBN('+');//
				}
			}
			else
			{
				LCD_CHR_copyBN(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_copyBN(chr[k]);
	}
	
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_NUM_drawBNF(int num, unsigned int figure, unsigned int f)
{
	int i, j, k, sign;
	unsigned char chr[6], temp;
	
	if( figure > 8 )
	{
		return;
	}
	
	if(num < 0)
	{
		num = (~num) + 1;
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	
	
	i = 0;
	do									// 各桁数値の抽出ループ
	{
		temp = num % 10;				// 下位の桁から数字を抽出
		chr[i ++] = temp + '0';		// 数字を文字コードに変換
	} while (( num /= 10 ) != 0);		// 数値の桁数までループ
	i --;
		
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == -1)					//負数の場合
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{								//正数の場合
			chr[i] = ' ';				//頭桁に-ｽﾍﾟｰｽ記号付加(+記号は付けない)
	//		chr[i] = '+';				//
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == -1)			//負数の場合
				{
					LCD_CHR_copyBN('-');//頭桁に-記号付加
                }
				else					//正数の場合
				{
					LCD_CHR_copyBN(' ');//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
	//        		LCD_CHR_copyBN('+');//
				}
			}
			else
			{
				LCD_CHR_copyBN(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		if(k == f)
		{
			if(f != 0)
			{
				LCD_CHR_copyBN('.');
				LCD_CHR_copyBN(chr[k]);
			}
		}
		else
		{
			LCD_CHR_copyBN(chr[k]);
		}
	}
	
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_CHR_copyBN2(unsigned char chr)
{
	unsigned long i, j, font_addr;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j ++)
	{
		for(i = 0; i < 16; i ++)
		{
			if(g_drawbuff_flg)
			{
				(*(ADATA + ((g_LCD_x + i * 2    ) + (g_LCD_y + j * 2    ) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(ADATA + ((g_LCD_x + i * 2 + 1) + (g_LCD_y + j * 2    ) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(ADATA + ((g_LCD_x + i * 2    ) + (g_LCD_y + j * 2 + 1) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(ADATA + ((g_LCD_x + i * 2 + 1) + (g_LCD_y + j * 2 + 1) * 320))) = *(FONT + font_addr + i + j * 320);
			}
			else
			{
				(*(BDATA + ((g_LCD_x + i * 2    ) + (g_LCD_y + j * 2    ) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(BDATA + ((g_LCD_x + i * 2 + 1) + (g_LCD_y + j * 2    ) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(BDATA + ((g_LCD_x + i * 2    ) + (g_LCD_y + j * 2 + 1) * 320))) = *(FONT + font_addr + i + j * 320);
				(*(BDATA + ((g_LCD_x + i * 2 + 1) + (g_LCD_y + j * 2 + 1) * 320))) = *(FONT + font_addr + i + j * 320);
			}
		}
	}
	g_LCD_x = g_LCD_x  + 32;
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_CHR_drawBN2(unsigned char chr[])
{
	unsigned int i;
	
	for(i = 0; i <= 19; i++)
	{
		if(chr[i] == '\0') return;
		LCD_CHR_copyBN2(chr[i]);
	}
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_NUM_drawBN2(int num, unsigned int figure)
{
	int i, j, k, sign;
	unsigned char chr[6], temp;
	
	if( figure > 8 )
	{
		return;
	}
	
	if(num < 0)
	{
		num = (~num) + 1;
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	
	
	i = 0;
	do									// 各桁数値の抽出ループ
	{
		temp = num % 10;				// 下位の桁から数字を抽出
		chr[i ++] = temp + '0';		// 数字を文字コードに変換
	} while (( num /= 10 ) != 0);		// 数値の桁数までループ
	i --;
		
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == -1)					//負数の場合
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{								//正数の場合
			chr[i] = ' ';				//頭桁に-ｽﾍﾟｰｽ記号付加(+記号は付けない)
	//		chr[i] = '+';				//
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == -1)			//負数の場合
				{
					LCD_CHR_copyBN2('-');//頭桁に-記号付加
                }
				else					//正数の場合
				{
					LCD_CHR_copyBN2(' ');//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
	//        		LCD_CHR_copyBN2('+');//
				}
			}
			else
			{
				LCD_CHR_copyBN2(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		LCD_CHR_copyBN2(chr[k]);
	}
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_NUM_drawBN2F(int num, unsigned int figure, unsigned int f)
{
	int i, j, k, sign;
	unsigned char chr[6], temp;
	
	if( figure > 8 )
	{
		return;
	}
	
	if(num < 0)
	{
		num = (~num) + 1;
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	
	
	i = 0;
	do									// 各桁数値の抽出ループ
	{
		temp = num % 10;				// 下位の桁から数字を抽出
		chr[i ++] = temp + '0';		// 数字を文字コードに変換
	} while (( num /= 10 ) != 0);		// 数値の桁数までループ
	i --;
		
	if((figure - 1) < i)				//表示桁数チェック
	{
		return;
	}
	
	if(i == (figure - 1))				//MAX桁の場合
	{
		i += 1;							//頭の桁を１つ増やす
		if(sign == -1)					//負数の場合
		{
			chr[i] = '-';				//頭桁に-記号付加
		}
		else
		{								//正数の場合
			chr[i] = ' ';				//頭桁に-ｽﾍﾟｰｽ記号付加(+記号は付けない)
	//		chr[i] = '+';				//
		}
	}
	else
	{									//MAX桁以下の場合
		for( j = 0; j < ((figure) -i ); j++ )		//最初に頭から不足桁数分のｽﾍﾟｰｽ付加
		{
			if(j == ((figure - 1) - i ))//数値頭の±符号処理
			{
				if(sign == -1)			//負数の場合
				{
					LCD_CHR_copyBN2('-');//頭桁に-記号付加
                }
				else					//正数の場合
				{
					LCD_CHR_copyBN2(' ');//頭桁にｽﾍﾟｰｽ記号付加(+記号は付けない)
	//        		LCD_CHR_copyBN2('+');//
				}
			}
			else
			{
				LCD_CHR_copyBN2(' ');	//不足桁数だけスペース表示
			}            
		}
	}
	// 数字コード表示ルーチン
   	for(k = i; k >= 0; k --)			// 上位の桁から順次
	{
		if(k == f)
		{
			if(f != 0)
			{
				LCD_CHR_copyBN2('.');
				LCD_CHR_copyBN2(chr[k]);
			}
		}
		else
		{
			LCD_CHR_copyBN2(chr[k]);
		}
	}
	
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_CHR_copyB(unsigned int x, unsigned int y, unsigned char chr, unsigned int color)
{
	unsigned long	i, j, font_addr;
	unsigned long	dst_data, font_data;
	unsigned long	rd, gd, bd,rs, gs, bs, alpha;
	
	// フォントテーブルデータの座標の参照先を算出
	font_addr = (((((chr - 0x20) & 0x000000F0) >> 4) * 24) * 320) + ((((chr - 0x20) & 0x0000000F) * 16));
	
	for(j = 0; j < 24; j++)
	{
		for(i = 0; i < 16; i++)
		{
			if(DrawBuff_flg)
			{
				dst_data	= (*(ADATA + ((x + i) + (y + j) * 320)));				// 貼り付け先データの該当ピクセルデータの算出
			}
			else
			{
				dst_data	= (*(BDATA + ((x + i) + (y + j) * 320)));				// 貼り付け先データの該当ピクセルデータの算出
			}
			font_data	= (*(FONT +  + i + j * 320));								// フォントテーブルデータの該当ピクセルデータの算出(アルファデータ)
			rd			= ((dst_data >> 11) & 0x001F);								// 貼り付け先データのR要素の算出
			gd			= ((dst_data >>  5) & 0x003F);								// 貼り付け先データのG要素の算出
			bd			= ((dst_data      ) & 0x001F);								// 貼り付け先データのB要素の算出
			rs			= ((color         ) & 0x001F);								// フォント指定色のR要素の算出
			gs			= ((color    >>  5) & 0x003F);								// フォント指定色のG要素の算出
			bs			= ((color    >> 11) & 0x001F);								// フォント指定色のB要素の算出
			alpha		= font_data & 0x1F;											// フォントテーブルデータからアルファ量を算出
			rd			= (rd *  alpha       + rs * (0x1F -  alpha      )) / 0x1F;	// R要素のアルファブレンド
			gd			= (gd * (alpha << 1) + gs * (0x3F - (alpha << 1))) / 0x3F;	// G要素のアルファブレンド
			bd			= (bd *  alpha       + bs * (0x1F -  alpha      )) / 0x1F;	// B要素のアルファブレンド
			dst_data	= (rd << 11) | (gd << 5) | bd;	
			if(DrawBuff_flg)
			{
				(*(ADATA + ((x + i) + (y + j) * 320))) = dst_data;
			}
			else
			{
				(*(BDATA + ((x + i) + (y + j) * 320))) = dst_data;
			}
		}
	}
}
*/

/*
// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
void LCD_CHR_drawB(unsigned int x, unsigned int y, unsigned char chr[], unsigned int color)
{
	unsigned int i;
	
	for(i = 0; i <= 19; i++)
	{
		if(chr[i] == '\0') return;
		LCD_CHR_copyB(x + i * 16, y, chr[i], color);
	}
}
*/
