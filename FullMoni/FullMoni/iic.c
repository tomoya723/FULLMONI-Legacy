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
// filename		:	i2cEEPROM.c
// brief		:	FullMoni rev.C シリアルフラッシュROM管理
// author		:	Tomoya Sato
// update		:	2021/02/02
// version		:	1.05
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include <machine.h>
#include "iodefine.h"
#include "iic.h"

// --------------------------------------------------------------------
// グローバル変数宣言
// --------------------------------------------------------------------
unsigned char  iic_mode;							/* IIC mode							*/
unsigned short mt_cnt;								/* IIC master transmit data counter	*/
unsigned short mr_cnt;								/* IIC master receive data counter	*/
unsigned char  randrd_cnt;
unsigned short mt_num;								/* IIC master transmit data number	*/
unsigned short mr_num;								/* IIC master receive data number	*/
unsigned char  *mt_data;
unsigned char  *mr_data;
unsigned char  MemAddress;
unsigned char  mt_addr;

// --------------------------------------------------------------------
// IICバス初期化
// --------------------------------------------------------------------
void Init_IIC(void)
{
	unsigned char  tmp;
	
//  P1.ICR.BIT.B7 = 1;								/* input buffers are valid			*/
//  P1.ICR.BIT.B6 = 1;								/* P17:SCL0, P16:SDA0				*/
	
	IIC20.ICCRA.BIT.ICE = 1;						/* IIC transfer operations : Enable	*/
	IIC20.ICMR.BIT.WAIT = 0;						/* WAIT=0							*/
	IIC20.SAR.BYTE = SLAVE_ADDR;					/* Slave address					*/
//  IIC20.ICCRA.BYTE = 0x8D;						/* transfer rate : 20MHz,100kbps	*/
	IIC20.ICCRA.BYTE = 0x8F;						/* transfer rate : 24MHz,93.75kbps	*/
	IIC20.ICIER.BYTE = 0xBC;						/* Enable Interrupt source, Ack=1	*/
	tmp = IIC20.ICSR.BYTE;
	IIC20.ICSR.BYTE = 0x00;							/* all status clear					*/
	
	mt_cnt = 0;
	mr_cnt = 0;
	randrd_cnt = 0;
	iic_mode = MODE_IDLE;							/* Master transfer mode				*/
}

// --------------------------------------------------------------------
// マスタ ページライト 開始
// --------------------------------------------------------------------
unsigned char mtrs_start(const unsigned char *dtadd, unsigned char mtbuf,unsigned short dtnum)
{
	unsigned char  rtn;
	
	rtn = 0;
	set_imask_exr(6);								/* Disable interrupt				*/
	
	if ( iic_mode != MODE_IDLE )					/* Mode check						*/
	{
		rtn = 1;
	}												/* Bus Free (BBSY = 0)?				*/
	else if ( IIC20.ICCRB.BIT.BBSY != 0 )			/* Bus condition check				*/
	{
		rtn = 2;
	}												/* Bus Free (BBSY=0)?				*/
	else if ( dtnum == 0 )
	{
		rtn = 3;									/* ERR: number of data is "0"		*/
	}
	else
	{
		iic_mode = MODE_MT;							/* Set transfer/receive mode		*/
		mt_addr = mtbuf;
		mt_data = (unsigned char *)dtadd;			/* Top address of transfer data		*/
		mt_num = dtnum;								/* number of transfer data			*/
		mt_cnt = 0;
		
		IIC20.ICIER.BIT.TIE = 0;					/* Disable interrupt				*/
		IIC20.ICCRA.BYTE |= 0x30u;					/* Master transmit					*/
		IIC20.ICCRB.BYTE = 0xBD;					/* Generate start condition			*/
		IIC20.ICIER.BIT.TIE = 1;					/* Enable interrupt					*/
	}
	
	set_imask_exr(0);								/* Enable interrupt					*/
	
	return rtn;
}

// --------------------------------------------------------------------
// マスタ受信 開始
// --------------------------------------------------------------------
unsigned char mrcv_start(const unsigned char *dtadd, unsigned short dtnum)
{
	unsigned char  rtn;
	
	rtn = 0;
	set_imask_exr(6);								/* Disable interrupt				*/
	
	if ( iic_mode != MODE_IDLE )					/* Mode check						*/
	{
		rtn = 1;
	}												/* Bus Free (BBSY = 0)?				*/
	else if ( IIC20.ICCRB.BIT.BBSY != 0 )			/* Bus condition check				*/
	{
		rtn = 2;
	}												/* Bus Free (BBSY=0)?				*/
	else if ( dtnum == 0 )
	{
		rtn = 3;									/* ERR: number of data is "0"		*/
	}
	else
	{
		iic_mode = MODE_MR;							/* Set transfer/receive mode		*/
		mr_data = (unsigned char *)dtadd;			/* Top address of receive data		*/
		mr_num = dtnum;								/* number of receive data			*/
		mr_cnt = 0;
		
		IIC20.ICIER.BIT.TIE = 0;					/* Disable interrupt				*/
		IIC20.ICCRA.BYTE |= 0x30u;					/* Master transmit					*/
		IIC20.ICCRB.BYTE = 0xBD;					/* Generate start condition			*/
		IIC20.ICIER.BIT.TIE = 1;					/* Enable interrupt					*/
	}
	
	set_imask_exr(0);								/* Enable interrupt					*/
	
	return rtn;
}

