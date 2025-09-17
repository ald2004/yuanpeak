#include "Display.h"
#include "Serial.h"
#include "lv_examples.h"
#include "demos/lv_demos.h"
#include "pic.h"

// extern const unsigned char gImage_xxxx[] ;

void displayinit(){
    //  lvgl init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_demo_stress();
    while(1){
        lv_tick_inc(1);
        lv_task_handler();
        // vTaskDelay(5);
        delay_1ms(5);
    }

}