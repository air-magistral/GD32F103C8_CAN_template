/*!
 \file    gd32f10x_it.c
 \brief   interrupt service routines

 \version 2014-12-26, V1.0.0, firmware for GD32F10x
 \version 2017-06-20, V2.0.0, firmware for GD32F10x
 \version 2018-07-31, V2.1.0, firmware for GD32F10x
 \version 2020-09-30, V2.2.0, firmware for GD32F10x
 */

/*
 Copyright (c) 2020, GigaDevice Semiconductor Inc.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 3. Neither the name of the copyright holder nor the names of its contributors
 may be used to endorse or promote products derived from this software without
 specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 OF SUCH DAMAGE.
 */

#include "gd32f10x_it.h"
#include "gd32f10x_eval.h"

extern FlagStatus can0_receive_flag;
extern can_receive_message_struct receive_message;
extern can_trasnmit_message_struct transmit_message;
extern int prog;
extern int n;
extern int b;
extern int v;
extern int sign;

int m, b0, m0, b_s, m_s;
extern uint32_t address;
/*!
 \brief      this function handles NMI exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void NMI_Handler(void) {
}

/*!
 \brief      this function handles HardFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void HardFault_Handler(void) {
	/* if Hard Fault exception occurs, go to infinite loop */
	while (1) {
	}
}

/*!
 \brief      this function handles MemManage exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void MemManage_Handler(void) {
	/* if Memory Manage exception occurs, go to infinite loop */
	while (1) {
	}
}

/*!
 \brief      this function handles BusFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void BusFault_Handler(void) {
	/* if Bus Fault exception occurs, go to infinite loop */
	while (1) {
	}
}

/*!
 \brief      this function handles UsageFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void UsageFault_Handler(void) {
	/* if Usage Fault exception occurs, go to infinite loop */
	while (1) {
	}
}

/*!
 \brief      this function handles SVC exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void SVC_Handler(void) {
}

/*!
 \brief      this function handles DebugMon exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void DebugMon_Handler(void) {
}

/*!
 \brief      this function handles PendSV exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void PendSV_Handler(void) {
}

/*!
 \brief      this function handles SysTick exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
//void SysTick_Handler(void) {
//
//}
/*!
 \brief      this function handles CAN0 RX0 exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void CAN0_RX1_IRQHandler(void) {
	/* check the receive message */
	can_message_receive(CAN0, CAN_FIFO1, &receive_message);

	if ((address == receive_message.rx_efid)
			&& (CAN_FF_EXTENDED == receive_message.rx_ff)
			&& (2 == receive_message.rx_dlen)) {
		//can0_receive_flag = SET;
		can0_receive_flag = SET;

		sign = receive_message.rx_data[0] >> 4;
		b_s = receive_message.rx_data[1] & 0x3; /* brightnes */
		m_s = receive_message.rx_data[0] & 0xF; /* prog */

		v++;
		if (v > 250) {
			n = 0;
			v = 0;
		}
		/* ----------------------------sign type----------------------------- */
		switch (sign) {
		case 0:
			if ((b != b_s) || (m != m_s)) {
				b = b_s;
				m = m_s;
				if (m < 7) {
					prog = m;
					n = 0;
					v = 0;
				} else {
				}
			}
			transmit_message.tx_data[0] = receive_message.rx_data[0];
			transmit_message.tx_data[1] = receive_message.rx_data[1];
			can_message_transmit(CAN0, &transmit_message);
			break;
		case 1:
			if ((b0 != b_s) || (m0 != m_s)) {
				b0 = b_s;
				m0 = m_s;
				n = 0;
				v = 0;
			}
			break;
		}

	}
}

