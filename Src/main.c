#include <stdio.h>
#include <stdlib.h>

#include "diag/trace.h"
#include "timer.h"
#include "gd32f10x.h"
#include "gd32f10x_eval.h"

#define SIGN  1		//LEFT_RIGH
//#define SIGN  1		//ROAD

/* select CAN baudrate */
/* 1MBps */
//#define CAN_BAUDRATE  1000
/* 500kBps */
//#define CAN_BAUDRATE  500
/* 250kBps */
#define CAN_BAUDRATE  250
/* 125kBps */
//#define CAN_BAUDRATE  125
/* 100kBps */
//#define CAN_BAUDRATE  100
/* 50kBps */
//#define CAN_BAUDRATE  50
/* 20kBps */
//#define CAN_BAUDRATE  20
FlagStatus can0_receive_flag;
FlagStatus can0_error_flag;
can_parameter_struct can_init_parameter;
can_filter_parameter_struct can_filter_parameter;
can_trasnmit_message_struct transmit_message;
can_receive_message_struct receive_message;

int prog;
int n;
int stat = 1;

int brightnes = 744; /* 25% = 744 || 50% = 2023 || 75% = 4221 || 100% =7999 */

#if SIGN ==0
uint32_t address = 0x18FFA110;
#elif SIGN == 1
uint32_t address = 0x18FFA210;
#else
#error "please select list SIGN in private defines in main.c "
#endif

void nvic_config(void);
void gpio_config(void);
void timer_config(void);
void can_config(can_parameter_struct can_parameter,
		can_filter_parameter_struct can_filter);
void set_prog(int);
void blink(void);
void blink_LEFT(void);
void blink_RIGH(void);
void LIGH_OFF(void);
void LIGH_ON(void);
void LIGH_RIGH(void);
void LIGH_LEFT(void);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(void) {
	timer_start();
	can0_receive_flag = RESET;
	can0_error_flag = RESET;

	/* configure GPIO */
	gpio_config();

	/* configure NVIC */
	nvic_config();

	/* configure timer */
	timer_config();

//	/* configure USART */
//	gd_eval_com_init(EVAL_COM0);
//	/* configure key */
//	key_init(KEY_TAMPER, KEY_MODE_GPIO);

	/* initialize CAN and filter */
	can_config(can_init_parameter, can_filter_parameter);
	/* enable can receive FIFO0 not empty interrupt */
	can_interrupt_enable(CAN0, CAN_INT_RFNE1);

	/* initialize transmit message */
	can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
	transmit_message.tx_sfid = 0x00;
#if SIGN ==0
	transmit_message.tx_efid = 0x18FFA71E;
#elif SIGN == 1
	transmit_message.tx_efid = 0x18FFA81E;
#else
	#error "please select list SIGN in private defines in main.c "
	#endif

	transmit_message.tx_ft = CAN_FT_DATA;
	transmit_message.tx_ff = CAN_FF_EXTENDED;
	transmit_message.tx_dlen = 2;

	transmit_message.tx_data[0] = 0x0U;
	transmit_message.tx_data[1] = 0x0U;

	can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);

	while (1) {

		/* CAN0 receive data correctly, the received data is printed */
		if (SET == can0_receive_flag) {
			//can0_receive_flag = RESET;
			if (n == 0) {
				transmit_message.tx_data[0] = prog;
				can_message_transmit(CAN0, &transmit_message);
			}
			set_prog(prog);
		}

		/* CAN0 error */
		if (SET == can0_error_flag) {
			can0_error_flag = RESET;
		}
	}
}

void can_config(can_parameter_struct can_parameter,
		can_filter_parameter_struct can_filter) {
	can_struct_para_init(CAN_INIT_STRUCT, &can_parameter);
	can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);
	/* initialize CAN register */
	can_deinit(CAN0);

	/* initialize CAN parameters */
	can_parameter.time_triggered = DISABLE;
	can_parameter.auto_bus_off_recovery = DISABLE;
	can_parameter.auto_wake_up = DISABLE;
	can_parameter.auto_retrans = DISABLE;
	can_parameter.rec_fifo_overwrite = DISABLE;
	can_parameter.trans_fifo_order = DISABLE;
	can_parameter.working_mode = CAN_NORMAL_MODE;
	can_parameter.resync_jump_width = CAN_BT_SJW_1TQ;
	can_parameter.time_segment_1 = CAN_BT_BS1_5TQ;
	can_parameter.time_segment_2 = CAN_BT_BS2_3TQ;

	/* 1MBps */
