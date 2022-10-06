#include "../include/intel4004.hpp"

// No Operation
void Intel4004::nop()
{
    pc++;
}

// Jump Uncoditional
void Intel4004::jun()
{
    // set pc to last 12b
    pc = ((read_rom(pc) & 0xF) << 8) + read_rom(pc + 1);
}

// Load Immediate
void Intel4004::ldm()
{
    // Loads byte into acc
    acc = read_rom(pc) & 0xF;
    pc++;
}

// Load
void Intel4004::ld()
{
    // Load data from register to acc
    uint8_t r = read_rom(pc) & 0xF;
    acc = registers[r];
    pc++;
}

// Exchange
void Intel4004::xch()
{
    // swap accumulator and register
    uint8_t r = read_rom(pc) & 0xF;
    uint8_t acbr = acc; // buffer
    acc = registers[r];
    registers[r] = acbr;
    pc++;
}
// Add
void Intel4004::add()
{
    // add register with carry to acc
    uint8_t r = read_rom(pc) & 0xF;
    uint8_t addition = acc + registers[r] + carry;
    acc = addition & 0xF;
    carry = (addition & (1 << 4)) > 0;
    pc++;
}

// Subtract
void Intel4004::sub()
{
    // add complement of register to acc
    uint8_t r = read_rom(pc) & 0xF;
    uint8_t subtraction = acc + (~registers[r] & 0xF) + carry;
    acc = subtraction & 0xF;
    carry = (subtraction & (0x10)) > 0;
    pc++;
}

// Fetch Immediate
void Intel4004::fim()
{
    // Fill a double bank with constant
    uint8_t r = read_rom(pc) & 0b1110;
    registers[r] = (read_rom(pc + 1) & 0xF0) >> 4; // set first 4 bit to lower bank
    registers[r + 1] = read_rom(pc + 1) & 0xF;     // set last 4 bit to higher bank
    pc += 2;
}

// Increment
void Intel4004::inc()
{
    // increment register by one
    uint8_t r = read_rom(pc) & 0xF;
    registers[r] = (registers[r] + 1) & 0xF;
    pc++;
}

// Branch Back and Load
void Intel4004::bbl()
{
    acc = read_rom(pc) & 0xF; // set acc

    pc = sr[sr_index];
    sr_index = (sr_index-1 +3) % 3;
}

// Jump Indirect
void Intel4004::jin()
{
    uint8_t r = read_rom(pc) & 0b1110;
    uint8_t ph = (pc & 0xF00) >> 8;
    uint8_t pm = registers[r];
    uint8_t pl = registers[r + 1];

    if ((pc & 0xFF) == 0xFF)
        ph++; // go to next page if at (ph) 1111 1111

    pc = ((ph << 8) | (pm << 4) | pl) & 0xFFF; // only 12 bit
}
// Send register control
void Intel4004::src()
{
    uint8_t r = read_rom(pc) & 0b1110;
    reg_ctl = (registers[r] >> 4) | (registers[r + 1]); // set register control to bank
    pc++;
}

// Fetch indirect from ROM
void Intel4004::fin()
{
    // load rom content of addr specified in reg 0 and reg 1 to register specified by opcode
    uint8_t r = read_rom(pc) & 0b1110;

    uint8_t ph = (pc & 0xF00) >> 8;
    uint8_t pm = registers[0];
    uint8_t pl = registers[1];

    if ((pc & 0xFF) == 0xFF)
        ph++; // go to next page if at (ph) 1111 1111

    uint16_t rom_addr = ((ph << 8) | (pm << 4) | pl) & 0xFFF; // only 12 bit

    uint8_t first_rom_content = read_rom(rom_addr); 
    registers[r] = first_rom_content & 0xF;
    registers[r+1] = (first_rom_content & 0xF0) >> 4;
    
    pc++;
}
// Jump to Subroutine
void Intel4004::jms()
{
    sr[sr_index] = (pc + 1) & 0xFFF;
    sr_index = (sr_index+1) % 3;
    pc = ((read_rom(pc) << 8) | read_rom(pc + 1)) & 0xFFF;
}

// Jump Conditional
void Intel4004::jcn()
{
    u_int8_t conditions = read_rom(pc) & 0b1111;   // last four bits
    bool condition_invert = conditions & 0b1000;   // first bit = 1 -> invert jump condition
    bool condition_acc_zero = conditions & 0b100;  // jump if acc is zero
    bool condition_carry_zero = conditions & 0b10; // jump if carry is 1
    bool condition_test_pin = conditions & 0b1;    // jump if testpin is 0

    bool jump = (condition_acc_zero && acc == 0) ||
                (condition_carry_zero && carry == 1) ||
                (condition_test_pin && testpin == 0);

    if (condition_invert)
        jump = !jump;

    if (!jump)
    {
        pc += 2;
        return;
    }

    // condition is true -> jump

    uint8_t ph = (pc & 0xF00) >> 8;
    if ((pc & 0xFF) >= 0xFE)
        ph++; // go to next page if at (ph) 1111 1110 or (ph) 1111 1111

    pc = ((ph << 8) | read_rom(pc + 1)) & 0xFFF; // jump to adress given in opcode
}
// Increment and Skip
void Intel4004::isz()
{
    // Increment index register skip jump if zero
    uint8_t r = read_rom(pc) & 0xF;
    registers[r] = (registers[r] +1) & 0xF;

    if(registers[r] == 0)
    {
        pc+=2;
        return;
    }

    uint8_t ph = (pc & 0xF00) >> 8;
    if ((pc & 0xFF) >= 0xFE)
        ph++; // go to next page if at (ph) 1111 1110 or (ph) 1111 1111

    pc = ((ph << 8) | read_rom(pc + 1)) & 0xFFF; // jump to adress given in opcode

}