// --------------------------------------------------------------------
// シーケンシャルランダムリード 開始
// --------------------------------------------------------------------
unsigned char mrandrd_start(const unsigned char *mrbuf, unsigned char mtbuf, unsigned short dtnum)
{
	unsigned char  rtn;
	
	rtn = 0;
	set_imask_exr(6);								/* Disable interrupt				*/
	
	if ( iic_mode != MODE_IDLE )					/* Mode check						*/
	{
		rtn = 1;
	}												/* Bus Free (BBSY = 0)?				*/
	else if ( IIC20.ICCRB.BIT.BBSY != 0 )			/* Bus condition check				*/
	{
		rtn = 2;
	}												/* Bus Free (BBSY=0)?				*/
	else if ( dtnum == 0 )
	{
		rtn = 3;									/* ERR: number of data is "0"		*/
	}
	else
	{
		iic_mode = MODE_MR_RAND;
		MemAddress = mtbuf;
		mt_data = &MemAddress;
		mr_data = (unsigned char *)mrbuf;			/* Top address of receive data		*/
		mr_num = dtnum;								/* number of receive data			*/
		randrd_cnt = 0;

		IIC20.ICIER.BIT.TIE = 0;					/* Disable interrupt				*/
		IIC20.ICCRA.BYTE |= 0x30u;					/* Master transmit					*/
		IIC20.ICCRB.BYTE = 0xBD;					/* Generate start condition			*/
		IIC20.ICIER.BIT.TIE = 1;					/* Enable interrupt					*/
	}
	
	set_imask_exr(0);								/* Enable interrupt					*/
	
	return rtn;
}

// --------------------------------------------------------------------
// IIC2 ch0 割り込みハンドラ
// --------------------------------------------------------------------
void iici0_interrupt(void)
{
	if ( IIC20.ICSR.BIT.STOP == 1 )
	{
		receive_stop_condition();
	}
	else
	{
		switch ( iic_mode )							/* mode check						*/
		{
			case MODE_MT:
				master_transfer();					/* Master transfer					*/
				break;
			case MODE_MR:
				master_receive();					/* Master receive					*/
				break;
			case MODE_MR_RAND:
				master_randomread();				/* Random read						*/
				break;
			default:
				break;
		}
	}
}

// --------------------------------------------------------------------
// 受信 ストップコンディション
// --------------------------------------------------------------------
void receive_stop_condition(void)
{
	unsigned char  tmp;

	if( (iic_mode==MODE_MR)							/* Check mode						*/
		 && ((mr_cnt-2)==mr_num))					/* Check Nack						*/
	{
		mr_data[mr_cnt - 3] = IIC20.ICDRR;			/* Store the received data			*/
	}
	else if( (iic_mode==MODE_MR_RAND)				/* Check mode						*/
		 && ((randrd_cnt-5)==mr_num))				/* Check Nack						*/
	{
		mr_data[randrd_cnt - 3] = IIC20.ICDRR;		/* Store the received data			*/
//		mr_data[0] = IIC20.ICDRR;					/* Store the received data			*/
	}
	
	IIC20.ICCRA.BIT.RCVD = 0;						/* Enables next reception			*/
	IIC20.ICCRA.BYTE &= 0xCFu;						/* MST,TRS=00,  slave receive mode	*/
	
	tmp = IIC20.ICSR.BYTE;
	IIC20.ICSR.BYTE = 0x00;							/* all status clear					*/
	
	IIC20.ICIER.BYTE = 0xBC;						/* Enable Interrupt source, Ack=1	*/
	iic_mode = MODE_IDLE;							/* Slave receive mode				*/
}

