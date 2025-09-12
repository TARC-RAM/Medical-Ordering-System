# Library Management System - Overdue Fee Calculation Fix

## Problem Description

The original library management assembly code had issues in the overdue fee calculation, specifically in the conversion routine that converts the input string in `DAYS_BUF` into a numeric value.

### Issues Fixed

1. **Incorrect termination check**: The original code used a termination check for carriage return (13), which sometimes led to processing extra characters.

2. **Incorrect ADD instruction**: The original code used an incorrect ADD instruction that added from BX instead of the digit value.

3. **Unreliable character processing**: The conversion loop didn't properly handle the exact number of characters to process.

## Solution Implemented

### Key Changes Made

1. **Added TEN constant**: Added `TEN DW 10` in the .DATA segment for use in the multiplication step.

2. **Fixed conversion loop**: 
   - Now uses the count byte from the input buffer (`DAYS_BUF[1]`) to determine exactly how many characters to process
   - Uses a count-based loop instead of termination character checking
   - Correctly accumulates digits using BX as accumulator

3. **Corrected digit processing**:
   - Fixed the ADD instruction to properly add the converted digit value
   - Proper ASCII to numeric conversion using `SUB AL, '0'`

### Fee calculation Logic

The overdue fee is calculated as follows:
- Days beyond 14 are considered overdue
- First 7 days overdue: RM 1 per day
- Subsequent days: RM 2 per day  
- Maximum cap: RM 50

### Test Cases Verified

| Total Days | Overdue Days | Expected Fee | Result |
|------------|--------------|--------------|---------|
| 14 | 0 | RM 0 | ✅ PASS |
| 15 | 1 | RM 1 | ✅ PASS |
| 19 | 5 | RM 5 | ✅ PASS |
| 21 | 7 | RM 7 | ✅ PASS |
| 22 | 8 | RM 9 | ✅ PASS |
| 25 | 11 | RM 15 | ✅ PASS |
| 50 | 36 | RM 50 (capped) | ✅ PASS |

**Key Fix Validation**: Returning a book 5 days after the due date (19 total days) now correctly outputs RM 5 instead of RM 2305.

## Code Structure

The `library_management.asm` file includes:

- **Data Section**: Contains constants, input buffers, and variables
- **MAIN procedure**: Handles user interaction and program flow  
- **CALCULATE_LATE_FEE procedure**: Core logic for string conversion and fee calculation
- **DISPLAY_NUMBER procedure**: Converts numeric results back to displayable format

### Critical Fix in CALCULATE_LATE_FEE

```assembly
; OLD (problematic) approach:
; - Used termination character checking
; - Incorrect ADD instruction

; NEW (fixed) approach:
MOV CL, DAYS_BUF[1]     ; Get actual count of characters entered
LEA SI, DAYS_BUF[2]     ; Point to start of actual digits

CONVERT_LOOP:
    CMP CX, 0           ; Check if we've processed all characters
    JE CONVERSION_DONE  ; If count is 0, we're done
    
    ; Multiply current result by 10
    MOV AX, BX
    MUL TEN             ; Use TEN constant
    MOV BX, AX
    
    ; Convert ASCII digit to numeric and add
    MOV AL, [SI]        ; Get current character
    SUB AL, '0'         ; Convert ASCII to digit
    MOV AH, 0
    ADD BX, AX          ; FIXED: Now correctly adds digit value
    
    INC SI
    DEC CX              ; Use count-based processing
    JMP CONVERT_LOOP
```

This fix ensures reliable conversion of input strings to numeric values and accurate overdue fee calculations.