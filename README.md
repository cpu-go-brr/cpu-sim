# CPU Simulation

## Ideen
- 

## Vorgehen
- Intel 4004 bauen
  - Parsing von assembler-Datei und Konvertireung in object code (hex)
  - Instructions als Functionen in `include/instructions.hpp` unsetzten
    - Eine Instruction/Function verändert nur Werte in den privaten Variablen in `include/intel4004.hpp`
  


## Installation
```bash
git clone https://github.com/cpu-go-brr/cpu-sim.git
mkdir build && cd build
cmake ..
make
```
## Usage
```bash
./build/simulator
```