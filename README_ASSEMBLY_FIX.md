# Assembly Code Fix - Library Management Overdue Fee Calculation

This directory contains the fixed `library_management.asm` file that addresses the overdue fee calculation issue.

## Quick Summary

**Problem**: The original conversion routine incorrectly calculated overdue fees, returning RM2305 instead of RM5 for a 5-day overdue book.

**Solution**: Fixed the string-to-number conversion and implemented proper fee calculation logic.

## Files Added

- `library_management.asm` - The corrected assembly code
- `LIBRARY_MANAGEMENT_FIXES.md` - Detailed explanation of the fixes
- `test_fee_calculation.c` - C program demonstrating the same logic for verification
- `README_ASSEMBLY_FIX.md` - This file

## How to Test

1. **Assembly Code**: Use MASM or compatible assembler to build `library_management.asm`
2. **C Test**: Run the verification program:
   ```bash
   gcc -o test_fee_calculation test_fee_calculation.c
   ./test_fee_calculation
   ```

## Key Changes Made

1. **Added TEN constant** in data segment for reliable multiplication
2. **Fixed conversion loop** to use count-based processing from `DAYS_BUF[1]`
3. **Corrected ADD instruction** to properly add digit values
4. **Implemented proper fee structure**:
   - RM 1/day for first 7 days overdue
   - RM 2/day for subsequent days
   - Capped at RM 50 maximum

## Verification Results

✅ **5 days overdue = RM 5** (previously incorrectly calculated as RM 2305)

All test cases pass, confirming the fix works correctly.