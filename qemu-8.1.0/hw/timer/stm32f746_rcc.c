/*
 * STM32F746 Rcc
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
#include "hw/timer/stm32f746_rcc.h"
#include "migration/vmstate.h"
#include "qemu/log.h"
#include "qemu/module.h"

#ifndef STM_RCC_ERR_DEBUG
#define STM_RCC_ERR_DEBUG 0
#endif

#define DB_PRINT_L(lvl, fmt, args...) do { \
    if (STM_RCC_ERR_DEBUG >= lvl) { \
        qemu_log("%s: " fmt, __func__, ## args); \
    } \
} while (0)

#define DB_PRINT(fmt, args...) DB_PRINT_L(1, fmt, ## args)


static void stm32f746_rcc_interrupt(void *opaque)
{

}

static inline int64_t stm32f746_ns_to_ticks(STM32F746RccState *s, int64_t t)
{
    return 0;
}



static void stm32f746_rcc_reset(DeviceState *dev)
{
    STM32F746RccState *s = STM32F746RCC(dev);

    s->rcc_cr         = 0x00000083;
    s->rcc_pllcfgr    = 0x24003010;
    s->rcc_cfgr       = 0x00000000;
    s->rcc_cir        = 0x00000000;
    s->rcc_ahb1rstr   = 0x00000000;
    s->rcc_ahb2rstr   = 0x00000000;
    s->rcc_ahb3rstr   = 0x00000000;
    s->rcc_reserved1  = 0x00000000;
    s->rcc_apb1rstr   = 0x00000000;
    s->rcc_apb2rstr   = 0x00000000;
    s->rcc_reserved2  = 0x00000000;
    s->rcc_reserved3  = 0x00000000;
    s->rcc_ahb1enr    = 0x00100000;
    s->rcc_ahb2enr    = 0x00000000;
    s->rcc_ahb3enr    = 0x00000000;
    s->rcc_reserved4  = 0x00000000;
    s->rcc_apb1enr    = 0x00000000;
    s->rcc_apb2enr    = 0x00000000;
    s->rcc_reserved5  = 0x00000000;
    s->rcc_reserved6  = 0x00000000;
    s->rcc_ahb1lpenr  = 0x7EF7B7FF;
    s->rcc_ahb2lpenr  = 0x000000F1;
    s->rcc_ahb3lpenr  = 0x00000003;
    s->rcc_reserved7  = 0x00000000;
    s->rcc_apb1lpenr  = 0xFFFFCBFF;
    s->rcc_apb2lpenr  = 0x04F77F33;
    s->rcc_reserved8  = 0x00000000;
    s->rcc_reserved9  = 0x00000000;
    s->rcc_bdcr		  = 0x00000000;
    s->rcc_csr		  = 0x0E000000;
    s->rcc_reserveda  = 0x00000000;
    s->rcc_reservedb  = 0x00000000;
    s->rcc_sscgr 	  = 0x00000000;
    s->rcc_plli2scfgr = 0x24003000;
    s->rcc_pllsaicfgr = 0x24003000;
    s->rcc_dckcfgr1   = 0x00000000;
    s->rcc_dckcfgr2   = 0x00000000;
}

static uint64_t stm32f746_rcc_read(void *opaque, hwaddr offset,
                           unsigned size)
{
    STM32F746RccState *s = opaque;
    uint64_t retvalue = 0;

    DB_PRINT("Read 0x%"HWADDR_PRIx"\n", offset);

    switch (offset) {
	case RCC_CR         : retvalue =(uint64_t)s->rcc_cr        ; break;
    case RCC_PLLCFGR    : retvalue =(uint64_t)s->rcc_pllcfgr   ; break;
    case RCC_CFGR       : retvalue =(uint64_t)s->rcc_cfgr      ; break;
    case RCC_CIR        : retvalue =(uint64_t)s->rcc_cir       ; break;
    case RCC_AHB1RSTR   : retvalue =(uint64_t)s->rcc_ahb1rstr  ; break;
    case RCC_AHB2RSTR   : retvalue =(uint64_t)s->rcc_ahb2rstr  ; break;
    case RCC_AHB3RSTR   : retvalue =(uint64_t)s->rcc_ahb3rstr  ; break;
    case RCC_RESERVED1  : retvalue =(uint64_t)s->rcc_reserved1 ; break;
    case RCC_APB1RSTR   : retvalue =(uint64_t)s->rcc_apb1rstr  ; break;
    case RCC_APB2RSTR   : retvalue =(uint64_t)s->rcc_apb2rstr  ; break;
    case RCC_RESERVED2  : retvalue =(uint64_t)s->rcc_reserved2 ; break;
    case RCC_RESERVED3  : retvalue =(uint64_t)s->rcc_reserved3 ; break;
    case RCC_AHB1ENR    : retvalue =(uint64_t)s->rcc_ahb1enr   ; break;
    case RCC_AHB2ENR    : retvalue =(uint64_t)s->rcc_ahb2enr   ; break;
    case RCC_AHB3ENR    : retvalue =(uint64_t)s->rcc_ahb3enr   ; break;
    case RCC_RESERVED4  : retvalue =(uint64_t)s->rcc_reserved4 ; break;
    case RCC_APB1ENR    : retvalue =(uint64_t)s->rcc_apb1enr   ; break;
    case RCC_APB2ENR    : retvalue =(uint64_t)s->rcc_apb2enr   ; break;
    case RCC_RESERVED5  : retvalue =(uint64_t)s->rcc_reserved5 ; break;
    case RCC_RESERVED6  : retvalue =(uint64_t)s->rcc_reserved6 ; break;
    case RCC_AHB1LPENR  : retvalue =(uint64_t)s->rcc_ahb1lpenr ; break;
    case RCC_AHB2LPENR  : retvalue =(uint64_t)s->rcc_ahb2lpenr ; break;
    case RCC_AHB3LPENR  : retvalue =(uint64_t)s->rcc_ahb3lpenr ; break;
    case RCC_RESERVED7  : retvalue =(uint64_t)s->rcc_reserved7 ; break;
    case RCC_APB1LPENR  : retvalue =(uint64_t)s->rcc_apb1lpenr ; break;
    case RCC_APB2LPENR  : retvalue =(uint64_t)s->rcc_apb2lpenr ; break;
    case RCC_RESERVED8  : retvalue =(uint64_t)s->rcc_reserved8 ; break;
    case RCC_RESERVED9  : retvalue =(uint64_t)s->rcc_reserved9 ; break;
    case RCC_BDCR	    : retvalue =(uint64_t)s->rcc_bdcr	   ; break;
    case RCC_CSR		: retvalue =(uint64_t)s->rcc_csr	   ; break;
    case RCC_RESERVEDA  : retvalue =(uint64_t)s->rcc_reserveda ; break;
    case RCC_RESERVEDB  : retvalue =(uint64_t)s->rcc_reservedb ; break;
    case RCC_SSCGR 	    : retvalue =(uint64_t)s->rcc_sscgr 	   ; break;
    case RCC_PLLI2SCFGR : retvalue =(uint64_t)s->rcc_plli2scfgr; break;
    case RCC_PLLSAICFGR : retvalue =(uint64_t)s->rcc_pllsaicfgr; break;
    case RCC_DCKCFGR1   : retvalue =(uint64_t)s->rcc_dckcfgr1  ; break;
    case RCC_DCKCFGR2   : retvalue =(uint64_t)s->rcc_dckcfgr2  ; break;

    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, offset);
    }

    return retvalue;
}

static void stm32f746_rcc_write(void *opaque, hwaddr offset,
                        uint64_t val64, unsigned size)
{
    STM32F746RccState *s = opaque;
    uint32_t value = val64;
	uint32_t temp_cr = 0;
	uint32_t temp_cfgr = 0;
	
    DB_PRINT("Write 0x%x, 0x%"HWADDR_PRIx"\n", value, offset);

    switch (offset) {
	case RCC_CR: 
		s->rcc_cr = value;
		temp_cr = s->rcc_cr & 0x00010000;
		if(temp_cr != 0){
			s->rcc_cr |= 0x00020000;
		}
		else{
			s->rcc_cr &= 0xFFFDFFFF;
		}
		
		temp_cr = s->rcc_cr & 0x01000000;
		if(temp_cr != 0){
			s->rcc_cr |= 0x02000000;
		}
		else{
			s->rcc_cr &= 0xFDFFFFFF;
		}
		
		temp_cr = s->rcc_cr & 0x04000000;
		if(temp_cr != 0){
			s->rcc_cr |= 0x08000000;
		}
		else{
			s->rcc_cr &= 0xF7FFFFFF;
		} 

		temp_cr = s->rcc_cr & 0x10000000;
		if(temp_cr != 0){
			s->rcc_cr |= 0x20000000;
		}
		else{
			s->rcc_cr &= 0xDFFFFFFF;
		} 
		
	break;
    case RCC_PLLCFGR    : s->rcc_pllcfgr    = value; break;
    case RCC_CFGR       : 
    	s->rcc_cfgr       = value;
    	temp_cfgr = s->rcc_cfgr & 0x00000003;
    	s->rcc_cfgr |= temp_cfgr << 2;
    break;
    case RCC_CIR        : s->rcc_cir        = value; break;
    case RCC_AHB1RSTR   : s->rcc_ahb1rstr   = value; break;
    case RCC_AHB2RSTR   : s->rcc_ahb2rstr   = value; break;
    case RCC_AHB3RSTR   : s->rcc_ahb3rstr   = value; break;
    case RCC_RESERVED1  : s->rcc_reserved1  = value; break;
    case RCC_APB1RSTR   : s->rcc_apb1rstr   = value; break;
    case RCC_APB2RSTR   : s->rcc_apb2rstr   = value; break;
    case RCC_RESERVED2  : s->rcc_reserved2  = value; break;
    case RCC_RESERVED3  : s->rcc_reserved3  = value; break;
    case RCC_AHB1ENR    : s->rcc_ahb1enr    = value; break;
    case RCC_AHB2ENR    : s->rcc_ahb2enr    = value; break;
    case RCC_AHB3ENR    : s->rcc_ahb3enr    = value; break;
    case RCC_RESERVED4  : s->rcc_reserved4  = value; break;
    case RCC_APB1ENR    : s->rcc_apb1enr    = value; break;
    case RCC_APB2ENR    : s->rcc_apb2enr    = value; break;
    case RCC_RESERVED5  : s->rcc_reserved5  = value; break;
    case RCC_RESERVED6  : s->rcc_reserved6  = value; break;
    case RCC_AHB1LPENR  : s->rcc_ahb1lpenr  = value; break;
    case RCC_AHB2LPENR  : s->rcc_ahb2lpenr  = value; break;
    case RCC_AHB3LPENR  : s->rcc_ahb3lpenr  = value; break;
    case RCC_RESERVED7  : s->rcc_reserved7  = value; break;
    case RCC_APB1LPENR  : s->rcc_apb1lpenr  = value; break;
    case RCC_APB2LPENR  : s->rcc_apb2lpenr  = value; break;
    case RCC_RESERVED8  : s->rcc_reserved8  = value; break;
    case RCC_RESERVED9  : s->rcc_reserved9  = value; break;
    case RCC_BDCR	    : s->rcc_bdcr	    = value; break;
    case RCC_CSR		: s->rcc_csr	    = value; break;
    case RCC_RESERVEDA  : s->rcc_reserveda  = value; break;
    case RCC_RESERVEDB  : s->rcc_reservedb  = value; break;
    case RCC_SSCGR 	    : s->rcc_sscgr 	    = value; break;
    case RCC_PLLI2SCFGR : s->rcc_plli2scfgr = value; break;
    case RCC_PLLSAICFGR : s->rcc_pllsaicfgr = value; break;
    case RCC_DCKCFGR1   : s->rcc_dckcfgr1   = value; break;
    case RCC_DCKCFGR2   : s->rcc_dckcfgr2   = value; break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, offset);
        return;
    }
}

static const MemoryRegionOps stm32f746_rcc_ops = {
    .read = stm32f746_rcc_read,
    .write = stm32f746_rcc_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const VMStateDescription vmstate_stm32f746_rcc = {
    .name = TYPE_STM32F746_RCC,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_INT64(tick_offset,  STM32F746RccState),
        VMSTATE_UINT32(rcc_cr        	,STM32F746RccState),
        VMSTATE_UINT32(rcc_pllcfgr   	,STM32F746RccState),
        VMSTATE_UINT32(rcc_cfgr       	,STM32F746RccState),
        VMSTATE_UINT32(rcc_cir        	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb1rstr  	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb2rstr  	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb3rstr   	,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved1  	,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb1rstr   	,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb2rstr  	,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved2 	,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved3  	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb1enr    	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb2enr    	,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb3enr    	,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved4 	,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb1enr   	,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb2enr   	,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved5 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved6 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb1lpenr 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb2lpenr 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_ahb3lpenr 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved7 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb1lpenr 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_apb2lpenr 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved8 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserved9 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_bdcr	   			,STM32F746RccState),
        VMSTATE_UINT32(rcc_csr	   			,STM32F746RccState),
        VMSTATE_UINT32(rcc_reserveda 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_reservedb 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_sscgr 	 		,STM32F746RccState),
        VMSTATE_UINT32(rcc_plli2scfgr		,STM32F746RccState),
        VMSTATE_UINT32(rcc_pllsaicfgr		,STM32F746RccState),
        VMSTATE_UINT32(rcc_dckcfgr1  		,STM32F746RccState),
        VMSTATE_UINT32(rcc_dckcfgr2  		,STM32F746RccState),
        VMSTATE_END_OF_LIST()
    }
};

static Property stm32f746_rcc_properties[] = {
    DEFINE_PROP_UINT64("clock-frequency", struct STM32F746RccState,
                       freq_hz, 1000000000),
    DEFINE_PROP_END_OF_LIST(),
};

static void stm32f746_rcc_init(Object *obj)
{
    STM32F746RccState *s = STM32F746RCC(obj);

    sysbus_init_irq(SYS_BUS_DEVICE(obj), &s->irq);

    memory_region_init_io(&s->iomem, obj, &stm32f746_rcc_ops, s,
                          "stm32f746_rcc", 0x400);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->iomem);
}

static void stm32f746_rcc_realize(DeviceState *dev, Error **errp)
{
    STM32F746RccState *s = STM32F746RCC(dev);
    s->timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, stm32f746_rcc_interrupt, s);
}

static void stm32f746_rcc_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = stm32f746_rcc_reset;
    device_class_set_props(dc, stm32f746_rcc_properties);
    dc->vmsd = &vmstate_stm32f746_rcc;
    dc->realize = stm32f746_rcc_realize;
}

static const TypeInfo stm32f746_rcc_info = {
    .name          = TYPE_STM32F746_RCC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32F746RccState),
    .instance_init = stm32f746_rcc_init,
    .class_init    = stm32f746_rcc_class_init,
};

static void stm32f746_rcc_register_types(void)
{
    type_register_static(&stm32f746_rcc_info);
}

type_init(stm32f746_rcc_register_types)
