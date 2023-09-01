/*
 * STM32F746 Flash InterFace
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

#ifndef HW_STM32F746_FLASHIF_H
#define HW_STM32F746_FLASHIF_H

#include "hw/sysbus.h"
#include "qom/object.h"

#define FLASH_IF_ACR     0x00
#define FLASH_IF_KEYR    0x04
#define FLASH_IF_OPTKEYR 0x08
#define FLASH_IF_SR      0x0C
#define FLASH_IF_CR      0x10
#define FLASH_IF_OPTCR   0x14
#define FLASH_IF_OPTCR1  0x18




#define TYPE_STM32F746_FLASH_IF "stm32f746-FlashIF"
typedef struct STM32F746FlashIFState STM32F746FlashIFState;
DECLARE_INSTANCE_CHECKER(STM32F746FlashIFState, STM32F746FLASH_IF,
                         TYPE_STM32F746_FLASH_IF)

struct STM32F746FlashIFState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion iomem;

    uint32_t flash_acr    ;
    uint32_t flash_keyr   ;
    uint32_t flash_optkeyr;
    uint32_t flash_sr     ;
    uint32_t flash_cr     ;
    uint32_t flash_optcr  ;
    uint32_t flash_optcr1 ;
};

#endif /* HW_STM32F746_FLASH_IF_H */