// Read RAM character
void Intel4004::rdm() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    uint8_t addr = (reg_ctl & 0b00001111);
    acc = ram[chip].mem[bank][addr];
    pc++;
}

// Read RAM status character 0
void Intel4004::rd0() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    acc = ram[chip].status[bank][0];
    pc++;
}

// Read RAM status character 1
void Intel4004::rd1() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    acc = ram[chip].status[bank][1];
    pc++;
}

// Read RAM status character 2
void Intel4004::rd2() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    acc = ram[chip].status[bank][2];
    pc++;
}

// Read RAM status character 3
void Intel4004::rd3() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    acc = ram[chip].status[bank][3];
    pc++;
}

//void ROM port
void Intel4004::rdr() 
{
    uint8_t chip = (reg_ctl & 0xF0) >> 4;
    acc = rom[chip].out;

    pc++;
}

// Write accumulator into RAM character
void Intel4004::wrm() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    uint8_t addr = (reg_ctl & 0b00001111);
    ram[chip].mem[bank][addr] = acc & 0xF;
    pc++;

}

// Write accumulator into RAM status character 0
void Intel4004::wr0() 
{ 
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    ram[chip].status[bank][0] = acc & 0xF;
    pc++;
}

// Write accumulator into RAM status character 1
void Intel4004::wr1() 
{ 
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    ram[chip].status[bank][1] = acc & 0xF;
    pc++;
}

// Write accumulator into RAM status character 2
void Intel4004::wr2() 
{ 
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    ram[chip].status[bank][2] = acc & 0xF;
    pc++;
}

// Write accumulator into RAM status character 3
void Intel4004::wr3() 
{ 
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    ram[chip].status[bank][3] = acc & 0xF;
    pc++;
}

// Write ROM port
void Intel4004::wrr() 
{ 
    uint8_t chip = (reg_ctl & 0xF0) >> 4;
    rom[chip].out = acc;

    pc++;
}

// Write RAM port
void Intel4004::wmp() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    ram[chip].out = acc;

    pc++;
}

// Add index register to accumulator with carry
void Intel4004::adm() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    uint8_t addr = (reg_ctl & 0b00001111);
    uint8_t val  = ram[chip].mem[bank][addr];
    uint8_t addition = acc + val + carry;
    acc = addition & 0xF;
    carry = (addition & (1 << 4)) > 0;
    pc++;
}

// Subtract from memory with borrow
void Intel4004::sbm() 
{
    uint8_t chip = (reg_ctl & 0b11000000) >> 6;
    uint8_t bank = (reg_ctl & 0b00110000) >> 4;
    uint8_t addr = (reg_ctl & 0b00001111);
    uint8_t val  = ram[chip].mem[bank][addr];
    uint8_t subtraction = acc + ~val + ~((uint8_t)carry);
    acc = subtraction & 0xF;
    carry = (subtraction & (1 << 4)) > 0;
    pc++; 
}

// Clear both
void Intel4004::clb() 
{
    acc = 0;
    carry = 0;

    pc++;
}

// Clear Carry
void Intel4004::clc() 
{
    carry = 0;

    pc++;
}

// Complement carry
void Intel4004::cmc() 
{ 
    carry = !carry;
    pc++;
}

// Set Carry
void Intel4004::stc() 
{
    carry = 1;
    pc++;
}

// Complement Accumulator
void Intel4004::cma() 
{
    acc = ~acc;
    pc++;
}

// Increment Accumulator
void Intel4004::iac() 
{
    uint8_t sum = acc + 1;
    acc = sum & 0xF;
    carry = (sum & 0x10) > 0; 

    pc++;
}

// Decrement Accumulator
void Intel4004::dac() 
{
    uint8_t sum = acc + 0xF;
    acc = sum & 0xF;
    carry = (sum & 0x10) == 0; 

    pc++;
}

// Rotate left
void Intel4004::ral() 
{
    bool oldcarry = carry;
    carry = (acc & 0x1000) == 1;
    acc = ((acc  << 1) | oldcarry) & 0xF;

    pc++;
}

// Rotate right
void Intel4004::rar() 
{
    bool oldcarry = carry;
    carry = (acc & 0x1) == 1;
    acc = ((oldcarry * 0x1F) | acc) >> 1;

    pc++;
}

// Transmit carry and clear
void Intel4004::tcc() 
{
    acc = carry;
    carry = 0;

    pc++;
}

// Decimal adjust accumulator
void Intel4004::daa() 
{
    bool increment = carry || acc > 9;

    pc++;
    if(!increment) return;
    uint8_t sum = acc + 6;

    acc = sum & 0xF;
    carry = (sum & 0x10) > 0;
}

// Transfer carry subtract
void Intel4004::tcs() 
{
    acc = carry?10:9;
    carry = 0;
    pc++;
}

// Keyboard process
void Intel4004::kbp() 
{ 
    pc++;
    if(acc == 0 || acc == 1 || acc == 2 || acc == 4 || acc == 8) return;
    acc = 0xF;
}
void Intel4004::dcl() 
{
    reg_ctl = reg_ctl & 0b00111111 | (acc & 0b11) << 6;
    pc++;
}