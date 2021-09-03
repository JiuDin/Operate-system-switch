#include "clock.h"
#include "usb.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
 #include <libopencm3/cm3/scb.h>

#define STM32F1 1


static usbd_device* init_usb(void)
{  
    return usb_device_init(&st_usbfs_v1_usb_driver);
}

static void init_gpio(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    int i=0,j=0;
  
     gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO6);
     gpio_set(GPIOA, GPIO6); // Enable internal pull-up
     //Pull down the D+ pin level to make PC re-enumerate usb device.
     gpio_set_mode(GPIOA,  0x1, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12); 
     gpio_clear(GPIOA, GPIO12); // Enable internal pull-up
     for (i = 0; i < 800000; i++)	/* Wait a bit. */
	for (j = 0; j < 10; j++)
	  __asm__("nop");


}

// (Called from usb.c)
char read_switch_value(void)
{
    return gpio_get(GPIOA, GPIO6) ? '1' : '0';
}

usbd_device* usbd_dev;

static void switch_rst(void)
{
     static int sw_state_last;
     static  int first_sw_state=0;
     int sw_state;
     if(first_sw_state==0)
     {
        sw_state=gpio_get(GPIOA, GPIO6);
        sw_state_last=sw_state;
         first_sw_state=1;
     }
     sw_state=gpio_get(GPIOA, GPIO6);
    if(sw_state_last==sw_state)
    {

    }
    else
    {
       scb_reset_system();
    }
    sw_state_last=sw_state;

}


int main(void)
{
    init_clocks();
    init_gpio();

    usbd_dev = init_usb();

    while (1) {
        // Keep the USB device hardware fed
        // This can be done with interrupts, but the implementation differs
        // across devices so we're keeping this simple here.
        usbd_poll(usbd_dev);
        //When the switch is changed,reset the entire system and 
        //make sure the PC re-enumerate the usb device.
        switch_rst();
    }
}
