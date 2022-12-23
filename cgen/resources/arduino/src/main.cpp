#include <Arduino.h>
#include "${CPU_NAME}.hpp"
void setup()
{
// put your setup code here, to run once:
Serial.begin(9600);
while(!Serial.available());
}

${CPU_NAME} cpu{};
void loop()
{
bitset prog[] = {0x00}; 
cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));
cpu.simulate();
cpu.display();
    
exit(0);

}
