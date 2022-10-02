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
    // load adresses from stack, set acc
    pc = sr1;                 // set pc
    sr1 = sr2;                // push stack up
    sr2 = sr3;                // push stack up
    sr3 = 0;                  // void last register
    acc = read_rom(pc) & 0xF; // set acc
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
    uint8_t r = read_rom(pc) && 0b1110;
    reg_ctl = (registers[r] >> 4) | (registers[r + 1]); // set register control to bank
    pc++;
}

// Fetch indirect from ROM
void Intel4004::fin()
{
    // load rom content of addr specified in reg 0 and reg 1 to register specified by opcode
    uint8_t r = read_rom(pc) && 0b1110;

    uint8_t ph = (pc & 0xF00) >> 8;
    uint8_t pm = registers[0];
    uint8_t pl = registers[1];

    if ((pc & 0xFF) == 0xFF)
        ph++; // go to next page if at (ph) 1111 1111

    uint16_t rom_addr = ((ph << 8) | (pm << 4) | pl) & 0xFFF; // only 12 bit

    registers[r] = read_rom(rom_addr);
    registers[r + 1] = read_rom((rom_addr + 1) & 0xFFF);
}
// Jump to Subroutine
void Intel4004::jms()
{
    sr3 = sr2;
    sr2 = sr1;
    sr1 = (pc + 1) & 0xFFF;
    pc = (read_rom(pc) << 8) | read_rom(pc + 1) & 0xFFF;
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

void Intel4004::rdm() { return; }
void Intel4004::rd0() { return; }
void Intel4004::rd1() { return; }
void Intel4004::rd2() { return; }
void Intel4004::rd3() { return; }
void Intel4004::rdr() { return; }
void Intel4004::wrm() { return; }
void Intel4004::wr0() { return; }
void Intel4004::wr1() { return; }
void Intel4004::wr2() { return; }
void Intel4004::wr3() { return; }
void Intel4004::wrr() { return; }
void Intel4004::wmp() { return; }
void Intel4004::adm() { return; }
void Intel4004::sbm() { return; }
void Intel4004::clb() { return; }
void Intel4004::clc() { return; }
void Intel4004::cmc() { return; }
void Intel4004::stc() { return; }
void Intel4004::cma() { return; }
void Intel4004::iac() { return; }
void Intel4004::dac() { return; }
void Intel4004::ral() { return; }
void Intel4004::rar() { return; }
void Intel4004::tcc() { return; }
void Intel4004::daa() { return; }
void Intel4004::tcs() { return; }
void Intel4004::kbp() { return; }
void Intel4004::dcl() { return; }