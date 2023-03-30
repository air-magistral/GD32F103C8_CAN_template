/*!
 \file    gd32f10x_eval.h
 \brief   definitions for GD32F10x_EVAL's leds, keys and COM ports hardware resources

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

#ifndef GD32F10X_EVAL_H
#define GD32F10X_EVAL_H

#ifdef cplusplus
 extern "C" {
#endif

#include "gd32f10x.h"

/* exported types */
typedef enum {
	LED_LEFT = 0, LED_STROB = 1, LED_RIGH = 2
} led_typedef_enum;

typedef enum {
	KEY_WAKEUP = 0, KEY_TAMPER = 1, KEY_USER = 2
} key_typedef_enum;

typedef enum {
	KEY_MODE_GPIO = 0, KEY_MODE_EXTI = 1
} keymode_typedef_enum;




#define LEDn                             3U

#define LED_LEFT_PIN                         GPIO_PIN_14
#define LED_LEFT_GPIO_PORT                   GPIOB
#define LED_LEFT_GPIO_CLK                    RCU_GPIOB

#define LED_RIGH_PIN                         GPIO_PIN_12
#define LED_RIGH_GPIO_PORT                   GPIOB
#define LED_RIGH_GPIO_CLK                    RCU_GPIOB

#define LED_STROB_PIN                         GPIO_PIN_13
#define LED_STROB_GPIO_PORT                   GPIOB
#define LED_STROB_GPIO_CLK                    RCU_GPIOB

#define COMn                             2U

#define EVAL_COM0                        USART0
#define EVAL_COM0_CLK                    RCU_USART0
#define EVAL_COM0_TX_PIN                 GPIO_PIN_9
#define EVAL_COM0_RX_PIN                 GPIO_PIN_10
#define EVAL_COM0_GPIO_PORT              GPIOA
#define EVAL_COM0_GPIO_CLK               RCU_GPIOA

#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCU_USART1
#define EVAL_COM1_TX_PIN                 GPIO_PIN_2
#define EVAL_COM1_RX_PIN                 GPIO_PIN_3
#define EVAL_COM1_GPIO_PORT              GPIOA
#define EVAL_COM1_GPIO_CLK               RCU_GPIOA

#define KEYn                             3U

/* wakeup push-button */
#define WAKEUP_KEY_PIN                   GPIO_PIN_0
#define WAKEUP_KEY_GPIO_PORT             GPIOA
#define WAKEUP_KEY_GPIO_CLK              RCU_GPIOA
#define WAKEUP_KEY_EXTI_LINE             EXTI_0
#define WAKEUP_KEY_EXTI_PORT_SOURCE      GPIO_PORT_SOURCE_GPIOA
#define WAKEUP_KEY_EXTI_PIN_SOURCE       GPIO_PIN_SOURCE_0
#define WAKEUP_KEY_EXTI_IRQn             EXTI0_IRQn  

/* tamper push-button */
#define TAMPER_KEY_PIN                   GPIO_PIN_6
#define TAMPER_KEY_GPIO_PORT             GPIOA
#define TAMPER_KEY_GPIO_CLK              RCU_GPIOA
#define TAMPER_KEY_EXTI_LINE             EXTI_6
#define TAMPER_KEY_EXTI_PORT_SOURCE      GPIO_PORT_SOURCE_GPIOA
#define TAMPER_KEY_EXTI_PIN_SOURCE       GPIO_PIN_SOURCE_6
#define TAMPER_KEY_EXTI_IRQn             EXTI10_15_IRQn

/* user push-button */
#define USER_KEY_PIN                     GPIO_PIN_14
#define USER_KEY_GPIO_PORT               GPIOB
#define USER_KEY_GPIO_CLK                RCU_GPIOB
#define USER_KEY_EXTI_LINE               EXTI_14
#define USER_KEY_EXTI_PORT_SOURCE        GPIO_PORT_SOURCE_GPIOB
#define USER_KEY_EXTI_PIN_SOURCE         GPIO_PIN_SOURCE_14
#define USER_KEY_EXTI_IRQn               EXTI10_15_IRQn

/* function declarations */

/* configure led GPIO */
void led_init(led_typedef_enum lednum);
/* turn on selected led */
void led_on(led_typedef_enum lednum);
/* turn off selected led */
void led_off(led_typedef_enum lednum);
/* toggle the selected led */
void led_toggle(led_typedef_enum lednum);
/* configure key */
void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode);
/* return the selected key state */
uint8_t key_state_get(key_typedef_enum key);
/* configure COM port */
void com_init(uint32_t com);

#ifdef cplusplus
}
#endif

#endif /* GD32F10X_EVAL_H */
