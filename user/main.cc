#include "HAL/HAL.h"
#include "config/version.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#include "gd32f4xx.h"
#include "HAL/systick.h"
#include <stdio.h>
#include "HAL/bsp_usart.h"

#ifdef __cplusplus
}
#endif

#include "HAL/Serial.h"

int main(void){
    HAL::Init();
    

    while(1) {
        delay_1ms(1000);
        Serial::println(".");
    }
}