#include "Display.h"

#include <rtthread.h>

void displayinit(){
    // Serial::println(" \n \r 11111 lvgl init 11111 \n \r ");

    //  lvgl init
    lv_init();
    rt_kprintf("  \n \r 55555555555 \n \r");
    lv_port_disp_init();
    rt_kprintf("\n \r  2222222222 lvgl inited.  2222 \n \r ");
    //lv_port_indev_init
    // lv_port_indev_init();
    // rt_kprintf(" \n \r 3333333333 touch inited.  333333333 \n \r  ");
    // lv_demo_stress();    
    // rt_kprintf("  \n \r 666666666666666666666 \n \r");
    ushort count=1; 
    while(1){
        // Serial::println("  \n \r 777777777777777777777777 \n \r");
        rt_thread_mdelay(5);
        // lv_tick_inc(5);
        // Serial::println("  \n \r 888888888888888888 \n \r");
        lv_task_handler();
        // lv_timer_handler();
        if((count/999))
        {rt_kprintf("\n \r new we get tick : %d \n \r",rt_tick_get());count=1;}
        else count++;
        // vTaskDelay(5);
        // delay_1ms(5);
    }

}