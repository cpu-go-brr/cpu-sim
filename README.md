# CPU Simulation

## Ideen
- 

## Vorgehen
- Intel 4004 bauen
  - Parsing von assembler-Datei und Konvertierung in object code (hex)
  - Instructions als Funktionen in `include/instructions.hpp` umsetzten
    - Eine Instruction/Funktion verändert nur Werte in den privaten Variablen in `include/intel4004.hpp`
  - RAM integrieren
  - komplexes Programm laufen lassen/entwickeln (Pong)
  - Server bauen
  - Website um Zustand der CPU zu setzten bauen / erstmal recherche
  - Instruction Set erweitern (Intel 8008, AMD64 evtl. Config-only)
  


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
