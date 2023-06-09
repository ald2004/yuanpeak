#pragma once 

#ifdef __cplusplus
extern "C"{
#endif

#include "systick.h"
#include "bsp_usart.h"

#ifdef __cplusplus
}
#endif
struct Serial
{
    uint32_t br;

    Serial(uint32_t br)
    :br(br){
        
    }
    static void begin(uint32_t br){
        systick_config();
        usart_gpio_config(br);
    };
    
    static size_t println(const char *str){
        size_t n = 0;
        while (*str)
        {
            usart_send_string((uint8_t*)str++);
            n++;
        }
        return n;
    }
    
};

