BP=5  ; PAIR BALL_POS
BPY=10   ; SINGLE REGISTER
BPX=11   ; SINGLE REGISTER
BV=6  ; PAIR BALL_VELOCITY
BVX=12   ; SINGLE REGISTER
BVY=13   ; SINGLE REGISTER
BC=7  ; PAIR BALL_COUNTER
BCX=14  ; SINGLE REGISTER
BCY=15  ; SINGLE REGISTER

START   ; Entrypoint
        JMS RESET ; RESET REGISTERS
LOOP_1
        JMS MOVE  ; MOVE BALL
        JUN LOOP_1
        JUN DONE

RESET   ; Reset Variables
        FIM BP, $37 ; RESET BALL_POS      
        FIM BV, $12 ; RESET BALL_VEL
        FIM BC, $00 ; RESET BALL_VEL
        BBL 0       ; RETURN 0

DONE    JUN DONE    ; ENDLESS LOOP


MOVE
            ; STORE PREV POS
        LD BPY
        XCH R0
        LD BPX
        XCH R1

        ; CALC NEW VEL
            ; DID I BOUNCE RIGHT?
        LD BPX
        CMA
        JCN %1100  BRE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BVX
        XCH BVX

BRE

        ; DID I BOUNCE LEFT?
        LD BPX
        JCN %1100  BLE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BVX
        XCH BVX

BLE
        ; DID I BOUNCE TOP
        LD BPY
        JCN %1100  BTE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BVY
        XCH BVY

BTE
        ; DID I BOUNCE BOT

        LDM 8
        XCH R2

        LD BPY
        SUB R2
        
        CMA
        JCN %1100  BBE ; LEAVE if no bounce
        LDM 0
        CLC
        SUB BVY
        XCH BVY
BBE

        ; CALC NEW POSITION
            ; X
        LD BPX ; LOAD CURRENT POS_X
        CLC
        ADD BVX; ADD VEL_X
        XCH BPX; Store back

            ; Y
        LD BPY ; LOAD CURRENT POS_Y
        CLC
        ADD BVY; ADD VEL_Y
        XCH BPY; Store back



            ; CLEAR prev POS
        SRC P0 ; SRC BALL POS
        LDM $0
        WRM  ; WRITE 0 TO BALL POS
            ; DRAW BALL
        SRC P6
        LDM $1 
        WRM ; Write Current Pos
        BBL 0