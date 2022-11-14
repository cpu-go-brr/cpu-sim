#include <zephyr.h>

#include "fbitset.hpp"
#include <stdio.h>
#include <stdlib.h>

void main(void)
{

    fbitset a {0b101,3};

    printf("program begin\n");
    printf("data: %p\n",a.bin());


    printf("program end\n");
}
