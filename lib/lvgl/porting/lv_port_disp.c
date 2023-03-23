/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES 800
#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif
#define MY_DISP_VER_RES 480
#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif
lv_disp_t * disp;
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * color_p);
static int32_t            x1_flush;
static int32_t            y1_flush;
static int32_t            x2_flush;
static int32_t            y2_fill;
static int32_t            y_fill_act;
static const lv_color_t *buf_to_flush;
static lv_disp_t *our_disp = NULL;
static lv_disp_t disp_drv;
extern uint16_t *my_fb;
#define LCD_FRAME_BUF_ADDR          0XC0000000
#define COLOR_BUF_SIZE (LV_HOR_RES_MAX*LV_VER_RES_MAX)
#define TLI_LCD_FRAMEBUF_SIZE      (COLOR_BUF_SIZE*2)

/**********************
 *  STATIC VARIABLES
 **********************/
// #include "HAL/bsp_usart.h"
// static size_t println(const char *str){
//         size_t n = 0;
//         while (*str)
//         {
//             usart_send_string((uint8_t*)str++);
//             n++;
//         }
//         return n;
//     }
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();
    
    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_disp_t * disp = lv_disp_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    rt_kprintf("1111111111111111");
    // println("22222222222222222222");
    lv_disp_set_flush_cb(disp, disp_flush);
// println("3333333333333333");
    /* Example 1
     * One buffer for partial rendering*/
    static lv_color_t buf_1_1[MY_DISP_HOR_RES * 10];                          /*A buffer for 10 rows*/
    lv_disp_set_draw_buffers(disp, buf_1_1, NULL, sizeof(buf_1_1), LV_DISP_RENDER_MODE_PARTIAL);
// println("444444444444444444444444444444");
    /* Example 2
     * Two buffers for partial rendering
     * In flush_cb DMA or similar hardware should be used to update the display in the background.*/
    // static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];
    // static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];
    // lv_disp_set_draw_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISP_RENDER_MODE_PARTIAL);

    /* Example 3
     * Two buffers screen sized buffer for double buffering.
     * Both LV_DISP_RENDER_MODE_DIRECT and LV_DISP_RENDER_MODE_FULL works, see their comments*/


    // static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];
    // lv_disp_set_draw_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISP_RENDER_MODE_DIRECT);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    uint16_t POINT[5]={WHITE,BLUE,RED,YELLOW,GREEN};
    uint16_t BACK[5]={LIGHTGREEN,LIGHTGRAY,LGRAY,LGRAYBLUE,LBBLUE};
    // init lckfb display
     /* 8080 mcu屏 */
    LCD_Init(); //显示屏初始化代码
    
    POINT_COLOR=POINT[4];
    BACK_COLOR=BACK[0];
    LCD_Clear(BACK[4]);
    // LCD_ShowString(30,50,480,80,24,1,"https://lckfb.com");
    // LCD_ShowString(30,80,480,110,24,1,lcd_id);
    // LCD_ShowString(30,110,480,140,24,1,"touch test....");
    LCD_Scan_Dir(D2U_L2R);
    rt_kprintf("disp_init finish.");
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(disp_flush_enabled || 1) {
    //     /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

        int32_t x;
        int32_t y;
        for(y = area->y1; y <= area->y2; y++) {
            for(x = area->x1; x <= area->x2; x++) {
                /*Put a pixel to the display. For example:*/
                // put_px(x, y, *color_p)
                LCD_Fast_DrawPoint(x,y,*(uint16_t *)(color_p));
                color_p++;
            }
        }
    // void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)
    // BlockWrite(area->x1,area->x2,area->y1,area->y2);
    // LCD_WriteRAM_Prepare();
    // LCD_WriteRAM(*(uint16_t *)color_p); //*(uint16_t *)&c1;
    // void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color)

    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
