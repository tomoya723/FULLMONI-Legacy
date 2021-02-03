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
// filename		:	intprg.c
// brief		:	FullMoni rev.C 割り込みベクタ
// author		:	Tomoya Sato
// update		:	2021/02/02
// version		:	1.05
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ユーザーヘッダファイル
// --------------------------------------------------------------------
#include "iodefine.h"
#include "init_system.h"
#include "iic.h"
#include <machine.h>
#pragma section IntPRG

// vector 1 Reserved

// vector 2 Reserved

// vector 3 Reserved

// vector 4 Illegal code
__interrupt(vect=4) void INT_Illegal_code(void){/* sleep(); */}
// vector 5 Trace
__interrupt(vect=5) void INT_Trace(void){/* sleep(); */}
// vector 6 Reserved

// vector 7 NMI
__interrupt(vect=7) void INT_NMI(void){/* sleep(); */}
// vector 8 trap #0
__interrupt(vect=8) void INT_TRAP0(void){/* sleep(); */}
// vector 9 trap #1
__interrupt(vect=9) void INT_TRAP1(void){/* sleep(); */}
// vector 10 trap #2
__interrupt(vect=10) void INT_TRAP2(void){/* sleep(); */}
// vector 11 trap #3
__interrupt(vect=11) void INT_TRAP3(void){/* sleep(); */}
// vector 12 CPU Address error
__interrupt(vect=12) void INT_CPU_Address(void){/* sleep(); */}
// vector 13 DMA Address error
__interrupt(vect=13) void INT_DMA_Address(void){/* sleep(); */}
// vector 14 Reserved

// vector 15 Reserved

// vector 16 Reserved

// vector 17 Reserved

// vector 18 Sleep
__interrupt(vect=18) void INT_Sleep(void){/* sleep(); */}
// vector 19 Reserved

// vector 20 Reserved

// vector 21 Reserved

// vector 22 Reserved

// vector 23 Reserved

// vector 24 Reserved

// vector 25 Reserved

// vector 26 Reserved

// vector 27 Reserved

// vector 28 Reserved

// vector 29 Reserved

// vector 30 Reserved

// vector 31 Reserved

// vector 32 Reserved

// vector 33 Reserved

// vector 34 Reserved

// vector 35 Reserved

// vector 36 Reserved

// vector 37 Reserved

// vector 38 Reserved

// vector 39 Reserved

// vector 40 Reserved

// vector 41 Reserved

// vector 42 Reserved

// vector 43 Reserved

// vector 44 Reserved

// vector 45 Reserved

// vector 46 Reserved

// vector 47 Reserved

// vector 48 Reserved

// vector 49 Reserved

// vector 50 Reserved

// vector 51 Reserved

// vector 52 Reserved

// vector 53 Reserved

// vector 54 Reserved

// vector 55 Reserved

// vector 56 Reserved

// vector 57 Reserved

// vector 58 Reserved

// vector 59 Reserved

// vector 60 Reserved

// vector 61 Reserved

// vector 62 Reserved

// vector 63 Reserved

// vector 64 External trap IRQ0
__interrupt(vect=64) void INT_IRQ0(void){/* sleep(); */}
// vector 65 External trap IRQ1
__interrupt(vect=65) void INT_IRQ1(void){/* sleep(); */}
// vector 66 External trap IRQ2
__interrupt(vect=66) void INT_IRQ2(void){/* sleep(); */}
// vector 67 External trap IRQ3
__interrupt(vect=67) void INT_IRQ3(void){Int_CAN2515();}
// vector 68 External trap IRQ4
__interrupt(vect=68) void INT_IRQ4(void){/* sleep(); */}
// vector 69 External trap IRQ5
__interrupt(vect=69) void INT_IRQ5(void){/* sleep(); */}
// vector 70 External trap IRQ6
__interrupt(vect=70) void INT_IRQ6(void){/* sleep(); */}
// vector 71 External trap IRQ7
__interrupt(vect=71) void INT_IRQ7(void){/* sleep(); */}
// vector 72 External trap IRQ8
__interrupt(vect=72) void INT_IRQ8(void){/* sleep(); */}
// vector 73 External trap IRQ9
__interrupt(vect=73) void INT_IRQ9(void){/* sleep(); */}
// vector 74 External trap IRQ10
__interrupt(vect=74) void INT_IRQ10(void){/* sleep(); */}
// vector 75 External trap IRQ11
__interrupt(vect=75) void INT_IRQ11(void){/* sleep(); */}
// vector 76 Reserved

