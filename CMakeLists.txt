cmake_minimum_required(VERSION 3.17)
# include(ARMClang_Cortex-M4.cmake)
# CMSIS_EnableFPU(FALSE)

project(gd32f450zgt6 LANGUAGES C ASM CXX)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX d)
add_definitions(-DGD32F450 -DUSE_STDPERIPH_DRIVER)
set(C_TARGET_FLAG --target=arm-arm-none-eabi)
# set(ASM_TARGET_FLAG --target=arm-arm-none-eabi )
# set(LINKER_TARGET_FLAG --cpu=Cortex-M4.fp.sp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
 
set(CROSS_COMPILE_PREFIX /opt/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi)
set(CMAKE_C_COMPILER ${CROSS_COMPILE_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE_PREFIX}-g++)
set(CMAKE_CPP_COMPILER ${CROSS_COMPILE_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${CROSS_COMPILE_PREFIX}-objcopy)
set(CMAKE_OBJDUMP ${CROSS_COMPILE_PREFIX}-objdump)
set(CMAKE_SIZE ${CROSS_COMPILE_PREFIX}-size)
set(CMAKE_AR ${CROSS_COMPILE_PREFIX}-ar)

set(CPU "-mcpu=cortex-m4")
set(FLOAT-ABI "")
#NONE for Cortex-M0/M0+/M3
set(FPU "")
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT-ABI}")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -std=gnu99 -Wall -fstack-usage -Wstack-usage=512 -fdata-sections -ffunction-sections -fno-common -fmessage-length=0 ${DBG_FLAGS} " CACHE INTERNAL "C compiler flags")
#CPP 
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -fno-rtti -fno-exceptions -fno-builtin -Wall -fdata-sections -ffunction-sections ${DBG_FLAGS} " CACHE INTERNAL "Cxx compiler flags")
#ASFLAGS
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp ${DBG_FLAGS} ")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -specs=nosys.specs -specs=nano.specs -Wl,--print-memory-usage,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections" CACHE INTERNAL "Exe linker flags")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-lc -lm -lnosys" CACHE INTERNAL "Shared linker flags")
# for use printf & scanf with float
set(COMMON_FLAGS "-specs=nosys.specs -specs=nano.specs -u _printf_float -u _scanf_float")

#Uncomment for hardware floating point
# add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
# add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
# add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)
# add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
# add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_compile_options(-Og)

