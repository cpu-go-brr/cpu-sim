#include <zephyr.h>
uint32_t led = (1u << 27);

void main(void)
{

    REG_PIOB_OER = led;

    printk("Hello there, %s\n", CONFIG_BOARD);

    while (true)
    {
        REG_PIOB_SODR = led; // Set Output Data Register, turns LED on
        k_sleep({10000});    // wait for a second
        printk("ON\n");
        REG_PIOB_CODR = led; // Clear Output Data Register, turns LED off
        k_sleep({10000});    // wait for a second
        printk("OFF\n");
    }
}
