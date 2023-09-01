/*
 * STM32F2XX Timer
 *
 * Copyright (c) 2014 Alistair Francis <alistair@alistair23.me>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HW_STM32F746_RCC_H
#define HW_STM32F746_RCC_H

#include "hw/sysbus.h"
#include "qemu/timer.h"
#include "qom/object.h"

#define RCC_CR         0x00
#define RCC_PLLCFGR    0x04
#define RCC_CFGR       0x08
#define RCC_CIR        0x0C
#define RCC_AHB1RSTR   0x10
#define RCC_AHB2RSTR   0x14
#define RCC_AHB3RSTR   0x18
#define RCC_RESERVED1  0x1C
#define RCC_APB1RSTR   0x20
#define RCC_APB2RSTR   0x24
#define RCC_RESERVED2  0x28
#define RCC_RESERVED3  0x2C
#define RCC_AHB1ENR    0x30
#define RCC_AHB2ENR    0x34
#define RCC_AHB3ENR    0x38
#define RCC_RESERVED4  0x3C
#define RCC_APB1ENR    0x40
#define RCC_APB2ENR    0x44
#define RCC_RESERVED5  0x48
#define RCC_RESERVED6  0x4C
#define RCC_AHB1LPENR  0x50
#define RCC_AHB2LPENR  0x54
#define RCC_AHB3LPENR  0x58
#define RCC_RESERVED7  0x5C
#define RCC_APB1LPENR  0x60
#define RCC_APB2LPENR  0x64
#define RCC_RESERVED8  0x68
#define RCC_RESERVED9  0x6C
#define RCC_BDCR	   0x70
#define RCC_CSR		   0x74
#define RCC_RESERVEDA  0x78
#define RCC_RESERVEDB  0x7C
#define RCC_SSCGR 	   0x80
#define RCC_PLLI2SCFGR 0x84
#define RCC_PLLSAICFGR 0x88
#define RCC_DCKCFGR1   0x8C
#define RCC_DCKCFGR2   0x90



#define TYPE_STM32F746_RCC "stm32f746-rcc"
typedef struct STM32F746RccState STM32F746RccState;
DECLARE_INSTANCE_CHECKER(STM32F746RccState, STM32F746RCC,
                         TYPE_STM32F746_RCC)

struct STM32F746RccState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion iomem;
    QEMUTimer *timer;
    qemu_irq irq;

    int64_t tick_offset;
    uint64_t hit_time;
    uint64_t freq_hz;

    uint32_t rcc_cr        ;
    uint32_t rcc_pllcfgr   ;
    uint32_t rcc_cfgr      ;
    uint32_t rcc_cir       ;
    uint32_t rcc_ahb1rstr  ;
    uint32_t rcc_ahb2rstr  ;
    uint32_t rcc_ahb3rstr  ;
    uint32_t rcc_reserved1 ;
    uint32_t rcc_apb1rstr  ;
    uint32_t rcc_apb2rstr  ;
    uint32_t rcc_reserved2 ;
    uint32_t rcc_reserved3 ;
    uint32_t rcc_ahb1enr   ;
    uint32_t rcc_ahb2enr   ;
    uint32_t rcc_ahb3enr   ;
    uint32_t rcc_reserved4 ;
    uint32_t rcc_apb1enr   ;
    uint32_t rcc_apb2enr   ;
    uint32_t rcc_reserved5 ;
    uint32_t rcc_reserved6 ;
    uint32_t rcc_ahb1lpenr ;
    uint32_t rcc_ahb2lpenr ;
    uint32_t rcc_ahb3lpenr ;
    uint32_t rcc_reserved7 ;
    uint32_t rcc_apb1lpenr ;
    uint32_t rcc_apb2lpenr ;
    uint32_t rcc_reserved8 ;
    uint32_t rcc_reserved9 ;
    uint32_t rcc_bdcr	   ;
    uint32_t rcc_csr	   ;
    uint32_t rcc_reserveda ;
    uint32_t rcc_reservedb ;
    uint32_t rcc_sscgr 	   ;
    uint32_t rcc_plli2scfgr;
    uint32_t rcc_pllsaicfgr;
    uint32_t rcc_dckcfgr1  ;
    uint32_t rcc_dckcfgr2  ;
};

#endif /* HW_STM32F2XX_TIMER_H */

