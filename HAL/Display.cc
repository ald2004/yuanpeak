#include "Display.h"
#include "Serial.h"


void displayinit(){
    Serial::println(" \n \r 11111 lvgl init 11111 \n \r ");

    //  lvgl init
    lv_init();
    lv_port_disp_init();
    Serial::println("\n \r  2222222222 lvgl inited.  2222 \n \r ");
    //lv_port_indev_init
    lv_port_indev_init();
    Serial::println(" \n \r 3333333333 touch inited.  333333333 \n \r  ");
    lv_demo_stress();   
    Serial::println("  \n \r 44444444444444444444444444444 \n \r");
    while(1){
        lv_tick_inc(1);
        lv_task_handler();
        // vTaskDelay(5);
        delay_1ms(5);
    }

}