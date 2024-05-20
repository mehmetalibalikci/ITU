; Because we can use only 8 registers, I have to use many push and pop operations at many places to save original values of registers and load again.
; I tried to explain all of the code so that it will be understandable. I hope it is so.
; Mehmet Ali Balikçi
; 150200059

ARRAY_SIZE					EQU		100		; Size definition: each element 4 byte, total 400 byte

; Load the array in txt file
							AREA const_data, CODE, READONLY
array_start 				DCD 0xa603e9e1, 0xb38cf45a, 0xf5010841, 0x32477961, 0x10bc09c5, 0x5543db2b, 0xd09b0bf1, 0x2eef070e, 0xe8e0e237, 0xd6ad2467
							DCD 0xc65a478b, 0xbd7bbc07, 0xa853c4bb, 0xfe21ee08, 0xa48b2364, 0x40c09b9f, 0xa67aff4e, 0x86342d4a, 0xee64e1dc, 0x87cdcdcc
							DCD 0x2b911058, 0xb5214bbc, 0xff4ecdd7, 0x3da3f26,  0xc79b2267, 0x6a72a73a, 0xd0d8533d, 0x5a4af4a6, 0x5c661e05, 0xc80c1ae8
							DCD 0x2d7e4d5a, 0x84367925, 0x84712f8b, 0x2b823605, 0x17691e64, 0xea49cba,  0x1d4386fb, 0xb085bec8, 0x4cc0f704 ,0x76a4eca9
							DCD 0x83625326, 0x95fa4598, 0xe82d995e, 0xc5fb78cb, 0xaf63720d, 0xeb827b5,  0xcc11686d, 0x18db54ac, 0x8fe9488c, 0xe35cf1
							DCD 0xd80ec07d, 0xbdfcce51, 0x9ef8ef5c, 0x3a1382b2, 0xe1480a2a, 0xfe3aae2b, 0x2ef7727c, 0xda0121e1, 0x4b610a78, 0xd30f49c5
							DCD 0x1a3c2c63, 0x984990bc, 0xdb17118a, 0x7dae238f, 0x77aa1c96, 0xb7247800, 0xb117475f, 0xe6b2e711, 0x1fffc297, 0x144b449f
							DCD 0x6f08b591, 0x4e614a80, 0x204dd082, 0x163a93e0, 0xeb8b565a, 0x5326831,  0xf0f94119, 0xeb6e5842, 0xd9c3b040, 0x9a14c068
							DCD 0x38ccce54, 0x33e24bae, 0xc424c12b, 0x5d9b21ad, 0x355fb674, 0xb224f668, 0x296b3f6b, 0x59805a5f, 0x8568723b, 0xb9f49f9d
							DCD 0xf6831262, 0x78728bab, 0x10f12673, 0x984e7bee, 0x214f59a2, 0xfb088de7, 0x8b641c20, 0x72a0a379, 0x225fe86a, 0xd98a49f3	
array_end		
		
							AREA emptyspace, DATA, readwrite
time_start					SPACE 400						 	; TO KEEP TIME CALCULATIONS
time_end												
bubble_start				SPACE 400							; TO KEEP SORTED ELEMENTS
bubble_end		
		
; SysTick Settings		
		
SysTick_CTRL        		EQU    	0xE000E010    ;SYST_CSR -> SysTick Control and Status Register
SysTick_RELOAD      		EQU    	0xE000E014    ;SYST_RVR -> SysTick Reload Value Register
SysTick_VAL         		EQU    	0xE000E018    ;SYST_CVR -> SysTick Current Value Register
RELOAD						EQU		0X1963F	  	  ;RELOAD VALUE ACCORDING TO MY CALCULATION
START						EQU		0x7;		  ;THE VALUE TO START THE TIMER
STOP						EQU		2_110		  ;THE VALUE TO STOP THE TIMER
					
;MAIN CODE					
							AREA bubble_sort, CODE, READONLY
							ENTRY
							THUMB
							ALIGN