// --------------------------------------------------------------------
// マスタ ページライト処理
// --------------------------------------------------------------------
void master_transfer(void)
{
	unsigned char  tmp;

	if ( IIC20.ICSR.BIT.NACKF == 1 )				/* No acknowledge detection			*/
	{
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/

		while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL = Low?						*/
		tmp = IIC20.ICSR.BYTE;						/* status clear						*/
		IIC20.ICSR.BIT.NACKF = 0;
		IIC20.ICSR.BIT.TDRE = 0;
		IIC20.ICSR.BIT.TEND = 0;
		
		IIC20.ICCRB.BYTE = 0x3D;					/* Generate stop condition			*/
		mt_cnt++;
	}
	else if ( mt_cnt == 0 )
	{
		IIC20.ICDRT = MT_ID;						/* Transmit "Slave address+W(0)"	*/
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 1;					/* Transmit end interrupt enable	*/
		mt_cnt++;
	}
	else if ( mt_cnt == (mt_num + 1))
	{
		IIC20.ICDRT = mt_data[mt_cnt - 2];			/* Transmit last data				*/
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 1;					/* Transmit end interrupt enable	*/
		mt_cnt++;
	}
	else if ( mt_cnt == 1 )
	{
		IIC20.ICDRT = mt_addr;						/* Transmit start address			*/
		IIC20.ICIER.BIT.TIE = 1;					/* Transmit interrupt enable		*/
		IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
		mt_cnt++;
	}
	else if ( mt_cnt == 2 )
	{
		IIC20.ICDRT = mt_data[mt_cnt - 2];			/* Transmit data					*/
		IIC20.ICIER.BIT.TIE = 1;					/* Transmit interrupt enable		*/
		IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
		mt_cnt++;
	}
	else if ( mt_cnt < (mt_num + 1))
	{
		IIC20.ICDRT = mt_data[mt_cnt - 2];			/* Transmit data					*/
		mt_cnt++;
	}
	else
	{
		IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
		
		while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL=Low?							*/
		tmp = IIC20.ICSR.BYTE;						/* Status clear						*/
		IIC20.ICSR.BIT.TEND = 0;
		IIC20.ICSR.BIT.STOP = 0;
		IIC20.ICCRB.BYTE = 0x3D;					/* Generate stop condition			*/
		mt_cnt++;
	}
}

// --------------------------------------------------------------------
// マスタ受信処理
// --------------------------------------------------------------------
void master_receive(void)
{
	unsigned char  tmp;

	if ( mr_cnt == 1 )
	{
		if ( IIC20.ICSR.BIT.NACKF == 1 )			/* No acknowledge detection			*/
		{
			IIC20.ICIER.BIT.TIE = 0;				/* Transmit interrupt disable		*/
			IIC20.ICIER.BIT.TEIE = 0;				/* Transmit end interrupt disable	*/
			
			while ( IIC20.ICCRB.BIT.SCLO != 0 );	/* SCL = Low?						*/
			tmp = IIC20.ICSR.BYTE;					/* status clear						*/
			IIC20.ICSR.BIT.NACKF = 0;
			IIC20.ICSR.BIT.TDRE = 0;
			IIC20.ICSR.BIT.TEND = 0;
			IIC20.ICCRB.BYTE = 0x3D;				/* Generate stop condition			*/
			mr_cnt++;
		}
		else
		{
			IIC20.ICIER.BIT.TEIE = 0;				/* Transmit end interrupt disable	*/
			IIC20.ICIER.BIT.RIE = 1;				/* Receive interrupt enable			*/
			
			IIC20.ICCRA.BIT.RCVD = 1;				/* Disable continuous receive		*/
			
			tmp = IIC20.ICSR.BYTE;					/* status clear						*/
			IIC20.ICSR.BIT.TEND = 0;
			
			IIC20.ICCRA.BIT.TRS = 0;				/* Set receive mode					*/
			
			tmp = IIC20.ICSR.BYTE;					/* status clear						*/
			IIC20.ICSR.BIT.TDRE = 0;
			
			if ( mr_num == 1 )
			{
				IIC20.ICIER.BIT.ACKBT = 1;			/* Set acknowledge of the final byte*/
			}
			else
			{
				IIC20.ICIER.BIT.ACKBT = 0;			/* Set acknowledge					*/
			}
			
			tmp = IIC20.ICDRR;						/* Dummy read						*/
			mr_cnt++;
		}
	}
	else if ( mr_cnt == 0 )
	{
		IIC20.ICDRT = MR_ID;						/* Transmit "Slave address+R(1)"	*/
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 1;					/* Transmit end interrupt enable	*/
		mr_cnt++;
	}
	else if ( mr_cnt < mr_num )
	{
		mr_data[mr_cnt - 2] = IIC20.ICDRR;			/* Store the received data			*/
		mr_cnt++;
	}
	else if ( mr_cnt == mr_num )
	{
		IIC20.ICIER.BIT.ACKBT = 1;					/* Set acknowledge of the final byte*/
		IIC20.ICCRA.BIT.RCVD = 1;					/* Disable continuous receive		*/
		
		mr_data[mr_cnt - 2] = IIC20.ICDRR;			/* Store the received data			*/
		mr_cnt++;
	}
	else											/* mr_cnt > mr_num					*/
	{
		IIC20.ICIER.BIT.RIE = 0;					/* Receive interrupt disable		*/
		
		while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL=Low?							*/
		tmp = IIC20.ICSR.BYTE;						/* Status clear						*/
		IIC20.ICSR.BIT.STOP = 0;
		IIC20.ICCRB.BYTE = 0x3D;					/* Generate stop condition			*/
		mr_cnt++;
	}
}