# lvgl  =============================================================================================
# include(FetchContent)
option(LV_USE_DEMO_STRESS "lvgl stress test" ON)
file(GLOB_RECURSE LV_USE_DEMO_STRESS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/demos/stress/*.c)
if(LV_USE_DEMO_STRESS)
add_compile_definitions(WITH_OPENCV2)

endif()
# set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/lvgl)
set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/lvgl)
set(LV_CONF_PATH ${LVGL_ROOT_DIR}/lv_conf.h CACHE STRING "" FORCE)
option(LV_LVGL_H_INCLUDE_SIMPLE
       "Use #include \"lvgl.h\" instead of #include \"../../lvgl.h\"" ON)

# Option to define LV_CONF_INCLUDE_SIMPLE, default: ON
option(LV_CONF_INCLUDE_SIMPLE
       "Use #include \"lv_conf.h\" instead of #include \"../../lv_conf.h\"" ON)
option(LV_CONF_BUILD_DISABLE_EXAMPLES "disable example." ON) 
option(LV_CONF_BUILD_DISABLE_DEMOS "disable demos." ON)
# Option to set LV_CONF_PATH, if set parent path LV_CONF_DIR is added to
# includes
option(LV_CONF_PATH "Path defined for lv_conf.h")
get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# Option to build shared libraries (as opposed to static), default: OFF
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Set sources used for LVGL components
file(GLOB_RECURSE LVGL_SOURCES ${LVGL_ROOT_DIR}/src/*.c)
# file(GLOB_RECURSE EXAMPLE_SOURCES ${LVGL_ROOT_DIR}/examples/*.c)
file(GLOB EXAMPLE_SOURCES 
    ${LVGL_ROOT_DIR}/porting/lv_port_disp.c
    ${LVGL_ROOT_DIR}/porting/lv_port_indev.c
)
file(GLOB_RECURSE DEMO_SOURCES ${LVGL_ROOT_DIR}/demos/*.c)
# Build LVGL library
# add_library(lvgl ${LVGL_SOURCES})
# add_library(lvgl::lvgl ALIAS lvgl)

# target_compile_definitions(
#   lvgl PUBLIC $<$<BOOL:${LV_LVGL_H_INCLUDE_SIMPLE}>:LV_LVGL_H_INCLUDE_SIMPLE>
#               $<$<BOOL:${LV_CONF_INCLUDE_SIMPLE}>:LV_CONF_INCLUDE_SIMPLE>)

# Add definition of LV_CONF_PATH only if needed
# if(LV_CONF_PATH)
#   target_compile_definitions(lvgl PUBLIC LV_CONF_PATH=${LV_CONF_PATH})
# endif()

# Include root and optional parent path of LV_CONF_PATH
# target_include_directories(lvgl SYSTEM PUBLIC ${LVGL_ROOT_DIR} ${LV_CONF_DIR})
# Build LVGL example library
if(NOT LV_CONF_BUILD_DISABLE_EXAMPLES)
    add_library(lvgl_examples ${EXAMPLE_SOURCES})
    add_library(lvgl::examples ALIAS lvgl_examples)

    target_include_directories(lvgl_examples SYSTEM PUBLIC ${LVGL_ROOT_DIR}/examples)
    target_link_libraries(lvgl_examples PUBLIC lvgl)
endif()

# Build LVGL demos library
if(NOT LV_CONF_BUILD_DISABLE_DEMOS)
    add_library(lvgl_demos ${DEMO_SOURCES})
    add_library(lvgl::demos ALIAS lvgl_demos)

    target_include_directories(lvgl_demos SYSTEM PUBLIC ${LVGL_ROOT_DIR}/demos)
    target_link_libraries(lvgl_demos PUBLIC lvgl)
endif()

# Lbrary and headers can be installed to system using make install
file(GLOB LVGL_PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/lv_conf.h"
     "${CMAKE_SOURCE_DIR}/lvgl.h")

if("${LIB_INSTALL_DIR}" STREQUAL "")
  set(LIB_INSTALL_DIR "lib")
endif()
if("${INC_INSTALL_DIR}" STREQUAL "")
  set(INC_INSTALL_DIR "include/lvgl")
endif()

# install(
#   DIRECTORY "${CMAKE_SOURCE_DIR}/src"
#   DESTINATION "${CMAKE_INSTALL_PREFIX}/${INC_INSTALL_DIR}/"
#   FILES_MATCHING
#   PATTERN "*.h")

# set_target_properties(
#   lvgl
#   PROPERTIES OUTPUT_NAME lvgl
#              ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#              LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#              RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#              PUBLIC_HEADER "${LVGL_PUBLIC_HEADERS}")

# install(
#   TARGETS lvgl
#   ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
#   LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
#   RUNTIME DESTINATION "${LIB_INSTALL_DIR}"
#   PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}")
# lvgl  =============================================================================================



set(ASM_SOURCES ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32F4xx/Source/GCC/startup_gd32f450_470.S)
file(GLOB_RECURSE SOURCES
    # ${PROJECT_SOURCE_DIR}/GD32F4xx/*.c
    ${PROJECT_SOURCE_DIR}/user/*.c
    ${PROJECT_SOURCE_DIR}/HAL/*.c
    ${PROJECT_SOURCE_DIR}/HAL/*.cc
    ${PROJECT_SOURCE_DIR}/Firmware/CMSIS/GD/GD32F4xx/Source/system_gd32f4xx.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_gpio.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_timer.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_rcu.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_usart.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_spi.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_adc.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_exti.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_misc.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_crc.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_dac.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_tli.c
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_exmc.c
    ${PROJECT_SOURCE_DIR}/Hardware/key/key.c
    ${PROJECT_SOURCE_DIR}/Hardware/LED/led.c
    ${PROJECT_SOURCE_DIR}/Hardware/LCD/lcd.c
    ${PROJECT_SOURCE_DIR}/Hardware/LCD/pic_480800.c
    ${PROJECT_SOURCE_DIR}/Hardware/touch/touch.c
    ${PROJECT_SOURCE_DIR}/Hardware/usart0/usart0.c
    ${PROJECT_SOURCE_DIR}/User/gd32f4xx_it.c
    ${PROJECT_SOURCE_DIR}/User/systick.c
    ${PROJECT_SOURCE_DIR}/user/main.cc
    ${PROJECT_SOURCE_DIR}/Firmware/CMSIS/GD/GD32F4xx/Source/GCC/startup_gd32f450_470.S
    )
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/Firmware/CMSIS/GD/GD32F4xx/Include
    ${PROJECT_SOURCE_DIR}/Firmware/CMSIS
    ${PROJECT_SOURCE_DIR}/Firmware/GD32F4xx_standard_peripheral/Include
    ${PROJECT_SOURCE_DIR}/lvgl
    ${PROJECT_SOURCE_DIR}/lvgl/examples
    )
set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/Firmware/Ld/Link.ld)

add_executable(
    ${PROJECT_NAME}.elf 
    ${SOURCES} 
    ${LVGL_SOURCES}
    ${EXAMPLE_SOURCES}
    ${LV_USE_DEMO_STRESS_SOURCE}
)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
# add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")
# set_property(SOURCE ${ASM_SOURCES} PROPERTY LANGUAGE ASM)
# add_custom_command(TARGET ${PROJECT_NAME}.elf  POST_BUILD COMMAND scp -P 613 ${PROJECT_NAME}.elf proxy:/mnt/z/)