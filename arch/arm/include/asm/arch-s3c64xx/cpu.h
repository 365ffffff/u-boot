/*
 * (C) Copyright 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * Heungjun Kim <riverful.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#ifndef _S3C64XX_CPU_H
#define _S3C64XX_CPU_H

#include <asm/arch/s3c6410.h>

#define S3C64XX_CPU_NAME	"S3C64xx"

#define S3C64XX_MMC_BASE	(0x7c200000)
#define S3C64XX_PRO_ID		(0x7e00e000)
#define S3C64XX_SYS_BASE	(0x7e00f000)
#define S3C64XX_ONENAND_BASE	(0x70100000)
#define S3C64XX_KEYPAD_BASE	(0x7e00a000)
#define S3C64XX_FIMD_BASE	(0x77100000)
#define S3C64XX_WATCHDOG_BASE	(0x7e004000)
#define S3C64XX_UART_BASE	(0x7f005000)
#define S3C64XX_TIMER_BASE	(0x7f006000)
#define S3C64XX_GPIO_BASE	(0x7f008000)

#ifndef __ASSEMBLY__
extern unsigned int samsung_cpu_id;

static inline void samsung_set_cpu_id(void)
{
	int id;

	/* Look at S3C6410-like ID register first */
	id = SYS_ID_REG;
	if (!id) {
		/* Fall back to S3C6400-like ID register */
		INF_REG7_REG = 0;
		id = INF_REG7_REG;
	}

	/* The ID looks like: x64YYxxx, where 64YY is SoC model */
	id >>= 12;
	samsung_cpu_id = id & 0xffff;
}

static inline char *samsung_get_cpu_name(void)
{
	return S3C64XX_CPU_NAME;
}

#define SAMSUNG_BASE(device, base)				\
static inline unsigned int __attribute__((no_instrument_function)) \
	samsung_get_base_##device(void) \
{								\
	return S3C64XX_##base;					\
}

SAMSUNG_BASE(sys, SYS_BASE)
SAMSUNG_BASE(gpio, GPIO_BASE)
SAMSUNG_BASE(pro_id, PRO_ID)
SAMSUNG_BASE(mmc, MMC_BASE)
SAMSUNG_BASE(sromc, SROM_BASE)
SAMSUNG_BASE(timer, TIMER_BASE)
SAMSUNG_BASE(uart, UART_BASE)
SAMSUNG_BASE(watchdog, WATCHDOG_BASE)
SAMSUNG_BASE(onenand, ONENAND_BASE)
SAMSUNG_BASE(keypad, KEYPAD_BASE)
SAMSUNG_BASE(fimd, FIMD_BASE)
#endif

#endif	/* _S3C64XX_CPU_H */
