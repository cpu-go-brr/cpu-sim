#include <zephyr.h>
 #include <vector>
uint32_t led = (1u << 27); 

void main(void)
{

    std::vector<int> a{1,1,1};
    for(const auto& i: a)
            printk("%d\n", i);

    REG_PIOB_OER = led; 

    printk("Hello World, %s\n", CONFIG_BOARD);

    while(true)
    {
        REG_PIOB_SODR = led; // Set Output Data Register, turns LED on 
        k_sleep({10000});         // wait for a second    
        REG_PIOB_CODR = led; // Clear Output Data Register, turns LED off 
        k_sleep({10000});         // wait for a second    
    }
}
