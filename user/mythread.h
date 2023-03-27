#include <rtthread.h>
#include "lib/lvgl/lvgl.h"
#include "lib/lvgl/porting/lv_port_disp.h"
#include "lib/lvgl/demos/lv_demos.h"
#include "rtthread/include/rtdbg.h"

void rt_mythread_entry(void*p){
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

void rt_mythread_init(void)
{
    rt_thread_t tid;
#ifdef RT_USING_HEAP
    tid = rt_thread_create("main", rt_mythread_entry, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(tid != RT_NULL);
#else
    rt_err_t result;
    tid = &main_thread;
    result = rt_thread_init(tid, "main", main_thread_entry, RT_NULL,
                            main_stack, sizeof(main_stack), RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(result == RT_EOK);
    /* if not define RT_USING_HEAP, using to eliminate the warning */
    (void)result;
#endif
    rt_thread_startup(tid);
}




static struct rt_thread lvgl_thread;
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*1/3)
#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif /* PKG_LVGL_THREAD_STACK_SIZE */
#define PKG_LVGL_DISP_REFR_PERIOD 5
static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

void my_print(lv_log_level_t level,  const char* dsc)
{
    rt_kprintl("%s",dsc);
}

static void lvgl_thread_entry(void *parameter)
{
#if LV_USE_LOG
    lv_log_register_print_cb(my_print);
#endif /* LV_USE_LOG */
    lv_init();
    lv_port_disp_init();
    lv_demo_stress();  
    // lv_port_indev_init();
    // lv_user_gui_init();

    /* handle the tasks of LVGL */
    while(1)
    {
        // lv_tick_inc(1);
        lv_task_handler();
        rt_thread_mdelay(PKG_LVGL_DISP_REFR_PERIOD);
    }
}

static int lvgl_thread_init(void)
{
    rt_err_t err;

    err = rt_thread_init(&lvgl_thread, "LVGL", lvgl_thread_entry, RT_NULL,
           &lvgl_thread_stack[0], sizeof(lvgl_thread_stack), PKG_LVGL_THREAD_PRIO, 0);
    if(err != RT_EOK)
    {
        LOG_E("Failed to create LVGL thread");
        return -1;
    }
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_ENV_EXPORT(lvgl_thread_init);