START   FIM 4P, 0
        SRC 4P
        RDR
        XCH 0
        INC 8
        SRC 4P
        RDR
        XCH 1
        JMS AND
        XCH 2
        WMP
        JUN START
        NOP
*=104

AND     CLB
        XCH 2
        LDM 4
AND_3   XCH 0
        RAR
        XCH 0
        JCN CZ, ROTR1
        XCH 1
        RAR
        XCH 1
ROTR2   XCH 2
        RAR
        XCH 2
        DAC
        JCN ANZ, AND_3
        BBL 0
ROTR1   XCH 1
        RAR
        XCH 1
        CLC
        JUN ROTR2
CZ=10
ANZ=12
cZ = 23
pC = *

$