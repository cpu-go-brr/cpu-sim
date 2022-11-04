# CPU Simulation

## Ideen
- 

## Vorgehen
- [x] Intel 4004 bauen
  - [/] Parsing von assembler-Datei und Konvertierung in object code (hex)
  - [x] Instructions als Funktionen in `include/instructions.hpp` umsetzten
    - Eine Instruction/Funktion verändert nur Werte in den privaten Variablen in `include/intel4004.hpp`
  - [x] RAM integrieren
  - [/] komplexes Programm laufen lassen/entwickeln (Pong)
  - [x] Server bauen
  - [ ] Website um Zustand der CPU zu setzten bauen / erstmal recherche
- [/] Generator bauen
  - Instruction Set erweitern (Intel 8008, AMD64 evtl. Config-only
    - 6502
    - Brainfuck


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
