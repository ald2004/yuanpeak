#pragma once 

#include "gd32f4xx.h"
#include "gd32f4xx_usart.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_gpio.h"

// #include "systick.h"
#include "stdio.h"

#define BSP_USART_TX_RCU  RCU_GPIOA
#define BSP_USART_RX_RCU  RCU_GPIOA
#define BSP_USART_RCU     RCU_USART0

#define BSP_USART_TX_PORT GPIOA
#define BSP_USART_RX_PORT GPIOA
#define BSP_USART_AF 			GPIO_AF_7
#define BSP_USART_TX_PIN  GPIO_PIN_9
#define BSP_USART_RX_PIN  GPIO_PIN_10

#define BSP_USART 				USART0


void usart_gpio_config(uint32_t band_rate);
void usart_send_data(uint8_t ucch);
void usart_send_string(uint8_t *ucstr);