__main						FUNCTION
							EXPORT		__main

							LDR R0,=bubble_start	; MEMORY ADDRESS FOR SORTED
							LDR R1,=time_start      ; MEMORY ADDRESS FOR ARRAY OF THE EXECUTION TIMES
							PUSH {R1}				; SAVE THE ORIGINAL VALUE OF R1
							LDR R2,=array_start		; TO WATCH MEMORY SCREEN
							LDR R3,=ARRAY_SIZE		; ASSIGN ARRAY SIZE TO R3
							BL Init_SysTick_Timer	; INITIALIZE THE TIMER
							MOVS R4,#2				; i = 2, FOR ITERATION
outer_loop					CMP R4, R3				; IF i > array_size 
							BGT end_prog			; THEN ENDS PROGRAM, ELSE
							BL copy_array			; THEN COPY THE ELEMENTS FROM UNSORTED ARRAY TO BUBBLE SORT ARRAY TO SORT
							BL Save_Start_Time		; RECORD THE START TIME
							BL BubbleSort			; IF i <= array_size THEN RUN BUBBLESORT FUNCTION
							BL Save_Execution_Time  ; CALCULATE AND RECORD THE EXECUTION TIME TO MEMORY
							ADDS R4, R4, #1			; i++
							B  outer_loop

copy_array					PUSH {R4}				; SAVE THE ORIGINAL i VALUE
							MOVS R6, #0				; OFFSET FOR COPYING ARRAY
copy						CMP R4, #0				; IF i <= 0  
							BLE finish_copy			; THEN FINISH THE COPY OPERATION
							LDR R5, [R2, R6]		; R5 = array_start[i]
							STR R5, [R0, R6]		; DO bubble_start[i] = R5  SO THAT bubble_start[i] = array_start[i]
							ADDS R6, #4				; OFFSET += 1
							SUBS R4, #1				; i++
							B copy		
finish_copy					POP {R4}				; SAVE THE ORIGINAL i VALUE
							MOVS R5, #0				; RESET THE REGISTER R5
							MOVS R6, #0				; RESET THE REGISTER R5
							BX LR					; RETURN
							


BubbleSort					PUSH {R3,R2, R0}		; RECORD THE ORIGINAL VALUES OF REGISTERS
							SUBS R5, R4, #1			; NUMBER OF ITERATIONS: size - 1 
first_loop					MOVS R6, R5				; NUMBER OF COMPARISON: size - 1
							
							LDR R0,	=bubble_start	; ASSIGN START ADDRESS OF THE ARRAY TO R0
