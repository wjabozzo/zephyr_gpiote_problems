/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>

static const struct device *const missing_device = \
	DEVICE_DT_GET(DT_ALIAS(gpiote));

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);
	printk("Gpiote is ready: %d\n", device_is_ready(missing_device));
}