// vector 77 Reserved

// vector 78 Reserved

// vector 79 Reserved

// vector 80 Reserved

// vector 81 WOVI
__interrupt(vect=81) void INT_WOVI(void){/* sleep(); */}
// vector 82 Reserved

// vector 83 Reserved

// vector 84 Reserved

// vector 85 Reserved

// vector 86 ADI
__interrupt(vect=86) void INT_ADI(void){/* sleep(); */}
// vector 87 Reserved

// vector 88 TGI0A TPU0
__interrupt(vect=88) void INT_TGI0A_TPU0(void){Int_50msFunc();}
// vector 89 TGI0B TPU0
__interrupt(vect=89) void INT_TGI0B_TPU0(void){/* sleep(); */}
// vector 90 TGI0C TPU0
__interrupt(vect=90) void INT_TGI0C_TPU0(void){/* sleep(); */}
// vector 91 TGI0D TPU0
__interrupt(vect=91) void INT_TGI0D_TPU0(void){/* sleep(); */}
// vector 92 TCI0V TPU0
__interrupt(vect=92) void INT_TCI0V_TPU0(void){/* sleep(); */}
// vector 93 TGI1A TPU1
__interrupt(vect=93) void INT_TGI1A_TPU1(void){/* sleep(); */}
// vector 94 TGI1B TPU1
__interrupt(vect=94) void INT_TGI1B_TPU1(void){/* sleep(); */}
// vector 95 TCI1V TPU1
__interrupt(vect=95) void INT_TCI1V_TPU1(void){/* sleep(); */}
// vector 96 TCI1U TPU1
__interrupt(vect=96) void INT_TCI1U_TPU1(void){/* sleep(); */}
// vector 97 TGI2A TPU2
__interrupt(vect=97) void INT_TGI2A_TPU2(void){/* sleep(); */}
// vector 98 TGI2B TPU2
__interrupt(vect=98) void INT_TGI2B_TPU2(void){/* sleep(); */}
// vector 99 TCI2V TPU2
__interrupt(vect=99) void INT_TCI2V_TPU2(void){/* sleep(); */}
// vector 100 TCI2U TPU2
__interrupt(vect=100) void INT_TCI2U_TPU2(void){/* sleep(); */}
// vector 101 TGI3A TPU3
__interrupt(vect=101) void INT_TGI3A_TPU3(void){/* sleep(); */}
// vector 102 TGI3B TPU3
__interrupt(vect=102) void INT_TGI3B_TPU3(void){/* sleep(); */}
// vector 103 TGI3C TPU3
__interrupt(vect=103) void INT_TGI3C_TPU3(void){/* sleep(); */}
// vector 104 TGI3D TPU3
__interrupt(vect=104) void INT_TGI3D_TPU3(void){/* sleep(); */}
// vector 105 TCI3V TPU3
__interrupt(vect=105) void INT_TCI3V_TPU3(void){/* sleep(); */}
// vector 106 TGI4A TPU4
__interrupt(vect=106) void INT_TGI4A_TPU4(void){/* sleep(); */}
// vector 107 TGI4B TPU4
__interrupt(vect=107) void INT_TGI4B_TPU4(void){/* sleep(); */}
// vector 108 TCI4V TPU4
__interrupt(vect=108) void INT_TCI4V_TPU4(void){/* sleep(); */}
// vector 109 TCI4U TPU4
__interrupt(vect=109) void INT_TCI4U_TPU4(void){/* sleep(); */}
// vector 110 TGI5A TPU5
__interrupt(vect=110) void INT_TGI5A_TPU5(void){/* sleep(); */}
// vector 111 TGI5B TPU5
__interrupt(vect=111) void INT_TGI5B_TPU5(void){/* sleep(); */}
// vector 112 TCI5V TPU5
__interrupt(vect=112) void INT_TCI5V_TPU5(void){/* sleep(); */}
// vector 113 TCI5U TPU5
__interrupt(vect=113) void INT_TCI5U_TPU5(void){/* sleep(); */}
// vector 114 Reserved

// vector 115 Reserved

