#include "Display.h"
#include "Serial.h"


void displayinit(){
    Serial::println("\r 11111 lvgl init 11111");

    //  lvgl init
    lv_init();
    lv_port_disp_init();
    Serial::println("\r 2222222222 lvgl inited.  2222 ");
    //lv_port_indev_init
    lv_port_indev_init();
    Serial::println("\r 3333333333 touch inited.  333333333 ");
}