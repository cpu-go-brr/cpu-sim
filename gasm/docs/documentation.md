# Documentation for gasm (General Assembler)

## TODO
- [ ] set PC to address
- [x] different number systems
  - [x] $ff
  - [x] %11011
- [ ] arguments to op-codes
  - [ ] comma and/or space separated
  - [ ] use of variables and labels
  - [ ] descriptive letters on the end of the given number
    - [ ] 12R
    - [ ] $ffP
    - [ ] %1001B
  - [ ] arguments are "cut off" after the max size is exceeded
    - bsp: argument has length of 4 bits and given argument is 24
    - last 4 bits of 24 => 11000 & b1111 = 1000 => argument is 8
- [ ] code comments (;)
- [ ] pragmas
  - [ ] .END
  - [ ] .BYTE
- [ ] Setting values in the config yaml

## Table of contents

- [Labels and Identifiers](#labels-and-identifiers)
  - [Labels](#labels)
  - [Identifiers](#identifiers)
    - [Supported number systems](#supported-number-systems)

## Labels and Identifiers

Just as in any other assembly language you can make use of labels and identifiers in your asm-code. Labels and identifiers have to follow a certain regular expression (regex). <br>
The regex for the names is `[A-Za-z][A-Za-z0-9_]*`.

### Labels

Labels are used to store the address of the following OP-code.

Examples:
```
LABEL1  OP1
        OP2
LABEL2  
        OP3
        OP4
```
In this example the value of LABEL1 will be the address of OP1 (0). LABEL2 will have the value 3 (if OP1 and OP2 are instructions with 1 byte in length each)

### Identifiers

Identifiers are similar to constant variables in many programming languages. They can be initialized with a certain value and the value cant change. There is on exception though:<br>
Identifiers can be re-assigned when parsing the asm-code. <br>
<br>
Example:

```
VAR1 = 12
JUMP VAR1
VAR1 = 4
```

In this example VAR1 has the value 4. The last value assignment to an identifier is the one that will be used for **the entire program**. This means that the JUMP instruction will have the value 4 as argument and not 12.

#### Supported number systems

You can assign values to identifiers in three number systems: decimal, hexadecimal and binary. The use of these number systems is pretty straight forward: <br>

- Decimal: `[0-9]`
- Hexadecimal: `$[0-9A-Fa-f]`
- Binary: `%[10]`

## Arguments for instructions

to be useful some instructions have to accept arguments 

