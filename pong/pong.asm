PEDAL_POS=5
PEDAL_POS_L=10
PEDAL_POS_R=11  
BALL_POS=6  ; PAIR BALL_POS
BALL_POS_Y=12   ; SINGLE REGISTER
BALL_POS_X=13   ; SINGLE REGISTER
BALL_VEL=7  ; PAIR BALL_VELOCITY
BALL_VEL_X=14   ; SINGLE REGISTER
BALL_VEL_Y=15   ; SINGLE REGISTER

START   ; Entrypoint
        JMS RESET ; RESET REGISTERS
LOOP_1
        ;JMS MOVE  ; MOVE BALL
        JMS PEDAL_L ; MOVE PEDAL LEFT
        JUN LOOP_1
        JUN DONE

RESET   ; Reset Variables
        FIM BALL_POS, $37 ; RESET BALL_POS      
        FIM BALL_VEL, $11 ; RESET BALL_VEL
        FIM PEDAL_POS, $33 ; RESET BALL_VEL
        FIM 0, $00 ; RESET FIRST REGISTER
        CLB

        ;DRAW BALL
        SRC BALL_POS
        LDM 1
        WRM

        ;DRAW PEDALS
        ;DRAW LEFT_PEDAL
        LD PEDAL_POS_L
        XCH 0
        SRC 0
        LDM 2
        WRM

        ;DRAW RIGHT_PEDAL
        ;LD PEDAL_POS_R
        ;XCH 0
        ;LDM 15
        ;XCH 1
        ;SRC 0
        ;LDM 2
        ;WRM

        FIM 0, $00 ; RESET FIRST REGISTER

        BBL 0       ; RETURN 0

DONE    JUN DONE    ; ENDLESS LOOP


PEDAL_L
        RDR ;READ INPUT
        ;NOW LETS TEST IF UP IS PRESSED
        RAL
        JCN %1010 NO_LEFT_PEDAL_UP
        CLC
        ;WE ARE PRESSING UP
        ;ARE WE ALREADY AT TOP?
        LD PEDAL_POS_L
        JCN %0100 NO_LEFT_PEDAL_UP
        ;WE ARE NOT AT TOP 
        ; REMOVE OLD PEDAL
        XCH 0
        LDM 0
        XCH 1
        SRC 0
        LDM 0
        WRM
        ; WRITE NEW PEDAL
        LD PEDAL_POS_L
        DAC
        XCH PEDAL_POS_L
        LD PEDAL_POS_L
        XCH 0
        SRC 0
        LDM 2
        WRM
        BBL0
NO_LEFT_PEDAL_UP

        ;ARE WE DOWN?
        RAL
        JCN %1010 NO_LEFT_PEDAL_DOWN
        CLC
        ;YES WE ARE DOWN
        ;ARE WE ALREADY COMPLETELY DOWN?
        LDM 7
        SUB PEDAL_POS_L
        JCN %0100 NO_LEFT_PEDAL_DOWN
        ; REMOVE OLD PEDAL
        LD PEDAL_POS_L
        XCH 0
        LDM 0
        XCH 1
        SRC 0
        LDM 0
        WRM
        ; WRITE NEW PEDAL
        INC PEDAL_POS_L
        LD PEDAL_POS_L
        XCH 0
        SRC 0
        LDM 2
        WRM
NO_LEFT_PEDAL_DOWN
        BBL 0

MOVE
            ; STORE PREV POS
        LD BALL_POS_Y
        XCH 0
        LD BALL_POS_X
        XCH 1

        ; CALC NEW VEL
            ; DID I BOUNCE RIGHT?
        LD BALL_POS_X
        IAC
        CMA
        JCN %1100  BRE ; LEAVE if no bounce

        ;We have to check if there is a pedal
        LDM 0
        CLC
        SUB BALL_VEL_X
        XCH BALL_VEL_X

BRE
        ; DID I BOUNCE LEFT?
        LD BALL_POS_X
        DAC
        JCN %1100  BLE ; LEAVE if no bounce
        ;We have to check if there is a pedal
        LDM 0
        CLC
        SUB BALL_VEL_X
        XCH BALL_VEL_X

BLE
        ; DID I BOUNCE TOP
        LD BALL_POS_Y
        JCN %1100  BTE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BALL_VEL_Y
        XCH BALL_VEL_Y

BTE
        ; DID I BOUNCE BOT

        LDM 7
        CLC
        SUB BALL_POS_Y
        JCN %1100  BBE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BALL_VEL_Y
        XCH BALL_VEL_Y
BBE

        ; CALC NEW POSITION
            ; X
        LD BALL_POS_X ; LOAD CURRENT POS_X
        CLC
        ADD BALL_VEL_X; ADD VEL_X
        XCH BALL_POS_X; Store back

            ; Y
        LD BALL_POS_Y ; LOAD CURRENT POS_Y
        CLC
        ADD BALL_VEL_Y; ADD VEL_Y
        XCH BALL_POS_Y; Store back



            ; CLEAR prev POS
        SRC 0 ; SRC BALL POS
        LDM $0
        WRM  ; WRITE 0 TO BALL POS
            ; DRAW BALL
        SRC 6
        LDM $1 
        WRM ; Write Current Pos
        BBL 0