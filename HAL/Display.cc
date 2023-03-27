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
    lv_demo_stress();    
    rt_kprintf("  \n \r 666666666666666666666 \n \r");
    
}