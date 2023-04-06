GPIOTE linking problem
===

Problem
---

This project does not link, the device for gpiote is never mapped to the linker.
```
c:/ncs/toolchains/v2.3.0/opt/zephyr-sdk/arm-zephyr-eabi/bin/../lib/gcc/arm-zephyr-eabi/12.1.0/../../../../arm-zephyr-eabi/bin/ld.exe: app/libapp.a(main.c.obj): in function `main':
D:\wjabozzo\onedrive_wolke\proyectos\tests\gpiote\src\main.c:16: undefined reference to `__device_dts_ord_27'
collect2.exe: error: ld returned 1 exit status
```

Looking at the linker map, there is no mapping to the device.
```
$ grep __device_dts build/zephyr/zephyr_pre0.map
                0x0000000000004a58                __device_dts_ord_15
                0x0000000000004a70                __device_dts_ord_25
```

Setup
---

This project was created using visual studio code nfr connect "Create a new application" option with nfr 2.3.0 SDK and based on the 'hello_world' example. The board folder was generated using the "Create a new board" option for the nfr52840 chip.

The devicetree was modified to use gpiote:

```dts
/ {
	model = "gpiote_test";
	compatible = "gpiote-test";

    ...

	aliases {
		gpiote = &gpiote;
	};


};

&gpio0 {
	status = "okay";
};

&gpiote {
	status = "okay";
};

&flash0 {
...
```

The following Kconfig variables were set in proj.conf to activate gpiote:

```Kconfig
CONFIG_GPIO=y
CONFIG_GPIO_NRFX=y
CONFIG_NRFX_GPIOTE=y
```

And main.c the gpiote device is fetched and used once:

```c
#include <zephyr/kernel.h>
#include <zephyr/device.h>

static const struct device *const missing_device = \
	DEVICE_DT_GET(DT_ALIAS(gpiote));

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);
	printk("Gpiote is ready: %d\n", device_is_ready(missing_device));
}
```
