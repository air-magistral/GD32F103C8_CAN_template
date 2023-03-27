#include <stdio.h>
#include <stdlib.h>

#include "diag/trace.h"
#include "timer.h"
#include "gd32f10x.h"
#include "gd32f10x_eval.h"

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

void nvic_config(void);
void gpio_config(void);
void can_config(can_parameter_struct can_parameter,
		can_filter_parameter_struct can_filter);

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

	/* configure USART */
//	gd_eval_com_init(EVAL_COM0);
	/* configure key */

	gd_eval_key_init(KEY_TAMPER, KEY_MODE_GPIO);

	gd_eval_led_off(LED4);

	/* initialize CAN and filter */
	can_config(can_init_parameter, can_filter_parameter);
	/* enable can receive FIFO0 not empty interrupt */
	can_interrupt_enable(CAN0, CAN_INT_RFNE1);

	/* initialize transmit message */
	can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);

	transmit_message.tx_sfid = 0x00;
	transmit_message.tx_efid = 0xaabb;
	transmit_message.tx_ft = CAN_FT_DATA;
	transmit_message.tx_ff = CAN_FF_EXTENDED;
	transmit_message.tx_dlen = 8;

	transmit_message.tx_data[0] = 0xA0U;
	transmit_message.tx_data[1] = 0xA1U;
	transmit_message.tx_data[2] = 0xA2U;
	transmit_message.tx_data[3] = 0xA3U;
	transmit_message.tx_data[4] = 0xA4U;
	transmit_message.tx_data[5] = 0xA5U;
	transmit_message.tx_data[6] = 0xA6U;
	transmit_message.tx_data[7] = 0xA7U;

	while (1) {
		/* test whether the Tamper key is pressed */
		if (0 == gd_eval_key_state_get(KEY_TAMPER)) {
			/* transmit message */
			can_message_transmit(CAN0, &transmit_message);
			gd_eval_led_toggle(LED4);
			/* waiting for the Tamper key up */
			while (0 == gd_eval_key_state_get(KEY_TAMPER))
				;
		}
		/* CAN0 receive data correctly, the received data is printed */
		if (SET == can0_receive_flag) {
			can0_receive_flag = RESET;
			gd_eval_led_toggle(LED4);
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
	can_struct_para_init(CAN_INIT_STRUCT, &can_filter);
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
	can_filter.filter_list_high = 0x0000;
	can_filter.filter_list_low = 0x0000;
	can_filter.filter_mask_high = 0x0000;
	can_filter.filter_mask_low = 0x0000;
	can_filter.filter_fifo_number = CAN_FIFO1;
	can_filter.filter_enable = ENABLE;

	can_filter_init(&can_filter);

	/* CAN0 filter number */
	can_filter.filter_number = 15;
	can_filter_init(&can_filter);
}

void nvic_config(void) {
	/* configure CAN0 NVIC */
	nvic_irq_enable(CAN0_RX1_IRQn, 0, 0);

}

void gpio_config(void) {
	/* enable CAN clock */
	rcu_periph_clock_enable(RCU_CAN0);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_AF);

	/* configure CAN0 GPIO */
	gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_11); /* CAN_RX*/
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12); /* CAN_TX */

	/* configure LED GPIO */
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
