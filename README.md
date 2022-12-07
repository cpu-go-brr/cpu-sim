# CPU Simulation

## Ideen
- 

## Vorgehen
- [x] Intel 4004 bauen
  - [x] Parsing von assembler-Datei und Konvertierung in object code (hex)
  - [x] Instructions als Funktionen in `include/instructions.hpp` umsetzten
    - Eine Instruction/Funktion verändert nur Werte in den privaten Variablen in `include/intel4004.hpp`
  - [x] RAM integrieren
  - [x] komplexes Programm laufen lassen/entwickeln (Pong)
  - [x] Server bauen
  - [x] Website um Zustand der CPU zu setzten bauen / erstmal recherche
- [x] Generator bauen
  - Instruction Set erweitern (Intel 8008, AMD64 evtl. Config-only
    - 6502
    - [x] Brainfuck


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
