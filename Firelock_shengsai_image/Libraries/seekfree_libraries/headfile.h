
#ifndef _headfile_h
#define _headfile_h



#include "common.h"
#include <stdint.h>
#include "board.h"

//------CH32V103 SDK头文件
#include "ch32v10x.h"
#include "ch32v10x_adc.h"
#include "ch32v10x_bkp.h"
#include "ch32v10x_crc.h"
#include "ch32v10x_dbgmcu.h"
#include "ch32v10x_dma.h"
#include "ch32v10x_exti.h"
#include "ch32v10x_flash.h"
#include "ch32v10x_gpio.h"
#include "ch32v10x_i2c.h"
#include "ch32v10x_iwdg.h"
#include "ch32v10x_pwr.h"
#include "ch32v10x_rcc.h"
#include "ch32v10x_rtc.h"
#include "ch32v10x_spi.h"
#include "ch32v10x_tim.h"
#include "ch32v10x_usart.h"
#include "ch32v10x_wwdg.h"
#include "ch32v10x_usb.h"
#include "ch32v10x_usb_host.h"
#include "ch32v10x_misc.h"


//------逐飞科技单片机外设驱动头文件
#include "zf_adc.h"
#include "zf_camera.h"
#include "zf_flash.h"
#include "zf_gpio.h"
#include "zf_nvic.h"
#include "zf_pwm.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_qtimer.h"
#include "zf_uart.h"
#include "zf_pit.h"

//------逐飞科技产品驱动头文件

#include "SEEKFREE_IIC.h"
#include "SEEKFREE_PRINTF.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_WIRELESS.h"

#endif