// vector 116 CMIA0 TMR0
__interrupt(vect=116) void INT_CMIA0_TMR0(void){/* sleep(); */}
// vector 117 CMIB0 TMR0
__interrupt(vect=117) void INT_CMIB0_TMR0(void){/* sleep(); */}
// vector 118 OVI0 TMR0
__interrupt(vect=118) void INT_OVI0_TMR0(void){/* sleep(); */}
// vector 119 CMIA1 TMR1
__interrupt(vect=119) void INT_CMIA1_TMR1(void){/* sleep(); */}
// vector 120 CMIB1 TMR1
__interrupt(vect=120) void INT_CMIB1_TMR1(void){/* sleep(); */}
// vector 121 OVI1 TMR1
__interrupt(vect=121) void INT_OVI1_TMR1(void){/* sleep(); */}
// vector 122 CMIA2 TMR2
__interrupt(vect=122) void INT_CMIA2_TMR2(void){/* sleep(); */}
// vector 123 CMIB2 TMR2
__interrupt(vect=123) void INT_CMIB2_TMR2(void){/* sleep(); */}
// vector 124 OVI2 TMR2
__interrupt(vect=124) void INT_OVI2_TMR2(void){/* sleep(); */}
// vector 125 CMIA3 TMR3
__interrupt(vect=125) void INT_CMIA3_TMR3(void){/* sleep(); */}
// vector 126 CMIB3 TMR3
__interrupt(vect=126) void INT_CMIB3_TMR3(void){/* sleep(); */}
// vector 127 OVI3 TMR3
__interrupt(vect=127) void INT_OVI3_TMR3(void){/* sleep(); */}
// vector 128 TEND0 DMAC
__interrupt(vect=128) void INT_TEND0_DMAC(void){/* sleep(); */}
// vector 129 TEND1 DMAC
__interrupt(vect=129) void INT_TEND1_DMAC(void){/* sleep(); */}
// vector 130 TEND2 DMAC
__interrupt(vect=130) void INT_TEND2_DMAC(void){/* sleep(); */}
// vector 131 TEND3 DMAC
__interrupt(vect=131) void INT_TEND3_DMAC(void){/* sleep(); */}
// vector 132 TEND0 EXDMAC
__interrupt(vect=132) void INT_TEND0_EXDMAC(void){/* sleep(); */}
// vector 133 TEND1 EXDMAC
__interrupt(vect=133) void INT_TEND1_EXDMAC(void){/* sleep(); */}
// vector 134 TEND2 EXDMAC
__interrupt(vect=134) void INT_TEND2_EXDMAC(void){/* sleep(); */}
// vector 135 TEND3 EXDMAC
__interrupt(vect=135) void INT_TEND3_EXDMAC(void){/* sleep(); */}
// vector 136 EEND0 DMAC
__interrupt(vect=136) void INT_EEND0_DMAC(void){/* sleep(); */}
// vector 137 EEND1 DMAC
__interrupt(vect=137) void INT_EEND1_DMAC(void){/* sleep(); */}
// vector 138 EEND2 DMAC
__interrupt(vect=138) void INT_EEND2_DMAC(void){/* sleep(); */}
// vector 139 EEND3 DMAC
__interrupt(vect=139) void INT_EEND3_DMAC(void){/* sleep(); */}
// vector 140 EEND0 EXDMAC
__interrupt(vect=140) void INT_EEND0_EXDMAC(void){/* sleep(); */}
// vector 141 EEND1 EXDMAC
__interrupt(vect=141) void INT_EEND1_EXDMAC(void){/* sleep(); */}
// vector 142 EEND2 EXDMAC
__interrupt(vect=142) void INT_EEND2_EXDMAC(void){/* sleep(); */}
// vector 143 EEND3 EXDMAC
__interrupt(vect=143) void INT_EEND3_EXDMAC(void){/* sleep(); */}
// vector 144 ERI0 SCI0
__interrupt(vect=144) void INT_ERI0_SCI0(void){/* sleep(); */}
// vector 145 RXI0 SCI0
__interrupt(vect=145) void INT_RXI0_SCI0(void){/* sleep(); */}
// vector 146 TXI0 SCI0
__interrupt(vect=146) void INT_TXI0_SCI0(void){/* sleep(); */}
// vector 147 TEI0 SCI0
__interrupt(vect=147) void INT_TEI0_SCI0(void){/* sleep(); */}
// vector 148 ERI1 SCI1
__interrupt(vect=148) void INT_ERI1_SCI1(void){/* sleep(); */}
// vector 149 RXI1 SCI1
__interrupt(vect=149) void INT_RXI1_SCI1(void){/* sleep(); */}
// vector 150 TXI1 SCI1
__interrupt(vect=150) void INT_TXI1_SCI1(void){/* sleep(); */}
// vector 151 TEI1 SCI1
__interrupt(vect=151) void INT_TEI1_SCI1(void){/* sleep(); */}
// vector 152 ERI2 SCI2
__interrupt(vect=152) void INT_ERI2_SCI2(void){/* sleep(); */}
// vector 153 RXI2 SCI2
__interrupt(vect=153) void INT_RXI2_SCI2(void){/* sleep(); */}
// vector 154 TXI2 SCI2
__interrupt(vect=154) void INT_TXI2_SCI2(void){/* sleep(); */}
// vector 155 TEI2 SCI2
__interrupt(vect=155) void INT_TEI2_SCI2(void){/* sleep(); */}
// vector 156 Reserved

