#include "Display.h"
#include "Serial.h"
#include "lv_examples.h"
#include "demos/lv_demos.h"

#include "maomao.h"
#include "baozi.h"

void displayinitxx(){
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


const lv_image_dsc_t img_baozi = {
  .header = {
    .magic = LV_IMAGE_HEADER_MAGIC,
    .cf = LV_COLOR_FORMAT_RGB565,
    .w = 306,
    .h = 240,
  },
  .data_size = 73440 * 2,
  .data = baozi,
};

const lv_image_dsc_t img_maomao = {
  .header = {
    .magic = LV_IMAGE_HEADER_MAGIC,
    .cf = LV_COLOR_FORMAT_RGB565,
    .w = 215,
    .h = 240,
  },
  .data_size = 51600 * 2,
  .data = maomao,
};


void displayinit(){
    //  lvgl init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    // lv_demo_stress();

    lv_obj_t * icon = lv_image_create(lv_screen_active());

    /* From variable */
    lv_image_set_src(icon, &img_maomao);

    while(1){
      if(GT1151_Scan(0))
        lv_image_set_src(icon, &img_baozi);
        lv_tick_inc(1);
        lv_task_handler();
        // vTaskDelay(5);
        delay_1ms(5);
    }

}