;INIT - LOAD VALUE
lda_immediate 3

LOOP; CYCLE
clc_implied
ror_accumulator
bcc_relative EVEN
rol_accumulator
sta_absolute $0800
rol_accumulator
adc_absolute $0800
adc_absolute 1

EVEN
inx_implied

cmp_immediate 1
beq_relative DONE
jmp_absolute LOOP

DONE
jmp_absolute DONE