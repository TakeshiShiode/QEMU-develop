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

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/misc/stm32f746_flashif.h"
#include "migration/vmstate.h"
#include "qemu/log.h"
#include "qemu/module.h"



static void stm32f746_flashif_reset(DeviceState *dev)
{
    STM32F746FlashIFState *s = STM32F746FLASH_IF(dev);

    s->flash_acr      = 0x00000000;
    s->flash_keyr     = 0x00000000;
    s->flash_optkeyr  = 0x00000000;
    s->flash_sr       = 0x00000000;
    s->flash_cr       = 0x80000000;
    s->flash_optcr    = 0xC0FFAAFD;
    s->flash_optcr1   = 0xFF7F0080;
}

static uint64_t stm32f746_flashif_read(void *opaque, hwaddr offset,
                           unsigned size)
{
    STM32F746FlashIFState *s = opaque;
    uint64_t retvalue = 0;

    switch (offset) {
	case FLASH_IF_ACR      : retvalue =(uint64_t)s->flash_acr      ; break;
    case FLASH_IF_KEYR     : retvalue =(uint64_t)s->flash_keyr     ; break;
    case FLASH_IF_OPTKEYR  : retvalue =(uint64_t)s->flash_optkeyr  ; break;
    case FLASH_IF_SR       : retvalue =(uint64_t)s->flash_sr       ; break;
    case FLASH_IF_CR       : retvalue =(uint64_t)s->flash_cr       ; break;
    case FLASH_IF_OPTCR    : retvalue =(uint64_t)s->flash_optcr    ; break;
    case FLASH_IF_OPTCR1   : retvalue =(uint64_t)s->flash_optcr1   ; break;

    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, offset);
    }

    return retvalue;
}

static void stm32f746_flashif_write(void *opaque, hwaddr offset,
                        uint64_t val64, unsigned size)
{
    STM32F746FlashIFState *s = opaque;
    uint32_t value = val64;

    switch (offset) {
    case FLASH_IF_ACR      : s->flash_acr      = value; break;
    case FLASH_IF_KEYR     : s->flash_keyr     = value; break;
    case FLASH_IF_OPTKEYR  : s->flash_optkeyr  = value; break;
    case FLASH_IF_SR       : s->flash_sr       = value; break;
    case FLASH_IF_CR       : s->flash_cr       = value; break;
    case FLASH_IF_OPTCR    : s->flash_optcr    = value; break;
    case FLASH_IF_OPTCR1   : s->flash_optcr1   = value; break;
 
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, offset);
        return;
    }
}

static const MemoryRegionOps stm32f746_flashif_ops = {
    .read = stm32f746_flashif_read,
    .write = stm32f746_flashif_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const VMStateDescription vmstate_stm32f746_flashif = {
    .name = TYPE_STM32F746_FLASH_IF,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(flash_acr     	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_keyr    	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_optkeyr  	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_sr       	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_cr      	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_optcr   	,STM32F746FlashIFState),
        VMSTATE_UINT32(flash_optcr1   	,STM32F746FlashIFState),
        VMSTATE_END_OF_LIST()
    }
};

static Property stm32f746_flashif_properties[] = {
    DEFINE_PROP_END_OF_LIST(),
};

static void stm32f746_flashif_init(Object *obj)
{
    STM32F746FlashIFState *s = STM32F746FLASH_IF(obj);

    memory_region_init_io(&s->iomem, obj, &stm32f746_flashif_ops, s,
                          "stm32f746-FlashIF", 0x400);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->iomem);
}

static void stm32f746_flashif_realize(DeviceState *dev, Error **errp)
{

}

static void stm32f746_flashif_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = stm32f746_flashif_reset;
    device_class_set_props(dc, stm32f746_flashif_properties);
    dc->vmsd = &vmstate_stm32f746_flashif;
    dc->realize = stm32f746_flashif_realize;
}

static const TypeInfo stm32f746_flashif_info = {
    .name          = TYPE_STM32F746_FLASH_IF,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32F746FlashIFState),
    .instance_init = stm32f746_flashif_init,
    .class_init    = stm32f746_flashif_class_init,
};

static void stm32f746_flashif_register_types(void)
{
    type_register_static(&stm32f746_flashif_info);
}

type_init(stm32f746_flashif_register_types)
