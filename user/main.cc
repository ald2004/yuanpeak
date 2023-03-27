#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "config/version.h"
// #include "gd32f4xx.h"

// #include "HAL/systick.h"
// #include <stdio.h>
// #include <rtthread.h>
// #include "HAL/bsp_usart.h"
// #include "lv_demos.h"
// #include "lib/lvgl/lvgl.h"
// #include <rtdevice.h>
#include "mythread.h"
#ifdef __cplusplus
}
#endif
#include "HAL/HAL.h"
#include "HAL/Serial.h"
#include "HAL/Display.h"


// W9825G6KH-6
int main(void){

    // uint16_t i,j;
    // uint8_t t = 0;
    // uint16_t lastpos[5][2];
    // led_init();
    // key_init();
    HAL::Init();
    // displayinit();
    // rt_mythread_init();
    lvgl_thread_init();
    rt_kprintl("new wet :%d",333);
    while(1) {
        Serial::println("-");
        rt_thread_mdelay(1000);
    //     // rt_kprintf("now we get tick :%d \r\n",rt_tick_get()/RT_TICK_PER_SECOND);
    //     // GT1151_Scan(0);
    //     // for (t = 0; t < CT_MAX_TOUCH; t++) 
    //     // {
    //     //     if ((tp_dev.sta) & (1 << t))
    //     //     {
    //     //         if (lastpos[t][0] == 0XFFFF)
    //     //         {
    //     //             lastpos[t][0] = tp_dev.x[t];
    //     //             lastpos[t][1] = tp_dev.y[t];
    //     //         }
    //     //         lastpos[t][0] = tp_dev.x[t];
    //     //         lastpos[t][1] = tp_dev.y[t];
    //     //         printf("tp_dev.x[t]:%d tp_dev.y[t]:%d\r\n", tp_dev.x[t], tp_dev.y[t]);
                
    //     //         LCD_Fast_DrawPoint(tp_dev.x[t], tp_dev.y[t],POINT_COLOR);
    //     //         LCD_Fast_DrawPoint(tp_dev.x[t]-1, tp_dev.y[t],POINT_COLOR);
    //     //         LCD_Fast_DrawPoint(tp_dev.x[t], tp_dev.y[t]-1,POINT_COLOR);
    //     //         LCD_Fast_DrawPoint(tp_dev.x[t]+1, tp_dev.y[t],POINT_COLOR);
    //     //         LCD_Fast_DrawPoint(tp_dev.x[t], tp_dev.y[t]+1,POINT_COLOR);
                
    //     //         i=0; //重新计时
    //     //     }
    //     //     else  lastpos[t][0] = 0XFFFF;
    //     // }
    //     // delay_1ms(1);
    }
}