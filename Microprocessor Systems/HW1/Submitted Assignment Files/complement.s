		AREA example, CODE, READONLY
		ENTRY
		ALIGN
__main	FUNCTION
		EXPORT __main
		
		LDR  R1,=number  ; Load the number into register R1
		MVNS R2, R1    ; Negate the value in R1 and store it in R2 , takes 1's complement
		MOVS R2, R2    ; Set R2 to its own value (no effect)

number 	EQU 120

		ENDFUNC
		END