Second_loop					LDR R3, [R0]			; 1ST NUMBER
							LDR R2, [R0, #4]		; 2ND NUMBER
								
							CMP R3,R2				; COMPARE TWO NUMBERS
							BLO SKIP				; IF R1 < R2, C=0 THEN SKIP
							STR R2, [R0]			; ELSE R1 > R2, C=1 THEN EXCHANGE DATA BETWEEN MEMORY WITH REGISTER CONTENT
							STR R3, [R0,#4]			; EXCHANGE OPERATION
							
SKIP						ADDS R0, R0, #4			; INCREASE THE ADDRESS REGISTER FOR NEXT COMPARISON 
							SUBS R6, #1				; COMPARISON -= 1
							BNE Second_loop			; IF COMPARISON = 0 THEN RETURN AT THE BEGINNING OF SECOND LOOP
							SUBS R5,#1				; ITERATION -=1
							BNE first_loop			; IF ITERATION = 0 THEN RETURN AT THE BEGINNING OF FIRST LOOP
							POP{R3,R2,R0}			; LOAD THE ORIGINAL VALUES TO REGISTERS
							BX LR					; RETURN
							

Init_SysTick_Timer			PUSH	{R3, R2, R7}		;RECORD THE ORIGINAL VALUES OF REGISTERS
							LDR 	R7, =SysTick_CTRL	;LOAD THE ADDRESS OF SYSTICK CONTROL REGISTER
							LDR		R2, =RELOAD			;LOAD THE RELOAD VALUE TO R2
							LDR		R3, =START			;LOAD THE START VALUE TO R3
							STR		R2, [R7, #4]		;SET THE RELOAD VALUE
							STR		R3,	[R7]			;START THE TIMER
							POP 	{R3, R2, R7}		;LOAD THE ORIGINAL VALUES TO REGISTERS
							BX		LR					;RETURN
							
		
Save_Start_Time				PUSH {R7}					;RECORD THE ORIGINAL VALUES OF REGISTER
							LDR R7, =SysTick_CTRL		;LOAD THE ADDRESS OF SYSTICK CONTROL REGISTER
							LDR R5, [R7, #8] 			;SAVE THE TIME AS START TIME
							POP {R7}					;LOAD THE ORIGINAL VALUES TO REGISTER R7
							MOVS R6, R7					;COPY R7 TO R6 TO USE DECIDE IF INTERRUPT OCCUR OR NOT BETWEEN START TIME AND FINISH TIME
							PUSH {R5,R6}				;COMPARING R6 AND R7, IF ANY INTERRUPT OCCUR THEN R6 WILL BE SMALLER THAN R7 BECAUSE R7 INCREASE BY 1
							MOVS R5, #0					;RESET THE REGISTER R5
							BX  LR						;RETURN

Save_Execution_Time			POP {R5, R6}				;LOAD START TIME
							CMP R7, R6					;IF INTERRUPT REALIZED BEFORE
							BGT interrupt				;THEN CALCULATE ACCORDING TO THAT
							PUSH {R7}					;SAVE INTERRUPT COUNTER
							LDR R7, =SysTick_CTRL		;LOAD ADDRESS OF SYSTICK CONTROL REGISTER
							LDR R6, [R7, #8]  			;SAVE CURRENT VALUE AS FINISH TIME					
							POP {R7}					;LOAD THE ORIGNIAL VALUE OF R7			
							SUBS R5, R5, R6				;ELSE CALCULATE EXECUTION TIME: FINISH TIME - START TIME
							B continue					;THEN SKIP THE STEPS BELOW										
interrupt					PUSH {R7}					;SAVE INTERRUPT COUNTER
							LDR R7, =SysTick_CTRL		;LOAD ADDRESS OF SYSTICK CONTROL REGISTER
							LDR R6, [R7, #8]  			;SAVE CURRENT VALUE AS FINISH TIME					
							POP {R7}					;LOAD THE ORIGNIAL VALUE OF R7
							PUSH {R2}					;SAVE THE ORIGINAL VALUE OF R2
							LDR R2,=RELOAD				;LOAD THE RELOAD VALUE TO R2
							SUBS R2, R2, R6				;RELOAD - CURRENT VALUE 
							ADDS R5, R5, R2				;EXECUTION TIME = START TIME + (RELOAD - CURRENT VALUE)
							POP {R2}					;LOAD THE ORIGINAL VALUE OF R2
continue					STR	 R5,[R1]				;EXECUTION_TIME [X] = EXECUTION TIME
							ADDS R1, #4					;X++
							MOVS R6, #0					;RESET THE REGISTER R6
							MOVS R5, #0					;RESET THE REGISTER R6
							
							BX  LR						;RETURN

Stop_SysTick_Timer			PUSH {R7}					;RECORD THE ORIGINAL VALUE OF R7
							LDR R7, =SysTick_CTRL		;LOAD THE ADDRESS OF SYSTICK CONTROL REGISTER
							LDR R5,=STOP				;LOAD THE STOP VALUE TO R5
							STR R5, [R7]				;STOP THE TIMER
							MOVS R5, #0					;RESET THE REGISTER R5
							STR R5, [R7, #4]			;RESET THE SYSTICK RELOAD VALUE
							STR R5, [R7, #8]			;RESET THE SYSTICK CURRENT VALUE
							POP {R7}					;LOAD THE ORIGINAL VALUE OF R7
							BX LR						;RETURN		
							
end_prog					BL Stop_SysTick_Timer		;STOP THE TIMER
							POP{R1}						;LOAD THE ORIGINAL VALUE OF R1, TIME ARRAY
							ENDFUNC						;ENDS FUNCTION
							END							;ENDS PROGRAM
					