// vector 157 Reserved

// vector 158 Reserved

// vector 159 Reserved

// vector 160 ERI4 SCI4
__interrupt(vect=160) void INT_ERI4_SCI4(void){/* sleep(); */}
// vector 161 RXI4 SCI4
__interrupt(vect=161) void INT_RXI4_SCI4(void){/* sleep(); */}
// vector 162 TXI4 SCI4
__interrupt(vect=162) void INT_TXI4_SCI4(void){/* sleep(); */}
// vector 163 TEI4 SCI4
__interrupt(vect=163) void INT_TEI4_SCI4(void){/* sleep(); */}
// vector 164 TGI6A TPU6
__interrupt(vect=164) void INT_TGI6A_TPU6(void){Int_1msFunc();}
// vector 165 TGI6B TPU6
__interrupt(vect=165) void INT_TGI6B_TPU6(void){/* sleep(); */}
// vector 166 TGI6C TPU6
__interrupt(vect=166) void INT_TGI6C_TPU6(void){/* sleep(); */}
// vector 167 TGI6D TPU6
__interrupt(vect=167) void INT_TGI6D_TPU6(void){/* sleep(); */}
// vector 168 TGI6V TPU6
__interrupt(vect=168) void INT_TGI6V_TPU6(void){/* sleep(); */}
// vector 169 TGI7A TPU7
__interrupt(vect=169) void INT_TGI7A_TPU7(void){/* sleep(); */}
// vector 170 TGI7B TPU7
__interrupt(vect=170) void INT_TGI7B_TPU7(void){/* sleep(); */}
// vector 171 TGI7V TPU7
__interrupt(vect=171) void INT_TGI7V_TPU7(void){/* sleep(); */}
// vector 172 TGI7U TPU7
__interrupt(vect=172) void INT_TGI7U_TPU7(void){/* sleep(); */}
// vector 173 TGI8A TPU8
__interrupt(vect=173) void INT_TGI8A_TPU8(void){/* sleep(); */}
// vector 174 TGI8B TPU8
__interrupt(vect=174) void INT_TGI8B_TPU8(void){/* sleep(); */}
// vector 175 TGI8V TPU8
__interrupt(vect=175) void INT_TGI8V_TPU8(void){/* sleep(); */}
// vector 176 TGI8U TPU8
__interrupt(vect=176) void INT_TGI8U_TPU8(void){/* sleep(); */}
// vector 177 TGI9A TPU9
__interrupt(vect=177) void INT_TGI9A_TPU9(void){/* sleep(); */}
// vector 178 TGI9B TPU9
__interrupt(vect=178) void INT_TGI9B_TPU9(void){/* sleep(); */}
// vector 179 TGI9C TPU9
__interrupt(vect=179) void INT_TGI9C_TPU9(void){/* sleep(); */}
// vector 180 TGI9D TPU9
__interrupt(vect=180) void INT_TGI9D_TPU9(void){/* sleep(); */}
// vector 181 TGI9V TPU9
__interrupt(vect=181) void INT_TGI9V_TPU9(void){/* sleep(); */}
// vector 182 TGI10A TPU10
__interrupt(vect=182) void INT_TGI10A_TPU10(void){/* sleep(); */}
// vector 183 TGI10B TPU10
__interrupt(vect=183) void INT_TGI10B_TPU10(void){/* sleep(); */}
// vector 184 Reserved

// vector 185 Reserved

