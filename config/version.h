#pragma once

// #define GD32F4xx

/* Firmware Version */
#define VERSION_FIRMWARE_NAME   "[littleVisual]"
#define VERSION_SOFTWARE        "v1.0"
#define VERSION_HARDWARE        "v1.1"
#define VERSION_AUTHOR_NAME     "PZH"

/* Number to string macro */
#define _VERSION_NUM_TO_STR_(n)  #n
#define VERSION_NUM_TO_STR(n)   _VERSION_NUM_TO_STR_(n)

/* LVGL Version */
#include "lvgl.h"
#define VERSION_LVGL            "v"\
                                VERSION_NUM_TO_STR(LVGL_VERSION_MAJOR)\
                                "."\
                                VERSION_NUM_TO_STR(LVGL_VERSION_MINOR)\
                                "."\
                                VERSION_NUM_TO_STR(LVGL_VERSION_PATCH)\
                                " "\
                                LVGL_VERSION_INFO