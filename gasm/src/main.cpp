#include <iostream>
#include <iomanip>
#include "gasm.hpp"
#include "argument_parser.hpp"
#include <fstream>
#include <filesystem>

int main(int argc, char **argv)
{
    ArgumentParser parser(argc, argv);

    GenericAssembler gasm = GenericAssembler();

    std::string code_file = parser.getCode();
    std::string cpu_file = parser.getCPU();
    std::string out_file = parser.getOut();
    std::string format_param = parser.getFormat();

    std::string s = R"(
; four bit "AND" routine on the Intel 4004
;
START	FIM 4P, 0	    ; LOAD ROM PORT 0 ADDRESS
	SRC 4P	        	; SEND ROM PORT ADDRESS
	RDR		            ; READ INPUT A
	XCH 0		        ; A TO REGISTER 0
	INC 8	        	; LOAD ROM PORT 1 ADDRESS
	SRC 4P	        	; SEND ROM PORT ADDRESS
	RDR		            ; READ INPUT B
	XCH 1		        ; B TO REGISTER 1
	JMS AND		        ; EXECUTE "AND"
	XCH 2		        ; LOAD RESULT C
	WMP		            ; STORE AT MEMORY PORT 0
	JUN START	        ; RESTART
	NOP
*=104
;			"AND" SUBROUTINE
AND	CLB	            	; CLEAR ACCUMULATOR AND CARRY
	XCH 2	        	; CLEAR REGISTER 2
	LDM 4		        ; LOAD LOOP COUNT (LC)
AND_3	XCH 0		    ; LOAD A, LC TO REGISTER 0
	RAR	            	; ROTATE LEAST SIGNIFICANT BIT TO CARRY
	XCH 0	        	; RETURN ROTATED A TO REG 0, LC TO ACC
	JCN CZ, ROTR1	    ; JUMP TO ROTR1 IF CARRY ZERO
	XCH 1	        	; LOAD B, LC TO ACCUMULATOR
	RAR                 ; ROTATE LEAST SIGNIFICANT BIT TO CARRY
	XCH 1	        	; RETURN ROTATED B TO REG 1, LC TO ACC
ROTR2	XCH 2           ; LOAD PARTIAL RESULT C, LC TO REG 2
	RAR                 ; ROTATE CARRY INTO PARTIAL RESULT MSB
	XCH 2	        	; LOAD LC, RETURN C TO REGISTER 2
	DAC		            ; DECREMENT THE ACCUMULATOR (LC)
	JCN ANZ, AND_3  	; LOOP IF LC NON ZERO
	BBL 0               ; RETURN
ROTR1	XCH 1           ; LOAD B, LC TO REGISTER 1
	RAR                 ; ROTATE B
	XCH 1	           	; RETURN ROTATED B TO REG 1, LC TO ACC
	CLC                 ; CLEAR CARRY
	JUN ROTR2	        ; RETURN TO LOOP
CZ=10
ANZ=12
$
)";

    // Load yaml and assemble string separately
    gasm.load_yaml(cpu_file);
    std::vector<int> assembled_code = gasm.assemble_string(s);

    // Load yaml and assemble file together
    // std::vector<int> assembled_code = gasm.assemble_file(code_file, cpu_file);

    // Load yaml and assemble string together
    // std::vector<int> assembled_code = gasm.assemble_string(s, cpu_file);

    std::filesystem::create_directories(std::filesystem::path(out_file).parent_path());
    std::ofstream out(out_file);

    for (size_t i = 0; i < assembled_code.size(); i++)
    {
        if (format_param == "bin")
            out << (char)assembled_code[i];
        if (format_param == "c")
        {
            out << "0x";
            out << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i];
            if (i != assembled_code.size() - 1)
                out << ",";
        }
        if (format_param == "hex")
            out << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i] << " ";
    }

    if (format_param != "bin")
        out << "\n";

    out.close();
    return 0;
}
