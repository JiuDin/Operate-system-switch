
# Firmware of  'operating system switch'
Thanks for stecman, the firmware of hardware are refer from his work "hw-boot-selection".

**(Required)**  On Linux, you'll need `gcc-arm-none-eabi` and `python` installed to build and `openocd` to flash.

**(Required)** You can use follow command to build and flash the firmware,  before you do that, make sure you have a jlink or stlink to connect the device with your computer. 

**(Optional)** You can update the library  named libopencm3, or just use the version in the directory. The details you can reference with stecman's project. And you only need to replace the 'src' directory.

## Building

```
cd  hw-os-selection
# Build the firmware with stm32f103c6t6
 make   
 # Flash with a J-Link programmer connected by SWD
make flash 
# Flash with an ST-Link programmer connected by SWD
make flash PROGRAMMER=stlink

```

## Attention

1. the default  mcu  is  `stm32f103c6t6`,  if you use other stm32f1xx chip,  such as `stm32f103c8t6` ,you can use :  `make DEVICE=stm32f103c8t6`
 2. Until now,  the project only supported the series of stm32f1xx.
3.  The other series of chips are temporarily unable to provide support because the author does not have the relevant hardware, but you can try to replace them with F1 series chips from manufacturers such as `GD32` and `CK32`.