// vector 186 TGI10V TPU10
__interrupt(vect=186) void INT_TGI10V_TPU10(void){/* sleep(); */}
// vector 187 TGI10U TPU10
__interrupt(vect=187) void INT_TGI10U_TPU10(void){/* sleep(); */}
// vector 188 TGI11A TPU11
__interrupt(vect=188) void INT_TGI11A_TPU11(void){/* sleep(); */}
// vector 189 TGI11B TPU11
__interrupt(vect=189) void INT_TGI11B_TPU11(void){/* sleep(); */}
// vector 190 TGI11V TPU11
__interrupt(vect=190) void INT_TGI11V_TPU11(void){/* sleep(); */}
// vector 191 TGI11U TPU11
__interrupt(vect=191) void INT_TGI11U_TPU11(void){/* sleep(); */}
// vector 192 Reserved

// vector 193 Reserved

// vector 194 Reserved

// vector 195 Reserved

// vector 196 Reserved

// vector 197 Reserved

// vector 198 Reserved

// vector 199 Reserved

// vector 200 Reserved

// vector 201 Reserved

// vector 202 Reserved

// vector 203 Reserved

// vector 204 Reserved

// vector 205 Reserved

// vector 206 Reserved

// vector 207 Reserved

// vector 208 Reserved

// vector 209 Reserved

// vector 210 Reserved

// vector 211 Reserved

// vector 212 Reserved

// vector 213 Reserved

// vector 214 Reserved

// vector 215 Reserved

// vector 216 IICI0 IIC2
__interrupt(vect=216) void INT_IICI0_IIC2(void){iici0_interrupt();}
// vector 217 Reserved

// vector 218 IICI1 IIC2
__interrupt(vect=218) void INT_IICI1_IIC2(void){/* sleep(); */}
// vector 219 Reserved

// vector 220 RXI5 SCI5
__interrupt(vect=220) void INT_RXI5_SCI5(void){Int_Handler_UART_Rx();}
// vector 221 TXI5 SCI5
__interrupt(vect=221) void INT_TXI5_SCI5(void){Int_Handler_UART_Tx();}
// vector 222 ERI5 SCI5
__interrupt(vect=222) void INT_ERI5_SCI5(void){Int_Handler_UART_Rx_ERR();}
// vector 223 TEI5 SCI5
__interrupt(vect=223) void INT_TEI5_SCI5(void){Int_Handler_UART_Tx_END();}
// vector 224 RXI6 SCI6
__interrupt(vect=224) void INT_RXI6_SCI6(void){/* sleep(); */}
// vector 225 TXI6 SCI6
__interrupt(vect=225) void INT_TXI6_SCI6(void){/* sleep(); */}
// vector 226 ERI6 SCI6
__interrupt(vect=226) void INT_ERI6_SCI6(void){/* sleep(); */}
// vector 227 TEI6 SCI6
__interrupt(vect=227) void INT_TEI6_SCI6(void){/* sleep(); */}
// vector 228 CMIA4/CMIB4 TMR4
__interrupt(vect=228) void INT_CMIA4_CMIB4_TMR4(void){/* sleep(); */}
// vector 229 CMIA5/CMIB5 TMR5
__interrupt(vect=229) void INT_CMIA5_CMIB5_TMR5(void){/* sleep(); */}
// vector 230 CMIA6/CMIB6 TMR6
__interrupt(vect=230) void INT_CMIA6_CMIB6_TMR6(void){/* sleep(); */}
// vector 231 CMIA7/CMIB7 TMR7
__interrupt(vect=231) void INT_CMIA7_CMIB7_TMR7(void){/* sleep(); */}
// vector 232 USBINTN0 USB
__interrupt(vect=232) void INT_USBINTN0_USB(void){/* sleep(); */}
// vector 233 USBINTN1 USB
__interrupt(vect=233) void INT_USBINTN1_USB(void){/* sleep(); */}
// vector 234 USBINTN2 USB
__interrupt(vect=234) void INT_USBINTN2_USB(void){/* sleep(); */}
// vector 235 USBINTN3 USB
__interrupt(vect=235) void INT_USBINTN3_USB(void){/* sleep(); */}
// vector 236 Reserved

// vector 237 ADI1
__interrupt(vect=237) void INT_ADI1(void){/* sleep(); */}
// vector 238 RESUME USB
__interrupt(vect=238) void INT_RESUME_USB(void){/* sleep(); */}
// vector 239 Reserved

// vector 240 Reserved

// vector 241 Reserved

// vector 242 Reserved

// vector 243 Reserved

// vector 244 Reserved

// vector 245 Reserved

// vector 246 Reserved

// vector 247 Reserved

// vector 248 Reserved

// vector 249 Reserved

// vector 250 Reserved

// vector 251 Reserved

// vector 252 Reserved

// vector 253 Reserved

// vector 254 Reserved

// vector 255 Reserved