#if CAN_BAUDRATE == 1000
	can_parameter.prescaler = 6;
	/* 500KBps */
#elif CAN_BAUDRATE == 500
    can_parameter.prescaler = 12;
    /* 250KBps */
#elif CAN_BAUDRATE == 250
	can_parameter.prescaler = 24;
	/* 125KBps */
#elif CAN_BAUDRATE == 125
    can_parameter.prescaler = 48;
    /* 100KBps */
#elif  CAN_BAUDRATE == 100
    can_parameter.prescaler = 60;
    /* 50KBps */
#elif  CAN_BAUDRATE == 50
    can_parameter.prescaler = 120;
    /* 20KBps */
#elif  CAN_BAUDRATE == 20
	can_parameter.prescaler = 300;
#else
#error "please select list can baudrate in private defines in main.c "
#endif
	/* initialize CAN */
	can_init(CAN0, &can_parameter);

	/* initialize filter */
	can_filter.filter_number = 0;
	can_filter.filter_mode = CAN_FILTERMODE_MASK;
	can_filter.filter_bits = CAN_FILTERBITS_32BIT;
	can_filter.filter_list_high = (uint16_t) (0x18FFA010 >> 13);
	can_filter.filter_list_low = (uint16_t) (((uint16_t) 0x18FFA010 << 3)
			| (1U << 2));
	can_filter.filter_mask_high = (uint16_t) (0x1FFFF0FF >> 13);
	can_filter.filter_mask_low = (uint16_t) (((uint16_t) 0x1FFFF0FF << 3)
			| (1U << 2));
	can_filter.filter_fifo_number = CAN_FIFO1;
	can_filter.filter_enable = ENABLE;

	can_filter_init(&can_filter);

}

void nvic_config(void) {
	/* configure CAN0 NVIC */
	nvic_irq_enable(CAN0_RX1_IRQn, 0, 0);

}

void gpio_config(void) {
	/* enable CAN clock */
	gpio_afio_deinit();
	rcu_periph_clock_enable(RCU_CAN0);
	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_AF);

	/* configure CAN0 GPIO */
	gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_11); /* CAN_RX */
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12); /* CAN_TX */

	/* configure LED GPIO */
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
}

void timer_config(void) {

	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;

	rcu_periph_clock_enable(RCU_TIMER0);

	timer_deinit(TIMER0);

	/* TIMER1 configuration */
	timer_initpara.prescaler = 107;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 7999;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER0, &timer_initpara);

	/* CH1,CH2 and CH3 configuration in PWM mode */
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER0, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER0, TIMER_CH_1, &timer_ocintpara);
	timer_channel_output_config(TIMER0, TIMER_CH_2, &timer_ocintpara);

	timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0);
	timer_channel_output_mode_config(TIMER0, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER0, TIMER_CH_0,
	TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0);
	timer_channel_output_mode_config(TIMER0, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER0, TIMER_CH_1,
	TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0);
	timer_channel_output_mode_config(TIMER0, TIMER_CH_2, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER0, TIMER_CH_2,
	TIMER_OC_SHADOW_DISABLE);

	timer_primary_output_config(TIMER0, ENABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER0);
	/* auto-reload preload enable */
	timer_enable(TIMER0);
}

void set_prog(int prog_num) {
	switch (prog_num) {
	case 0:
		LIGH_OFF();
		break;
	case 1:
		LIGH_ON();
		break;
	case 2:
		LIGH_LEFT();
		break;
	case 3:
		LIGH_RIGH();
		break;
	case 4:
		blink();
		break;
	case 5:
		blink_LEFT();
		break;
	case 6:
		blink_RIGH();
		break;
	}
}

void LIGH_OFF() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n = 0;
		break;
	}
}

void LIGH_ON() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n = 0;
		break;
	}
}

void LIGH_LEFT() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(1000);
		n = 0;
		break;
	}
}

void LIGH_RIGH() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(1000);
		n = 0;
		break;
	}
}

void blink() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n = 0;
		break;
	}
}

void blink_LEFT() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_sleep(600);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_sleep(600);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, brightnes); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_sleep(600);
		n = 0;
		break;
	}
}

void blink_RIGH() {
	switch (n) {
	case 0:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_1, 0); /*LEFT*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n++;
		break;
	case 1:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(400);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n++;
		break;
	case 2:
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, brightnes); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, brightnes); /*RIGH*/
		timer_sleep(80);
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 0); /*STROB*/
		timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_2, 0); /*RIGH*/
		timer_sleep(600);
		n = 0;
		break;
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