// --------------------------------------------------------------------
// シーケンシャルランダムリード処理
// --------------------------------------------------------------------
void master_randomread(void)
{
	unsigned char  tmp;

	if ( randrd_cnt == 4 )
	{
		if ( IIC20.ICSR.BIT.NACKF == 1 )				/* No acknowledge detection			*/
		{
			IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
			IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
			
			tmp = IIC20.ICSR.BYTE;						/* status clear						*/
			IIC20.ICSR.BIT.NACKF = 0;
			IIC20.ICSR.BIT.TDRE = 0;
			IIC20.ICSR.BIT.TEND = 0;
			while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL=Low?							*/
			IIC20.ICCRB.BYTE = 0x3D;					/* Generate stop condition			*/
			randrd_cnt++;
		}
		else
		{
			while ( IIC20.ICCRB.BIT.SCLO != 0 );	/* SCL = Low?						*/
			
			IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
			IIC20.ICIER.BIT.RIE = 1;					/* Receive interrupt enable			*/
			
			IIC20.ICCRA.BIT.RCVD = 1;					/* Disable continuous receive		*/
			
			tmp = IIC20.ICSR.BYTE;						/* status clear						*/
			IIC20.ICSR.BIT.TEND = 0;
			
			IIC20.ICCRA.BIT.TRS = 0;					/* Set receive mode					*/
			
			tmp = IIC20.ICSR.BYTE;						/* status clear						*/
			IIC20.ICSR.BIT.TDRE = 0;
			
			if ( mr_num == 1 )
			{
				IIC20.ICIER.BIT.ACKBT = 1;				/* Set acknowledge of the final byte*/
			}
			else
			{
				IIC20.ICIER.BIT.ACKBT = 0;				/* Set acknowledge					*/
			}
			
			tmp = IIC20.ICDRR;							/* Dummy read						*/
			randrd_cnt++;
		}
	}
	else if ( randrd_cnt == 0 )
	{
		IIC20.ICDRT = MT_ID;						/* Transmit "Slave address+W(0)"	*/
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 1;					/* Transmit end interrupt enable	*/
		randrd_cnt++;
	}
	else if ( randrd_cnt == 1 )
	{
		IIC20.ICDRT = mt_data[0];					/* Transmit last data				*/
		randrd_cnt++;
	}
	else if ( randrd_cnt == 2 )
	{
		IIC20.ICIER.BIT.TIE = 1;					/* Enable interrupt					*/
		IIC20.ICIER.BIT.TEIE = 0;					/* Transmit end interrupt disable	*/
		
		tmp = IIC20.ICSR.BYTE;						/* status clear						*/
		IIC20.ICSR.BIT.TEND = 0;
		
		while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL=Low?							*/
		IIC20.ICCRB.BYTE = 0xBD;					/* Generate start condition			*/
		randrd_cnt++;
	}
	else if ( randrd_cnt == 3 )
	{
		IIC20.ICDRT = MR_ID;						/* Transmit "Slave address+R(1)"	*/
		IIC20.ICIER.BIT.TIE = 0;					/* Transmit interrupt disable		*/
		IIC20.ICIER.BIT.TEIE = 1;					/* Transmit end interrupt enable	*/
		randrd_cnt++;
	}
	else if ( randrd_cnt < (mr_num + 3) )
	{
		mr_data[randrd_cnt - 5] = IIC20.ICDRR;		/* Store the received data			*/
		randrd_cnt++;
	}
	else if ( randrd_cnt == (mr_num + 3) )
	{
		IIC20.ICIER.BIT.ACKBT = 1;					/* Set acknowledge of the final byte*/
		IIC20.ICCRA.BIT.RCVD = 1;					/* Disable continuous receive		*/
		
		mr_data[randrd_cnt - 5] = IIC20.ICDRR;		/* Store the received data			*/
		randrd_cnt++;
	}
	else											/* randrd_cnt > (mr_num + 4)		*/
	{
		IIC20.ICIER.BIT.RIE = 0;					/* Receive interrupt disable		*/

		while ( IIC20.ICCRB.BIT.SCLO != 0 );		/* SCL=Low?							*/
		tmp = IIC20.ICSR.BYTE;						/* Status clear						*/
		IIC20.ICSR.BIT.STOP = 0;
		IIC20.ICCRB.BYTE = 0x3D;					/* Generate stop condition			*/
		randrd_cnt++;
	}
}
