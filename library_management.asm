.MODEL SMALL
.STACK 100H

.DATA
    ; Constant for multiplication in conversion
    TEN         DW 10
    
    ; Input buffer for days (first byte is max length, second is actual count, rest is data)
    DAYS_BUF    DB 4, ?, 4 DUP(?)
    
    ; Messages for user interaction
    PROMPT_MSG  DB 'Enter number of days book is overdue: $'
    RESULT_MSG  DB 'Overdue fee: RM$'
    NEWLINE     DB 13, 10, '$'
    
    ; Variables for calculations
    DAYS_NUM    DW 0
    FEE_AMOUNT  DW 0

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    ; Display prompt
    LEA DX, PROMPT_MSG
    MOV AH, 09H
    INT 21H
    
    ; Get user input
    LEA DX, DAYS_BUF
    MOV AH, 0AH
    INT 21H
    
    ; Convert string to number and calculate fee
    CALL CALCULATE_LATE_FEE
    
    ; Display result
    LEA DX, NEWLINE
    MOV AH, 09H
    INT 21H
    
    LEA DX, RESULT_MSG
    MOV AH, 09H
    INT 21H
    
    ; Convert fee amount to string and display
    MOV AX, FEE_AMOUNT
    CALL DISPLAY_NUMBER
    
    ; Exit program
    MOV AH, 4CH
    INT 21H
MAIN ENDP

CALCULATE_LATE_FEE PROC
    ; Save registers
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    PUSH SI
    
    ; Initialize conversion variables
    MOV BX, 0               ; BX will be our accumulator
    MOV CL, DAYS_BUF[1]     ; Get the actual count of characters entered
    MOV CH, 0               ; Clear upper byte of CX
    LEA SI, DAYS_BUF[2]     ; Point to start of actual digits
    
    ; Convert string to number using count-based loop
CONVERT_LOOP:
    CMP CX, 0               ; Check if we've processed all characters
    JE CONVERSION_DONE      ; If count is 0, we're done
    
    ; Multiply current result by 10
    MOV AX, BX              ; Move current accumulator to AX
    MUL TEN                 ; Multiply by 10
    MOV BX, AX              ; Store result back in BX
    
    ; Convert ASCII digit to numeric and add
    MOV AL, [SI]            ; Get current character
    SUB AL, '0'             ; Convert ASCII to digit
    MOV AH, 0               ; Clear upper byte
    ADD BX, AX              ; Add digit to accumulator (fixed: was incorrectly adding from BX)
    
    ; Move to next character
    INC SI
    DEC CX                  ; Decrement character count
    JMP CONVERT_LOOP
    
CONVERSION_DONE:
    MOV DAYS_NUM, BX        ; Store converted number
    
    ; Calculate overdue fee
    ; Fee structure: RM 1/day for first 7 days overdue, RM 2/day thereafter, capped at RM 50
    ; Days beyond 14 are considered overdue
    
    MOV AX, BX              ; Get number of days
    CMP AX, 14              ; Compare with due date threshold
    JLE NO_FEE              ; If <= 14 days, no fee
    
    SUB AX, 14              ; Calculate overdue days (days beyond 14)
    MOV BX, AX              ; Store overdue days in BX
    
    ; Calculate fee based on tiered structure
    MOV AX, 0               ; Initialize fee accumulator
    
    ; First 7 days overdue: RM 1 per day
    CMP BX, 7
    JLE FIRST_TIER_ONLY
    
    ; More than 7 days overdue
    ADD AX, 7               ; Add RM 7 for first 7 days
    SUB BX, 7               ; Subtract 7 from remaining days
    
    ; Remaining days: RM 2 per day
    MOV DX, BX              ; Remaining days to DX
    SHL DX, 1               ; Multiply by 2 (shift left)
    ADD AX, DX              ; Add to fee
    JMP CHECK_CAP
    
FIRST_TIER_ONLY:
    ; Only first tier applies (1-7 days overdue)
    MOV AX, BX              ; Fee = overdue days * 1
    
CHECK_CAP:
    ; Cap at RM 50
    CMP AX, 50
    JLE STORE_FEE
    MOV AX, 50              ; Cap at RM 50
    
STORE_FEE:
    MOV FEE_AMOUNT, AX
    JMP FEE_DONE
    
NO_FEE:
    MOV FEE_AMOUNT, 0
    
FEE_DONE:
    ; Restore registers
    POP SI
    POP DX
    POP CX
    POP BX
    POP AX
    RET
CALCULATE_LATE_FEE ENDP

DISPLAY_NUMBER PROC
    ; Convert number in AX to string and display
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    
    ; Handle special case of 0
    CMP AX, 0
    JNE NOT_ZERO
    MOV DL, '0'
    MOV AH, 02H
    INT 21H
    JMP DISPLAY_DONE
    
NOT_ZERO:
    MOV BX, 10              ; Divisor
    MOV CX, 0               ; Digit counter
    
DIGIT_LOOP:
    MOV DX, 0               ; Clear remainder
    DIV BX                  ; Divide AX by 10
    PUSH DX                 ; Push remainder (digit) onto stack
    INC CX                  ; Increment digit counter
    CMP AX, 0               ; Check if quotient is 0
    JNE DIGIT_LOOP
    
PRINT_DIGITS:
    POP DX                  ; Get digit from stack
    ADD DL, '0'             ; Convert to ASCII
    MOV AH, 02H             ; Display character
    INT 21H
    LOOP PRINT_DIGITS
    
DISPLAY_DONE:
    POP DX
    POP CX
    POP BX
    POP AX
    RET
DISPLAY_NUMBER ENDP

END MAIN